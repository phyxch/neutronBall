//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class nbDetectorConstruction;
class nbEventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbSteppingAction : public G4UserSteppingAction
{
  public:
  
    // constructor & destructors
    nbSteppingAction(nbDetectorConstruction*, nbEventAction*);
   ~nbSteppingAction();

    // inbuilt method in steppingAction class
    virtual void UserSteppingAction(const G4Step*);
    
  private:
    
    // objects of detector construction & eventAction class
    nbDetectorConstruction* fDetector;  
    nbEventAction* fEventAction;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

