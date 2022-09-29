#include "nbActionInitialization.hh"
#include "nbPrimaryGeneratorAction.hh"
#include "nbRunAction.hh"
#include "nbEventAction.hh"
#include "nbTrackingAction.hh"
#include "nbSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbActionInitialization::nbActionInitialization(nbDetectorConstruction* detector)
 : G4VUserActionInitialization(),
   fDetector(detector)
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbActionInitialization::~nbActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbActionInitialization::BuildForMaster() const
{
  nbRunAction* runAction = new nbRunAction(fDetector, 0);
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbActionInitialization::Build() const
{
  nbPrimaryGeneratorAction* primary = new nbPrimaryGeneratorAction();
  SetUserAction(primary);
    
  nbRunAction* runAction = new nbRunAction(fDetector, primary);
  SetUserAction(runAction);
  
  nbEventAction* event = new nbEventAction();
  SetUserAction(event);  
  
  nbTrackingAction* trackingAction = new nbTrackingAction(fDetector, event);
  SetUserAction(trackingAction);
  
  nbSteppingAction* steppingAction = new nbSteppingAction(fDetector, event);
  SetUserAction(steppingAction);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

