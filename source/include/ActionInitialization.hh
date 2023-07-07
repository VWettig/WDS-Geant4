#pragma once

#include <G4VUserActionInitialization.hh>

#include "DataManager.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"



class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization(DataManager* data_manager);
    ~ActionInitialization();

    void Build() const;

private:
    PrimaryGeneratorAction* primary_generator_action;

    EventAction* event_action;
};