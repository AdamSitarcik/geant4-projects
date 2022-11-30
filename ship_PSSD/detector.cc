#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  G4Track *track = aStep->GetTrack();

  // track->SetTrackStatus(fStopAndKill);

  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

  G4ThreeVector startPos = preStepPoint->GetPosition();
  G4ThreeVector endPos = postStepPoint->GetPosition();

  const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

  G4VPhysicalVolume *physVol = touchable->GetVolume();
  G4ThreeVector posDet = physVol->GetTranslation();

  G4int evtID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->FillNtupleIColumn(0, evtID);
  man->FillNtupleDColumn(1, endPos[0]);
  man->FillNtupleDColumn(2, endPos[1]);
  man->FillNtupleDColumn(3, endPos[2]);
  man->AddNtupleRow(0);

  return true;
}
