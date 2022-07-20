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

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  MyDetectorConstruction();
  ~MyDetectorConstruction();

  virtual G4VPhysicalVolume *Construct();

private:
  G4Material *vacuum, *detMat1, *detMat2;
  G4Box *solidWorld, *solidDetector_PSSD;
  G4Tubs *solidDetector_Ge;
  G4LogicalVolume *logicWorld, *logicDetector_PSSD, *logicDetector_Ge;
  G4VPhysicalVolume *physWorld, *physDetector_PSSD, *physDetector_Ge;

  G4double pssdWidth, pssdLength, pssdThickness, xWorld, yWorld, zWorld;

  void DefineMaterial();

};
#endif
