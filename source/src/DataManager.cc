#include "DataManager.hh"

#include <G4ios.hh>



DataManager::DataManager() {

}

DataManager::~DataManager() {

}



void DataManager::OpenFile(G4String path) {
    if(file.is_open()) {
        G4cout << "Failed to open file: A file is already open" << G4endl;
        return;
    }

    file.open(path);

    if(!file.is_open()) {
        G4cout << "Failed to open file" << G4endl;
        return;
    }
}

void DataManager::CloseFile() {
    if(!file.is_open()) {
        G4cout << "No file is currently open" << G4endl;
        return;
    }

    file.close();
}



void DataManager::WriteSensorData(G4int run_id, G4int event_id, DetectorHitsCollection* hits) {
    if(!file.is_open()) {
        return;
    }
    
    G4int hit_count = hits->GetSize();
    for(G4int i = 0; i < hit_count; i++) {
        DetectorHit* hit = (DetectorHit*) hits->GetHit(i);

        file << run_id << "," << event_id << "," << hit->GetTubeID() << "," << hit->GetTrackID() << std::endl;
    }
}