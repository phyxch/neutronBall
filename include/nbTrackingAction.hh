// created on August 22, 2022

#ifndef nbTrackingAction_h
#define nbTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class nbEventAction;
class nbTrackingMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbTrackingAction : public G4UserTrackingAction {

  // some data members of nbTrackingAction class
  private:
    nbEventAction*        fEvent;
    nbTrackingMessenger*  fTrackMessenger;
    
    G4double fCharge, fMass;        
    G4bool   fFullChain;

    G4double fTime_birth,  fTime_end;
    G4double fTimeWindow1, fTimeWindow2;

  public:  
    nbTrackingAction(nbEventAction*);
   ~nbTrackingAction();
   
    // some inbuilt virtual methods for TrackingAction class
    virtual void  PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);
    
    // some user define methods
    void SetFullChain(G4bool flag) 
    { 
    	fFullChain = flag;
    };
    
    void SetTimeWindow(G4double , G4double);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

