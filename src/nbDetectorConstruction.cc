// Neutron ball detector construction
//
// Created on 10/13/2021: hexc, Mayur, Tien, Weisen, Austin
// neutron ball detector is constructed as a shell with a predeinfed inner and outer radia.
//
// Updated on 10/20/2021: hexc, Mayur, Tien and Weisen
//    Add code for reading in the detector configuration file

#include "nbDetectorConstruction.hh"

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

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* nbDetectorConstruction::fMagFieldMessenger = nullptr; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbDetectorConstruction::nbDetectorConstruction()
 : G4VUserDetectorConstruction(),
   shellPV(nullptr),
   fCheckOverlaps(true)
{

  std::string line;
  char varName[10];
  G4double inputVal[3];
  std::ifstream nbConfig("config.txt");
  G4int i = 0;
  if (nbConfig.is_open())
    {
      while (getline(nbConfig, line))
	{
	  char* token = strtok((char *)line.c_str(), ",\t");
	  int num = 0;
	  while (token != NULL)
	    {
	      G4cout << token << G4endl;
	      if (num++ != 0) inputVal[i++] = atoi(token);
	      token = strtok(NULL,",\t");
		/*
		  G4cout << line << G4endl;
		  strtok(line.c_str(), " ,\t");
		  inputVal[i++] = atoi(strtok(NULL, " ,\t"));
		*/
	    }
	}
    }
  
  inner_r = inputVal[0]*mm;
  outer_r = inputVal[1]*mm;
  matType = (G4int)inputVal[2];
  G4cout << "inner_r: " << inner_r << "   outer_r: " << outer_r << "   matType: " << matType << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbDetectorConstruction::~nbDetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* nbDetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Pb");
  nistManager->FindOrBuildMaterial("G4_AIR");
  
  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* nbDetectorConstruction::DefineVolumes()
{
  // Geometry parameters

  auto worldSizeXY = 1.5 * outer_r;
  auto worldSizeZ  = worldSizeXY; 
  
  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  if (matType == 1)
    {
      shellMaterial = G4Material::GetMaterial("G4_Pb");
    } else if (matType == 2)
    {
      shellMaterial = G4Material::GetMaterial("G4_AIR");
    } else if (matType == 3)
    {
      shellMaterial = G4Material::GetMaterial("liquidArgon");
    } else {
    G4cout << "Material is NOT defined! " << G4endl;
    exit(1);
  }
 
  if ( ! defaultMaterial || ! shellMaterial  ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("nbDetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }  
   
  //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeXY/2, worldSizeXY/2, worldSizeZ/2); // its size
                         
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
  // Make neutron ball detector (i.e., a shell)
  //

  // Define the angles for spheres
  G4double startAnglePhi = 0.0*deg;
  G4double spanningAnglePhi = 360.0*deg;
  G4double startAngleTheta = 0.0*deg;
  G4double spanningAngleTheta = 180.0*deg; //90

  auto solidShell = new G4Sphere("Shell", inner_r, outer_r,
			       startAnglePhi, spanningAnglePhi, 
			       startAngleTheta, spanningAngleTheta);
  
  auto shellLV
    = new G4LogicalVolume(
                 solidShell,     // its solid
                 shellMaterial,  // its material
                 "shellLV");   // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 shellLV,          // its logical volume                         
                 "shellPV",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //
  // print parameters
  //
  G4cout
    << G4endl 
    << "------------------------------------------------------------" << G4endl
    << "---> The shell dimension:  inner_r " << inner_r  << "   outer_r " 
    << outer_r  << G4endl
    << "------------------------------------------------------------" << G4endl;
  
  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto simpleShellVisAtt= new G4VisAttributes(G4Colour(0.3,0.4,0.5));
  simpleShellVisAtt->SetVisibility(true);
  shellLV->SetVisAttributes(simpleShellVisAtt);

  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbDetectorConstruction::ConstructSDandField()
{ 
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
