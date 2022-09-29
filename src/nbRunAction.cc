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
  
  analysisManager->CreateNtuple("T1", "Emitted Particles");
  analysisManager->CreateNtupleDColumn(1, "PID");       //column 0
  analysisManager->CreateNtupleDColumn(1, "Energy");    //column 1
  analysisManager->CreateNtupleDColumn(1, "Time");      //column 2
  analysisManager->CreateNtupleDColumn(1, "Weight");    //column 3
  analysisManager->FinishNtuple(1);
  
  analysisManager->CreateNtuple("T2", "RadioIsotopes");
  analysisManager->CreateNtupleDColumn(2, "PID");       //column 0
  analysisManager->CreateNtupleDColumn(2, "Time");      //column 1
  analysisManager->CreateNtupleDColumn(2, "Weight");    //column 2
  analysisManager->FinishNtuple(2);
  
  analysisManager->CreateNtuple("T3", "Energy depositions");
  analysisManager->CreateNtupleDColumn(3, "Energy");    //column 0
  analysisManager->CreateNtupleDColumn(3, "Time");      //column 1
  analysisManager->CreateNtupleDColumn(3, "Weight");    //column 2
  analysisManager->FinishNtuple(3);
  
  analysisManager->CreateNtuple("RDecayProducts", "All Products of RDecay");
  analysisManager->CreateNtupleDColumn(4, "PID");       //column 0
  analysisManager->CreateNtupleDColumn(4, "Z");         //column 1
  analysisManager->CreateNtupleDColumn(4, "A");         //column 2    
  analysisManager->CreateNtupleDColumn(4, "Energy");    //column 3
  analysisManager->CreateNtupleDColumn(4, "Time");      //column 4
  analysisManager->CreateNtupleDColumn(4, "Weight");    //column 5
  analysisManager->FinishNtuple(4);
  
  analysisManager->CreateNtuple("particleData", "All data");
  analysisManager->CreateNtupleDColumn(5, "X");       //column 0
  analysisManager->CreateNtupleDColumn(5, "Y");         //column 1
  analysisManager->CreateNtupleDColumn(5, "Z");         //column 2    
  analysisManager->CreateNtupleDColumn(5, "pID");    //column 3
  analysisManager->CreateNtupleDColumn(5, "pName");      //column 4
  analysisManager->CreateNtupleDColumn(5, "pVol");    //column 5
  analysisManager->FinishNtuple(5);
             
  //histograms
  //
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // if ( analysisManager->IsActive() ) {
  //   analysisManager->OpenFile();
  // }  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunAction::EndOfRunAction(const G4Run*)
{
  if (isMaster) fRun->EndOfRun();    
  
  //save histograms      
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // if ( analysisManager->IsActive() ) {
  //   analysisManager->Write();
  //   analysisManager->CloseFile();
  // }
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile("output.root");
      
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

