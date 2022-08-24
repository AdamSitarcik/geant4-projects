#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
  projectile_loses_in_target = 0; // 0 - includes TOF, C foils and mylars. 1 - only half of the target and PSSD generated

  xWorld = 200*mm;
  yWorld = 200*mm;
  zWorld = 400*mm;

  pssdWidth = 5*mm;
  pssdLength = 35*mm;
  pssdThickness = 0.3*mm;

  n_tof = 1;
  tofWidth = 7*mm;
  tofLength = 7*mm;
  // tofThickness = 0.15*um;
  tofThickness = 1.5*um;


  n_mylar = 1;
  mylarWidth = 10*mm;
  mylarLength = 10*mm;
  mylarThickness = 0.01*um;

  targetXY = 5*mm;
  // targetThickness = 1.106*um; // SmF3
  targetThickness = 2.066*um; // PrF3

  targetPosition = 50.*mm;
  targetPositionIonLoss = 10.*mm;

  carbonLayerThicknessBehindTarget = 0.18*um;
  carbonLayerThicknessInFrontTarget = 0.045*um;

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
  carbon = nist->FindOrBuildMaterial("G4_C");
  mylar = nist->FindOrBuildMaterial("G4_MYLAR");

  // targetMat = new G4Material("targetMat", 2.7133*g/cm3, 2); // SmF3
  // targetMat->AddElement(nist->FindOrBuildElement("Sm"),1);
  // targetMat->AddElement(nist->FindOrBuildElement("F"),3);

  targetMat = new G4Material("targetMat", 2.5266*g/cm3, 2); // PrF3
  targetMat->AddElement(nist->FindOrBuildElement("Pr"),1);
  targetMat->AddElement(nist->FindOrBuildElement("F"),3);

}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
  logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
  physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

  solidDetector_PSSD = new G4Box("solidDetector_PSSD", pssdWidth/2, pssdLength/2, pssdThickness/2);
  logicDetector_PSSD = new G4LogicalVolume(solidDetector_PSSD, pssdMat, "logicDetector_PSSD");
  physDetector_PSSD = new G4PVPlacement(0, G4ThreeVector(0., 0., -pssdThickness/2), logicDetector_PSSD, "physDetector_PSSD", logicWorld, false, 0, true);

  // if(projectile_loses_in_target == 0)
  // {
    solidTOF = new G4Box("solidTOF", tofWidth/2., tofLength/2., tofThickness/2.);
    logicTOF = new G4LogicalVolume(solidTOF, carbon, "logicTOF");
    for(G4int i = 0; i<n_tof; i++){
      for(G4int j=0; j<1; j++){
        physTOF = new G4PVPlacement(0, G4ThreeVector(0., 0., (15.+8*i+2*j)*mm), logicTOF, "physTOF", logicWorld, false, 0, true);
      }
    }

    solidMylar = new G4Box("solidMylar", mylarWidth/2., mylarLength/2., mylarThickness/2.);
    logicMylar = new G4LogicalVolume(solidMylar, mylar, "logicMylar");
    for(G4int i=0; i<n_mylar; i++){
      // physMylar = new G4PVPlacement(0, G4ThreeVector(0., 0., (5+2*i)*mm), logicMylar, "physMylar", logicWorld, false, 0, true);
    }

    solidTarget = new G4Box("solidTarget", targetXY/2., targetXY/2., targetThickness/2.);
    logicTarget = new G4LogicalVolume(solidTarget, targetMat, "logicTarget");
    // physTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., targetPosition), logicTarget, "physTarget", logicWorld, false, 0, true);

    solidCLayer = new G4Box("solidCLayer", targetXY/2., targetXY/2., carbonLayerThicknessBehindTarget/2.);
    logicCLayer = new G4LogicalVolume(solidCLayer, carbon, "logicCLayer");
    // physCLayer = new G4PVPlacement(0, G4ThreeVector(0., 0., targetPosition-targetThickness/2.-carbonLayerThicknessBehindTarget/2.), logicCLayer, "physCLayer", logicWorld, false, 0, true);
  // }
  // else if(projectile_loses_in_target == 1)
  // {
  //   solidTarget = new G4Box("solidTarget", targetXY/2., targetXY/2., targetThickness/4.);
  //   logicTarget = new G4LogicalVolume(solidTarget, targetMat, "logicTarget");
  //   physTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., targetPositionIonLoss), logicTarget, "physTarget", logicWorld, false, 0, true);

  //   solidCLayer = new G4Box("solidCLayer", targetXY/2., targetXY/2., carbonLayerThicknessInFrontTarget/2.);
  //   logicCLayer = new G4LogicalVolume(solidCLayer, carbon, "logicCLayer");
  //   physCLayer = new G4PVPlacement(0, G4ThreeVector(0., 0., targetPositionIonLoss+targetThickness/2.+carbonLayerThicknessInFrontTarget/2.), logicCLayer, "physCLayer", logicWorld, false, 0, true);
  // }

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
