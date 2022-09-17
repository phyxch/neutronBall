 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nbHistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbHistoManager::nbHistoManager()
  : fFileName("rdecay02")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbHistoManager::~nbHistoManager()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbHistoManager::Book()
{
  // Create or get analysis manager
  // G4AnalysisManager* analysis = G4AnalysisManager::Instance();
  // 
  // analysis->SetDefaultFileType("root");
  // analysis->SetFileName(fFileName);
  // analysis->SetVerboseLevel(1);
  // analysis->SetActivation(true);     //enable inactivation of histos, nTuples
    
  // nTuples
  //
  ////analysis->SetNtupleDirectoryName("ntuple");
  ////analysis->SetFirstNtupleId(1);
  //       
  // analysis->CreateNtuple("T1", "Emitted Particles");
  // analysis->CreateNtupleDColumn("PID");       //column 0
  // analysis->CreateNtupleDColumn("Energy");    //column 1
  // analysis->CreateNtupleDColumn("Time");      //column 2
  // analysis->CreateNtupleDColumn("Weight");    //column 3
  // analysis->FinishNtuple();
  // 
  // analysis->CreateNtuple("T2", "RadioIsotopes");
  // analysis->CreateNtupleDColumn("PID");       //column 0
  // analysis->CreateNtupleDColumn("Time");      //column 1
  // analysis->CreateNtupleDColumn("Weight");    //column 2
  // analysis->FinishNtuple();
  // 
  // analysis->CreateNtuple("T3", "Energy depositions");
  // analysis->CreateNtupleDColumn("Energy");    //column 0
  // analysis->CreateNtupleDColumn("Time");      //column 1
  // analysis->CreateNtupleDColumn("Weight");    //column 2
  // analysis->FinishNtuple();
  // 
  // analysis->CreateNtuple("RDecayProducts", "All Products of RDecay");
  // analysis->CreateNtupleDColumn("PID");       //column 0
  // analysis->CreateNtupleDColumn("Z");         //column 1
  // analysis->CreateNtupleDColumn("A");         //column 2    
  // analysis->CreateNtupleDColumn("Energy");    //column 3
  // analysis->CreateNtupleDColumn("Time");      //column 4
  // analysis->CreateNtupleDColumn("Weight");    //column 5
  // analysis->FinishNtuple();
  // 
  // analysis->SetNtupleActivation(false);          
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

