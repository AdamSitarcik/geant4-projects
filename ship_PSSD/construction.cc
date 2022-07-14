#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *vacuum = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material *detMat1 = nist->FindOrBuildMaterial("G4_Si");
  G4Material *detMat2 = nist->FindOrBuildMaterial("G4_Ge");

  G4Box *solidWorld = new G4Box("solidWorld", 200*mm, 200*mm, 200*mm);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

  G4double detSizeX = 5*mm;
  G4double detSizeY = 35*mm;
  G4double detSizeZ = 0.3*mm;

  G4Box *solidDetector_PSSD = new G4Box("solidDetector_PSSD", detSizeX/2, detSizeY/2, detSizeZ/2);
  logicDetector_PSSD = new G4LogicalVolume(solidDetector_PSSD, detMat1, "logicDetector_PSSD");
  G4VPhysicalVolume *physDetector_PSSD = new G4PVPlacement(0, G4ThreeVector(0., 0., detSizeZ/2), logicDetector_PSSD, "physDetector_PSSD", logicWorld, false, 0, true);

  G4Tubs *solidDetector_Ge = new G4Tubs("solidDetector_Ge", 0*mm, 35*mm, 140*mm/2, 0., 360*deg);
  logicDetector_Ge = new G4LogicalVolume(solidDetector_Ge, detMat2, "logicDetector_Ge");
  G4VPhysicalVolume *physDetector_Ge = new G4PVPlacement(0, G4ThreeVector(0., 0., 72*mm), logicDetector_Ge, "physDetector_Ge", logicWorld, false, 0, true);  

  return physWorld;
}
