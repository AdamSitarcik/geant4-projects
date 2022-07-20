#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4GenericMessenger.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		MyDetectorConstruction();
		~MyDetectorConstruction();

		virtual G4VPhysicalVolume *Construct();

		G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
	private:
		virtual void ConstructSDandField();

		G4int nCols, nRows;

		G4Box *solidWorld, *solidRadiator, *solidDetector;
		G4LogicalVolume *logicWorld, *logicRadiator, *logicDetector;
		G4VPhysicalVolume *physWorld, *physRadiator, *physDetector;
		G4Material *worldMat, *shapeMat, *detMat, *SiO2, *H2O, *Aerogel;
		G4MaterialPropertiesTable *mptAerogel, *mptShape, *mptWorld;
		G4Element *C;

		G4double xWorld, yWorld, zWorld, xRadiator, yRadiator, zRadiator, zDetector;

		G4GenericMessenger *fMessenger;

		void DefineMaterial();

		G4LogicalVolume *fScoringVolume;
};
#endif
