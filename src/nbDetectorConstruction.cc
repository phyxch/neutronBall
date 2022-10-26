// Neutron ball detector construction
//
// Created on 10/13/2021: hexc, Mayur, Tien, Weisen, Austin
// neutron ball detector is constructed as a shell with a predeinfed inner and outer radia.
//
// Updated on 10/20/2021: hexc, Mayur, Tien and Weisen
//    Add code for reading in the detector configuration file
//
// Updated on 11/10/2021: hexc, Mayur, Tien, Jarvious
//   Add soil material with vaiable water contents
//   Make multiple soil layers
//
// Updated on 22 Aug, 2022
// commented unused variables and added some more comments


// This file will make use nbDetectorConstruction.hh

#include "nbDetectorConstruction.hh"

#include "nbDetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4RunManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


// constructor to initialization values of shellPV, overlap checks 
// set data member values from config.txt file
nbDetectorConstruction::nbDetectorConstruction()
 : G4VUserDetectorConstruction(),
   shellPV_1(nullptr),
   fCheckOverlaps(true),
   fractionMassForH(0.),
   fractionMassForOH(0.),
   pHValue(4.0),
   fdetectorMessenger(0)
{
  // set the values for H and OH concentration by default
  pHValue = 4;
  fractionMassForH = (pHValue*100.00)/14.00;
  fractionMassForOH = 100.00-fractionMassForH;
  
  // call detector messenger
  fdetectorMessenger = new nbDetectorMessenger(this);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// destructor
nbDetectorConstruction::~nbDetectorConstruction()
{ 
    delete fdetectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// member function of header file
G4VPhysicalVolume* nbDetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // initialize the shell materials
  shellMaterial_1 = Air;
  shellMaterial_2 = Air;
  shellMaterial_3 = Air;
  shellMaterial_4 = Air;
  shellMaterial_5 = Air;
  
  // this is core material data map
  // all the materials you defined in DefineMaterials() should be
  // mentioned here
  StringToMaterialMapper = {
        {"Fe", Fe},
        {"Fe2O3", Fe2O3},
        {"Al2O3", Al2O3},
        {"Mn", Mn},
        {"Mn2O3", Mn2O3},
        {"Ra", Ra},
        {"Air", Air},
        {"H2O", H2O},
        {"OH",OH},
        {"MgO", MgO},
        {"TiO2", TiO2},
        {"CaO", CaO},
        {"pH", pH}
  };
  
  // read the config file for getting default radius of each layer
  G4String layerName;
  // read the data through configuration file
  std::ifstream infile ("mainConfig.txt");

  std::string line;

  while (std::getline(infile, line))
  {
    vector<string> row_values;

    split(line, ',', row_values);
    
    if(row_values[0] == "r1") r1 = stod(row_values[1])*cm;    
    else if(row_values[0] == "r2") r2 = stod(row_values[1])*cm; 
    else if(row_values[0] == "r3") r3 = stod(row_values[1])*cm; 
    else if(row_values[0] == "r4") r4 = stod(row_values[1])*cm; 
    else if(row_values[0] == "r5") r5 = stod(row_values[1])*cm; 
    else
    {
        if(row_values[0] == "layer1")
        {
            int flag = 0;
            for (const auto& itr: StringToMaterialMapper) 
            {
                if(itr.first == row_values[1])
                {
                    flag = 1;
                    auto materialName = itr.second;
                    shellMaterial_1 = materialName;
                    break;
                }
                
            }
            if(flag == 0)
            {
                G4cout<<row_values[1]<<" is not found in your datamap"<<G4endl;
                exit(0);
            }
        }
        else if(row_values[0] == "layer2")
        {
            int flag = 0;
            for (const auto& itr: StringToMaterialMapper) 
            {
                if(itr.first == row_values[1])
                {
                    flag = 1;
                    auto materialName = itr.second;
                    shellMaterial_2 = materialName;
                    // G4double fractionMass = stod(row_values[2]);
                    // chem_composition_2.insert({materialName, fractionMass*perCent});
                    break;
                }
                
            }
            if(flag == 0)
            {
                G4cout<<row_values[1]<<" is not found in your datamap"<<G4endl;
                exit(0);
            }
        }
        else if(row_values[0] == "layer3")
        {
            int flag = 0;
            for (const auto& itr: StringToMaterialMapper) 
            {
                if(itr.first == row_values[1])
                {
                    flag = 1;
                    auto materialName = itr.second;
                    shellMaterial_3 = materialName;
                    break;
                }
            }
            if(flag == 0)
            {
                G4cout<<row_values[1]<<" is not found in your datamap"<<G4endl;
                exit(0);
            }
        }
        else if(row_values[0] == "layer4")
        {
            int flag = 0;
            for (const auto& itr: StringToMaterialMapper) 
            {
                if(itr.first == row_values[1])
                {
                    flag = 1;
                    auto materialName = itr.second;
                    shellMaterial_4 = materialName;
                    break;
                }
            }
            if(flag == 0)
            {
                G4cout<<row_values[1]<<" is not found in your datamap"<<G4endl;
                exit(0);
            }
        }
        else if(row_values[0] == "layer5")
        {
            int flag = 0;
            for (const auto& itr: StringToMaterialMapper) 
            {
                if(itr.first == row_values[1])
                {
                    flag = 1;
                    G4cout<<itr.second<<G4endl;
                    auto materialName = itr.second;
                    shellMaterial_5 = materialName;
                    break;
                }
            }
            if(flag == 0)
            {
                G4cout<<row_values[1]<<" is not found in your datamap"<<G4endl;
                exit(0);
            }
        }
    }
  }

  G4cout << "r1 : " << r1 << G4endl;
  G4cout << "r2 : " << r2 << G4endl; 
  G4cout << "r3 : " << r3 << G4endl; 
  G4cout << "r4 : " << r4 << G4endl; 
  G4cout << "r5 : " << r5 << G4endl; 

  
  // fill soil layers
  //FillSoilLayersWithMaps();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorConstruction::DefineMaterials()
{   
  // Lead material defined using NIST Manager
  nistManager = G4NistManager::Instance();
  nistManager->SetVerbose(1);
  
  //
  // create all your materials in this function
  //
  
  // define pure nist materials
  H = nistManager->FindOrBuildMaterial("G4_H");
  Fe = nistManager->FindOrBuildMaterial("G4_Fe");
  Mn = nistManager->FindOrBuildMaterial("G4_Mn");
  Ra = nistManager->FindOrBuildMaterial("G4_Ra");
 
  // define nist compounds
  H2O  = nistManager->FindOrBuildMaterial("G4_WATER");
  H2O->GetIonisation()->SetMeanExcitationEnergy(75.0*eV); // you may or may not include this line, overwrite computed meanExcitationEnergy with ICRU recommended value 
  
  Air = nistManager->FindOrBuildMaterial("G4_AIR");
  SiO2 = nistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  Al2O3 = nistManager->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
  Fe2O3 = nistManager->FindOrBuildMaterial("G4_FERRIC_OXIDE");
  CaO = nistManager->FindOrBuildMaterial("G4_CALCIUM_OXIDE");
  MgO = nistManager->FindOrBuildMaterial("G4_MAGNESIUM_OXIDE");
  TiO2 = nistManager->FindOrBuildMaterial("G4_TITANIUM_DIOXIDE");
 
  // define elements
  elO = new G4Element("Oxygen"  ,symbol="O" , z= 8., a= 16.00*g/mole);
  elH = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);
  elC  = nistManager->FindOrBuildElement("C");
  elN  = nistManager->FindOrBuildElement("N");
  elMn = nistManager->FindOrBuildElement("Mn");
  
  Mn2O3 = new G4Material("ManganeseOxide", density = 4.5*g/cm3, ncomponents = 2);
  Mn2O3->AddElement(elMn, natoms=2);
  Mn2O3->AddElement(elO, natoms=3);
  
  //////////////////////////// pH section ////////////////////////////

  // create OH for material
  OH = new G4Material("Hydroxide", density = 1.33*g/cm3, ncomponents = 2);
  OH->AddElement(elO, natoms=1);
  OH->AddElement(elH, natoms=1);
  
  // pH material to add in soil
  pH = new G4Material("pH", density = 1.33*g/cm3, ncomponents = 2);
  pH->AddMaterial(H, fractionmass=fractionMassForH*perCent);
  pH->AddMaterial(OH, fractionmass=fractionMassForOH*perCent);
  
  // G4cout << "H concentration = " << fractionMassForH << G4endl;
  // G4cout << "OH concentration = " << fractionMassForOH << G4endl;
  
  //////////////////////////// end pH section ////////////////////////////
  
  // organic material
  // We assume organic soil components have 1.33 g/cm3 density. This number should be updated with
  // specifric soil type simulation. 4/12/2019
  OrganicMat = new G4Material("Organic", density = 1.33*g/cm3, ncomponents = 4);
  OrganicMat->AddElement(elC, natoms=50);
  OrganicMat->AddElement(elO, natoms=42);
  OrganicMat->AddElement(elH, natoms=5);
  OrganicMat->AddElement(elN, natoms=3); 
  
  // Vacuum
  defaultMaterial = new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Liquid argon material
  // new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
  //        // The argon by NIST Manager is a gas with a different density
  // Print materials
  // G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* nbDetectorConstruction::DefineVolumes()
{  
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
 
  // Geometry parameters  
  
  // World
  //
  auto worldSizeXY = 2.5 * r1;
  // auto worldSizeZ  = worldSizeXY; 
  
  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeXY/2, worldSizeXY/2, worldSizeXY/2); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //                               
  // Make neutron ball detector (i.e., multiple layers)
  //

  // Define the angles for spheres
  G4double startAnglePhi = 0.0*deg;
  G4double spanningAnglePhi = 360.0*deg;
  G4double startAngleTheta = 0.0*deg;
  G4double spanningAngleTheta = 180.0*deg; //90

  // Outer shell
  auto solidShell_1 = new G4Sphere("Shell", 0, r1,
			       startAnglePhi, spanningAnglePhi, 
			       startAngleTheta, spanningAngleTheta);  
  shellLV_1
    = new G4LogicalVolume(
                 solidShell_1,     // its solid
                 shellMaterial_1,  // its material
                 "shellLV_1");   // its name
                                   
  shellPV_1 = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 shellLV_1,          // its logical volume                         
                 "shellPV_1",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

  // 1st layer (A/Ap 0-6 inches)
  auto solidShell_2 = new G4Sphere("Shell_1", 0, r2,
				 startAnglePhi, spanningAnglePhi, 
				 startAngleTheta, spanningAngleTheta);
  
  shellLV_2
    = new G4LogicalVolume(
                 solidShell_2,     // its solid
                 shellMaterial_2,  // its material
                 "shellLV_2");   // its name
                                   
  shellPV_2 = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 shellLV_2,          // its logical volume                         
                 "shellPV_2",    // its name
                 shellLV_1,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  // 2nd layer (E 6-9 inches - 100-9)
  auto solidShell_3 = new G4Sphere("Shell_2", 0, r3,
				   startAnglePhi, spanningAnglePhi, 
				   startAngleTheta, spanningAngleTheta);
  
  shellLV_3
    = new G4LogicalVolume(
			  solidShell_3,     // its solid
			  shellMaterial_3,  // its material
			  "shellLV_3");   // its name
  
  shellPV_3 = new G4PVPlacement(
				0,                // no rotation
				G4ThreeVector(),  // at (0,0,0)
				shellLV_3,          // its logical volume                         
				"shellPV_3",    // its name
				shellLV_2,          // its mother  volume
				false,            // no boolean operation
				0,                // copy number
				fCheckOverlaps);  // checking overlaps 
  
  
  // 3rd layer (Be, Bt, Bc 9-53 inches - 100-53 = 47)
  auto solidShell_4 = new G4Sphere("Shell_3", 0, r4,
				   startAnglePhi, spanningAnglePhi, 
				   startAngleTheta, spanningAngleTheta);
  
  shellLV_4
    = new G4LogicalVolume(
			  solidShell_4,     // its solid
			  shellMaterial_4,  // its material
			  "shellLV_4");   // its name
  
  shellPV_4 = new G4PVPlacement(
				0,                // no rotation
				G4ThreeVector(),  // at (0,0,0)
				shellLV_4,          // its logical volume                         
				"shellPV_4",    // its name
				shellLV_3,          // its mother  volume
				false,            // no boolean operation
				0,                // copy number
				fCheckOverlaps);  // checking overlaps 
  
  
  // 4th layer (C 53-80 inches - 100-80 = 20)
  auto solidShell_5 = new G4Sphere("Shell_4", 0, r5,
                                   startAnglePhi, spanningAnglePhi, 
                                   startAngleTheta, spanningAngleTheta);
  
  shellLV_5
    = new G4LogicalVolume(
                          solidShell_5,     // its solid
                          shellMaterial_5,  // its material
                          "shellLV_5");   // its name
  
  shellPV_5 = new G4PVPlacement(
                                0,                // no rotation
                                G4ThreeVector(),  // at (0,0,0)
                                shellLV_5,          // its logical volume
                                "shellPV_5",    // its name
                                shellLV_4,          // its mother  volume
                                false,            // no boolean operation
                                0,                // copy number
                                fCheckOverlaps);  // checking overlaps

  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto simpleShellVisAtt= new G4VisAttributes(G4Colour(0.3,0.4,0.5));
  simpleShellVisAtt->SetVisibility(true);
  shellLV_1->SetVisAttributes(simpleShellVisAtt);

  auto simpleShellVisAtt_1= new G4VisAttributes(G4Colour(0.3,0.4,0.1));
  simpleShellVisAtt_1->SetVisibility(true);
  shellLV_2->SetVisAttributes(simpleShellVisAtt_1);

  auto simpleShellVisAtt_2= new G4VisAttributes(G4Colour(0.3,0.3,0.2));
  simpleShellVisAtt_2->SetVisibility(true);
  shellLV_3->SetVisAttributes(simpleShellVisAtt_2);

  auto simpleShellVisAtt_3= new G4VisAttributes(G4Colour(0.3,0.1,0.2));
  simpleShellVisAtt_3->SetVisibility(true);
  shellLV_4->SetVisAttributes(simpleShellVisAtt_3);
  
  // Print Layerwise Materials 
  PrintLayersMaterials();

  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorConstruction::PrintLayersMaterials()
{
  G4cout << "\t******* MATERIALS OF EACH LAYER *******" << G4endl;
  G4cout << " layer 1 material : " << shellLV_1->GetMaterial()->GetName() << G4endl; 
  G4cout << " layer 2 material : " << shellLV_2->GetMaterial()->GetName() << G4endl; 
  G4cout << " layer 3 material : " << shellLV_3->GetMaterial()->GetName() << G4endl; 
  G4cout << " layer 4 material : " << shellLV_4->GetMaterial()->GetName() << G4endl; 
  G4cout << " layer 5 material : " << shellLV_5->GetMaterial()->GetName() << G4endl; 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorConstruction::updatepH(G4double value)
{
    pHValue = value;
    // write code to update value of
    // fractionMassForH and fractionMassForOH 
    fractionMassForH = ((pHValue*100)/14);
    fractionMassForOH = (100.00 - fractionMassForH);
    
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorConstruction::setLayerMaterial(G4String matName, int layerNumber) 
{
    int flag = 0;
    for (const auto& itr: StringToMaterialMapper) 
    {
        if(itr.first == matName)
        {
            flag = 1;
            auto materialName = itr.second;
            
            // assign this material to proper layer
            if(layerNumber == 1)
            {
                shellMaterial_1 = materialName;
                if(shellLV_1) { shellLV_1->SetMaterial(shellMaterial_1); }
                G4RunManager::GetRunManager()->PhysicsHasBeenModified();
                G4cout<<"layer 1 is set to material: "<<matName<<G4endl;
                PrintLayersMaterials();
            }
            
            else if(layerNumber == 2)
            {
                shellMaterial_2 = materialName;
                if(shellLV_2) { shellLV_2->SetMaterial(shellMaterial_2); }
                G4RunManager::GetRunManager()->PhysicsHasBeenModified();
                G4cout<<"layer 2 is set to material: "<<matName<<G4endl;
                PrintLayersMaterials();
            }
            
            else if(layerNumber == 3)
            {
                shellMaterial_3 = materialName;
                if(shellLV_3) { shellLV_3->SetMaterial(shellMaterial_3); }
                G4RunManager::GetRunManager()->PhysicsHasBeenModified();
                G4cout<<"layer 3 is set to material: "<<matName<<G4endl;
                PrintLayersMaterials();
            }
            
            else if(layerNumber == 4)
            {
                shellMaterial_4 = materialName;
                if(shellLV_4) { shellLV_4->SetMaterial(shellMaterial_4); }
                G4RunManager::GetRunManager()->PhysicsHasBeenModified();
                G4cout<<"layer 4 is set to material: "<<matName<<G4endl;
                PrintLayersMaterials();
            }
            
            else if(layerNumber == 5)
            {
                shellMaterial_5 = materialName;
                if(shellLV_5) { shellLV_5->SetMaterial(shellMaterial_5); }
                G4RunManager::GetRunManager()->PhysicsHasBeenModified();
                G4cout<<"layer 5 is set to material: "<<matName<<G4endl;
                PrintLayersMaterials();
            }
            
            else 
            {
                G4cout << "layerNumber : " << layerNumber << "is invalid" << G4endl;
                exit(0);
            }
            
            
            G4RunManager::GetRunManager()->PhysicsHasBeenModified();
            PrintLayersMaterials();
            flag = 1;
            break;
        }
    }
    if(flag == 0)
    {
        G4cout<<matName<<" is not found in your datamap"<<G4endl;
        PrintLayersMaterials();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorConstruction::setLayerHeight(G4double height, int layerNumber) 
{
    if(layerNumber == 1)
    {
        r1 = height;
        G4cout << "r1 is changed to " << r1 << G4endl;
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }
    
    else if(layerNumber == 2)
    {
        r2 = height;
        G4cout << "r2 is changed to " << r1 << G4endl;
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }
    
    else if(layerNumber == 3)
    {
        r3 = height;
        G4cout << "r3 is changed to " << r1 << G4endl;
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }
    
    else if(layerNumber == 4)
    {
        r4 = height;
        G4cout << "r4 is changed to " << r1 << G4endl;
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }
    
    else if(layerNumber == 5)
    {
        r5 = height;
        G4cout << "r5 is changed to " << r1 << G4endl;
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }
    
    else
    {
        G4cout << "invalid layerNumber" << G4endl;
    }
    
    G4cout << "r1 : " << r1 << G4endl;
    G4cout << "r2 : " << r2 << G4endl;
    G4cout << "r3 : " << r3 << G4endl;
    G4cout << "r4 : " << r4 << G4endl;
    G4cout << "r5 : " << r5 << G4endl;
}

// void nbDetectorConstruction::setLayer1Height(G4double height) 
// {
//     r1 = height;
//     G4cout << "r1 is changed to " << r1 << G4endl;
//     G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// void nbDetectorConstruction::setLayer2Height(G4double height) 
// {
//     r2 = height;
//     G4cout << "r2 is changed to " << r2 << G4endl;
//     G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// void nbDetectorConstruction::setLayer3Height(G4double height) 
// {
//     r3 = height;
//     G4cout << "r3 is changed to " << r3 << G4endl;
//     G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// void nbDetectorConstruction::setLayer4Height(G4double height) 
// {
//     r4 = height;
//     G4cout << "r4 is changed to " << r4 << G4endl;
//     G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// void nbDetectorConstruction::setLayer5Height(G4double height) 
// {
//     r5 = height;
//     G4cout << "r5 is changed to " << r5 << G4endl;
//     G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4String nbDetectorConstruction::getNameOfLayer1()
{
    return "shellPV_1"; // this is first layer beneath the surface
}

G4String nbDetectorConstruction::getNameOfLayer2()
{
    return "shellPV_2"; // the second layer below that
}

G4String nbDetectorConstruction::getNameOfLayer3()
{
    return "shellPV_3"; // the third layer below that
}

G4String nbDetectorConstruction::getNameOfLayer4()
{
    return "shellPV_4"; // the fourth layer below that
}

G4String nbDetectorConstruction::getNameOfLayer5()
{
    return "shellPV_5"; // the fifth layer below that
}

G4String nbDetectorConstruction::getWorld()
{
    return "World"; // return world
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorConstruction::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorConstruction::FillSoilLayersWithMaps()
{
    // create soil layers
  // Based on: http://gfnun.unal.edu.co/fileadmin/content/gruposdeinvestigacion/fisicanuclear/Tesis/DanielAndrade_TG.pdf
  // layer 1
  // soilOne = new G4Material("DrySoil", density = 0.6*g/cm3, ncomponents=chem_composition_1.size());
  // for (it = chem_composition_1.begin(); it != chem_composition_1.end(); it++) {
  //       soilOne->AddMaterial(it->first, fractionmass=it->second);
  // }
  
  // layer 2
  // 10% moisture content
  // soilOne10W = new G4Material("DrySoil10W", density = 0.6*g/cm3, ncomponents=chem_composition_2.size());
  // for (it = chem_composition_2.begin(); it != chem_composition_2.end(); it++) {
  //       soilOne10W->AddMaterial(it->first, fractionmass=it->second);
  // }
  
  
  // layer 3
  // 20% moisture content. Need new density value?
  // soilOne20W = new G4Material("DrySoil20W", density = 0.6*g/cm3, ncomponents=chem_composition_3.size());
  // for (it = chem_composition_3.begin(); it != chem_composition_3.end(); it++) {
  //       soilOne20W->AddMaterial(it->first, fractionmass=it->second);
  // }
  
  // layer 4
  // 30% moisture content. Need new density value?
  // soilOne30W = new G4Material("DrySoil30W", density = 0.6*g/cm3, ncomponents=chem_composition_4.size());
  // for (it = chem_composition_4.begin(); it != chem_composition_4.end(); it++) {
  //       soilOne30W->AddMaterial(it->first, fractionmass=it->second);
  // }
    
  // layer 5 (inner most)
  // 40% moisture content. Need new density value?
  // soilOne40W = new G4Material("DrySoil40W", density = 0.6*g/cm3, ncomponents=chem_composition_5.size());
  // for (it = chem_composition_5.begin(); it != chem_composition_5.end(); it++) {
  //       soilOne40W->AddMaterial(it->first, fractionmass=it->second);
  // }
}
