#include "nbPhysicsList.hh"
#include "nbDriftPhysics.hh"

#include <iomanip>   

#include <CLHEP/Units/SystemOfUnits.h>

#include "globals.hh"
#include "G4ios.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"

#include "QGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"

#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"


nbPhysicsList::nbPhysicsList()
:G4VModularPhysicsList()
{
  G4int ver = 1;

  defaultCutValue = 0.7*CLHEP::mm;  
  SetVerboseLevel(ver);
  
  // intialise all physics lists
  DecayPhysics = new G4DecayPhysics(ver);
  EmStandardPhysics =  new G4EmStandardPhysics(ver);
  EmExtraPhysics = new G4EmExtraPhysics(ver);
  RadioactiveDecayPhysics = new G4RadioactiveDecayPhysics(ver);
  HadronPhysicsQGSP_BERT_HP = new G4HadronPhysicsQGSP_BERT_HP(ver);
  IonPhysics = new G4IonPhysics(ver);
  StoppingPhysics = new G4StoppingPhysics(ver);
  HadronElasticPhysicsHP = new G4HadronElasticPhysicsHP(ver);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbPhysicsList::~nbPhysicsList()
{
  delete DecayPhysics;
  delete EmStandardPhysics;
  delete EmExtraPhysics;
  delete RadioactiveDecayPhysics;
  delete HadronElasticPhysicsHP;
  delete HadronPhysicsQGSP_BERT_HP;
  delete IonPhysics;
  delete StoppingPhysics;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbPhysicsList::ConstructParticle()
{
  // construct the particles which are going to use
  DecayPhysics->ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbPhysicsList::ConstructProcess()
{
  AddTransportation();
  
  // add custom physics list here
  DecayPhysics->ConstructProcess();
  EmStandardPhysics->ConstructProcess();
  EmExtraPhysics->ConstructProcess();
  RadioactiveDecayPhysics->ConstructProcess();
  HadronElasticPhysicsHP->ConstructProcess();
  HadronPhysicsQGSP_BERT_HP->ConstructProcess();
  IonPhysics->ConstructProcess();
  StoppingPhysics->ConstructProcess();
  
  AddDriftPhysics();
}

void nbPhysicsList::AddDriftPhysics()
{
  driftPhysicsProcesss = new nbDriftPhysics();

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while ((*particleIterator)()){
    G4ParticleDefinition* particle = particleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (driftPhysicsProcesss->IsApplicable(*particle) && pmanager)
      {
	        pmanager->AddContinuousProcess(driftPhysicsProcesss);
      }
  }
}

