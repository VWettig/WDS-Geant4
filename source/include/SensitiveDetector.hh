#pragma once

#include <G4VSensitiveDetector.hh>

#include "DetectorHit.hh"



class SensitiveDetector : public G4VSensitiveDetector {
public:
    SensitiveDetector(G4String name);
    ~SensitiveDetector();

    void Initialize(G4HCofThisEvent* hce);
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* hist);
    void EndOfEvent(G4HCofThisEvent* hce);

private:
    DetectorHitsCollection* hits;
};