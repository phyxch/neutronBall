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

nbActionInitialization::nbActionInitialization
                            (nbDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbActionInitialization::~nbActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbActionInitialization::BuildForMaster() const
{
  SetUserAction(new nbRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbActionInitialization::Build() const
{
  SetUserAction(new nbPrimaryGeneratorAction);
  SetUserAction(new nbRunAction);
  SetUserAction(new nbEventAction);
  SetUserAction(new nbSteppingAction(fDetConstruction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
