// Created on 10/13/2021
// 

#ifndef nbSteppingAction_h
#define nbSteppingAction_h 1

#include "G4UserSteppingAction.hh"

// class nbDetectorConstruction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track 
/// lengths of charged particles in Absober and Gap layers and
/// updated in nbRunData object.

class nbSteppingAction : public G4UserSteppingAction
{

private:
  // const nbDetectorConstruction* fDetConstruction;

public:
  // nbSteppingAction(const nbDetectorConstruction* detectorConstruction);
  
  // currently I do not need any user action class in stepping action
  nbSteppingAction();
  ~nbSteppingAction();

  virtual void UserSteppingAction(const G4Step* step);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
