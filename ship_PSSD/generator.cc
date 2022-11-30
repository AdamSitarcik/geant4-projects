#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fElectronParticleGun = new G4ParticleGun(1);

  fMainParticleGun = new G4ParticleGun(1);

  fIonParticleGun = new G4ParticleGun(1);

  fProtonParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fElectronParticleGun;
  delete fMainParticleGun;
  delete fIonParticleGun;
  delete fProtonParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries (G4Event *anEvent)
{
  ionZ = 26;
  ionA = 56;
  G4double ion_kinetic_energy = 70.;

  G4double impDepth = 4.4; // in um

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

  G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(ionZ, ionA, 0.);

  G4ParticleDefinition *electron = particleTable->FindParticle("e-");
  G4ParticleDefinition *alpha = particleTable->FindParticle("alpha");
  G4ParticleDefinition *proton = particleTable->FindParticle("proton");  
  G4ParticleDefinition *gamma = particleTable->FindParticle("gamma");

  G4double dirXel = G4UniformRand()-0.5;
  G4double dirYel = G4UniformRand()-0.5;
  G4double dirZel = G4UniformRand()-0.5;

  G4double dirX = G4UniformRand()-0.5;
  G4double dirY = G4UniformRand()-0.5;
  G4double dirZ = G4UniformRand()-0.5;

  G4double particleEnergy = 20; // in keV

  // Input and calculation of parameters of electrons in case of IC simulations
  G4double convTransitionEnergy = 180;
  G4double elKEnergy = convTransitionEnergy - 85.53;
  G4double elLEnergy = convTransitionEnergy - 15;
  G4double electronEnergy; 
  G4double totalICC = 2.38;
  G4double KL_ratio = 3.95;
  G4double ICConK = totalICC/(KL_ratio+1)*KL_ratio;

  G4ThreeVector posGun(0., 0., -impDepth*um);
  // G4ThreeVector posIonGun(G4RandGauss::shoot(0,0.1)*mm, G4RandGauss::shoot(0,0.1)*mm, ionSourcePosition);

  G4ThreeVector dirElGun(dirXel, dirYel, dirZel);
  // G4ThreeVector dirElGun(0., 0., -1.);

  // G4ThreeVector posProtonGun(G4RandGauss::shoot(0,0.1)*mm, G4RandGauss::shoot(0,0.1)*mm, protonSourcePosition);

  G4ThreeVector dirMainGun(dirX, dirY, dirZ);
  // G4ThreeVector dirIonGun(dirXion, dirYion, dirZion);

  // fIonParticleGun->SetParticlePosition(posIonGun);
  // fIonParticleGun->SetParticleMomentumDirection(dirIonGun);
  // fIonParticleGun->SetParticleDefinition(ion);
  // fIonParticleGun->SetParticleCharge(0.*eplus);
  // fIonParticleGun->SetParticleEnergy(G4RandGauss::shoot(ion_kinetic_energy, 0)*MeV);

  // fProtonParticleGun->SetParticlePosition(posProtonGun);
  // fProtonParticleGun->SetParticleMomentumDirection(dirIonGun);
  // fProtonParticleGun->SetParticleDefinition(proton);
  // fProtonParticleGun->SetParticleEnergy(G4RandGauss::shoot(16,2)*MeV);

  G4int generate_electrons = 0; // 0 - do not generate conversion electrons, 1 - generate CEs
  
  if(generate_electrons == 1){
    fElectronParticleGun->SetParticlePosition(posGun);
    fElectronParticleGun->SetParticleMomentumDirection(dirElGun);
    fElectronParticleGun->SetParticleDefinition(electron);
  }

  if(G4UniformRand()<totalICC/(totalICC+1.))
  {
    if(G4UniformRand()<(1/totalICC*ICConK)){
      electronEnergy = elKEnergy;
    }
    else{
      electronEnergy = elLEnergy;
    }
    fElectronParticleGun->SetParticleEnergy(electronEnergy*keV);
    // fElectronParticleGun->GeneratePrimaryVertex(anEvent);
  }

  fMainParticleGun->SetParticleEnergy(particleEnergy*keV);
  fMainParticleGun->SetParticlePosition(posGun);
  fMainParticleGun->SetParticleMomentumDirection(dirMainGun);
  fMainParticleGun->SetParticleDefinition(gamma);

  fMainParticleGun->GeneratePrimaryVertex(anEvent);
  // fIonParticleGun->GeneratePrimaryVertex(anEvent);
  // fProtonParticleGun->GeneratePrimaryVertex(anEvent);
}
