// code updated on 23 August, 2022
// fully revamped as per rdecay01; might need to add code from previous neutronBall nbEventAction.cc file
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nbEventAction.hh"
#include "nbHistoManager.hh"
#include "nbRun.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbEventAction::nbEventAction()
:G4UserEventAction(),
 fDecayChain(),fEvisTot(0.)
{
  // Set default print level 
  G4RunManager::GetRunManager()->SetPrintProgress(10000);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbEventAction::~nbEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbEventAction::BeginOfEventAction(const G4Event*)
{
 fDecayChain = " ";
 fEvisTot = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbEventAction::EndOfEventAction(const G4Event* evt)
{
 G4int evtNb = evt->GetEventID(); 
 G4int printProgress = G4RunManager::GetRunManager()->GetPrintProgress();
 //printing survey
 //
 if (evtNb%printProgress == 0) 
   G4cout << "    End of event. Decay chain:" << fDecayChain 
          << G4endl << G4endl;
 
 //total visible energy
 G4AnalysisManager::Instance()->FillH1(9, fEvisTot);
 nbRun* run = static_cast<nbRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
 run->EvisEvent(fEvisTot);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



