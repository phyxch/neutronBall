// Created on 10/13/2021
// 

#include "nbPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4IonTable.hh"
#include "G4Geantino.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbPrimaryGeneratorAction::nbPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr)
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  /* default particle kinematic
  //
  // auto particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  // fParticleGun->SetParticleDefinition(particleDefinition);
  //  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  // fParticleGun->SetParticleEnergy(50.*MeV);
  */
  
  // default particle properties
  fParticleGun->SetParticleEnergy(0*eV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  // set momentum
  G4double px = 2*G4UniformRand() - 1;
  G4double py = 2*G4UniformRand() - 1;
  G4double pz = 2*G4UniformRand() - 1;
  auto p = G4ThreeVector(px,py,pz);
  fParticleGun->SetParticleMomentumDirection(p);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbPrimaryGeneratorAction::~nbPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume 
  // from G4LogicalVolumeStore
  //
//  G4double worldZHalfLength = 0.;
//  auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

  // Check that the world volume has box shape
//  G4Box* worldBox = nullptr;
//  if (  worldLV ) {
//    worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
//  }

//  if ( worldBox ) {
//    worldZHalfLength = worldBox->GetZHalfLength();  
//  }
//  else  {
//    G4ExceptionDescription msg;
//    msg << "World volume of box shape not found." << G4endl;
//    msg << "Perhaps you have changed geometry." << G4endl;
//    msg << "The gun will be place in the center.";
//    G4Exception("nbPrimaryGeneratorAction::GeneratePrimaries()",
//      "MyCode0002", JustWarning, msg);
//  } 
  
  // Set gun position
  //  fParticleGun
  //    ->SetParticlePosition(G4ThreeVector(0., 0., -worldZHalfLength));
  // fParticleGun
  //  ->SetParticlePosition(G4ThreeVector(0., 0., 0.));
  
//  G4double px = 2*G4UniformRand() - 1;
//  G4double py = 2*G4UniformRand() - 1;
//  G4double pz = 2*G4UniformRand() - 1;
//  auto p = G4ThreeVector(px,py,pz);
//  fParticleGun->SetParticleMomentumDirection(p);

  if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {  
    G4int Z = 10, A = 24;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;
    
    G4ParticleDefinition* ion
       = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);
  }

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

