#include "EventAction.hh"

#include <G4Event.hh>
#include <G4Run.hh>
#include <G4RunManager.hh>



EventAction::EventAction(DataManager* data_manager) : G4UserEventAction(), data_manager(data_manager) {

}

EventAction::~EventAction() {

}



void EventAction::EndOfEventAction(const G4Event* event) {
    G4int run_id = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID();
    G4int event_id = event->GetEventID();
    data_manager->WriteSensorData(run_id, event_id, (DetectorHitsCollection*) event->GetHCofThisEvent()->GetHC(0));
}