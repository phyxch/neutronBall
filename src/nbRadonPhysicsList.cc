#include "nbRadonPhysicsList.hh"
#include "globals.hh"
#include "G4GenericIon.hh"
#include "nbDriftPhysics.hh"
#include "G4ProcessManager.hh"


nbRadonPhysicsList::nbRadonPhysicsList(G4int verbose, const G4String& name) : G4VPhysicsConstructor(name)
{
  
}

nbRadonPhysicsList::~nbRadonPhysicsList()
{
  
}

void nbRadonPhysicsList::ConstructParticle()
{
  // nothing to write here.
}

void nbRadonPhysicsList::ConstructProcess()
{
  nbDriftPhysics* driftPhysicsProcesss = new nbDriftPhysics();

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







