// Created on 10/13/2021
//

#ifndef nbActionInitialization_h
#define nbActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class nbDetectorConstruction;

/// Action initialization class.
///

class nbActionInitialization : public G4VUserActionInitialization
{
  public:
    nbActionInitialization(nbDetectorConstruction*);
    virtual ~nbActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    nbDetectorConstruction* fDetConstruction;
};

#endif

