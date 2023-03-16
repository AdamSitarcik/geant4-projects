#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
  // RegisterPhysics (new G4EmStandardPhysics());
  // RegisterPhysics (new G4EmPenelopePhysics());
  // RegisterPhysics (new G4EmLowEPPhysics());
  RegisterPhysics (new G4EmLivermorePhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
