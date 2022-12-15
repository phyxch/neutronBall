#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "G4PhysListFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


class G4VPhysicsConstructor;
class nbDriftPhysics;


class nbPhysicsList: public G4VModularPhysicsList
{
public:
  nbPhysicsList();
 ~nbPhysicsList();

public:
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  
  void AddDriftPhysics();
  
public:
  // declare some variables here
  G4VPhysicsConstructor* DecayPhysics;
  G4VPhysicsConstructor* EmStandardPhysics;
  G4VPhysicsConstructor* EmExtraPhysics;
  G4VPhysicsConstructor* RadioactiveDecayPhysics;
  G4VPhysicsConstructor* HadronElasticPhysicsHP;
  G4VPhysicsConstructor* HadronPhysicsQGSP_BERT_HP;
  G4VPhysicsConstructor* IonPhysics;
  G4VPhysicsConstructor* StoppingPhysics;
  
  nbDriftPhysics* driftPhysicsProcesss;
}; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
