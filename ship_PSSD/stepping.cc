#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction)
{
  fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  // G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();

  // if(volume != fScoringVolume)
  //   return;

  if (volume->GetName() == "logicDetector_PSSD") {
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);
  }
  else if (volume->GetName() == "logicDetector_Veto") {
    G4double eveto = step->GetTotalEnergyDeposit();
    fEventAction->AddEVeto(eveto);
  }
  else if (volume->GetName() == "logicDetector_Ge"){
    G4double egamma = step->GetTotalEnergyDeposit();
    fEventAction->AddEGamma(egamma);
  }

}
