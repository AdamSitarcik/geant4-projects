#include "run.hh"

MyEventAction::MyEventAction()
{
  fEdep = 0.;
  fEVeto = 0.;
  for (G4int i = 0; i < 4; i++)
  {
    fEGa[i] = 0.;
  }
}

MyEventAction::~MyEventAction()
{
}

void MyEventAction::BeginOfEventAction(const G4Event *)
{
  fEdep = 0.;
  fEVeto = 0.;
  for (G4int i = 0; i < 4; i++)
  {
    fEGa[i] = 0.;
  }
}

void MyEventAction::EndOfEventAction(const G4Event *)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  // fEdep = G4RandGauss::shoot(fEdep, 0.017); // Defining the resolution of the PSSD
  fEdep = fEdep * 1000; // Convert energy from MeV to keV
  for (G4int i = 0; i < 4; i++)
  {
    fEGa[i] = fEGa[i] * 1000;
    fEGa[i] = G4RandGauss::shoot(fEGa[i], 1.07); // Defining the resolution of the Ge detectpr
  }
  // fEVeto = G4RandGauss::shoot(fEVeto,0.025); // Defining the resolution of the VETO

  man->FillNtupleDColumn(4, fEdep);
  man->FillNtupleDColumn(5, fEVeto);
  // man->FillNtupleDColumn(6, fEGa);
  man->AddNtupleRow(0);
}
