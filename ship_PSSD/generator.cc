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
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

  ionZ = 23;
  ionA = 51;
  G4double ion_kinetic_energy = 235;

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

  G4double dirXion = G4RandGauss::shoot(0,0.01);
  G4double dirYion = G4RandGauss::shoot(0,0.01);
  G4double dirZion = -1;

  G4double ionSourcePosition = 55.*mm;

  G4double protonSourcePosition = 4.*mm;

  G4double alphaEnergy = G4RandGauss::shoot(7155,12);

  G4ThreeVector posGun(0., 0., -G4RandGauss::shoot(4.3,0.1)*um);
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

    if(G4UniformRand()<totalICC/(totalICC+1.))
    {
      if(G4UniformRand()<(1/totalICC*ICConK)){
        G4double electronEnergy = G4RandGauss::shoot(22.5,15);
        fElectronParticleGun->SetParticleEnergy(electronEnergy*keV);
        fElectronParticleGun->GeneratePrimaryVertex(anEvent);
      }
      else{
        G4double electronEnergy = G4RandGauss::shoot(93.4,18);
        fElectronParticleGun->SetParticleEnergy(electronEnergy*keV);
        fElectronParticleGun->GeneratePrimaryVertex(anEvent);
      }
    }
  }

  fAlphaParticleGun->SetParticleEnergy(alphaEnergy*keV);
  fAlphaParticleGun->SetParticlePosition(posGun);
  fAlphaParticleGun->SetParticleMomentumDirection(dirAlGun);
  fAlphaParticleGun->SetParticleDefinition(alpha);

  // fAlphaParticleGun->GeneratePrimaryVertex(anEvent);
  fIonParticleGun->GeneratePrimaryVertex(anEvent);
  // fProtonParticleGun->GeneratePrimaryVertex(anEvent);
}
