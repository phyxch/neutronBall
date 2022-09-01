// code updated on 23 August, 2022
// fully revamped as per rdecay01; might need to add code from previous neutronBall nbEventAction.cc file

#include "nbActionInitialization.hh"
#include "nbPrimaryGeneratorAction.hh"
#include "nbRunAction.hh"
#include "nbEventAction.hh"
#include "nbTrackingAction.hh"
#include "nbSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbActionInitialization::nbActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbActionInitialization::~nbActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbActionInitialization::BuildForMaster() const
{
  nbRunAction* runAction = new nbRunAction(0);
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbActionInitialization::Build() const
{
  nbPrimaryGeneratorAction* primary = new nbPrimaryGeneratorAction();
  SetUserAction(primary);
    
  nbRunAction* runAction = new nbRunAction(primary);
  SetUserAction(runAction);
  
  nbEventAction* eventAction = new nbEventAction();
  SetUserAction(eventAction);
  
  nbTrackingAction* trackingAction = new nbTrackingAction(eventAction);
  SetUserAction(trackingAction);
	
  nbSteppingAction* steppingAction = new nbSteppingAction();
  SetUserAction(steppingAction);
  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

