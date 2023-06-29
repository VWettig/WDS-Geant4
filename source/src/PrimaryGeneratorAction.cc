#include "PrimaryGeneratorAction.hh"

#include <CLHEP/Units/SystemOfUnits.h>
#include <G4ParticleTable.hh>

using namespace CLHEP;



PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction() {
    particle_gun = new G4ParticleGun(1);

    G4ParticleTable* particle_table = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particle_table->FindParticle("proton");

    particle_gun->SetParticleDefinition(particle);
    particle_gun->SetParticleEnergy(1.0 * GeV);
    particle_gun->SetParticlePosition(G4ThreeVector(0.0, 0.0, -0.9 * m));
    particle_gun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete particle_gun;
}



void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    particle_gun->GeneratePrimaryVertex(event);
}