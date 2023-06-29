#include "SensitiveDetector.hh"

#include <G4VisManager.hh>



SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name) {
    collectionName.insert("DetectorHitsCollection");
}

SensitiveDetector::~SensitiveDetector() {

}



void SensitiveDetector::Initialize(G4HCofThisEvent* hce) {
    hits = new DetectorHitsCollection(SensitiveDetectorName, collectionName[0]);
    hce->AddHitsCollection(GetCollectionID(0), hits);
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* hist) {
    (void) hist;

    G4int tube_id = step->GetPreStepPoint()->GetTouchable()->GetCopyNumber();

    DetectorHit* hit = new DetectorHit(tube_id);
    hits->insert(hit);

    if(G4VisManager::GetConcreteInstance())
        hit->Draw();
    
    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hce) {
    G4cout << "Number of hits: " << hce->GetHC(0)->GetSize() << G4endl;
    for(size_t i = 0; i < hce->GetHC(0)->GetSize(); i++) {
        DetectorHit* hit = (DetectorHit*) hce->GetHC(0)->GetHit(i);
        G4cout << "    " << hit->GetTubeID() << G4endl;
    }
}