// Created on 10/13/2021
//
// Updated on 10/20/2021
//   Added proper name for our detector

// Updated on 23 August, 2022
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nbRunAction_h
#define nbRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class nbRun; // instance of nbRun.hh
class nbHistoManager; // instance of nbHistoManager.hh
class nbPrimaryGeneratorAction; // instance of nbPrimaryGeneratorAction.hh

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbRunAction : public G4UserRunAction
{
  public:
    nbRunAction(nbPrimaryGeneratorAction*);
   ~nbRunAction();

    virtual G4Run* GenerateRun();   
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    
  private:
    nbPrimaryGeneratorAction* fPrimary;
    nbRun*                    fRun;
    nbHistoManager*           fHistoManager;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


