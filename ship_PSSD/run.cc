#include "run.hh"

MyRunAction::MyRunAction()
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->CreateNtuple("hits", "hits");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEAl");
  man->FinishNtuple(0);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginRunAction(const G4Run* run)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  G4int runID = run->GetRunID();
  std::stringstream strRunID;
  strRunID << runID;

  man->OpenFile("outputs/output"+strRunID.str()+".root");
}

void MyRunAction::EndRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->Write();
  man->CloseFile();
}
