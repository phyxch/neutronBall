#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class nbDetectorConstruction;

/// Action initialization class.
///

class nbActionInitialization : public G4VUserActionInitialization
{
  public:
    
    // constructor & destructor
    nbActionInitialization(nbDetectorConstruction* detector);
    virtual ~nbActionInitialization();
    
    // inbuilt methods in actionInitialization class
    virtual void BuildForMaster() const;
    virtual void Build() const;
   
  private:
    // create object of detector construction class
    nbDetectorConstruction* fDetector;
};

#endif

    

