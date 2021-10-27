// Created on 10/13/2021
// 

#ifndef nbRunData_h
#define nbRunData_h 1

#include "G4Run.hh"
#include "globals.hh"

#include <array>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const G4int kShell = 0;
const G4int kGap = 1;
// const G4int kDim = 2;   // from example code
const G4int kDim = 1;

///  Run data class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers.
/// 
/// In order to reduce the number of data members a 2-dimensions array 
/// is introduced for each quantity:
/// - fEdep[], fTrackLength[].
///
/// The data are collected step by step in nbSteppingAction, and
/// the accumulated values are filled in histograms and entuple
/// event by event in nbEventAction.

class nbRunData : public G4Run
{
public:
  nbRunData();
  virtual ~nbRunData();

  void Add(G4int id, G4double de, G4double dl);
  void FillPerEvent();

  void Reset();

  // Get methods
  G4String  GetVolumeName(G4int id) const;
  G4double  GetEdep(G4int id) const;
  G4double  GetTrackLength(G4int id) const; 

private:
  std::array<G4String, kDim>  fVolumeNames;
  std::array<G4double, kDim>  fEdep;
  std::array<G4double, kDim>  fTrackLength; 
};

// inline functions

inline void nbRunData::Add(G4int id, G4double de, G4double dl) {
  fEdep[id] += de; 
  fTrackLength[id] += dl;
  // G4cout << " de: " << de << "  dl: " << dl << G4endl;
}

inline G4String  nbRunData::GetVolumeName(G4int id) const {
  return fVolumeNames[id];
}

inline G4double  nbRunData::GetEdep(G4int id) const {
  return fEdep[id];
}   

inline G4double  nbRunData::GetTrackLength(G4int id) const {
  return fTrackLength[id];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

