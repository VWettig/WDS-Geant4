#include "ActionInitialization.hh"



ActionInitialization::ActionInitialization(DataManager* data_manager) : G4VUserActionInitialization() {
    primary_generator_action = new PrimaryGeneratorAction;

    event_action = new EventAction(data_manager);
}

ActionInitialization::~ActionInitialization() {
    delete event_action;

    delete primary_generator_action;
}



void ActionInitialization::Build() const {
    SetUserAction(primary_generator_action);

    SetUserAction(event_action);
}