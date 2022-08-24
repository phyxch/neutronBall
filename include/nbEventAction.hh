// code updated on 23 August, 2022
// fully revamped as per rdecay01; might need to add code from previous neutronBall nbEventAction.hh file
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nbEventAction_h
#define nbEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbEventAction : public G4UserEventAction
{
  public:
   
    // constructor
    nbEventAction();
    
    // destructor
   ~nbEventAction();
   
  private:

    G4String        fDecayChain;                   
    G4double        fEvisTot;

  public:
  
    // virtual inbuilt method
    virtual void BeginOfEventAction(const G4Event*);
    
    // virtual inbuilt method
    virtual void   EndOfEventAction(const G4Event*);
    
    
    // user defined methods to collect some results 
    void AddDecayChain(G4String val) 
    {
    	fDecayChain += val;
    };
    
    void AddEvisible(G4double val)   
    {
    	fEvisTot    += val;
    };
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif



    
