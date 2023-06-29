#include "ActionInitialization.hh"



ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {
    primary_generator_action = new PrimaryGeneratorAction;
}

ActionInitialization::~ActionInitialization() {
    delete primary_generator_action;
}



void ActionInitialization::Build() const {
    SetUserAction(primary_generator_action);
}