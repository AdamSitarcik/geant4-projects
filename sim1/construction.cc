#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4Material *shapeMat = nist->FindOrBuildMaterial("G4_Pb");

	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

	G4Box *solidShape1 = new G4Box("shape1", 0.2*m, 0.2*m, 0.2*m);

	G4LogicalVolume *logicShape1 = new G4LogicalVolume(solidShape1, shapeMat, "logicShape1");

	//G4VPhysicalVolume *physShape1 = new G4PVPlacement(0, G4ThreeVector(0.1, 0.1, 0.1), logicShape1, "Shape1",logicWorld, false, 0, true);
	new G4PVPlacement(0, G4ThreeVector(0.1, 0.1, 0.1), logicShape1, "Shape1",logicWorld, false, 0, true);

	return physWorld;
}

