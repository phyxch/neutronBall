#include "nbDetectorMessenger.hh"
#include "nbDetectorConstruction.hh"

#include "G4UIdirectory.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbDetectorMessenger::nbDetectorMessenger(nbDetectorConstruction* det)
:fDetector(det)
{ 
  // create ui directory
  nbDir = new G4UIdirectory("/nb/");
  nbDir->SetGuidance("UI commands for this detector");
  
  detDir = new G4UIdirectory("/nb/det/");
  detDir->SetGuidance("detector control");
  
  detDir = new G4UIdirectory("/nb/det/pH/");
  detDir->SetGuidance("pH control");
  
  
  // set H fractionmass for pH
  pHSetterCmdForH = new G4UIcmdWithADouble("/nb/det/pH/setH",this);  
  pHSetterCmdForH->SetGuidance("define H fractionmass for pH");
  pHSetterCmdForH->SetGuidance("the default is pH = 4 means H concentratio = (pH * 100)/14");
  pHSetterCmdForH->SetParameterName("pH",false);    
  pHSetterCmdForH->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbDetectorMessenger::~nbDetectorMessenger()
{
  delete pHSetterCmdForH;
  delete detDir;
  delete nbDir;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
   
  if(command == pHSetterCmdForH)
  { 
    // set update pH at runtime 
    fDetector->updatepH(pHSetterCmdForH->GetNewDoubleValue(newValue)); 
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......    
