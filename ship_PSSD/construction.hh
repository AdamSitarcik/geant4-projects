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
  G4Material *vacuum, *silicon, *germanium, *aluminum;
  G4Box *solidWorld, *solidDetector_PSSD, *solidDetector_Veto, *solidDetectorClover;
  G4Tubs *solidDetector_Ge, *solidAlWindow;
  G4LogicalVolume *logicWorld, *logicDetector_PSSD, *logicDetector_Ge, *logicDetectorClover, *logicDetector_Veto, *logicAlWindow;
  G4VPhysicalVolume *physWorld, *physDetector_PSSD, *physDetector_Ge, *physDetectorClover, *physDetector_Veto, *physAlWindow;

  G4double pssdWidth, pssdLength, pssdThickness, xWorld, yWorld, zWorld, geSize, geRadius, geLength, windowThickness, windowRadius;
  G4double pssdPosition, windowPosition, gePosition, vetoPosition;

  void DefineMaterial();

  G4LogicalVolume *fScoringVolumePSSD, *fScoringVolumeVeto, *fScoringVolumeGe;
};
#endif
