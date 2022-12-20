/*
	20 dec 2022 : new class radonPhysicsList is added
*/

#ifndef nbRadonPhysicsList_h
#define nbRadonPhysicsList_h 1

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"

class G4VProcess;

class nbRadonPhysicsList : public G4VPhysicsConstructor
{
  public: 
    nbRadonPhysicsList(G4int verbose = 0, const G4String& name = "RadonPhysics");;
    // nbRadonPhysicsList(const G4String& name);

    virtual ~nbRadonPhysicsList();

    // construct particle and physics processes 
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    
    
    G4VPhysicsConstructor* DecayPhysics;

};

#endif // nbRadonPhysicsList_h
