#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
  RegisterPhysics (new G4EmStandardPhysics());
  // RegisterPhysics (new G4EmPenelopePhysics());
  // RegisterPhysics (new G4EmLowEPPhysics());
  RegisterPhysics (new G4EmLivermorePhysics());
  RegisterPhysics (new G4DecayPhysics());
  RegisterPhysics (new G4RadioactiveDecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{
}
