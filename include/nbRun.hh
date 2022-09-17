//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include <map>

class nbDetectorConstruction;
class G4ParticleDefinition;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nbRun : public G4Run
{
  public:
    
    nbRun(nbDetectorConstruction*);
   ~nbRun();

  public:
    void SetPrimary(G4ParticleDefinition* particle, G4double energy);         
    void CountProcesses(const G4VProcess* process, G4int iVol);
    void ParticleCount(G4String, G4double, G4int); 
    void AddEdep(G4double edep1, G4double edep2, G4double edep3, G4double edep4, G4double edep5, G4double edep6);
                          
    virtual void Merge(const G4Run*);
    void EndOfRun();
    void WriteActivity(G4int);     
   
  private:
  
    // c++ struct for storing data associated with each particle
    struct ParticleData {
     ParticleData()
       : fCount(0), fEmean(0.), fEmin(0.), fEmax(0.) {}
     ParticleData(G4int count, G4double ekin, G4double emin, G4double emax)
       : fCount(count), fEmean(ekin), fEmin(emin), fEmax(emax) {}
     G4int     fCount;
     G4double  fEmean;
     G4double  fEmin;
     G4double  fEmax;
    };
     
  private:
    // object of class nbDetectorConstruction class
    nbDetectorConstruction* fDetector;
    // instance of particleDefinition class
    G4ParticleDefinition* fParticle;
    // KE or E of particle is measure in eV
    G4double fEkin;
    
    G4double fEdep1, fEdep2, fEdep3, fEdep4, fEdep5, fEdep6;
    G4double tfEdep1, tfEdep2, tfEdep3, tfEdep4, tfEdep5, tfEdep6;
    G4double fEdepDetect, fEdepDetect2;    
    
    // process counter for each layer
    std::map<G4String,G4int>        fProcCounter1;
    std::map<G4String,G4int>        fProcCounter2;
    std::map<G4String,G4int>        fProcCounter3;
    std::map<G4String,G4int>        fProcCounter4;
    std::map<G4String,G4int>        fProcCounter5;
    std::map<G4String,G4int>        fProcCounter6; // for world
        
    // particle data maps for each layer
    std::map<G4String,ParticleData> fParticleDataMap1;                    
    std::map<G4String,ParticleData> fParticleDataMap2;
    std::map<G4String,ParticleData> fParticleDataMap3;
    std::map<G4String,ParticleData> fParticleDataMap4;
    std::map<G4String,ParticleData> fParticleDataMap5;
    std::map<G4String,ParticleData> fParticleDataMap6; // for world
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

