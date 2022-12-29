#include "globals.hh"
#include "G4ios.hh"
#include "G4VContinuousProcess.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"

class nbDriftPhysics : public G4VContinuousProcess
{
    public:
            nbDriftPhysics(const G4String& processName ="DriftPhysics");
            ~nbDriftPhysics();
          
    public:
            G4bool IsApplicable(const G4ParticleDefinition&);
            
            G4VParticleChange* AlongStepDoIt(const G4Track&, const G4Step&);
            
        //     G4double AlongStepGetPhysicalInteractionLength(
        //                       const G4Track& track,
        //                       G4double  previousStepSize,
        //                       G4double  currentMinimumStep,
        //                       G4double& proposedSafety,
        //                       G4GPILSelection* selection
        //                      );
            
            G4double GetContinuousStepLimit(const G4Track& aTrack,
                              G4double  previousStepSize,
                              G4double  currentMinimumStep,
                              G4double& currentSafety
                                                              )
            { return 0.; } // no need here
   
    public:
            G4int processCalledCounter = 0;
    
};
