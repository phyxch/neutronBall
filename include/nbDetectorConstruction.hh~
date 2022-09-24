// Created on 10/13/2021
//
// All of the geometric parameters of the neutron ball detector is define here
//
// Updated on 10/20/2021: hexc, Mayur, Tien, Weisen
//    Added code for reading on detector configuration parameter
//
// Updated on 11/10/2021: hexc, Mayur, Tien, Jarvious
//   Add more layers in the detector construct with different material properties.

#ifndef nbDetectorConstruction_h
#define nbDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;
class G4Material;

/// Detector construction class to define materials and geometry.
/// The detector consists of concentric spherical shells. One can have as many shell as we want.
/// In this version, we simply make single shell with inner and outer radius
/// 

class nbDetectorConstruction : public G4VUserDetectorConstruction
{
    public:

      // construction definition
      nbDetectorConstruction();
      // destructor definition
      virtual ~nbDetectorConstruction();
      
    public:

      // virtual function construct() which returns physical world volume
      virtual G4VPhysicalVolume* Construct();
      // currently we are not using any SDs (but defined)
      // virtual void ConstructSDandField();
     
    private:
      // methods
      //
      void DefineMaterials();
      G4VPhysicalVolume* DefineVolumes();
      
      // data members
      //
      static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
      // magnetic field messenger
      
      G4double inner_r, outer_r;
      G4int matType, matType_1, matType_2, matType_3;
      G4Material *shellMaterial, *shellMaterial_1, *shellMaterial_2, *shellMaterial_3, *shellMaterial_4;
      G4VPhysicalVolume  *shellPV, *shellPV_1, *shellPV_2, *shellPV_3, *shellPV_4;    // neutron ball shell physical volume
      
      G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps

    public:
      // user defined functions to get physical volume names of each layer
      G4String getNameOfLayer1(); // shellPV
      G4String getNameOfLayer2(); // shellPV_1
      G4String getNameOfLayer3(); // shellPV_2
      G4String getNameOfLayer4(); // shellPV_3
      G4String getNameOfLayer5(); // shellPV_4
      G4String getNameOfLayer6(); // world
      
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

