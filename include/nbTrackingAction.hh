//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class nbDetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbTrackingAction : public G4UserTrackingAction {

  public:  
  
    // constructor & desstructor
    nbTrackingAction(nbDetectorConstruction*);
   ~nbTrackingAction() {};
   
    // inbuilt methods for trackingAction class
    virtual void PreUserTrackingAction(const G4Track*);   
    virtual void PostUserTrackingAction(const G4Track*);
    
  private:
  
    // object of detector construction class
    nbDetectorConstruction* fDetector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

