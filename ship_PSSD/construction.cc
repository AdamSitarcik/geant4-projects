#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
  xWorld = 200*mm;
  yWorld = 200*mm;
  zWorld = 400*mm;

  pssdWidth = 5*mm;
  pssdLength = 35*mm;
  pssdThickness = 0.3*mm;

  tofWidth = 7*mm;
  tofLength = 7*mm;
  tofThickness = 0.15*um;

  DefineMaterial();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterial()
{
  G4NistManager *nist = G4NistManager::Instance();

  vacuum = nist->FindOrBuildMaterial("G4_Galactic");
  pssdMat = nist->FindOrBuildMaterial("G4_Si");
  detMat2 = nist->FindOrBuildMaterial("G4_Ge");
  tofMat = nist->FindOrBuildMaterial("G4_C");
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
  logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
  physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

  solidDetector_PSSD = new G4Box("solidDetector_PSSD", pssdWidth/2, pssdLength/2, pssdThickness/2);
  logicDetector_PSSD = new G4LogicalVolume(solidDetector_PSSD, pssdMat, "logicDetector_PSSD");
  physDetector_PSSD = new G4PVPlacement(0, G4ThreeVector(0., 0., -pssdThickness/2), logicDetector_PSSD, "physDetector_PSSD", logicWorld, false, 0, true);

  solidTOF = new G4Box("solidTOF", tofWidth/2., tofLength/2., tofThickness/2.);
  logicTOF = new G4LogicalVolume(solidTOF, tofMat, "logicTOF");
  for(G4int i = 0; i<6; i++){
    physTOF = new G4PVPlacement(0, G4ThreeVector(0., 0., (5.+5*i)*mm), logicTOF, "physTOF", logicWorld, false, i, true);

  }

  // solidDetector_Ge = new G4Tubs("solidDetector_Ge", 0*mm, 35*mm, 140*mm/2, 0., 360*deg);
  // logicDetector_Ge = new G4LogicalVolume(solidDetector_Ge, detMat2, "logicDetector_Ge");
  // G4VPhysicalVolume *physDetector_Ge = new G4PVPlacement(0, G4ThreeVector(0., 0., -72*mm), logicDetector_Ge, "physDetector_Ge", logicWorld, false, 0, true);

  fScoringVolume = logicDetector_PSSD;

  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

  logicDetector_PSSD->SetSensitiveDetector(sensDet);
}
