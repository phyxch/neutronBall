// Created on 10/13/2021
// 
// Updated:
//

#include "nbSteppingAction.hh"
#include "nbRunData.hh"
#include "nbDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

#include "nbRun.hh"
#include "G4AnalysisManager.hh"
#include "G4GenericAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// stepping action constructor
nbSteppingAction::nbSteppingAction(): G4UserSteppingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// stepping action destructor
nbSteppingAction::~nbSteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


void nbSteppingAction::UserSteppingAction(const G4Step* aStep)
{ 
    // instance of analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // instance of run class
    // nbRun* run = static_cast<nbRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    
    // get particle information
    G4ParticleDefinition* particle = aStep->GetTrack()->GetDefinition();
    G4String particleName   = particle->GetParticleName();    	
    
    G4bool isFirstStep = aStep->IsFirstStepInVolume();
    G4String volumeName = aStep->GetTrack()->GetVolume()->GetName();
    
    G4double x=aStep->GetPreStepPoint()->GetPosition().x();
    G4double y=aStep->GetPreStepPoint()->GetPosition().y();
    G4double z=aStep->GetPreStepPoint()->GetPosition().z();
    G4double px=aStep->GetPostStepPoint()->GetPosition().x();
    G4double py=aStep->GetPostStepPoint()->GetPosition().y();
    G4double pz=aStep->GetPostStepPoint()->GetPosition().z();

    if(isFirstStep)
    {
        // store the particle data
        // fill columns of ntuple id 1
    	analysisManager->FillNtupleSColumn(1, 0, volumeName);
        analysisManager->FillNtupleSColumn(1, 1, particleName);
        analysisManager->FillNtupleDColumn(1, 2, x);
        analysisManager->FillNtupleDColumn(1, 3, y);
        analysisManager->FillNtupleDColumn(1, 4, z);
        analysisManager->FillNtupleDColumn(1, 5, px);
        analysisManager->FillNtupleDColumn(1, 6, py);
        analysisManager->FillNtupleDColumn(1, 7, pz);
        // add this row to ntuple id 1
        analysisManager->AddNtupleRow(1);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
