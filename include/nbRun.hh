// 23 August 2022, Code added
/// Run.hh
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nbRun_h
#define nbRun_h 1

#include "G4Run.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include <map>

using namespace std;

// use defined class to store data
class G4ParticleDefinition;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// G4Run
class nbRun : public G4Run
{
  public:
  
    // constructor
    nbRun();
    
    // destructor
   ~nbRun();
   
   
  // declared struct particleData to store particleData
  // note: structs are used with constructors to initialize the values of variables
  private:
    
  struct ParticleDataPerLayer {
     ParticleDataPerLayer()
       : fCount(0) {}
     ParticleDataPerLayer(G4int count)
       : fCount(count) {}
     G4int     fCount;
    };
    
    std::map<G4String,ParticleDataPerLayer>  fParticlePerLayerDataMap;    
    
  
  private:    
    struct ParticleData {
     ParticleData()
       : fCount(0), fEmean(0.), fEmin(0.), fEmax(0.), fTmean(-1.) {}
     ParticleData(G4int count, G4double ekin, G4double emin, G4double emax,
                  G4double meanLife)
       : fCount(count), fEmean(ekin), fEmin(emin), fEmax(emax),
         fTmean(meanLife) {}
     G4int     fCount;
     G4double  fEmean;
     G4double  fEmin;
     G4double  fEmax;
     G4double  fTmean;
    };
     
  // user defined G4ParticleDefinition class has some data members
  private: 
    G4ParticleDefinition*  fParticle;
    G4double  fEkin;
             
    // created map to store the data of all particles together
    // each value in map = struct particleData
    std::map<G4String,ParticleData>  fParticleDataMap;    
    G4int    fDecayCount, fTimeCount;
    G4double fEkinTot[3];
    G4double fPbalance[3];
    G4double fEventTime[3];
    G4double fPrimaryTime;
    G4double fEvisEvent[3];
 
 // declared struct ActivityData to store activityData
 private:    
  struct ActivityData {
   ActivityData()
     : fNlife_t1(0), fNlife_t2(0), fNdecay_t1t2(0) {}
   ActivityData(G4int n1, G4int n2, G4int nd)
     : fNlife_t1(n1), fNlife_t2(n2), fNdecay_t1t2(nd) {}
   G4int  fNlife_t1;
   G4int  fNlife_t2;
   G4int  fNdecay_t1t2;
  };
  
  // created map to store the data of all Activities together
  // each value in map  = struct activityData
  std::map<G4String,ActivityData>  fActivityMap;
  G4double fTimeWindow1, fTimeWindow2; 

  public:
  
    // some concrete classes to store data
    void ParticleCount(G4String, G4double, G4double);
    void Balance(G4double,G4double);
    void EventTiming(G4double);
    void PrimaryTiming(G4double);
    void EvisEvent(G4double);

    void SetTimeWindow(G4double , G4double);
    void CountInTimeWindow(G4String, G4bool,G4bool,G4bool);
        
    void SetPrimary(G4ParticleDefinition* particle, G4double energy);
    void EndOfRun(); 
    
    // 
    void ParticleCountPerLayer(G4String, G4String);

    // override inbuilt method (refere doc to know more about virtual methods available in G4Run class)
    virtual void Merge(const G4Run*);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


