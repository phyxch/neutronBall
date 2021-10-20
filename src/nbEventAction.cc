// Created on 10/13/2021
// 
// Updated on 10/20/2021
//   Added proper names for the detector
//

#include "nbEventAction.hh"
#include "nbRunData.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbEventAction::nbEventAction()
 : G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbEventAction::~nbEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbEventAction::PrintEventStatistics(
                              G4double shellEdep, G4double shellTrackLength) const
{
  // print event statistics
  G4cout
     << "   Shell: total energy: " 
     << std::setw(7) << G4BestUnit(shellEdep, "Energy")
     << "       total track length: " 
     << std::setw(7) << G4BestUnit(shellTrackLength, "Length")
     << G4endl;
    /*
     << "        Gap: total energy: " 
     << std::setw(7) << G4BestUnit(gapEdep, "Energy")
     << "       total track length: " 
     << std::setw(7) << G4BestUnit(gapTrackLength, "Length")
     << G4endl;
    */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbEventAction::BeginOfEventAction(const G4Event* /*event*/)
{  
  auto runData 
    = static_cast<nbRunData*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  runData->Reset();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbEventAction::EndOfEventAction(const G4Event* event)
{
  auto runData 
    = static_cast<nbRunData*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  runData->FillPerEvent();

  //print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     

    PrintEventStatistics(
      runData->GetEdep(kShell),
      runData->GetTrackLength(kShell));
  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
