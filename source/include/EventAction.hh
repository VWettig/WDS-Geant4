#pragma once

#include <G4UserEventAction.hh>

#include "DataManager.hh"



class EventAction : public G4UserEventAction {
public:
    EventAction(DataManager* data_manager);
    ~EventAction();

    void EndOfEventAction(const G4Event* event);

private:
    DataManager* data_manager;
};