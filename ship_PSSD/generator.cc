#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fElectronParticleGun = new G4ParticleGun(1);

  fMainParticleGun = new G4ParticleGun(1);

  fIonParticleGun = new G4ParticleGun(1);

  fProtonParticleGun = new G4ParticleGun(1);

  fRtg1ParticleGun = new G4ParticleGun(1);

  fRtg2ParticleGun = new G4ParticleGun(1);

  fRemainingEnParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fElectronParticleGun;
  delete fMainParticleGun;
  delete fIonParticleGun;
  delete fProtonParticleGun;
  delete fRtg1ParticleGun;
  delete fRtg2ParticleGun;
  delete fRemainingEnParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries (G4Event *anEvent)
{
  ionZ = 26;
  ionA = 56;
  G4double ion_kinetic_energy = 70.;

  G4double impDepth = 8.; // in um

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

  G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(ionZ, ionA, 0.);

  G4ParticleDefinition *electron = particleTable->FindParticle("e-");
  G4ParticleDefinition *alpha = particleTable->FindParticle("alpha");
  G4ParticleDefinition *proton = particleTable->FindParticle("proton");  
  G4ParticleDefinition *gamma = particleTable->FindParticle("gamma");

  G4double dirXel = G4UniformRand()-0.5;
  G4double dirYel = G4UniformRand()-0.5;
  G4double dirZel = G4UniformRand()-0.5;
  
  G4double dirXrtg1 = G4UniformRand()-0.5;
  G4double dirYrtg1 = G4UniformRand()-0.5;
  G4double dirZrtg1 = G4UniformRand()-0.5;

  G4double dirXrtg2 = G4UniformRand()-0.5;
  G4double dirYrtg2 = G4UniformRand()-0.5;
  G4double dirZrtg2 = G4UniformRand()-0.5;

  G4double dirXRemainingEn = G4UniformRand()-0.5;
  G4double dirYRemainingEn = G4UniformRand()-0.5;
  G4double dirZRemainingEn = G4UniformRand()-0.5;

  G4double dirX = G4UniformRand()-0.5;
  G4double dirY = G4UniformRand()-0.5;
  G4double dirZ = G4UniformRand()-0.5;

  // Input and calculation of parameters of electrons in case of IC simulations
  // // custom gate
  // G4double particleEnergy = 7120; // in keV
  // G4double convTransitionEnergy = 235;
  // G4double totalICC = 3.36;
  // G4double K_ICC = 2.49;
  // G4double KL_ratio = 3.81;

  // // 108kev gate
  // G4double particleEnergy = 7120; // in keV
  // G4double convTransitionEnergy = 108;
  // G4double totalICC = 0.355;
  // G4double K_ICC = 0.283;
  // G4double KL_ratio = 5.16;

  // // 186kev gate
  // G4double particleEnergy = 7120; // in keV
  // G4double convTransitionEnergy = 285;
  // G4double totalICC = 0.451;
  // G4double K_ICC = 0.37;
  // G4double KL_ratio = 5.92;

  // 215kev gate
  G4double particleEnergy = 7150; // in keV
  G4double convTransitionEnergy = 145;
  G4double totalICC = 1.32;
  G4double K_ICC = 0.345;
  G4double KL_ratio = 0.474;

  // // 238kev gate
  // G4double particleEnergy = 7150; // in keV
  // G4double convTransitionEnergy = 180;
  // G4double totalICC = 1.616;
  // G4double K_ICC = 1.322;
  // G4double KL_ratio = 5.87;

  // // 255kev gate
  // G4double particleEnergy = 7263; // in keV
  // G4double convTransitionEnergy = 108;
  // G4double totalICC = 0.355;
  // G4double K_ICC = 0.283;
  // G4double KL_ratio = 5.16;

  G4double bindingK = 85.53;
  G4double bindingL = 14.2;
  G4double bindingM = 3;
  G4double elKEnergy = convTransitionEnergy - bindingK;
  G4double elLEnergy = convTransitionEnergy - bindingL;
  G4double elMEnergy = convTransitionEnergy - bindingM;
  G4double electronEnergy; 
  G4double rtgEn1;
  G4double rtgEn2;
  G4double remainingEnergy;
  // G4bool vacantK;
  // G4bool vacantL;

  G4double L_ICC = K_ICC/KL_ratio;
  G4double M_ICC = totalICC - K_ICC - L_ICC;
  G4double ICConK = totalICC/(KL_ratio+1)*KL_ratio;

  G4ThreeVector posGun(0., 0., impDepth*um);
  // G4ThreeVector posIonGun(G4RandGauss::shoot(0,0.1)*mm, G4RandGauss::shoot(0,0.1)*mm, ionSourcePosition);

  // G4ThreeVector dirElGun(0,0,1);

  // G4ThreeVector posProtonGun(G4RandGauss::shoot(0,0.1)*mm, G4RandGauss::shoot(0,0.1)*mm, protonSourcePosition);

  G4ThreeVector dirElGun(dirXel, dirYel, dirZel);
  G4ThreeVector dirMainGun(dirX, dirY, dirZ);
  G4ThreeVector dirRtg1Gun(dirXrtg1, dirYrtg1, dirZrtg1);
  G4ThreeVector dirRtg2Gun(dirXrtg2, dirYrtg2, dirZrtg2);
  G4ThreeVector dirRemEnGun(dirXRemainingEn, dirYRemainingEn, dirZRemainingEn);

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

  G4int generate_electrons = 1; // 0 - do not generate conversion electrons, 1 - generate CEs
  
  if(generate_electrons == 1){
    fElectronParticleGun->SetParticlePosition(posGun);
    fElectronParticleGun->SetParticleMomentumDirection(dirElGun);
    fElectronParticleGun->SetParticleDefinition(electron);
  
    fRtg1ParticleGun->SetParticlePosition(posGun);
    fRtg1ParticleGun->SetParticleMomentumDirection(dirRtg1Gun);
    fRtg1ParticleGun->SetParticleDefinition(gamma);

    fRtg2ParticleGun->SetParticlePosition(posGun);
    fRtg2ParticleGun->SetParticleMomentumDirection(dirRtg2Gun);
    fRtg2ParticleGun->SetParticleDefinition(gamma);
    
    fRemainingEnParticleGun->SetParticlePosition(posGun);
    fRemainingEnParticleGun->SetParticleMomentumDirection(dirRemEnGun);
    fRemainingEnParticleGun->SetParticleDefinition(gamma);
    
    G4double conversionTypePercent = G4UniformRand();
  
  // if(G4UniformRand()<0.5) {
    // electronEnergy = 100;
    // fElectronParticleGun->SetParticlePosition(posGun);
    // fElectronParticleGun->SetParticleMomentumDirection(dirElGun);
    // fElectronParticleGun->SetParticleDefinition(electron);
    // fElectronParticleGun->SetParticleEnergy(electronEnergy*keV);
    // fElectronParticleGun->GeneratePrimaryVertex(anEvent);
  // }

    if(G4UniformRand()<totalICC/(totalICC+1.))
    {
      if(conversionTypePercent < (K_ICC/totalICC)){
        electronEnergy = elKEnergy;
        // vacantK = true;
        if(G4UniformRand()<0.787) { // Kalfa RTG 
          rtgEn1 = 72.1;
          if(G4UniformRand()<0.26){
            rtgEn2 = 12;
            remainingEnergy = bindingK - (rtgEn1 + rtgEn2);
          }
          else {
            rtgEn2 = 6;
            remainingEnergy = bindingK - (rtgEn1 + rtgEn2);
          }
        }
        else { // Kbeta RTG
          rtgEn1 = 82.9;
          rtgEn2 = 0;
          remainingEnergy = bindingK - rtgEn1;
        }
      }
      else if(conversionTypePercent > (K_ICC/totalICC) && conversionTypePercent < (L_ICC/totalICC + K_ICC/totalICC)){
        electronEnergy = elLEnergy;
        rtgEn1 = 12;
        rtgEn2 = 0;
        remainingEnergy = bindingL - rtgEn1;
      }
      else {
        electronEnergy = elMEnergy;
        rtgEn1 = 0;
        rtgEn2 = 0;
        remainingEnergy = bindingM;
      }
      // electronEnergy = G4RandGauss::shoot(electronEnergy,10);
      fElectronParticleGun->SetParticleEnergy(electronEnergy*keV);
      if(rtgEn1 > 0) {
        fRtg1ParticleGun->SetParticleEnergy(rtgEn1*keV);
        fRtg1ParticleGun->GeneratePrimaryVertex(anEvent);
      }
      if(rtgEn1 > 0) {
        fRtg2ParticleGun->SetParticleEnergy(rtgEn2*keV);
        fRtg2ParticleGun->GeneratePrimaryVertex(anEvent);
      }
      fRemainingEnParticleGun->SetParticleEnergy(remainingEnergy*keV);
      fRemainingEnParticleGun->GeneratePrimaryVertex(anEvent);

      fElectronParticleGun->GeneratePrimaryVertex(anEvent);
    }
  }

  if(G4UniformRand()<totalICC/(totalICC+1.))
  {
    if(conversionTypePercent < (K_ICC/totalICC)){
      electronEnergy = elKEnergy;
    }
    else if(conversionTypePercent > (K_ICC/totalICC) && conversionTypePercent < (L_ICC/totalICC + K_ICC/totalICC)){
      electronEnergy = elLEnergy;
    }
    else {
      electronEnergy = elMEnergy;
    }
    // electronEnergy = G4RandGauss::shoot(electronEnergy,10);
    fElectronParticleGun->SetParticleEnergy(electronEnergy*keV);
    fElectronParticleGun->GeneratePrimaryVertex(anEvent);
  }
  }

  fMainParticleGun->SetParticleEnergy(particleEnergy*keV);
  fMainParticleGun->SetParticlePosition(posGun);
  fMainParticleGun->SetParticleMomentumDirection(dirMainGun);
  fMainParticleGun->SetParticleDefinition(alpha);

  fMainParticleGun->GeneratePrimaryVertex(anEvent);
  // fIonParticleGun->GeneratePrimaryVertex(anEvent);
  // fProtonParticleGun->GeneratePrimaryVertex(anEvent);
}
