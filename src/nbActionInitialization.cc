// Created on 10/13/2021
// 

#include "nbActionInitialization.hh"
#include "nbPrimaryGeneratorAction.hh"
#include "nbRunAction.hh"
#include "nbEventAction.hh"
#include "nbSteppingAction.hh"
#include "G4MTRunManager.hh"
#include "nbDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// nbActionInitialization constructor
nbActionInitialization::nbActionInitialization
                            (nbDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// nbActionInitialization destructor
nbActionInitialization::~nbActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// override virtual method from base class
void nbActionInitialization::BuildForMaster() const
{
  // initiaze nbRunAction class
  SetUserAction(new nbRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// override virtual method from base class
void nbActionInitialization::Build() const
{
  // initialize action classes
  SetUserAction(new nbPrimaryGeneratorAction);
  SetUserAction(new nbRunAction);
  SetUserAction(new nbEventAction);
  SetUserAction(new nbSteppingAction(fDetConstruction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
