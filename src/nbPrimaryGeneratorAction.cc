// August 23, 2022
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "nbPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>       /* cos */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbPrimaryGeneratorAction::nbPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  fParticleGun->SetParticleEnergy(0*eV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  

  
  // if you're setting a particle through the gun
  // use following decay energy in setting particle energy  
  // link: https://www.ld-didactic.de/software/524221en/Content/Appendix/Ra226Series.htm         
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbPrimaryGeneratorAction::~nbPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  // we need to setup momentum (mv)
  G4double p, px, py, pz;
  G4double theta, phi, PI;
  
  p = 191.108*MeV; // this is calculated using two body decay
  

  PI = 3.14159265;
  theta = 180*G4UniformRand();
  phi = 360*G4UniformRand();
  
  // G4cout << "theta = " << theta <<  "   Phi = " << phi << G4endl;
  
  pz = p * cos (theta*PI / 180.0);
  px = p * sin (theta*PI / 180.0) * cos (phi*PI / 360.0);
  py = p * sin (theta*PI / 180.0) * sin (phi*PI / 360.0);
    
  // G4cout<<"px : "<<px<<G4endl;
  // G4cout<<"py : "<<py<<G4endl;
  // G4cout<<"pz : "<<pz<<G4endl;    
    
  fParticleGun->SetParticleMomentum(G4ThreeVector(px,py,pz)); 

  if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {  
    G4int Z = 86, A = 222;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;
    
    G4ParticleDefinition* ion
      = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);
  }    
  //create vertex
  //   
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

