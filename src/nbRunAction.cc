// Created on 10/13/2021
// 

#include "nbRunAction.hh"
#include "nbRunData.hh"
#include "nbAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRunAction::nbRunAction()
 : G4UserRunAction()
{ 
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in nbAnalysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output
  
  // Book histograms, ntuple
  //
  
  // Creating histograms
  analysisManager->CreateH1("Eshell","Edep in shell", 100, 0., 100*MeV);
  //analysisManager->CreateH1("Egap","Edep in gap", 100, 0., 100*MeV);
  analysisManager->CreateH1("Lshell","trackL in shell", 100, 0., 1*m);
  //  analysisManager->CreateH1("Lgap","trackL in gap", 100, 0., 50*cm);

  // Creating ntuple
  //
  analysisManager->CreateNtuple("nb", "Edep and TrackL");
  analysisManager->CreateNtupleDColumn("Eshell");
  //  analysisManager->CreateNtupleDColumn("Egap");
  analysisManager->CreateNtupleDColumn("Lshell");
  //  analysisManager->CreateNtupleDColumn("Lgap");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRunAction::~nbRunAction()
{
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* nbRunAction::GenerateRun()
{
  return (new nbRunData);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "neutronBall";
  analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunAction::EndOfRunAction(const G4Run* /*aRun*/)
{
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl; 
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl; 
    }
    
    G4cout << " Eshell : mean = " 
       << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy") 
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;
    
    //    G4cout << " EGap : mean = " 
    //       << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy") 
    //       << " rms = " 
    //       << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Energy") << G4endl;
    
    G4cout << " Lshell : mean = " 
      << G4BestUnit(analysisManager->GetH1(1)->mean(), "Length") 
      << " rms = " 
      << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Length") << G4endl;

    //    G4cout << " LGap : mean = " 
    //      << G4BestUnit(analysisManager->GetH1(3)->mean(), "Length") 
    //      << " rms = " 
    //      << G4BestUnit(analysisManager->GetH1(3)->rms(),  "Length") << G4endl;
  }

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
