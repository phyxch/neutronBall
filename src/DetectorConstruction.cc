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


#include "DetectorConstruction.hh"

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

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   shellPV(nullptr),
   fCheckOverlaps(true)
{  
  //////////////////////////////////////////// CHANGE IF REQUIRED //////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /**/ inner_r = 1.0;                                                                                           /**/
  /**/ outer_r = 30.0;                                                                                          /**/
  /**/ matType = 7;                                                                                             /**/
  /**/ matType_1 = 6;                                                                                           /**/
  /**/ matType_2 = 5;                                                                                           /**/
  /**/ matType_3 = 4;                                                                                           /**/
  /**/ G4cout << "inner_r: " << inner_r << "   outer_r: " << outer_r << "   matType: " << matType << G4endl;    /**/
  /**/ G4cout << "inner_r: " << inner_r << "   outer_r: " << outer_r << "   matType_1: " << matType_1 << G4endl;/**/
  /**/ G4cout << "inner_r: " << inner_r << "   outer_r: " << outer_r << "   matType_2: " << matType_2 << G4endl;/**/
  /**/ G4cout << "inner_r: " << inner_r << "   outer_r: " << outer_r << "   matType_3: " << matType_3 << G4endl;/**/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
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

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{

  G4String symbol;             //a=mass of a mole;
  G4double a, z, density;      //z=mean number of protons;  
  G4int iz, n;                 //iz=number of protons  in an isotope; 
  // n=number of nucleons in an isotope;
  
  G4int ncomponents, natoms;
  G4double abundance, fractionmass;
  
  //
  // define Elements
  //
  
  G4Element* H  = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);
  G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z= 6., a= 12.01*g/mole);
  G4Element* N  = new G4Element("Nitrogen",symbol="N" , z= 7., a= 14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen"  ,symbol="O" , z= 8., a= 16.00*g/mole);
  G4Element* Mg = new G4Element("Magnesium", symbol="Mg", z = 12, a=24.305*g/mole);
  G4Element* Al = new G4Element("Aluminum", symbol="Al", z = 13, a=26.982*g/mole);
  G4Element* Si = new G4Element("Silicon",symbol="Si" , z= 14., a= 28.09*g/mole);
  G4Element* Ca = new G4Element("Calcium",symbol="Ca" , z= 20., a= 40.078*g/mole);
  G4Element* Ti = new G4Element("Titanium", symbol="Ti", z = 22, a=47.867*g/mole);
  G4Element* Fe = new G4Element("Iron",symbol="Fe" , z= 26., a= 55.845*g/mole);
  G4Element* W = new G4Element("Tungston",symbol="W" , z= 74., a= 183.85*g/mole);
  
  // Add soil materials
  auto H2O = new G4Material("Water", density= 0.998*g/cm3, ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  // overwrite computed meanExcitationEnergy with ICRU recommended value 
  H2O->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);
  
  auto SiO2 = new G4Material("quartz",density= 2.200*g/cm3, ncomponents=2);
  SiO2->AddElement(Si, natoms=1);
  SiO2->AddElement(O , natoms=2);
  
  auto Al2O3 = new G4Material("AlOxide", density = 3.95*g/cm3, ncomponents = 2);
  Al2O3 -> AddElement(Al, natoms=2);
  Al2O3 -> AddElement(O, natoms=3);
  
  auto Fe2O3 = new G4Material("FeOxide", density = 5.24*g/cm3, ncomponents = 2);
  Fe2O3 -> AddElement(Fe, natoms=2);
  Fe2O3 -> AddElement(O, natoms=3);

  auto CaO = new G4Material("CaOxide", density = 3.34*g/cm3, ncomponents = 2);
  CaO -> AddElement(Ca, natoms=1);
  CaO -> AddElement(O, natoms=1);

  auto MgO = new G4Material("MgOxide", density = 3.54*g/cm3, ncomponents = 2);
  MgO -> AddElement(Mg, natoms=1);
  MgO -> AddElement(O, natoms=1);
    
  auto TiO2 = new G4Material("TiOxide", density = 4.23*g/cm3, ncomponents = 2);
  TiO2 -> AddElement(Ti, natoms=1);
  TiO2 -> AddElement(O, natoms=2);

  // We assume organic soil components have 1.33 g/cm3 density. This number should be updated with
  // specifric soil type simulation. 4/12/2019
  G4Material* OrganicMat = new G4Material("Organic", density = 1.33*g/cm3, ncomponents = 4);
  OrganicMat -> AddElement(C, natoms=50);
  OrganicMat -> AddElement(O, natoms=42);
  OrganicMat -> AddElement(H, natoms=5);
  OrganicMat -> AddElement(N, natoms=3);

  // Define soil material
  // Based on: http://gfnun.unal.edu.co/fileadmin/content/gruposdeinvestigacion/fisicanuclear/Tesis/DanielAndrade_TG.pdf
  auto soilOne = new G4Material("DrySoil", density = 0.6*g/cm3, ncomponents=7);
  soilOne->AddMaterial(SiO2, fractionmass=61.3*perCent);
  soilOne->AddMaterial(Al2O3, fractionmass=13.0*perCent);
  soilOne->AddMaterial(Fe2O3, fractionmass=2.5*perCent);
  soilOne->AddMaterial(CaO, fractionmass=1.6*perCent);
  soilOne->AddMaterial(MgO, fractionmass=0.7*perCent);
  soilOne->AddMaterial(TiO2, fractionmass=0.6*perCent);
  soilOne->AddMaterial(OrganicMat, fractionmass=20.3*perCent);

  // 10% moisture content
  auto soilOne10W = new G4Material("DrySoil10W", density = 0.6*g/cm3, ncomponents=8);
  soilOne10W->AddMaterial(SiO2, fractionmass=55.17*perCent);
  soilOne10W->AddMaterial(Al2O3, fractionmass=11.7*perCent);
  soilOne10W->AddMaterial(Fe2O3, fractionmass=2.25*perCent);
  soilOne10W->AddMaterial(CaO, fractionmass=1.44*perCent);
  soilOne10W->AddMaterial(MgO, fractionmass=0.63*perCent);
  soilOne10W->AddMaterial(TiO2, fractionmass=0.54*perCent);
  soilOne10W->AddMaterial(OrganicMat, fractionmass=18.27*perCent);
  soilOne10W->AddMaterial(H2O, fractionmass=10.0*perCent);

  // 20% moisture content. Need new density value?
  auto soilOne20W = new G4Material("DrySoil20W", density = 0.6*g/cm3, ncomponents=8);
  soilOne20W->AddMaterial(SiO2, fractionmass=49.04*perCent);
  soilOne20W->AddMaterial(Al2O3, fractionmass=10.4*perCent);
  soilOne20W->AddMaterial(Fe2O3, fractionmass=2.0*perCent);
  soilOne20W->AddMaterial(CaO, fractionmass=1.28*perCent);
  soilOne20W->AddMaterial(MgO, fractionmass=0.56*perCent);
  soilOne20W->AddMaterial(TiO2, fractionmass=0.48*perCent);
  soilOne20W->AddMaterial(OrganicMat, fractionmass=16.24*perCent);
  soilOne20W->AddMaterial(H2O, fractionmass=20.0*perCent);

  // 30% moisture content. Need new density value?
  auto soilOne30W = new G4Material("DrySoil30W", density = 0.6*g/cm3, ncomponents=8);
  soilOne30W->AddMaterial(SiO2, fractionmass=42.91*perCent);
  soilOne30W->AddMaterial(Al2O3, fractionmass=9.1*perCent);
  soilOne30W->AddMaterial(Fe2O3, fractionmass=1.75*perCent);
  soilOne30W->AddMaterial(CaO, fractionmass=1.12*perCent);
  soilOne30W->AddMaterial(MgO, fractionmass=0.49*perCent);
  soilOne30W->AddMaterial(TiO2, fractionmass=0.42*perCent);
  soilOne30W->AddMaterial(OrganicMat, fractionmass=14.21*perCent);
  soilOne30W->AddMaterial(H2O, fractionmass=30.0*perCent);

  // Set materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");

  // shellMaterial 
  if (matType == 1)
    {
      shellMaterial = G4Material::GetMaterial("G4_Pb");
    } else if (matType == 2)
    {
      shellMaterial = G4Material::GetMaterial("G4_AIR");
    } else if (matType == 3)
    {
      shellMaterial = G4Material::GetMaterial("liquidArgon");
    } else if (matType == 4)
    {
      shellMaterial = soilOne;
    } else if (matType == 5)
    {
      shellMaterial = soilOne10W;
    } else if (matType == 6)
    {
      shellMaterial = soilOne20W;
    } else if (matType == 7)
    {
      shellMaterial = soilOne30W;
    } else {
    G4cout << "Material is NOT defined! " << G4endl;
    exit(1);
  }

  // shellMaterial_1 type 
  if (matType_1 == 1)
    {
      shellMaterial_1 = G4Material::GetMaterial("G4_Pb");
    } else if (matType_1 == 2)
    {
      shellMaterial_1 = G4Material::GetMaterial("G4_AIR");
    } else if (matType_1 == 3)
    {
      shellMaterial = G4Material::GetMaterial("liquidArgon");
    } else if (matType_1 == 4)
    {
      shellMaterial_1 = soilOne;
    } else if (matType_1 == 5)
    {
      shellMaterial_1 = soilOne10W;
    } else if (matType_1 == 6)
    {
      shellMaterial_1 = soilOne20W;
    } else if (matType_1 == 7)
    {
      shellMaterial_1 = soilOne30W;
    } else {
    G4cout << "Material_1 is NOT defined! " << G4endl;
    exit(1);
  }

  // shellMaterial_2 type 
  if (matType_2 == 1)
    {
      shellMaterial_2 = G4Material::GetMaterial("G4_Pb");
    } else if (matType_2 == 2)
    {
      shellMaterial_2 = G4Material::GetMaterial("G4_AIR");
    } else if (matType_2 == 3)
    {
      shellMaterial_2 = G4Material::GetMaterial("liquidArgon");
    } else if (matType_2 == 4)
    {
      shellMaterial_2 = soilOne;
    } else if (matType_2 == 5)
    {
      shellMaterial_2 = soilOne10W;
    } else if (matType_2 == 6)
    {
      shellMaterial_2 = soilOne20W;
    } else if (matType_2 == 7)
    {
      shellMaterial_2 = soilOne30W;
    } else {
    G4cout << "Material_2 is NOT defined! " << G4endl;
    exit(1);
  }
  
  // shellMaterial_3 type 
  if (matType_3 == 1)
    {
      shellMaterial_3 = G4Material::GetMaterial("G4_Pb");
    } else if (matType_3 == 2)
    {
      shellMaterial_3 = G4Material::GetMaterial("G4_AIR");
    } else if (matType_3 == 3)
    {
      shellMaterial_3 = G4Material::GetMaterial("liquidArgon");
    } else if (matType_3 == 4)
    {
      shellMaterial_3 = soilOne;
    } else if (matType_3 == 5)
    {
      shellMaterial_3 = soilOne10W;
    } else if (matType_3 == 6)
    {
      shellMaterial_3 = soilOne20W;
    } else if (matType_3 == 7)
    {
      shellMaterial_3 = soilOne30W;
    } else {
    G4cout << "Material_3 is NOT defined! " << G4endl;
    exit(1);
  }

  
  // Geometry parameters  

  //     
  // World
  //

  auto worldSizeXY = 2.5 * outer_r;
  auto worldSizeZ  = worldSizeXY; 
  
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
  // Make neutron ball detector (i.e., multiple layers)
  //

  // Define the angles for spheres
  G4double startAnglePhi = 0.0*deg;
  G4double spanningAnglePhi = 360.0*deg;
  G4double startAngleTheta = 0.0*deg;
  G4double spanningAngleTheta = 180.0*deg; //90

  // Outer shell
  auto solidShell = new G4Sphere("Shell", inner_r, outer_r,
             startAnglePhi, spanningAnglePhi, 
             startAngleTheta, spanningAngleTheta);  
  auto shellLV
    = new G4LogicalVolume(
                 solidShell,     // its solid
                 shellMaterial,  // its material
                 "shellLV");   // its name
                                   
  shellPV = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 shellLV,          // its logical volume                         
                 "shellPV",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

  // 1st layer
  
  auto solidShell_1 = new G4Sphere("Shell_1", 1.001*inner_r, 0.8*outer_r,
         startAnglePhi, spanningAnglePhi, 
         startAngleTheta, spanningAngleTheta);
  
  auto shellLV_1
    = new G4LogicalVolume(
                 solidShell_1,     // its solid
                 shellMaterial_1,  // its material
                 "shellLV_1");   // its name
                                   
  shellPV_1 = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 shellLV_1,          // its logical volume                         
                 "shellPV_1",    // its name
                 shellLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  // 2nd layer
  
  auto solidShell_2 = new G4Sphere("Shell_2", 1.002*inner_r, 0.6*outer_r,
           startAnglePhi, spanningAnglePhi, 
           startAngleTheta, spanningAngleTheta);
  
  auto shellLV_2
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
  
  // 3rd layer
  
  auto solidShell_3 = new G4Sphere("Shell_3", 1.003*inner_r, 0.4*outer_r,
           startAnglePhi, spanningAnglePhi, 
           startAngleTheta, spanningAngleTheta);
  
  auto shellLV_3
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

  auto simpleShellVisAtt_1= new G4VisAttributes(G4Colour(0.3,0.4,0.1));
  simpleShellVisAtt_1->SetVisibility(true);
  shellLV_1->SetVisAttributes(simpleShellVisAtt_1);

  auto simpleShellVisAtt_2= new G4VisAttributes(G4Colour(0.3,0.3,0.2));
  simpleShellVisAtt_2->SetVisibility(true);
  shellLV_2->SetVisAttributes(simpleShellVisAtt_2);

  auto simpleShellVisAtt_3= new G4VisAttributes(G4Colour(0.3,0.1,0.2));
  simpleShellVisAtt_3->SetVisibility(true);
  shellLV_3->SetVisAttributes(simpleShellVisAtt_3);
  
  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
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
