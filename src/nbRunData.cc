// Created on 10/13/2021
//
// Updated: 

#include "nbRunData.hh"
#include "nbAnalysis.hh"

#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRunData::nbRunData() 
 : G4Run(),
   fVolumeNames{ { "Absorber", "Gap" } }
{
  for ( auto& edep : fEdep ) { 
    edep = 0.; 
  }
  for ( auto& trackLength : fTrackLength ) {
    trackLength = 0.; 
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRunData::~nbRunData()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunData::FillPerEvent()
{
  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // accumulate statistic
  // in the order od the histograms, ntuple columns declarations
  G4int counter = 0;
  for ( auto edep : fEdep ) {
    analysisManager->FillH1(counter, edep);
    analysisManager->FillNtupleDColumn(counter++, edep);
  }
  for ( auto trackLength : fTrackLength ) {
    analysisManager->FillH1(counter, trackLength);
    analysisManager->FillNtupleDColumn(counter++, trackLength);
  }  
  analysisManager->AddNtupleRow();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRunData::Reset()
{ 
  for ( auto& edep : fEdep ) { 
    edep = 0.; 
  }
  for ( auto& trackLength : fTrackLength ) {
    trackLength = 0.; 
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
