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
#include "G4RootAnalysisReader.hh"

using G4AnalysisReader = G4RootAnalysisReader;

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
  analysisManager->CreateNtupleDColumn(1, "x");
  analysisManager->CreateNtupleDColumn(1, "y");
  analysisManager->CreateNtupleDColumn(1, "z");
  analysisManager->CreateNtupleDColumn(1, "px");
  analysisManager->CreateNtupleDColumn(1, "py");
  analysisManager->CreateNtupleDColumn(1, "pz");
  
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
 
 G4cout << "\n ===========================================================\n";
 G4cout << " per layer summary \n" << G4endl;
 G4cout << "\n ===========================================================\n";
 
 // Code to create (or get) analysis reader
 auto analysisReader = G4AnalysisReader::Instance();

 // Define a base file name
 analysisReader->SetFileName("output.root");

// Read ntuple
 G4int ntupleId = analysisReader->GetNtuple("Hits");
 G4String pLayerName;
 G4String pParticleName;
 G4int count_Rn222_shellPV = 0;
 G4int count_Rn222_shellPV_1 = 0;
 G4int count_Rn222_shellPV_2 = 0;
 G4int count_Rn222_shellPV_3 = 0;
 G4int count_Rn222_shellPV_4 = 0;
 G4int count_Rn222_world = 0;
 analysisReader->SetNtupleSColumn("layerName", pLayerName);
 analysisReader->SetNtupleSColumn("particleName", pParticleName);
 
 while ( analysisReader->GetNtupleRow()) {
     if(pLayerName == "shellPV" && pParticleName == "Rn222")
     {
     	count_Rn222_shellPV++;
     }
     else if(pLayerName == "shellPV_1" && pParticleName == "Rn222")
     {
     	count_Rn222_shellPV_1++;
     }
     else if(pLayerName == "shellPV_2" && pParticleName == "Rn222")
     {
     	count_Rn222_shellPV_2++;
     }
     else if(pLayerName == "shellPV_3" && pParticleName == "Rn222")
     {
     	count_Rn222_shellPV_3++;
     }
     else if(pLayerName == "shellPV_4" && pParticleName == "Rn222")
     {
     	count_Rn222_shellPV_4++;
     }
     
     else if(pLayerName == "World" && pParticleName == "Rn222")
     {
     	count_Rn222_world++;
     }
 }
 
 G4cout<<"radon count in shellPV: "<<count_Rn222_shellPV<<G4endl;
 G4cout<<"radon count in shellPV_1: "<<count_Rn222_shellPV_1<<G4endl;
 G4cout<<"radon count in shellPV_2: "<<count_Rn222_shellPV_2<<G4endl;
 G4cout<<"radon count in shellPV_3: "<<count_Rn222_shellPV_3<<G4endl;
 G4cout<<"radon count in shellPV_4: "<<count_Rn222_shellPV_4<<G4endl;
 G4cout<<"radon count in World: "<<count_Rn222_world<<G4endl;
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

