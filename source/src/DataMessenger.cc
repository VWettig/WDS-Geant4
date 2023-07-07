#include "DataMessenger.hh"

#include <G4UIdirectory.hh>



DataMessenger::DataMessenger(DataManager* data_manager) : G4UImessenger(), data_manager(data_manager) {
    dir_data = new G4UIdirectory("/data");

    cmd_data_open = new G4UIcmdWithAString("/data/open", this);
    cmd_data_open->SetParameterName("path", false);

    cmd_data_close = new G4UIcmdWithoutParameter("/data/close", this);
}

DataMessenger::~DataMessenger() {
    delete cmd_data_close;
    delete cmd_data_open;
    delete dir_data;
}



void DataMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if(command == cmd_data_open) {
        data_manager->OpenFile(value);
        return;
    }

    if(command == cmd_data_close) {
        data_manager->CloseFile();
        return;
    }
}