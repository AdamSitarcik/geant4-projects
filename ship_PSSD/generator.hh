#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
  MyPrimaryGenerator();
  ~MyPrimaryGenerator();

  virtual void GeneratePrimaries(G4Event*);

private:
  G4ParticleGun *fElectronParticleGun, *fMainParticleGun, *fIonParticleGun, *fProtonParticleGun, *fRtg1ParticleGun, *fRtg2ParticleGun, *fRemainingEnParticleGun;

  G4int ionZ, ionA;
};
#endif
