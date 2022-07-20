#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	nCols = 20;
	nRows = 20;
	xWorld = 0.5*m;
	yWorld = 0.5*m;
	zWorld = 0.5*m;

	xRadiator = 0.4*m;
	yRadiator = 0.4*m;
	zRadiator = 0.01*m;

	zDetector = 1*cm;

	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

	fMessenger->DeclareProperty("nCols", nCols, "Number of columns");
	fMessenger->DeclareProperty("nRows", nRows, "Number of rows");

	DefineMaterial();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterial()
{
	G4NistManager *nist = G4NistManager::Instance();

	worldMat = nist->FindOrBuildMaterial("G4_AIR");
	shapeMat = nist->FindOrBuildMaterial("G4_WATER");
	detMat = nist->FindOrBuildMaterial("G4_Ar");

	SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
	SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
	SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

	H2O = new G4Material("H2O", 1.*g/cm3, 2);
	H2O->AddElement(nist->FindOrBuildElement("H"),2);
	H2O->AddElement(nist->FindOrBuildElement("O"),1);

	C = nist->FindOrBuildElement("C");

	Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(H2O, 37.4*perCent);
	Aerogel->AddElement(C, 0.1*perCent);

	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexAerogel[2] = {1.1, 1.1};
	G4double rindexShape[2]={25., 25.};
	G4double rindexWorld[2] = {1., 1.};

	mptAerogel = new G4MaterialPropertiesTable();
	mptShape = new G4MaterialPropertiesTable();
	mptWorld = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
	mptShape->AddProperty("RINDEX", energy, rindexShape, 2);
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

	Aerogel->SetMaterialPropertiesTable(mptAerogel);
	shapeMat->SetMaterialPropertiesTable(mptShape);
	worldMat->SetMaterialPropertiesTable(mptWorld);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
	logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

	solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
	logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
	physRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.1*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);


	solidDetector = new G4Box("solidDetector", xWorld/nRows, yWorld/nCols, zDetector);
	logicDetector = new G4LogicalVolume(solidDetector, detMat, "logicalDetector");
	for(G4int i=0; i<nRows; i++){
		for(G4int j=0; j<nCols;j++){
			physDetector = new G4PVPlacement(0, G4ThreeVector(-xWorld+(i*m+xWorld)/nRows, -yWorld+(j*m+yWorld)/nCols, zWorld-zRadiator), logicDetector, "physDetector", logicWorld, false, j+i*nCols, true);
		}
	}
	fScoringVolume = logicDetector;


	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicDetector->SetSensitiveDetector(sensDet);
}
