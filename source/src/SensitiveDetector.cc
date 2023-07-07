#include "SensitiveDetector.hh"

#include <G4EventManager.hh>
#include <G4Event.hh>
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
    G4int track_id = step->GetTrack()->GetTrackID();

    DetectorHit* hit = new DetectorHit(tube_id, track_id);
    hits->insert(hit);

    if(G4VisManager::GetConcreteInstance())
        hit->Draw();
    
    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hce) {
    G4int event_id = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    G4int hit_count = hce->GetHC(0)->GetSize();
    G4cout << "[" << event_id << "] Number of hits: " << hit_count << G4endl;
}