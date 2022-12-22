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
  return true;
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
   const G4ParticleDefinition* particle = aStep.GetTrack()->GetParticleDefinition();  

   if(particle->GetAtomicMass() == 222 || particle->GetAtomicNumber() == 86)
   {
      G4cout << "this is radon" << G4endl;

      // we need to push the particle in upward direction here
   
      aParticleChange.Initialize(aTrack);   // this is from official source of G4VParticleChange OR G4VContinuousProcess
      
      // // get current velocity in this step 
      // 
      // G4double currentVelocity = aStep.GetPostStepPoint()->GetVelocity();
      // 
      // G4cout << "current velocity is = " << currentVelocity * mm/s << "mm/s" << G4endl;
      // 
      // G4double updatedVelocity = currentVelocity + 100 * m/s;
      // 
      // G4cout << "updated velocity is = " << updatedVelocity * mm/s  << "mm/s" << G4endl;
      // 
      // // propose this velocity
      // 
      // aParticleChange.ProposeVelocity(updatedVelocity);
      // 
      // auto dir = aStep.GetPostStepPoint()->GetMomentumDirection();
      // 
      // // G4ThreeVector tempMomentumDirection = new G4ThreeVector(0., 1., 0.);
      // // momentumDirection = momentumDirection + tempMomentum;
      // 
      // aParticleChange.ProposeMomentumDirection(G4ThreeVector(0., 1., 0.));
      
      // get current velocity in this step 
      
      G4double currentKE = aStep.GetPostStepPoint()->GetKineticEnergy();
      
      // G4cout << "current velocity is = " << currentKE << G4endl;
      
      G4double newKE = currentKE + 100. *MeV;
      
      // G4cout << "updated velocity is = " << newKE << G4endl;
      
      // propose this velocity
      
      aParticleChange.ProposeEnergy(newKE);
      
      // auto dir = aStep.GetPostStepPoint()->GetMomentumDirection();
      
      // G4ThreeVector tempMomentumDirection = new G4ThreeVector(0., 1., 0.);
      // momentumDirection = momentumDirection + tempMomentum;
      
      aParticleChange.ProposeMomentumDirection(G4ThreeVector(0., 1., 0.));

   }
      
   return &aParticleChange;
}






