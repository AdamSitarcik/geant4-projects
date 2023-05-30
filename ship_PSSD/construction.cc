#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
  xWorld = 200 * mm;
  yWorld = 200 * mm;
  zWorld = 400 * mm;

  pssdWidth = 5. * mm;
  pssdLength = 35. * mm;
  pssdThickness = 0.3 * mm;

  geRadius = 35 * mm;
  geSize = 70 * mm;
  geLength = 140 * mm;

  windowThickness = 1 * mm;
  windowRadius = 35 * mm;

  pssdPosition = pssdThickness / 2;
  windowPosition = pssdThickness + 12 * mm + windowThickness / 2;
  gePosition = 5 * mm + windowPosition + geLength / 2;
  vetoPosition = pssdPosition + pssdThickness / 2 + 1 * mm;

  DefineMaterial();
}

MyDetectorConstruction::~MyDetectorConstruction()
{
}

void MyDetectorConstruction::DefineMaterial()
{
  G4NistManager *nist = G4NistManager::Instance();

  vacuum = nist->FindOrBuildMaterial("G4_Galactic");
  silicon = nist->FindOrBuildMaterial("G4_Si");
  germanium = nist->FindOrBuildMaterial("G4_Ge");
  aluminum = nist->FindOrBuildMaterial("G4_Al");
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
  logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
  physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

  solidDetector_PSSD = new G4Box("solidDetector_PSSD", pssdWidth / 2, pssdLength / 2, pssdThickness / 2);
  logicDetector_PSSD = new G4LogicalVolume(solidDetector_PSSD, silicon, "logicDetector_PSSD");
  physDetector_PSSD = new G4PVPlacement(0, G4ThreeVector(0., 0., -pssdPosition), logicDetector_PSSD, "physDetector_PSSD", logicWorld, false, 0, true);

  solidDetector_Veto = new G4Box("solidDetector_Veto", pssdWidth / 2 * 16, pssdLength / 2, pssdThickness / 2);
  logicDetector_Veto = new G4LogicalVolume(solidDetector_Veto, silicon, "logicDetector_Veto");
  physDetector_Veto = new G4PVPlacement(0, G4ThreeVector(0., 0., -vetoPosition), logicDetector_Veto, "physDetector_Veto", logicWorld, false, 0, true);

  solidAlWindow = new G4Tubs("solidAlWindow", 0 * mm, windowRadius, windowThickness / 2., 0., 360 * deg);
  logicAlWindow = new G4LogicalVolume(solidAlWindow, aluminum, "logicAlWindow");
  physAlWindow = new G4PVPlacement(0, G4ThreeVector(0., 0., -windowPosition), logicAlWindow, "physAlWindow", logicWorld, false, 0, true);

  solidDetectorClover = new G4Box("solidDetectorClover", geSize / 2, geSize / 2, geLength / 2.);
  logicDetectorClover = new G4LogicalVolume(solidDetectorClover, germanium, "logicDetector_Ge");
  physDetectorClover = new G4PVPlacement(0, G4ThreeVector(-geSize / 2, geSize / 2, -gePosition), logicDetectorClover, "physDetectorClover", logicWorld, false, 0, true);
  physDetectorClover = new G4PVPlacement(0, G4ThreeVector(geSize / 2, geSize / 2, -gePosition), logicDetectorClover, "physDetectorClover", logicWorld, false, 1, true);
  physDetectorClover = new G4PVPlacement(0, G4ThreeVector(-geSize / 2, -geSize / 2, -gePosition), logicDetectorClover, "physDetectorClover", logicWorld, false, 2, true);
  physDetectorClover = new G4PVPlacement(0, G4ThreeVector(geSize / 2, -geSize / 2, -gePosition), logicDetectorClover, "physDetectorClover", logicWorld, false, 3, true);

  fScoringVolumePSSD = logicDetector_PSSD;
  fScoringVolumeVeto = logicDetector_Veto;
  fScoringVolumeGe = logicDetectorClover;

  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector *sensDet1 = new MySensitiveDetector("SensitiveDetector1");
  MySensitiveDetector *sensDet2 = new MySensitiveDetector("SensitiveDetector2");
  // MySensitiveDetector *sensDet3 = new MySensitiveDetector("SensitiveDetector3");

  logicDetector_PSSD->SetSensitiveDetector(sensDet1);
  logicDetector_Veto->SetSensitiveDetector(sensDet2);
  // logicDetector_Ge->SetSensitiveDetector(sensDet3);
}
