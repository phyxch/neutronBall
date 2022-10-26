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

  // following commands set materials for each soil layer
  // set layer 1 material
  layer1MatCmd = new G4UIcmdWithAString("/nb/det/setMaterialL1",this);
  layer1MatCmd->SetGuidance("set material for layer 1");
  layer1MatCmd->SetGuidance("Type: Air/H2O/Al2O3/Fe2O3");
  layer1MatCmd->SetParameterName("layer1Mat",false);
  layer1MatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  // set layer 2 material
  layer2MatCmd = new G4UIcmdWithAString("/nb/det/setMaterialL2",this);
  layer2MatCmd->SetGuidance("set material for layer 2");
  layer2MatCmd->SetGuidance("Type: Air/H2O/Al2O3/Fe2O3");
  layer2MatCmd->SetParameterName("layer2Mat",false);
  layer2MatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  // set layer 3 material
  layer3MatCmd = new G4UIcmdWithAString("/nb/det/setMaterialL3",this);
  layer3MatCmd->SetGuidance("set material for layer 3");
  layer3MatCmd->SetGuidance("Type: Air/H2O/Al2O3/Fe2O3");
  layer3MatCmd->SetParameterName("layer3Mat",false);
  layer3MatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  // set layer 4 material
  layer4MatCmd = new G4UIcmdWithAString("/nb/det/setMaterialL4",this);
  layer4MatCmd->SetGuidance("set material for layer 4");
  layer4MatCmd->SetGuidance("Type: Air/H2O/Al2O3/Fe2O3");
  layer4MatCmd->SetParameterName("layer4Mat",false);
  layer4MatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  // set layer 5 material
  layer5MatCmd = new G4UIcmdWithAString("/nb/det/setMaterialL5",this);
  layer5MatCmd->SetGuidance("set material for layer 5");
  layer5MatCmd->SetGuidance("Type: Air/H2O/Al2O3/Fe2O3");
  layer5MatCmd->SetParameterName("layer5Mat",false);
  layer5MatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  // following commands set heights for each soil layer
  // layer 1 height largest layer
  layer1HeightCmd = new G4UIcmdWithADoubleAndUnit("/nb/det/setHeightL1",this);
  layer1HeightCmd->SetGuidance("Set height for layer 1. Let Hi be the height of each layer where i from 1 to 5");
  layer1HeightCmd->SetGuidance("Then you must set Ti as: H1 > H2 > H3 > H4 > H5");
  layer1HeightCmd->SetUnitCategory("Length");
  layer1HeightCmd->SetParameterName("layer1Height",false);
  layer1HeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  // layer 1 height largest layer
  layer2HeightCmd = new G4UIcmdWithADoubleAndUnit("/nb/det/setHeightL2",this);
  layer2HeightCmd->SetGuidance("Set height for layer 2. Let Hi be the height of each layer where i from 1 to 5");
  layer2HeightCmd->SetGuidance("Then you must set Ti as: H1 > H2 > H3 > H4 > H5");
  layer2HeightCmd->SetUnitCategory("Length");
  layer2HeightCmd->SetParameterName("layer2Height",false);
  layer2HeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  // layer 3 height largest layer
  layer3HeightCmd = new G4UIcmdWithADoubleAndUnit("/nb/det/setHeightL3",this);
  layer3HeightCmd->SetGuidance("Set height for layer 3. Let Hi be the height of each layer where i from 1 to 5");
  layer3HeightCmd->SetGuidance("Then you must set Ti as: H1 > H2 > H3 > H4 > H5");
  layer3HeightCmd->SetUnitCategory("Length");
  layer3HeightCmd->SetParameterName("layer3Height",false);
  layer3HeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  // layer 4 height largest layer
  layer4HeightCmd = new G4UIcmdWithADoubleAndUnit("/nb/det/setHeightL4",this);
  layer4HeightCmd->SetGuidance("Set height for layer 4. Let Hi be the height of each layer where i from 1 to 5");
  layer4HeightCmd->SetGuidance("Then you must set Ti as: H1 > H2 > H3 > H4 > H5");
  layer4HeightCmd->SetUnitCategory("Length");
  layer4HeightCmd->SetParameterName("layer4Height",false);
  layer4HeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  // layer 5 height largest layer
  layer5HeightCmd = new G4UIcmdWithADoubleAndUnit("/nb/det/setHeightL5",this);
  layer5HeightCmd->SetGuidance("Set height for layer 5. Let Hi be the height of each layer where i from 1 to 5");
  layer5HeightCmd->SetGuidance("Then you must set Ti as: H1 > H2 > H3 > H4 > H5");
  layer5HeightCmd->SetUnitCategory("Length");
  layer5HeightCmd->SetParameterName("layer5Height",false);
  layer5HeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbDetectorMessenger::~nbDetectorMessenger()
{
  delete pHSetterCmdForH;

  delete layer2MatCmd;
  delete layer3MatCmd;
  delete layer4MatCmd;
  delete layer5MatCmd;

  delete layer5HeightCmd;
  delete layer4HeightCmd;
  delete layer3HeightCmd;
  delete layer2HeightCmd;
  delete layer1HeightCmd;
  
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
  
  if (command == layer1MatCmd)
  { 
    fDetector->setLayer1Material(newValue);
  }
  
  if (command == layer2MatCmd)
  { 
    fDetector->setLayer2Material(newValue);
  }
  
  if (command == layer3MatCmd)
  { 
    fDetector->setLayer3Material(newValue);
  }
  
  if (command == layer4MatCmd)
  { 
    fDetector->setLayer4Material(newValue);
  }
  
  if (command == layer5MatCmd)
  { 
    fDetector->setLayer5Material(newValue);
  }
  
  if (command == layer1HeightCmd) 
  { 
    fDetector->setLayer1Height(layer1HeightCmd->GetNewDoubleValue(newValue));
  }
  
  if (command == layer2HeightCmd) 
  { 
    fDetector->setLayer2Height(layer2HeightCmd->GetNewDoubleValue(newValue));
  }
  
  if (command == layer3HeightCmd) 
  { 
    fDetector->setLayer3Height(layer3HeightCmd->GetNewDoubleValue(newValue));
  }
  
  if (command == layer4HeightCmd) 
  { 
    fDetector->setLayer4Height(layer4HeightCmd->GetNewDoubleValue(newValue));
  }
  
  if (command == layer5HeightCmd) 
  { 
    fDetector->setLayer5Height(layer5HeightCmd->GetNewDoubleValue(newValue));
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......    
