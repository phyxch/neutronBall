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
    // instance of run class
    nbRun* run = static_cast<nbRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    
    // get particle information
    G4ParticleDefinition* particle = aStep->GetTrack()->GetDefinition();
    G4String particleName   = particle->GetParticleName();    	
    
    // write you code for stepping action here
    
    // instances of preStep and postStep
    // preStep -> can give you information about what happened in previous step
    // postStep -> can give you information about what is happening in current Step 
    // more here: https://geant4-forum.web.cern.ch/t/measuring-of-entrance-spectrum-of-particles-through-a-surface/3098
    
    // G4StepPoint* postStepPoint = aStep->GetPostStepPoint();
    // G4StepPoint* preStepPoint  = aStep->GetPreStepPoint();
    
    // get volume name
    // G4VPhysicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    
    // check: if this is first step 
    G4bool isFirstStep = aStep->IsFirstStepInVolume();
    // get the name of volume
    G4String volumeName = aStep->GetTrack()->GetVolume()->GetName();
    
    // count number of particles reached in outer layer
    if(volumeName == "shellPV" && isFirstStep == true)
    {
  	// call function
  	run->ParticleCountPerLayer(volumeName, particleName);
    }
    else
    {
    	// yes this is first step in volume
    	G4cout<<"NANANA"<<G4endl;	
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
