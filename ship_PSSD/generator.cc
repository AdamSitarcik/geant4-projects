#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fElectronParticleGun = new G4ParticleGun(1);
  fElectronParticleGun->SetParticleEnergy(300.*keV);

  fAlphaParticleGun = new G4ParticleGun(1);
  fAlphaParticleGun->SetParticleEnergy(8.*MeV);

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fElectronParticleGun;
  delete fAlphaParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries (G4Event *anEvent)
{
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

  G4String particleName1 = "e-";
  G4ParticleDefinition *electron = particleTable->FindParticle(particleName1);

  G4String particleName2 = "alpha";
  G4ParticleDefinition *alpha = particleTable->FindParticle(particleName2);

  G4double dirXel = G4UniformRand()-0.5;
  G4double dirYel = G4UniformRand()-0.5;
  G4double dirZel = G4UniformRand()-0.5;

  G4double dirXal = G4UniformRand()-0.5;
  G4double dirYal = G4UniformRand()-0.5;
  G4double dirZal = G4UniformRand()-0.5;

  G4ThreeVector posGun(0., 0., -6.*um);
  // G4ThreeVector dirGun(0., 0., -1.);
  // G4ThreeVector dirGun(G4UniformRand()-0.5, G4UniformRand()-0.5, -G4UniformRand()-0.5);
  G4ThreeVector dirElGun(dirXel, dirYel, dirZel);
  G4ThreeVector dirAlGun(dirXal, dirYal, dirZal);

  fElectronParticleGun->SetParticlePosition(posGun);
  fElectronParticleGun->SetParticleMomentumDirection(dirElGun);
  fElectronParticleGun->SetParticleDefinition(electron);

  fElectronParticleGun->GeneratePrimaryVertex(anEvent);

  fAlphaParticleGun->SetParticlePosition(posGun);
  fAlphaParticleGun->SetParticleMomentumDirection(dirAlGun);
  fAlphaParticleGun->SetParticleDefinition(alpha);

  // fAlphaParticleGun->GeneratePrimaryVertex(anEvent);
}
