#include "PhysicsList.hh"

#include <G4EmStandardPhysics.hh>



PhysicsList::PhysicsList() : G4VModularPhysicsList() {
    RegisterPhysics(new G4EmStandardPhysics);
}

PhysicsList::~PhysicsList() {

}