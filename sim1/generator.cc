#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fParticleGun = new G4ParticleGun(1);

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "proton";
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

  G4double randMomX = G4UniformRand()-0.5;
  G4double randMomY = G4UniformRand()-0.5;
  G4double randMomZ = G4UniformRand()-0.5;

  G4ThreeVector pos(0., 0., 0.);
  // G4ThreeVector mom(randMomX, randMomY, randMomZ);
  G4ThreeVector mom(0., 0., 1.);

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleEnergy(2.5*GeV);
  fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
