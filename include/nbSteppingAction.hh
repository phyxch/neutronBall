// Created on 10/13/2021
// 

#ifndef nbSteppingAction_h
#define nbSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class nbDetectorConstruction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track 
/// lengths of charged particles in Absober and Gap layers and
/// updated in nbRunData object.

class nbSteppingAction : public G4UserSteppingAction
{
public:
  nbSteppingAction(const nbDetectorConstruction* detectorConstruction);
  virtual ~nbSteppingAction();

  virtual void UserSteppingAction(const G4Step* step);
    
private:
  const nbDetectorConstruction* fDetConstruction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
