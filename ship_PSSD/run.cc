#include "run.hh"


MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->OpenFile("output.root");
  man->CreateNtuple("hits", "hits");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEAl");
  man->FinishNtuple(0);
}

void MyRunAction::EndRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->Write();
  man->CloseFile("output.root");
}
