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
  geLength = 140 * mm;

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
  carbon = nist->FindOrBuildMaterial("G4_C");
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
  logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
  physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

  solidDetector_PSSD = new G4Box("solidDetector_PSSD", pssdWidth / 2, pssdLength / 2, pssdThickness / 2);
  logicDetector_PSSD = new G4LogicalVolume(solidDetector_PSSD, silicon, "logicDetector_PSSD");
  physDetector_PSSD = new G4PVPlacement(0, G4ThreeVector(0., 0., -pssdThickness / 2), logicDetector_PSSD, "physDetector_PSSD", logicWorld, false, 0, true);


  solidDetector_Veto = new G4Box("solidDetector_Veto", pssdWidth / 2 * 16, pssdLength / 2, pssdThickness / 2);
  logicDetector_Veto = new G4LogicalVolume(solidDetector_Veto, silicon, "logicDetector_Veto");
  // physDetector_Veto = new G4PVPlacement(0, G4ThreeVector(0., 0., -pssdThickness/2 - 5*mm), logicDetector_Veto, "physDetector_Veto", logicWorld, false, 0, true);

  solidDetector_Ge = new G4Tubs("solidDetector_Ge", 0 * mm, geRadius, geLength / 2., 0., 360 * deg);
  logicDetector_Ge = new G4LogicalVolume(solidDetector_Ge, germanium, "logicDetector_Ge");
  physDetector_Ge = new G4PVPlacement(0, G4ThreeVector(0., 0., -pssdThickness - geLength / 2.0 - 5 * mm), logicDetector_Ge, "physDetector_Ge", logicWorld, false, 0, true);

  fScoringVolumePSSD = logicDetector_PSSD;
  fScoringVolumeVeto = logicDetector_Veto;
  fScoringVolumeGe = logicDetector_Ge;

  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector *sensDet1 = new MySensitiveDetector("SensitiveDetector1");
  MySensitiveDetector *sensDet2 = new MySensitiveDetector("SensitiveDetector2");
  MySensitiveDetector *sensDet3 = new MySensitiveDetector("SensitiveDetector3");

  logicDetector_PSSD->SetSensitiveDetector(sensDet1);
  logicDetector_Veto->SetSensitiveDetector(sensDet2);
  logicDetector_Ge->SetSensitiveDetector(sensDet3);
}
