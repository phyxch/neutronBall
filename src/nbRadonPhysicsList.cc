#include "nbRadonPhysicsList.hh"
#include "globals.hh"
#include "G4GenericIon.hh"
#include "nbDriftPhysics.hh"
#include "G4ProcessManager.hh"

#include "G4DecayPhysics.hh"

#include "G4IonConstructor.hh"

#include "G4IonTable.hh"

nbRadonPhysicsList::nbRadonPhysicsList(G4int verbose, const G4String& name) : G4VPhysicsConstructor(name)
{
  DecayPhysics = new G4DecayPhysics(1);
}

// nbRadonPhysicsList::nbRadonPhysicsList(const G4String&) : nbRadonPhysicsList(0)
// {}

nbRadonPhysicsList::~nbRadonPhysicsList()
{
  delete DecayPhysics;
}

void nbRadonPhysicsList::ConstructParticle()
{
  DecayPhysics->ConstructParticle();
  // G4GenericIon::GenericIon();
  // G4IonConstructor pIonConstructor;
  // pIonConstructor.ConstructParticle();
}

void nbRadonPhysicsList::ConstructProcess()
{
  // add drift physics process here
  //
  nbDriftPhysics* driftPhysicsProcesss = new nbDriftPhysics();
  
  ///////////////////////////CODE 1 ///////////////////////////////////////////////////
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  
  G4ParticleDefinition* particle = G4IonTable::GetIonTable()->GetIon(86,222,0.);
  G4ProcessManager* pmanager = particle->GetProcessManager();
  
  if (!pmanager) {
        std::ostringstream o;
        o << "Particle " << particle->GetParticleName() << "without a Process Manager";
        G4Exception("G4OpticalPhysics::ConstructProcess()","",
                     FatalException,o.str().c_str());
        return;                 // else coverity complains for pManager use             
  }
  
  if (driftPhysicsProcesss->IsApplicable(*particle) && pmanager)
  {
    pmanager->AddContinuousProcess(driftPhysicsProcesss);
    G4cout << "process is added " << G4endl;
  }
  /////////////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////// CODE 2 //////////////////////////////////////////////////
//   auto particleIterator=GetParticleIterator();
//   particleIterator->reset();
//   while ((*particleIterator)()) {
//    G4ParticleDefinition* particle = particleIterator->value();
//    G4ProcessManager* pmanager = particle->GetProcessManager();
//  
//    if (driftPhysicsProcesss->IsApplicable(*particle) && pmanager)
//      {
//  	        pmanager->AddContinuousProcess(driftPhysicsProcesss);
//      }
//   }
}







