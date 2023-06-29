#pragma once

#include <vector>

#include <globals.hh>
#include <G4Material.hh>
#include <G4VUserDetectorConstruction.hh>



class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    ~DetectorConstruction();

    void CreateMaterials();

    G4VPhysicalVolume* Construct();
    void ConstructSDandField();

private:
    void BuildDetector(G4VPhysicalVolume* parent);

private:
    G4Material* material_air;

    std::vector<G4LogicalVolume*> sensitive_volumes;
};