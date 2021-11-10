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
  nbDetectorConstruction();
  virtual ~nbDetectorConstruction();
  
public:
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
  
  // get methods
  //
  const G4VPhysicalVolume* GetShellPV() const;
  
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
  G4Material *shellMaterial, *shellMaterial_1, *shellMaterial_2, *shellMaterial_3;
  G4VPhysicalVolume  *shellPV, *shellPV_1, *shellPV_2, *shellPV_3;    // neutron ball shell physical volume
  
  G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

// inline functions

inline const G4VPhysicalVolume* nbDetectorConstruction::GetShellPV() const { 
  return shellPV; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

