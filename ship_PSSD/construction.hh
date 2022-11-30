#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Colour.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  MyDetectorConstruction();
  ~MyDetectorConstruction();

  virtual G4VPhysicalVolume *Construct();

  // G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}

  virtual void ConstructSDandField();

private:
  G4Material *vacuum, *silicon, *germanium, *carbon, *mylar, *targetMat;
  G4Box *solidWorld, *solidDetector_PSSD, *solidDetector_Veto, *solidTOF, *solidMylar, *solidTarget, *solidCLayer;
  G4Tubs *solidDetector_Ge;
  G4LogicalVolume *logicWorld, *logicDetector_PSSD, *logicDetector_Ge, *logicDetector_Veto, *logicTOF, *logicMylar, *logicTarget, *logicCLayer;
  G4VPhysicalVolume *physWorld, *physDetector_PSSD, *physDetector_Ge, *physDetector_Veto, *physTOF, *physMylar, *physTarget, *physCLayer;

  G4double pssdWidth, pssdLength, pssdThickness, xWorld, yWorld, zWorld, tofWidth, tofLength, tofThickness, mylarWidth, mylarLength, mylarThickness, targetXY, targetThickness, carbonLayerThicknessBehindTarget, carbonLayerThicknessInFrontTarget, targetPosition, targetPositionIonLoss;
  G4int projectile_loses_in_target, n_tof, n_mylar;

  void DefineMaterial();

  G4LogicalVolume *fScoringVolumePSSD, *fScoringVolumeVeto;
};
#endif
