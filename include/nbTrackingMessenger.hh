// created on August 22, 2022
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nbTrackingMessenger_h
#define nbTrackingMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class nbTrackingAction;
class G4UIcmdWithABool;
class G4UIcommand;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbTrackingMessenger: public G4UImessenger
{
  
  // some data members of class
  private:
    nbTrackingAction*   fTrackingAction;    
    G4UIcmdWithABool* fTrackingCmd;
    G4UIcommand*      fTimeWindowCmd;

  public:
    
    // constructor
    nbTrackingMessenger(nbTrackingAction*);
    
    // destructor
   ~nbTrackingMessenger();
    
    
    // inbuilt virtual method    
    virtual void SetNewValue(G4UIcommand*, G4String);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

