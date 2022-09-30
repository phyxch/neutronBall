//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nbRunAction.hh"
#include "nbRun.hh"
#include "nbDetectorConstruction.hh"
#include "nbPrimaryGeneratorAction.hh"
#include "nbHistoManager.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRunAction::nbRunAction(nbDetectorConstruction* det, nbPrimaryGeneratorAction* prim)
  : G4UserRunAction(),
    fDetector(det), fPrimary(prim), fRun(0), fHistoManager(0)
{
 // Book predefined histograms
 fHistoManager = new nbHistoManager(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRunAction::~nbRunAction()
{
 delete fHistoManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* nbRunAction::GenerateRun()
{ 
  // geant4 convention: instantiate G4Run object here
  fRun = new nbRun(fDetector); 
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunAction::BeginOfRunAction(const G4Run*)
{    
  // save Rndm status
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  if (isMaster) G4Random::showEngineStatus();
  
  // keep run condition
  if (fPrimary) { 
    G4ParticleDefinition* particle 
      = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);
  }
  
  // create instace of analysisManager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstNtupleId(1);
  // create and open file output.root for writing data in it
  analysisManager->OpenFile("output.root");
   
  analysisManager->CreateNtuple("RDecayProducts", "All Products of RDecay");
  analysisManager->CreateNtupleDColumn(1, "pID");       //column 0
  analysisManager->CreateNtupleDColumn(1, "Z");         //column 1
  analysisManager->CreateNtupleDColumn(1, "A");         //column 2    
  analysisManager->CreateNtupleDColumn(1, "energy");    //column 3
  analysisManager->CreateNtupleDColumn(1, "time");      //column 4
  // analysisManager->CreateNtupleDColumn(1, "weight");    //column 5
  analysisManager->FinishNtuple(1);
  
  analysisManager->CreateNtuple("particleData", "All data");
  analysisManager->CreateNtupleDColumn(2, "x");       //column 0
  analysisManager->CreateNtupleDColumn(2, "y");         //column 1
  analysisManager->CreateNtupleDColumn(2, "z");         //column 2    
  analysisManager->CreateNtupleDColumn(2, "pID");    //column 3
  analysisManager->CreateNtupleDColumn(2, "Z");         //column 1
  analysisManager->CreateNtupleDColumn(2, "A");    
  analysisManager->CreateNtupleSColumn(2, "pName");      //column 4
  analysisManager->CreateNtupleIColumn(2, "pVolume");    //column 5
  analysisManager->FinishNtuple(2);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunAction::EndOfRunAction(const G4Run*)
{
  if (isMaster) fRun->EndOfRun();    
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile("output.root");
      
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

