// Created on 10/13/2021
//
// All of the geometric parameters of the neutron ball detector is define here
//

#ifndef nbDetectorConstruction_h
#define nbDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

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
  G4VPhysicalVolume*   shellPV;     // neutron ball shell physical volume
  
  G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

// inline functions

inline const G4VPhysicalVolume* nbDetectorConstruction::GetShellPV() const { 
  return shellPV; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

