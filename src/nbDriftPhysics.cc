#include "nbDriftPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


// constructor
nbDriftPhysics::nbDriftPhysics(const G4String& processName)
 : G4VContinuousProcess(processName)
{
  G4cout << "process initialised successfully" << G4endl;
}

// destructor
nbDriftPhysics::~nbDriftPhysics()
{}

// IsApplicable
G4bool nbDriftPhysics::IsApplicable(const G4ParticleDefinition& particle) 
{   
  G4cout << "checking particle: " << particle.GetParticleName() << "A = " << particle.GetAtomicMass() << G4endl;
  if(particle.GetAtomicMass() == 222 && particle.GetAtomicNumber() == 86)
  {
   // this is radon
   G4cout << particle.GetParticleName() << " is applicable " << G4endl;
   return true;
  }
    
  return false;
}

// AlongStepGetPhysicalInteractionLength
G4double nbDriftPhysics::AlongStepGetPhysicalInteractionLength(
                              const G4Track& track,
                              G4double  previousStepSize,
                              G4double  currentMinimumStep,
                              G4double& proposedSafety,
                              G4GPILSelection* selection
                             )
{
  return 1. * mm;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// AlongStepDoIt
G4VParticleChange* nbDriftPhysics::AlongStepDoIt(const G4Track& aTrack, const G4Step& aStep)
{
   // we need to push the particle in upward direction here
   aParticleChange.Initialize(aTrack);
   G4double currentVelocity = aStep.GetPostStepPoint()->GetVelocity();
   G4cout << "current velocity is = " << currentVelocity * mm/s << "mm/s" << G4endl;
   G4double updatedVelocity = currentVelocity + 1 * mm/s;
   G4cout << "updated velocity is = " << updatedVelocity * mm/s  << "mm/s" << G4endl;
   
   // propose this velocity
   aParticleChange.ProposeVelocity(updatedVelocity);
   
   return &aParticleChange;
}






