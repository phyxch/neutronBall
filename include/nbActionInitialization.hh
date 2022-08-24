// code updated on 23 August, 2022
// fully revamped as per rdecay01; might need to add code from previous neutronBall nbActionInitialization.hh file

#ifndef nbActionInitialization_h
#define nbActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

class nbActionInitialization : public G4VUserActionInitialization
{
  public:
  
    nbActionInitialization();
    
    ~nbActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

#endif

    

