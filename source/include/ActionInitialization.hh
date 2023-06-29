#pragma once

#include <G4VUserActionInitialization.hh>

#include "PrimaryGeneratorAction.hh"



class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    ~ActionInitialization();

    void Build() const;

private:
    PrimaryGeneratorAction* primary_generator_action;
};