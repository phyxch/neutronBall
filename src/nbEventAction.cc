#include "nbEventAction.hh"

#include "nbRun.hh"
#include "nbHistoManager.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbEventAction::nbEventAction()
:G4UserEventAction(),
 fEdep1(0.), fEdep2(0.), fEdep3(0.), fEdep4(0.), fEdep5(0.), fEdep6(0.), 
 fWeight1(0.), fWeight2(0.), fWeight3(0.), fWeight4(0.), fWeight5(0.), fWeight6(0.),
 fTime0(-1*s)
{ 
    
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbEventAction::~nbEventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbEventAction::BeginOfEventAction(const G4Event*)
{
  fEdep1 = fEdep2 = fEdep3 = fEdep4 = fEdep5 = fEdep6 = 0.;
  fWeight1 = fWeight2 = fWeight3 = fWeight4 = fWeight5 = fWeight6 = 0.;
  fTime0 = -1*s;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbEventAction::AddEdep(G4int iVol, G4double edep,
                                      G4double time, G4double weight)
{
  // initialize t0
  if (fTime0 < 0.) fTime0 = time;
  
  // out of time window ?
  const G4double TimeWindow (1*microsecond);
  if (std::fabs(time - fTime0) > TimeWindow) return;
  
  if (iVol == 1) { fEdep1 += edep; fWeight1 += edep*weight;}  // layer 1
  if (iVol == 2) { fEdep2 += edep; fWeight2 += edep*weight;}  // layer 2
  if (iVol == 3) { fEdep3 += edep; fWeight3 += edep*weight;}  // layer 3
  if (iVol == 4) { fEdep4 += edep; fWeight4 += edep*weight;}  // layer 4
  if (iVol == 5) { fEdep5 += edep; fWeight5 += edep*weight;}  // layer 5
  if (iVol == 6) { fEdep6 += edep; fWeight6 += edep*weight;}  // layer 6 (world)
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbEventAction::EndOfEventAction(const G4Event*)
{
 // instance of analysis manager
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
 // total energy deposition
 G4double Etot = fEdep1 + fEdep2 + fEdep3 + fEdep4 + fEdep5 + fEdep6;
 // total weight
 G4double Wtot = (fWeight1 + fWeight2 + fWeight3 + fWeight4 + fWeight5 + fWeight6)/Etot;
 
 // pulse height in target
 //
 // if (fEdep1 > 0.) {
 //   fWeight1 /= fEdep1;
 //   analysisManager->FillH1(0, fEdep1, fWeight1);   
 // }
 
 // pulse height in detector
 //   
 // if (fEdep2 > 0.) {
 //   fWeight2 /= fEdep2;
 //   analysisManager->FillH1(1, fEdep2, fWeight2);
 // }
   
 // total
 //
 // analysisManager->FillH1(2, Etot, Wtot);
 
 // threshold in target and detector        
 // const G4double Threshold1(10*keV), Threshold2(10*keV);
  
 //coincidence, anti-coincidences 
 //  
 // G4bool coincidence       = ((fEdep1 >= Threshold1) && (fEdep2 >= Threshold2));
 // G4bool anti_coincidence1 = ((fEdep1 >= Threshold1) && (fEdep2 <  Threshold2));
 // G4bool anti_coincidence2 = ((fEdep1 <  Threshold1) && (fEdep2 >= Threshold2)); 

 // if (coincidence)       analysisManager->FillH1(3, fEdep2, fWeight2);
 // if (anti_coincidence1) analysisManager->FillH1(4, fEdep1, fWeight1);
 // if (anti_coincidence2) analysisManager->FillH1(5, fEdep2, fWeight2); 
 
 ////////////////////////////////////////////////////////////////////////////////

 // pass energies to Run
 //  
 nbRun* run = static_cast<nbRun*>(
            G4RunManager::GetRunManager()->GetNonConstCurrentRun());
             
 run->AddEdep (fEdep1, fEdep2, fEdep3, fEdep4, fEdep5, fEdep6);             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



