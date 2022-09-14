// August 22, 2022 Newly created physicsList.hh file
/// \brief Definition of the PhysicsList class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbPhysicsList: public G4VModularPhysicsList
{
  public:
    // physicsList constructor
    //
    nbPhysicsList();
    
    // physicsList destructor
   ~nbPhysicsList();

  protected:
    // Construct particle and physics
    
    // virtual function constructParticle()
    //
    virtual void ConstructParticle();
    
    // vitual function constructProcess()
    virtual void ConstructProcess(); 
    
    // virtual function SetCuts()
    virtual void SetCuts();   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif




