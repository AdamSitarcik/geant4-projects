#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fParticleGun = new G4ParticleGun(1);
  fParticleGun->SetParticleEnergy(100.*MeV);

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries (G4Event *anEvent)
{
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "e-";
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

  G4double dirX = G4UniformRand()-0.5;
  G4double dirY = G4UniformRand()-0.5;
  G4double dirZ = G4UniformRand()-0.5;

  G4ThreeVector posGun(0., 0., -6.3*um);
  // G4ThreeVector dirGun(0., 0., -1.);
  // G4ThreeVector dirGun(G4UniformRand()-0.5, G4UniformRand()-0.5, -G4UniformRand()-0.5);
  G4ThreeVector dirGun(dirX, dirY, -dirZ);

  fParticleGun->SetParticlePosition(posGun);
  fParticleGun->SetParticleMomentumDirection(dirGun);
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
