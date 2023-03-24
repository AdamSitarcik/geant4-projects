#include "event.hh"

MyEventAction::MyEventAction(MyRunAction *)
{
  fEdep = 0.;
  fEVeto = 0.;
  fEGa = 0.;
}

MyEventAction::~MyEventAction()
{
}

void MyEventAction::BeginOfEventAction(const G4Event *)
{
  fEdep = 0.;
  fEVeto = 0.;
  fEGa = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event *)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  fEdep = G4RandGauss::shoot(fEdep, 0.017); // Defining the resolution of the PSSD
  fEGa = G4RandGauss::shoot(fEGa, 0.0005); // Defining the resolution of the Ge detectpr
  fEdep = fEdep * 1000;                     // Convert energy from MeV to keV
  fEGa = fEGa * 1000;
  // fEVeto = G4RandGauss::shoot(fEVeto,0.025); // Defining the resolution of the VETO

  man->FillNtupleDColumn(4, fEdep);
  man->FillNtupleDColumn(5, fEVeto);
  man->FillNtupleDColumn(6, fEGa);
  man->AddNtupleRow(0);
}
