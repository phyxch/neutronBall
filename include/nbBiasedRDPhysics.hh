#ifndef BiasedRDPhysics_h
#define BiasedRDPhysics_h 1

#include "G4VPhysicsConstructor.hh"


class G4Radioactivation;

class nbBiasedRDPhysics : public G4VPhysicsConstructor
{
  public: 
    nbBiasedRDPhysics(G4int verbose = 1);
    nbBiasedRDPhysics(const G4String& name);
    virtual ~nbBiasedRDPhysics();

    // This is a dummy method for physics
    virtual void ConstructParticle();
 
    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type 
    virtual void ConstructProcess();

};

#endif


