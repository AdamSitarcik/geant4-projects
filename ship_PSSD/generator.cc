#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fElectronParticleGun = new G4ParticleGun(1);

  fAlphaParticleGun = new G4ParticleGun(1);

  fIonParticleGun = new G4ParticleGun(1);

  fProtonParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fElectronParticleGun;
  delete fAlphaParticleGun;
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

  G4String particleName1 = "e-";
  G4ParticleDefinition *electron = particleTable->FindParticle(particleName1);

  G4String particleName2 = "alpha";
  G4ParticleDefinition *alpha = particleTable->FindParticle(particleName2);

  G4String particleName3 = "proton";
  G4ParticleDefinition *proton = particleTable->FindParticle(particleName3);  

  G4double dirXel = G4UniformRand()-0.5;
  G4double dirYel = G4UniformRand()-0.5;
  G4double dirZel = G4UniformRand()-0.5;

  G4double dirXal = G4UniformRand()-0.5;
  G4double dirYal = G4UniformRand()-0.5;
  G4double dirZal = G4UniformRand()-0.5;

  G4double alphaEnergy = 7155;
  G4double convTransitionEnergy = 180;
  G4double elKEnergy = convTransitionEnergy - 85.53;
  G4double elLEnergy = convTransitionEnergy - 15;
  G4double electronEnergy; 
  G4double totalICC = 2.38;
  G4double KL_ratio = 3.95;
  G4double ICConK = totalICC/(KL_ratio+1)*KL_ratio;

  G4ThreeVector posGun(0., 0., -4.*um);
  G4ThreeVector posIonGun(G4RandGauss::shoot(0,0.1)*mm, G4RandGauss::shoot(0,0.1)*mm, ionSourcePosition);

  G4ThreeVector dirElGun(dirXel, dirYel, dirZel);
  // G4ThreeVector dirElGun(0., 0., -1.);

  G4ThreeVector posProtonGun(G4RandGauss::shoot(0,0.1)*mm, G4RandGauss::shoot(0,0.1)*mm, protonSourcePosition);

  G4ThreeVector dirAlGun(dirXal, dirYal, dirZal);
  // G4ThreeVector dirAlGun(0., 0., -1.);

  G4ThreeVector dirIonGun(dirXion, dirYion, dirZion);

  fIonParticleGun->SetParticlePosition(posIonGun);
  fIonParticleGun->SetParticleMomentumDirection(dirIonGun);
  fIonParticleGun->SetParticleDefinition(ion);
  fIonParticleGun->SetParticleCharge(0.*eplus);
  fIonParticleGun->SetParticleEnergy(G4RandGauss::shoot(ion_kinetic_energy, 0)*MeV);

  fProtonParticleGun->SetParticlePosition(posProtonGun);
  fProtonParticleGun->SetParticleMomentumDirection(dirIonGun);
  fProtonParticleGun->SetParticleDefinition(proton);
  fProtonParticleGun->SetParticleEnergy(G4RandGauss::shoot(16,2)*MeV);

  G4double totalICC = G4RandGauss::shoot(4.28, 0.15);
  G4double ICConK = G4RandGauss::shoot(0.544, 0.05);

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
    fElectronParticleGun->GeneratePrimaryVertex(anEvent);
  }

  fAlphaParticleGun->SetParticleEnergy(alphaEnergy*keV);
  fAlphaParticleGun->SetParticlePosition(posGun);
  fAlphaParticleGun->SetParticleMomentumDirection(dirAlGun);
  fAlphaParticleGun->SetParticleDefinition(alpha);

  // fAlphaParticleGun->GeneratePrimaryVertex(anEvent);
  fIonParticleGun->GeneratePrimaryVertex(anEvent);
  // fProtonParticleGun->GeneratePrimaryVertex(anEvent);
}
