#include "TrackingMessenger.hh"
#include "TrackingAction.hh"

#include "G4UIcmdWithABool.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingMessenger::TrackingMessenger(TrackingAction* trackA)
:G4UImessenger(),
 fTrackingAction(trackA),fTrackingCmd(0),fTimeWindowCmd(0)
{
  fTrackingCmd = new G4UIcmdWithABool("/rdecay01/fullChain",this);
  fTrackingCmd->SetGuidance("allow full decay chain");
  fTrackingCmd->SetParameterName("flag",true);
  fTrackingCmd->SetDefaultValue(true);

 fTimeWindowCmd = new G4UIcommand("/rdecay01/timeWindow",this);
 fTimeWindowCmd->SetGuidance("set time window to survey activity per nuclide");
 fTimeWindowCmd->SetGuidance("  t1, delta_t");
 //    
 G4UIparameter* t1Prm = new G4UIparameter("t1",'d',false);
 t1Prm->SetGuidance("time_1");
 t1Prm->SetParameterRange("t1>=0.");
 fTimeWindowCmd->SetParameter(t1Prm);
 //
 G4UIparameter* unit1Prm = new G4UIparameter("unit1",'s',false);
 unit1Prm->SetGuidance("unit of t1");
 G4String unitList = G4UIcommand::UnitsList(G4UIcommand::CategoryOf("second"));
 unit1Prm->SetParameterCandidates(unitList);
 fTimeWindowCmd->SetParameter(unit1Prm);
 //
 G4UIparameter* dtPrm = new G4UIparameter("dt",'d',false);
 dtPrm->SetGuidance("delta_t");
 dtPrm->SetParameterRange("dt>0.");
 fTimeWindowCmd->SetParameter(dtPrm);
 //
 G4UIparameter* unit2Prm = new G4UIparameter("unit2",'s',false);
 unit2Prm->SetGuidance("unit of dt");
 unit2Prm->SetParameterCandidates(unitList);
 fTimeWindowCmd->SetParameter(unit2Prm);
 //
 fTimeWindowCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingMessenger::~TrackingMessenger()
{
  delete fTrackingCmd;
  delete fTimeWindowCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if (command == fTrackingCmd)
   { fTrackingAction->SetFullChain(fTrackingCmd->GetNewBoolValue(newValue));}

  if (command == fTimeWindowCmd)
   {
     G4double t1; G4double dt;
     G4String unt1, unt2;
     std::istringstream is(newValue);
     is >> t1 >> unt1 >> dt >> unt2;
     t1 *= G4UIcommand::ValueOf(unt1);
     dt *= G4UIcommand::ValueOf(unt2);
     fTrackingAction->SetTimeWindow (t1, dt);
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
