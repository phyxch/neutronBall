// created on August 23, 2022
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nbRunAction.hh"
#include "nbRun.hh"
#include "nbPrimaryGeneratorAction.hh"
#include "nbHistoManager.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>

#include "G4GenericAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRunAction::nbRunAction(nbPrimaryGeneratorAction* kin)
:G4UserRunAction(),
 fPrimary(kin), fRun(0), fHistoManager(0)
{
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
  fRun = new nbRun();
  return fRun;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunAction::BeginOfRunAction(const G4Run*)
{ 
  // keep run condition
  if (fPrimary) { 
    G4ParticleDefinition* particle = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);

  }    
      
  // create instace of analysisManager
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstNtupleId(1);
  // create and open file output.root for writing data in it
  analysisManager->OpenFile("output.root");

  // ntuple Id 1
  analysisManager->CreateNtuple("Hits", "Hits");
  analysisManager->CreateNtupleSColumn(1, "layerName");
  analysisManager->CreateNtupleSColumn(1, "particleName");
  analysisManager->FinishNtuple(1);
  // end of ntuple with Id 1
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunAction::EndOfRunAction(const G4Run*)
{
 if (isMaster) fRun->EndOfRun();
            
 // create instance of analysisManager
 //
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 analysisManager->Write();
 analysisManager->CloseFile("output.root");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

