// Created on 10/13/2021
//


#ifndef nbEventAction_h
#define nbEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///
/// In EndOfEventAction(), it prints the accumulated quantities of the energy 
/// deposit and track lengths of charged particles in Absober and Gap layers 
/// stored in nbRunData object.

class nbEventAction : public G4UserEventAction
{
  public:
    nbEventAction();
    virtual ~nbEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
  private:
    // methods
    void PrintEventStatistics(G4double absoEdep, G4double absoTrackLength,
                              G4double gapEdep, G4double gapTrackLength) const;
};
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
