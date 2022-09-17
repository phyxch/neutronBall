#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbPhysicsList: public G4VModularPhysicsList
{
public:
  nbPhysicsList();
 ~nbPhysicsList();

public:
  virtual void ConstructParticle();
  virtual void SetCuts();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

