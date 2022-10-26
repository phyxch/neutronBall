#include "nbDetectorMessenger.hh"
#include "nbDetectorConstruction.hh"

#include "G4UIdirectory.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

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

  
  detDir = new G4UIdirectory("/nb/det/mat/");
  layerMatCmd = new G4UIcmdWithAString("/nb/det/mat/setMaterial",this);
  layerMatCmd->SetGuidance("set material with material name and layer number.");
  layerMatCmd->SetGuidance("Type: Air/H2O/Al2O3/Fe2O3");
  layerMatCmd->SetParameterName("materialName<space>layerNumber",false);
  layerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // following commands set heights for each soil layer
  detDir = new G4UIdirectory("/nb/det/height/");
  layerHeightCmd = new G4UIcmdWithAString("/nb/det/height/setHeight",this);
  layerHeightCmd->SetGuidance("e.g. 55 <space> 3 means 55cm for 3rd layer");
  layerHeightCmd->SetGuidance("Let Hi be the height of each layer where i from 1 to 5");
  layerHeightCmd->SetGuidance("Then you must set Ti as: H1 > H2 > H3 > H4 > H5");
  layerHeightCmd->SetParameterName("height<space>layerNumber",false);
  layerHeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbDetectorMessenger::~nbDetectorMessenger()
{
  delete pHSetterCmdForH;

  delete layerMatCmd;
  delete layerHeightCmd;
  
  delete detDir;
  delete nbDir;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
   
  if (command == pHSetterCmdForH)
  { 
    // set update pH at runtime 
    fDetector->updatepH(pHSetterCmdForH->GetNewDoubleValue(newValue)); 
  }
  
  if (command == layerMatCmd)
  { 
    // split the string
    vector<string> row_values;
    split(newValue, ' ', row_values);
    
    G4String matName = (G4String) row_values[0];
    int layerNumber = std::stoi(row_values[1]);
    
    G4cout << "material name : " << matName << G4endl;
    G4cout << "layer number : " << layerNumber << G4endl;
     
    fDetector->setLayerMaterial(matName, layerNumber);
  }
  
  if (command == layerHeightCmd) 
  { 
    // split the string
    vector<string> row_values;
    split(newValue, ' ', row_values);
    
    G4double layerHeight = std::stod(row_values[0])*cm;
    int layerNumber = std::stoi(row_values[1]);
    
    G4cout << "layer height : " << layerHeight << G4endl;
    G4cout << "layer number : " << layerNumber << G4endl;
    
    fDetector->setLayerHeight(layerHeight, layerNumber);
  }
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......    

void nbDetectorMessenger::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}
