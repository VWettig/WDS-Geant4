#include "DetectorConstruction.hh"

#include <CLHEP/Units/SystemOfUnits.h>
#include <G4Box.hh>
#include <G4FieldManager.hh>
#include <G4LogicalVolume.hh>
#include <G4MaterialPropertiesTable.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4RotationMatrix.hh>
#include <G4SDManager.hh>
#include <G4Tubs.hh>
#include <G4UniformMagField.hh>
#include <G4VisAttributes.hh>
#include <G4VPhysicalVolume.hh>

#include "SensitiveDetector.hh"

using namespace CLHEP;



constexpr G4double DETECTOR_WIDTH = 1.0 * m;
constexpr G4double DETECTOR_HEIGHT = 0.6 * m;
constexpr G4double DETECTOR_LENGTH = 1.2 * m;

constexpr G4double DETECTOR_PLATE_THICKNESS = 5.0 * mm;

constexpr G4int DETECTOR_TUBE_COUNT_X = 11;
constexpr G4int DETECTOR_TUBE_COUNT_Z = 11;
constexpr G4double DETECTOR_TUBE_SIDE_OFFSET = 10.0 * mm;
constexpr G4double DETECTOR_TUBE_THICKNESS = 1.0 * mm;
constexpr G4double DETECTOR_TUBE_RADIUS = 10.0 * mm;



constexpr G4double DETECTOR_TUBE_DELTA_X = (DETECTOR_WIDTH - 2.0 * DETECTOR_TUBE_SIDE_OFFSET) / (DETECTOR_TUBE_COUNT_X - 1);
constexpr G4double DETECTOR_TUBE_DELTA_Z = (DETECTOR_LENGTH - 2.0 * DETECTOR_TUBE_SIDE_OFFSET) / (DETECTOR_TUBE_COUNT_Z - 1);



DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {
    CreateMaterials();
}

DetectorConstruction::~DetectorConstruction() {

}



void DetectorConstruction::CreateMaterials() {
    G4NistManager* nist = G4NistManager::Instance();

    material_air = nist->FindOrBuildMaterial("G4_AIR");
}



G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4Box* world_solid = new G4Box("World", 1.0 * m, 1.0 * m, 1.0 * m);
    G4LogicalVolume* world_logical = new G4LogicalVolume(world_solid, material_air, "World");
    //world_logical->SetVisAttributes(G4VisAttributes(false));
    G4VPhysicalVolume* world_physical = new G4PVPlacement(nullptr, G4ThreeVector(0.0 * mm, 0.0 * mm, 0.0 * mm), world_logical, "World", nullptr, false, 0);

    BuildDetector(world_physical);

    return world_physical;
}

void DetectorConstruction::ConstructSDandField() {
    SensitiveDetector* detector_sensitive = new SensitiveDetector("Detector");
    for(G4LogicalVolume* volume : sensitive_volumes)
        volume->SetSensitiveDetector(detector_sensitive);
    G4SDManager::GetSDMpointer()->AddNewDetector(detector_sensitive);
}



void DetectorConstruction::BuildDetector(G4VPhysicalVolume* parent) {
    G4Box* detector_solid = new G4Box("Detector", 0.5 * DETECTOR_WIDTH, 0.5 * DETECTOR_HEIGHT, 0.5 * DETECTOR_LENGTH);
    G4LogicalVolume* detector_logical = new G4LogicalVolume(detector_solid, material_air, "Detector");
    detector_logical->SetVisAttributes(G4VisAttributes(false));
    G4MagneticField* detector_field = new G4UniformMagField(G4ThreeVector(0.0, 2.0 * tesla, 0.0));
    G4FieldManager* detector_field_manager = new G4FieldManager;
    detector_field_manager->SetDetectorField(detector_field);
    detector_field_manager->CreateChordFinder(detector_field);
    detector_logical->SetFieldManager(detector_field_manager, true);
    G4VPhysicalVolume* detector_physical = new G4PVPlacement(nullptr, G4ThreeVector(0.0 * mm, 0.0 * mm, 0.0 * mm), "Detector", detector_logical, parent, false, 0);

    G4Box* detector_plate_solid = new G4Box("Plate", 0.5 * DETECTOR_WIDTH, 0.5 * DETECTOR_PLATE_THICKNESS, 0.5 * DETECTOR_LENGTH);
    G4LogicalVolume* detector_plate_logical = new G4LogicalVolume(detector_plate_solid, material_air, "Plate");
    new G4PVPlacement(nullptr, G4ThreeVector(0.0 * mm, 0.5 * (DETECTOR_PLATE_THICKNESS + DETECTOR_HEIGHT), 0.0 * mm), "Plate", detector_plate_logical, detector_physical, false, 0);
    new G4PVPlacement(nullptr, G4ThreeVector(0.0 * mm, -0.5 * (DETECTOR_PLATE_THICKNESS + DETECTOR_HEIGHT), 0.0 * mm), "Plate", detector_plate_logical, detector_physical, false, 1);

    G4Tubs* detector_tube_solid = new G4Tubs("Tube", DETECTOR_TUBE_RADIUS - DETECTOR_TUBE_THICKNESS, DETECTOR_TUBE_RADIUS, 0.5 * DETECTOR_HEIGHT, 0.0 * deg, 360.0 * deg);
    G4LogicalVolume* detector_tube_logical = new G4LogicalVolume(detector_tube_solid, material_air, "Tube");
    sensitive_volumes.push_back(detector_tube_logical);
    G4RotationMatrix* detector_tube_rotation = new G4RotationMatrix;
    detector_tube_rotation->rotateX(90.0 * deg);
    for(G4int gz = 0; gz < DETECTOR_TUBE_COUNT_Z; gz++) {
        for(G4int gx = 0; gx < DETECTOR_TUBE_COUNT_X; gx++) {
            G4int tube_id = (gz * DETECTOR_TUBE_COUNT_X + gx) << 1;
            G4double px = DETECTOR_TUBE_SIDE_OFFSET + gx * DETECTOR_TUBE_DELTA_X - 0.5 * DETECTOR_WIDTH;
            G4double pz = DETECTOR_TUBE_SIDE_OFFSET + gz * DETECTOR_TUBE_DELTA_Z - 0.5 * DETECTOR_LENGTH;
            new G4PVPlacement(detector_tube_rotation, G4ThreeVector(px, 0.0 * mm, pz), "Tube", detector_tube_logical, detector_physical, false, tube_id);
            
            if(gx >= DETECTOR_TUBE_COUNT_X - 1 || gz >= DETECTOR_TUBE_COUNT_Z - 1)
                continue;
            
            tube_id = ((gz * (DETECTOR_TUBE_COUNT_X - 1) + gx) << 1) | 0b1;
            px = px + 0.5 * DETECTOR_TUBE_DELTA_X;
            pz = pz + 0.5 * DETECTOR_TUBE_DELTA_Z;
            new G4PVPlacement(detector_tube_rotation, G4ThreeVector(px, 0.0 * mm, pz), "Tube", detector_tube_logical, detector_physical, false, tube_id);
        }
    }
}