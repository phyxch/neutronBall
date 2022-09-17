//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nbSteppingAction.hh"

#include "nbDetectorConstruction.hh"
#include "nbRun.hh"
#include "nbEventAction.hh"
#include "nbHistoManager.hh"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbSteppingAction::nbSteppingAction(nbDetectorConstruction* det, nbEventAction* event)
: G4UserSteppingAction(), fDetector(det), fEventAction(event)
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbSteppingAction::~nbSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbSteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // instance of G4Run
  nbRun* run = static_cast<nbRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());    
  
  // instance of analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  //which volume ?
  //
  G4String volumeName = aStep->GetTrack()->GetVolume()->GetName(); // physical volume name
  G4int iVol = 0;
  if (volumeName == fDetector->getNameOfLayer1())   iVol = 1;
  if (volumeName == fDetector->getNameOfLayer2())   iVol = 2;
  if (volumeName == fDetector->getNameOfLayer3())   iVol = 3;
  if (volumeName == fDetector->getNameOfLayer4())   iVol = 4;
  if (volumeName == fDetector->getNameOfLayer5())   iVol = 5;
  if (volumeName == fDetector->getNameOfLayer6())   iVol = 6; // world

  // count processes
  // 
  const G4StepPoint* endPoint = aStep->GetPostStepPoint();
  const G4VProcess* process   = endPoint->GetProcessDefinedStep();
  run->CountProcesses(process, iVol);
  
  // energy deposit
  //
  G4double edepStep = aStep->GetTotalEnergyDeposit();
  if (edepStep <= 0.) return;
  G4double time   = aStep->GetPreStepPoint()->GetGlobalTime();
  G4double weight = aStep->GetPreStepPoint()->GetWeight();   
  fEventAction->AddEdep(iVol, edepStep, time, weight);
  
  //fill ntuple id = 2
  G4int id = 3;   
  analysisManager->FillNtupleDColumn(id,0, edepStep);
  analysisManager->FillNtupleDColumn(id,1, time/s);
  analysisManager->FillNtupleDColumn(id,2, weight);
  analysisManager->AddNtupleRow(id);      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

