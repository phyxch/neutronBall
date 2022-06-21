#include "EventAction.hh"
#include "HistoManager.hh"
#include "Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
:G4UserEventAction(),
 fDecayChain(),fEvisTot(0.)
{
  // Set default print level 
  G4RunManager::GetRunManager()->SetPrintProgress(10000);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
 fDecayChain = " ";
 fEvisTot = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
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
 Run* run 
  = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
 run->EvisEvent(fEvisTot);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


