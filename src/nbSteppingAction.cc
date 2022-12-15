//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nbSteppingAction.hh"

#include "nbDetectorConstruction.hh"
#include "nbRun.hh"
#include "nbEventAction.hh"
#include "nbHistoManager.hh"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbSteppingAction::nbSteppingAction(nbDetectorConstruction* det, nbEventAction* event)
: G4UserSteppingAction(), fDetector(det), fEventAction(event)
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbSteppingAction::~nbSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbSteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // instance of G4Run
  nbRun* run = static_cast<nbRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun()); 
  
  // instance of analysisManager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  // get volume of the current step
  G4String pVolume = aStep->GetTrack()->GetVolume()->GetName();
  G4int iVol = 0;
  if (pVolume == fDetector->getNameOfLayer1())   iVol = 1;
  if (pVolume == fDetector->getNameOfLayer2())   iVol = 2;
  if (pVolume == fDetector->getNameOfLayer3())   iVol = 3;
  if (pVolume == fDetector->getNameOfLayer4())   iVol = 4;
  if (pVolume == fDetector->getNameOfLayer5())   iVol = 5;
  if (pVolume == fDetector->getWorld())          iVol = 6; // let's say iVol = 6 is world
  
  const G4ParticleDefinition* particle = aStep->GetTrack()->GetParticleDefinition();  
  
  G4String pName   = particle->GetParticleName();
  G4int pID       = particle->GetPDGEncoding();
  G4int Z         = particle->GetAtomicNumber();
  G4int A         = particle->GetAtomicMass();
  G4double x=aStep->GetPostStepPoint()->GetPosition().x()/um;
  G4double y=aStep->GetPostStepPoint()->GetPosition().y()/um;
  G4double z=aStep->GetPostStepPoint()->GetPosition().z()/um;
  G4double pVelocity=aStep->GetPostStepPoint()->GetVelocity();
  G4double pKE=aStep->GetPostStepPoint()->GetKineticEnergy();
  G4double pX=aStep->GetPostStepPoint()->GetMomentum().x();
  G4double pY=aStep->GetPostStepPoint()->GetMomentum().y();
  G4double pZ=aStep->GetPostStepPoint()->GetMomentum().z();
  G4int evtNo = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  
  // if(A == 222 || z == 86)
  // {
  //     G4cout<<"x position: "<<x<<G4endl;
  //     G4cout<<"y position: "<<y<<G4endl;
  //     G4cout<<"z position: "<<z<<G4endl;
  //     G4cout<<"Atomic number(Z): "<<Z<<G4endl;
  //     G4cout<<"Atomic mass number(A): "<<A<<G4endl;
  //     G4cout<<"velocity: "<<pVelocity<<G4endl;
  //     G4cout<<"kinetic energy: "<<pKE<<G4endl;
  //     G4cout<<"x-direction momentum: "<<pX<<G4endl;
  //     G4cout<<"y-direction momentum: "<<pX<<G4endl;
  //     G4cout<<"z-direction momentum: "<<pZ<<G4endl;
  //     
  // }
  
  // fill ntuple with id = 2
  G4int id = 2;
  analysisManager->FillNtupleDColumn(id,0, x);
  analysisManager->FillNtupleDColumn(id,1, y);
  analysisManager->FillNtupleDColumn(id,2, z);
  analysisManager->FillNtupleDColumn(id,3, pID);
  analysisManager->FillNtupleDColumn(id,4, Z);
  analysisManager->FillNtupleDColumn(id,5, A);
  analysisManager->FillNtupleSColumn(id,6, pName);
  analysisManager->FillNtupleIColumn(id,7, iVol);
  analysisManager->FillNtupleDColumn(id,8, pVelocity);
  analysisManager->FillNtupleDColumn(id,9, pKE);
  analysisManager->FillNtupleDColumn(id,10, pX);
  analysisManager->FillNtupleDColumn(id,11, pY);
  analysisManager->FillNtupleDColumn(id,12, pZ);
  analysisManager->FillNtupleIColumn(id,13, evtNo);
  // add row
  analysisManager->AddNtupleRow(id);
  
  // if particle is in world volume
  
 
  // if (pVolume == fDetector->getWorld() && A == 222)
  // {
  //     aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  //     G4cout << "the particle << " << pName << " is stopped" << G4endl;
  // }
  // 
  // else if(A == 222)
  // {
  //    aStep->GetTrack()->SetTrackStatus(fAlive);
  // }
  
  
  
  // if(A == 222)
  // {
  //     // check the velocity of particle
  //     G4double currentVelocity =  aStep->GetPostStepPoint()->GetVelocity();
  //     
  //     G4cout << "currentVelocity : " << currentVelocity << G4endl;
  //     
  //     if(currentVelocity <= 0)
  //     {
  //         // give particle momentum direction and velocity
  //         // aStep->GetPreStepPoint()->SetKineticEnergy(86.0 * keV);
  //         aStep->GetPostStepPoint()->SetMomentumDirection(G4ThreeVector(0,1,0));
  //         aStep->GetPostStepPoint()->SetVelocity(10 * m/second);
  //         
  //         G4cout <<" velocity of " << aStep->GetTrack()->GetVelocity() << "is applied" << G4endl;
  //         // aStep->GetTrack()->SetTrackStatus(fAlive);
  //     }
  //     
  //     G4cout <<"track status is : " << aStep->GetTrack()->GetTrackStatus() << G4endl;
  // }
  // if the particle is radon
  // if(A == 222)
  // {
  //     // auto particleMomentum = aStep->GetTrack()->GetMomentum();
  //     // 
  //     // particleMomentum += G4ThreeVector(1.0, 1.0, 1.0);     
  //     
  //     auto vel = aStep->GetTrack()->GetVelocity();
  //     
  //     
  //     aStep->GetTrack()->SetVelocity(vel + 100000000000.00);
  // }
  // particle->SetParticleMomentum(G4ThreeVector(0,1,0)); 
  
  // aStep->GetPostStepPoint()->SetMomentumDirection(G4ThreeVector(0,1,0));
  // aStep->GetPostStepPoint()->SetVelocity(1 * m/second);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

