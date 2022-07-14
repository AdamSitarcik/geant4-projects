#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fParticleGun = new G4ParticleGun(1);
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

  G4ThreeVector posGun(0., 0., 5.*mm);
  G4ThreeVector dirGun(0., 0., -1.);

  fParticleGun->SetParticlePosition(posGun);
  fParticleGun->SetParticleMomentumDirection(dirGun);
  fParticleGun->SetParticleEnergy(250.*keV);
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
