//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nbTrackingAction.hh"
#include "nbEventAction.hh"

#include "nbDetectorConstruction.hh"
#include "nbRun.hh"
#include "nbHistoManager.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4HadronicProcessType.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleTypes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbTrackingAction::nbTrackingAction(nbDetectorConstruction* det, nbEventAction* EA)
:G4UserTrackingAction(), fDetector(det), fEvent(EA)
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbTrackingAction::PreUserTrackingAction(const G4Track* track)
{
  
  // G4cout << "pH value = "<<fDetector->pHValue<<G4endl;
  // G4cout << "H value = "<<fDetector->fractionMassForH<<G4endl;
  // G4cout << "OH value = "<<fDetector->fractionMassForOH<<G4endl;
  
  // instance of G4Run
  nbRun* run = static_cast<nbRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());    
  
  // instance of analysisManager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  const G4ParticleDefinition* particle = track->GetParticleDefinition();  
  G4String pName  = particle->GetParticleName();
  G4double pID    = particle->GetPDGEncoding();
  G4double Z      = particle->GetAtomicNumber();
  G4double A      = particle->GetAtomicMass();
  // G4double charge = particle->GetPDGCharge();    
  G4double energy = track->GetKineticEnergy();
  G4double time   = track->GetGlobalTime();
  // G4double weight = track->GetWeight();
  // G4double x = track->GetStep()->GetPostStepPoint()->GetPosition().x()/cm;
  // G4double y = track->GetStep()->GetPostStepPoint()->GetPosition().y()/cm;
  // G4double z = track->GetStep()->GetPostStepPoint()->GetPosition().z()/cm;
  // G4int trackID = track->GetTrackID();

  // if particle is anti neutrino; kill
  if (particle == G4AntiNeutrinoE::AntiNeutrinoE())
  {
      G4Track* tr = (G4Track*) track;
      tr->SetTrackStatus(fStopAndKill);
  }

  //which volume ?
  //
  G4String pVolume = track->GetVolume()->GetName(); // return physical volume name
  G4int iVol = 0;
  if (pVolume == fDetector->getNameOfLayer1())   iVol = 1;
  if (pVolume == fDetector->getNameOfLayer2())   iVol = 2;
  if (pVolume == fDetector->getNameOfLayer3())   iVol = 3;
  if (pVolume == fDetector->getNameOfLayer4())   iVol = 4;
  if (pVolume == fDetector->getNameOfLayer5())   iVol = 5;
  if (pVolume == fDetector->getWorld())          iVol = 6; // let's say iVol = 6 is world
  
  // count all particles regardless of PID == 1 or PID != 1
  run->ParticleCount(pName,energy,iVol);
  
  // if the track is secondary
  if(track->GetTrackID() != 1)
  {
      // we can check for radioactive products
      G4int processType = track->GetCreatorProcess()->GetProcessSubType();
      if (processType == fRadioactiveDecay) {
        //fill ntuple id = 1
        G4int id = 1;
        analysisManager->FillNtupleDColumn(id,0, pID);
        analysisManager->FillNtupleDColumn(id,1, Z);
        analysisManager->FillNtupleDColumn(id,2, A);
        analysisManager->FillNtupleDColumn(id,3, energy);
        analysisManager->FillNtupleDColumn(id,4, time/s);
        analysisManager->FillNtupleDColumn(id,5, fDetector->pHValue);
        analysisManager->FillNtupleSColumn(id,6, pName);
        analysisManager->AddNtupleRow(id);
      }
  }
  else
  {
      G4int id = 1;
      analysisManager->FillNtupleDColumn(id,0, pID);
      analysisManager->FillNtupleDColumn(id,1, Z);
      analysisManager->FillNtupleDColumn(id,2, A);
      analysisManager->FillNtupleDColumn(id,3, energy);
      analysisManager->FillNtupleDColumn(id,4, time/s);
      analysisManager->FillNtupleDColumn(id,5, fDetector->pHValue);
      analysisManager->FillNtupleSColumn(id,6, pName);
      analysisManager->AddNtupleRow(id);
  }
  
  // ion
  // https://apc.u-paris.fr/~franco/g4doxy/html/G4TrackStatus_8hh.html
  // // this will get you all radioactive elements since radioactive elements are unstable ions
  // particles can be atom, molecules or ions. 
  // atoms are single neutral particles
  // molecules are neutral particles made of multiple atoms 
  // ions are charged particles - two types - cations(net positive charge) and anions(net negative charge)
  // G4bool unstableIon = ((charge > 2.) && !(particle->GetPDGStable()));
  // if(unstableIon)
  // {
  //     G4cout<<"name: "<<name<<G4endl;
  // }
  
  // const G4ParticleMomentum dir = aTrack->GetMomentumDirection();
  // track->SetMomentumDirection(G4ThreeVector(dir.x(), dir.y(), std::abs(dir.z()));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbTrackingAction::PostUserTrackingAction(const G4Track* )
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    
