#pragma once

#include <G4ParticleGun.hh>
#include <G4VUserPrimaryGeneratorAction.hh>



class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* event);

private:
    G4ParticleGun* particle_gun;
};