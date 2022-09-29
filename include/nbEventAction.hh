#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbEventAction : public G4UserEventAction
{
  public:
    // constructors and destructors
    nbEventAction();
   ~nbEventAction();

  public:
    
    // inbuilt methods for eventAction class
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
    // void AddEdep(G4int iVol, G4double Edep, G4double time, G4double weight);
                
  private:
    // G4double fEdep1, fEdep2, fEdep3, fEdep4, fEdep5, fEdep6;
    // G4double fWeight1, fWeight2, fWeight3, fWeight4, fWeight5, fWeight6;
    // G4double fTime0;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    

