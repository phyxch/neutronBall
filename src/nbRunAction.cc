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

#include "G4AnalysisManager.hh"

#include <cstdio>
#include <ctime>
#include <iostream>
#include <fstream> 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRunAction::nbRunAction(nbDetectorConstruction* det, nbPrimaryGeneratorAction* prim)
  : G4UserRunAction(),
    fDetector(det), fPrimary(prim), fRun(0), fHistoManager(0)
{
  // create instace of analysisManager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->SetDefaultFileType("root");
  analysisManager->SetNtupleMerging(true);
  
  // we need to setfile name dynamically
  std::time_t rawtime;
  std::tm* timeinfo;
  char rootOutputFileBuffer [80];
  char descFileBuffer [80];

  std::time(&rawtime);
  timeinfo = std::localtime(&rawtime);

  std::strftime(rootOutputFileBuffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
  std::strftime(descFileBuffer,80,"%Y-%m-%d-%H-%M-%S.txt",timeinfo);
  
  rootOutputFile = rootOutputFileBuffer; // root file
  descFile = descFileBuffer;             // description file
  
  G4cout <<"root file: " << rootOutputFile << G4endl;
  G4cout <<"desc file: " << descFile << G4endl;
   
  analysisManager->SetFileName(rootOutputFile);
  
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstNtupleId(1);
  // create and open file output.root for writing data in it
  // analysisManager->OpenFile("output.root");
   
  analysisManager->CreateNtuple("RDecayProducts", "All Products of RDecay");
  analysisManager->CreateNtupleDColumn(1, "pID");       //column 0
  analysisManager->CreateNtupleDColumn(1, "Z");         //column 1
  analysisManager->CreateNtupleDColumn(1, "A");         //column 2    
  analysisManager->CreateNtupleDColumn(1, "energy");    //column 3
  analysisManager->CreateNtupleDColumn(1, "time");      //column 4
  analysisManager->CreateNtupleDColumn(1, "pH");        //column 5
  analysisManager->CreateNtupleSColumn(1, "pName");        //column 6
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
  analysisManager->CreateNtupleDColumn(2, "pVelocity");
  analysisManager->CreateNtupleDColumn(2, "pKE");
  analysisManager->CreateNtupleDColumn(2, "pX");
  analysisManager->CreateNtupleDColumn(2, "pY");
  analysisManager->CreateNtupleDColumn(2, "pZ");
  analysisManager->CreateNtupleIColumn(2, "evtNo");
  analysisManager->FinishNtuple(2);
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

void nbRunAction::BeginOfRunAction(const G4Run* aRun)
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
  
  // create desc file and write data to it 
  std::ofstream outfile (descFile);
  outfile << "no of events: "+std::to_string(aRun->GetNumberOfEventToBeProcessed()) << std::endl;
  outfile << "primary particle: Rn222" << std::endl;
  outfile << "layer 1 material: "+fDetector->shellLV_1->GetMaterial()->GetName() << std::endl;
  outfile << "layer 2 material: "+fDetector->shellLV_2->GetMaterial()->GetName() << std::endl;
  outfile << "layer 3 material: "+fDetector->shellLV_3->GetMaterial()->GetName() << std::endl;
  outfile << "layer 4 material: "+fDetector->shellLV_4->GetMaterial()->GetName() << std::endl;
  outfile << "layer 5 material: "+fDetector->shellLV_5->GetMaterial()->GetName() << std::endl;
  outfile << "layer 1 Radius: "+std::to_string(fDetector->r1/cm) << std::endl;
  outfile << "layer 2 Radius: "+std::to_string(fDetector->r2/cm) << std::endl;
  outfile << "layer 3 Radius: "+std::to_string(fDetector->r3/cm) << std::endl;
  outfile << "layer 4 Radius: "+std::to_string(fDetector->r4/cm) << std::endl;
  outfile << "layer 5 Radius: "+std::to_string(fDetector->r5/cm) << std::endl;
  outfile.close();
  //
  
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Reset histograms from previous run
  analysisManager->Reset();

  // Open an output file
  // The default file name is set in RunAction::RunAction(),
  // it can be overwritten in a macro
  analysisManager->OpenFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunAction::EndOfRunAction(const G4Run*)
{
  if (isMaster) fRun->EndOfRun();    
  
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile(false);      
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

