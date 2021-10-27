// Created on 10/13/2021
// 
// Updated:
//

#include "nbSteppingAction.hh"
#include "nbRunData.hh"
#include "nbDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbSteppingAction::nbSteppingAction(
                      const nbDetectorConstruction* detectorConstruction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbSteppingAction::~nbSteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nbSteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and track length step by step

  // get volume of the current step
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  //  G4cout << " Volume :  " << volume << G4endl;
  
  // energy deposit
  auto edep = step->GetTotalEnergyDeposit();
  
  // step length
  G4double stepLength = 0.;
  /*
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    stepLength = step->GetStepLength();
  }
  */
  stepLength = step->GetStepLength();
  //  G4cout << " ********* stepLength : " << stepLength << G4endl;
      
  auto runData = static_cast<nbRunData*>
    (G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  
  //  if ( volume == fDetConstruction->GetShellPV() ) {
  runData->Add(kShell, edep, stepLength);
  //  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
