#include <iostream>

#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"


int main(int argc, char** argv){
  G4RunManager *runManager = new G4RunManager;
  runManager->SetUserInitialization(new MyDetectorConstruction());
  runManager->SetUserInitialization(new MyPhysicsList());
  runManager->SetUserInitialization(new MyActionInitialization());

  runManager->Initialize();

  G4UIExecutive *ui = new G4UIExecutive(argc, argv);

  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  UImanager->ApplyCommand("/vis/open OGL");
  UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 2");
  UImanager->ApplyCommand("/vis/drawVolume");
  UImanager->ApplyCommand("/vis/viewer/set/autorefresh true");
  UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
  UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
  UImanager->ApplyCommand("/vis/viewer/set/background 1 1 1 1");
  UImanager->ApplyCommand("/vis/viewer/set/defaultColour 0 0 0 1");
  UImanager->ApplyCommand("/vis/viewer/set/globalLineWidthScale 2");
  // UImanager->ApplyCommand("");
  // UImanager->ApplyCommand("");
  // UImanager->ApplyCommand("");
  ui->SessionStart();

  return 0;
}
