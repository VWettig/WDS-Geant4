#pragma once

#include <fstream>

#include <G4String.hh>

#include "DetectorHit.hh"



class DataManager {
public:
    DataManager();
    ~DataManager();

    void OpenFile(G4String path);
    void CloseFile();

    void WriteSensorData(G4int run_id, G4int event_id, DetectorHitsCollection* hits);

private:
    std::ofstream file;
};