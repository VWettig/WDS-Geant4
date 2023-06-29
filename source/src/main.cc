#include <globals.hh>
#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"



int main(int argc, char** argv) {
    G4RunManager* run_manager = new G4RunManager;
    run_manager->SetUserInitialization(new DetectorConstruction);
    run_manager->SetUserInitialization(new PhysicsList);
    run_manager->SetUserInitialization(new ActionInitialization);
    run_manager->Initialize();

    G4UImanager* ui_manager = G4UImanager::GetUIpointer();
    
    if(argc == 1) {
        G4VisManager* vis_manager = new G4VisExecutive;
        vis_manager->Initialise();

        G4UIExecutive* ui_executive = new G4UIExecutive(argc, argv);

        ui_manager->ExecuteMacroFile("macros/init_vis.mac");
        ui_executive->SessionStart();

        delete ui_executive;
        delete vis_manager;
    } else {
        G4String command = "/control/execute ";
        G4String file_name(argv[1]);
        ui_manager->ApplyCommand(command + file_name);
    }

    delete run_manager;
    return 0;
}