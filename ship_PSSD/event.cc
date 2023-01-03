#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
  fEdep = 0.;
  fEVeto = 0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
  fEVeto = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  fEdep = G4RandGauss::shoot(fEdep,0.018)*1000; // Defining the resolution of the PSSD
  // fEVeto = G4RandGauss::shoot(fEVeto,0.025); // Defining the resolution of the VETO

  man->FillNtupleDColumn(4,fEdep);
  man->FillNtupleDColumn(5,fEVeto);
  man->AddNtupleRow(0);
}
