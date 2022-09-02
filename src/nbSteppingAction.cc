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
    
    // check: if this is first step 
    G4bool isFirstStep = aStep->IsFirstStepInVolume();
    // get the name of volume
    G4String volumeName = aStep->GetTrack()->GetVolume()->GetName();
    
    // store the particle data
    // fill columns of ntuple id 1
    analysisManager->FillNtupleSColumn(1, 0, volumeName);
    analysisManager->FillNtupleSColumn(1, 1, particleName);
    analysisManager->AddNtupleRow(1);
    
    
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
