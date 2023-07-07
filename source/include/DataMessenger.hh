#pragma once

#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithoutParameter.hh>

#include "DataManager.hh"



class DataMessenger : public G4UImessenger {
public:
    DataMessenger(DataManager* data_manager);
    ~DataMessenger();

    void SetNewValue(G4UIcommand* command, G4String value);
    
private:
    DataManager* data_manager;

    G4UIdirectory* dir_data;
    G4UIcmdWithAString* cmd_data_open;
    G4UIcmdWithoutParameter* cmd_data_close;
};