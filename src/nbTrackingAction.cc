//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nbTrackingAction.hh"

#include "nbDetectorConstruction.hh"
#include "nbRun.hh"
#include "nbHistoManager.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4HadronicProcessType.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbTrackingAction::nbTrackingAction(nbDetectorConstruction* det)
:G4UserTrackingAction(), fDetector(det)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbTrackingAction::PreUserTrackingAction(const G4Track* track)
{
  
  // instance of G4Run
  nbRun* run = static_cast<nbRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());    
  
  // instance of analysisManager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  //which volume ?
  //
  G4String volumeName = track->GetVolume()->GetName(); // return physical volume name
  G4int iVol = 0;
  if (volumeName == fDetector->getNameOfLayer1())   iVol = 1;
  if (volumeName == fDetector->getNameOfLayer2())   iVol = 2;
  if (volumeName == fDetector->getNameOfLayer3())   iVol = 3;
  if (volumeName == fDetector->getNameOfLayer4())   iVol = 4;
  if (volumeName == fDetector->getNameOfLayer5())   iVol = 5;
  if (volumeName == fDetector->getNameOfLayer6())   iVol = 6;
  
  
  //secondary particles only
  if (track->GetTrackID() == 1) return;
  
  const G4ParticleDefinition* particle = track->GetParticleDefinition();  
  G4String name   = particle->GetParticleName();
  G4int pid       = particle->GetPDGEncoding();
  G4int Z         = particle->GetAtomicNumber();
  G4int A         = particle->GetAtomicMass();
  G4double charge = particle->GetPDGCharge();    
  G4double energy = track->GetKineticEnergy();
  G4double time   = track->GetGlobalTime();
  G4double weight = track->GetWeight();
  
  // count particles in each soil layer
  run->ParticleCount(name,energy,iVol);
  
  //Radioactive decay products
  G4int processType = track->GetCreatorProcess()->GetProcessSubType();
  if (processType == fRadioactiveDecay) {
    //fill ntuple id = 3
    G4int id = 4;
    analysisManager->FillNtupleDColumn(id,0, double(pid));
    analysisManager->FillNtupleDColumn(id,1, double(Z));
    analysisManager->FillNtupleDColumn(id,2, double(A));
    analysisManager->FillNtupleDColumn(id,3, energy);
    analysisManager->FillNtupleDColumn(id,4, time/s);
    analysisManager->FillNtupleDColumn(id,5, weight);
    analysisManager->AddNtupleRow(id);
    
    if (charge < 3.) {   
      //fill ntuple id = 0
      id = 1;
      analysisManager->FillNtupleDColumn(id,0, double(pid));
      analysisManager->FillNtupleDColumn(id,1, energy);
      analysisManager->FillNtupleDColumn(id,2, time/s);
      analysisManager->FillNtupleDColumn(id,3, weight);
      analysisManager->AddNtupleRow(id);
    
      // analysisManager->FillH1(6, energy, weight);
      // analysisManager->FillH1(7, energy, weight);
      // analysisManager->FillH1(8, energy, weight);
    }                        
  }
  
  //all unstable ions produced in target
  G4bool unstableIon = ((charge > 2.) && !(particle->GetPDGStable()));
  if ((unstableIon) && (iVol == 1)) {
    //fill ntuple id = 1
    G4int id = 2;
    analysisManager->FillNtupleDColumn(id,0, double(pid));
    analysisManager->FillNtupleDColumn(id,1, time/s);
    analysisManager->FillNtupleDColumn(id,2, weight);
    analysisManager->AddNtupleRow(id);  
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbTrackingAction::PostUserTrackingAction(const G4Track* )
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


