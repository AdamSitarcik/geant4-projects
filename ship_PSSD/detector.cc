#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  G4Track *track = aStep->GetTrack();

  track->SetTrackStatus(fStopAndKill);

  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

  G4ThreeVector startPos = preStepPoint->GetPosition();
  G4ThreeVector endPos = postStepPoint->GetPosition();

  G4ThreeVector momEvent = preStepPoint->GetMomentum();
  G4double absMomEvent = momEvent.mag();

  G4cout << "absolute momentum: " << absMomEvent << G4endl;

  const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

  G4int copyNo = touchable->GetCopyNumber();

  G4cout << "copy number: " << copyNo << G4endl;

  G4VPhysicalVolume *physVol = touchable->GetVolume();
  G4ThreeVector posDet = physVol->GetTranslation();

  G4cout << "pos det: " << posDet << G4endl;

  G4int evtID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->FillNtupleIColumn(0, 0, evtID);
  man->FillNtupleDColumn(0, 1, absMomEvent);
  man->AddNtupleRow(0);

  return true;
}
