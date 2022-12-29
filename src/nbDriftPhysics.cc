/*
    Mayur: commented code of AlongStepGetPhysicalInteractionLength(),
    Mayur: IsApplicable is mimicked from advanced examples in geant4
*/

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
  return (particle.GetPDGCharge() != 0.);
}

// AlongStepGetPhysicalInteractionLength
// G4double nbDriftPhysics::AlongStepGetPhysicalInteractionLength(
//                               const G4Track& track,
//                               G4double  previousStepSize,
//                               G4double  currentMinimumStep,
//                               G4double& proposedSafety,
//                               G4GPILSelection* selection
//                              )
// {
//   // condition is set to "Not Forced"
//   *condition = NotForced;
  
//   G4double MaxChargedStep
//   G4double ProposedStep = DBL_MAX;

//   if((MaxChargedStep > 0.) &&
//      (track.GetVolume() != 0) &&
//      (track.GetVolume()->GetName() == ""))
//      ProposedStep = MaxChargedStep;

//   return ProposedStep;

// }

/////////////////////////////////////////////////////////////////////////////////////////////

// AlongStepDoIt
G4VParticleChange* nbDriftPhysics::AlongStepDoIt(const G4Track& aTrack, const G4Step& aStep)
{
   aParticleChange.Initialize(aTrack); 
   
   const G4ParticleDefinition* particle = aStep.GetTrack()->GetParticleDefinition();  
   if(particle->GetAtomicMass() == 222 || particle->GetAtomicNumber() == 86)
   {
      // G4cout << "processCalledCounter: " << processCalledCounter++ << G4endl;  

      G4double currentEnergy = aStep.GetPreStepPoint()->GetKineticEnergy();
      // G4cout << "current energy : " << currentEnergy << G4endl;
      aParticleChange.ProposeEnergy(currentEnergy + 1.0);
      // aParticleChange.ProposeMomentumDirection(G4ThreeVector(0., 1., 0.));
   }
  
   return &aParticleChange;
}






