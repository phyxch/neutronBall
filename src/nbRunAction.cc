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
      
  //histograms
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunAction::EndOfRunAction(const G4Run*)
{
 if (isMaster) fRun->EndOfRun();
            
 //save histograms
 //
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 if ( analysisManager->IsActive() ) {
  analysisManager->Write();
  analysisManager->CloseFile();
 } 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

