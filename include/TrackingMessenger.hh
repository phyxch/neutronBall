#ifndef TrackingMessenger_h
#define TrackingMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class TrackingAction;
class G4UIcmdWithABool;
class G4UIcommand;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackingMessenger: public G4UImessenger
{
  public:
    TrackingMessenger(TrackingAction*);
   ~TrackingMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    TrackingAction*   fTrackingAction;    
    G4UIcmdWithABool* fTrackingCmd;
    G4UIcommand*      fTimeWindowCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
