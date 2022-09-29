#include "nbRun.hh"
#include "nbDetectorConstruction.hh"
#include "nbPrimaryGeneratorAction.hh"
#include "nbHistoManager.hh"

#include "G4ProcessTable.hh"
#include "G4Radioactivation.hh"
#include "G4TwoVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRun::nbRun(nbDetectorConstruction* det)
: G4Run(),
  fDetector(det), fParticle(0), fEkin(0.)
{
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nbRun::~nbRun()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRun::SetPrimary(G4ParticleDefinition* particle, G4double energy)
{ 
  fParticle = particle; // set particle definition
  fEkin = energy; // set initial KE
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

                  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRun::ParticleCount(G4String name, G4double Ekin, G4int iVol)
{

  // layer 1
  if (iVol == 1) {
   std::map<G4String, ParticleData>::iterator it1 = fParticleDataMap1.find(name);
   if ( it1 == fParticleDataMap1.end()) {
     fParticleDataMap1[name] = ParticleData(1, Ekin, Ekin, Ekin);
   }
   else {
     ParticleData& data = it1->second;
     data.fCount++;
     data.fEmean += Ekin;
     //update min max
     G4double emin = data.fEmin;
     if (Ekin < emin) data.fEmin = Ekin;
     G4double emax = data.fEmax;
     if (Ekin > emax) data.fEmax = Ekin; 
   }   
  }
  
  // layer 2
  if (iVol == 2) {
   std::map<G4String, ParticleData>::iterator it2 = fParticleDataMap2.find(name);
   if ( it2 == fParticleDataMap2.end()) {
     fParticleDataMap2[name] = ParticleData(1, Ekin, Ekin, Ekin);
   }
   else {
     ParticleData& data = it2->second;
     data.fCount++;
     data.fEmean += Ekin;
     //update min max
     G4double emin = data.fEmin;
     if (Ekin < emin) data.fEmin = Ekin;
     G4double emax = data.fEmax;
     if (Ekin > emax) data.fEmax = Ekin; 
   }   
  }
  
  // layer 3
  if (iVol == 3) {
   std::map<G4String, ParticleData>::iterator it3 = fParticleDataMap3.find(name);
   if ( it3 == fParticleDataMap3.end()) {
     fParticleDataMap3[name] = ParticleData(1, Ekin, Ekin, Ekin);
   }
   else {
     ParticleData& data = it3->second;
     data.fCount++;
     data.fEmean += Ekin;
     //update min max
     G4double emin = data.fEmin;
     if (Ekin < emin) data.fEmin = Ekin;
     G4double emax = data.fEmax;
     if (Ekin > emax) data.fEmax = Ekin; 
   }   
  }  
  
  // layer 4
  if (iVol == 4) {
   std::map<G4String, ParticleData>::iterator it4 = fParticleDataMap4.find(name);
   if ( it4 == fParticleDataMap4.end()) {
     fParticleDataMap4[name] = ParticleData(1, Ekin, Ekin, Ekin);
   }
   else {
     ParticleData& data = it4->second;
     data.fCount++;
     data.fEmean += Ekin;
     //update min max
     G4double emin = data.fEmin;
     if (Ekin < emin) data.fEmin = Ekin;
     G4double emax = data.fEmax;
     if (Ekin > emax) data.fEmax = Ekin; 
   }   
  }  
  
  // layer 5
  if (iVol == 5) {
   std::map<G4String, ParticleData>::iterator it5 = fParticleDataMap5.find(name);
   if ( it5 == fParticleDataMap5.end()) {
     fParticleDataMap5[name] = ParticleData(1, Ekin, Ekin, Ekin);
   }
   else {
     ParticleData& data = it5->second;
     data.fCount++;
     data.fEmean += Ekin;
     //update min max
     G4double emin = data.fEmin;
     if (Ekin < emin) data.fEmin = Ekin;
     G4double emax = data.fEmax;
     if (Ekin > emax) data.fEmax = Ekin; 
   }   
  }  
  
  // world
  if (iVol == 6) {
   std::map<G4String, ParticleData>::iterator it6 = fParticleDataMap6.find(name);
   if ( it6 == fParticleDataMap6.end()) {
     fParticleDataMap6[name] = ParticleData(1, Ekin, Ekin, Ekin);
   }
   else {
     ParticleData& data = it6->second;
     data.fCount++;
     data.fEmean += Ekin;
     //update min max
     G4double emin = data.fEmin;
     if (Ekin < emin) data.fEmin = Ekin;
     G4double emax = data.fEmax;
     if (Ekin > emax) data.fEmax = Ekin; 
   }
  }
}
                 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


                 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRun::Merge(const G4Run* run)
{
  const nbRun* localRun = static_cast<const nbRun*>(run);
  
  //primary particle info
  //
  fParticle = localRun->fParticle;
  fEkin     = localRun->fEkin;
  
  


  //map: created particles in layer 1   
  std::map<G4String,ParticleData>::const_iterator itc1;
  for (itc1 = localRun->fParticleDataMap1.begin(); 
       itc1 != localRun->fParticleDataMap1.end(); ++itc1) {

    G4String name = itc1->first;
    const ParticleData& localData = itc1->second;   
    if ( fParticleDataMap1.find(name) == fParticleDataMap1.end()) {
      fParticleDataMap1[name]
       = ParticleData(localData.fCount, 
                      localData.fEmean, 
                      localData.fEmin, 
                      localData.fEmax);
    }
    else {
      ParticleData& data = fParticleDataMap1[name];   
      data.fCount += localData.fCount;
      data.fEmean += localData.fEmean;
      G4double emin = localData.fEmin;
      if (emin < data.fEmin) data.fEmin = emin;
      G4double emax = localData.fEmax;
      if (emax > data.fEmax) data.fEmax = emax; 
    }   
  }
  
  //map: created particles in layer 2   
  std::map<G4String,ParticleData>::const_iterator itc2;
  for (itc2 = localRun->fParticleDataMap2.begin(); 
       itc2 != localRun->fParticleDataMap2.end(); ++itc2) {

    G4String name = itc2->first;
    const ParticleData& localData = itc2->second;   
    if ( fParticleDataMap2.find(name) == fParticleDataMap2.end()) {
      fParticleDataMap2[name]
       = ParticleData(localData.fCount, 
                      localData.fEmean, 
                      localData.fEmin, 
                      localData.fEmax);
    }
    else {
      ParticleData& data = fParticleDataMap2[name];   
      data.fCount += localData.fCount;
      data.fEmean += localData.fEmean;
      G4double emin = localData.fEmin;
      if (emin < data.fEmin) data.fEmin = emin;
      G4double emax = localData.fEmax;
      if (emax > data.fEmax) data.fEmax = emax; 
    }   
  }
  
  //map: created particles in layer 3   
  std::map<G4String,ParticleData>::const_iterator itc3;
  for (itc3 = localRun->fParticleDataMap3.begin(); 
       itc3 != localRun->fParticleDataMap3.end(); ++itc3) {

    G4String name = itc3->first;
    const ParticleData& localData = itc3->second;   
    if ( fParticleDataMap3.find(name) == fParticleDataMap3.end()) {
      fParticleDataMap3[name]
       = ParticleData(localData.fCount, 
                      localData.fEmean, 
                      localData.fEmin, 
                      localData.fEmax);
    }
    else {
      ParticleData& data = fParticleDataMap3[name];   
      data.fCount += localData.fCount;
      data.fEmean += localData.fEmean;
      G4double emin = localData.fEmin;
      if (emin < data.fEmin) data.fEmin = emin;
      G4double emax = localData.fEmax;
      if (emax > data.fEmax) data.fEmax = emax; 
    }   
  }
  
  //map: created particles in layer 4
  std::map<G4String,ParticleData>::const_iterator itc4;
  for (itc4 = localRun->fParticleDataMap4.begin(); 
       itc4 != localRun->fParticleDataMap4.end(); ++itc4) {

    G4String name = itc4->first;
    const ParticleData& localData = itc4->second;   
    if ( fParticleDataMap4.find(name) == fParticleDataMap4.end()) {
      fParticleDataMap4[name]
       = ParticleData(localData.fCount, 
                      localData.fEmean, 
                      localData.fEmin, 
                      localData.fEmax);
    }
    else {
      ParticleData& data = fParticleDataMap4[name];   
      data.fCount += localData.fCount;
      data.fEmean += localData.fEmean;
      G4double emin = localData.fEmin;
      if (emin < data.fEmin) data.fEmin = emin;
      G4double emax = localData.fEmax;
      if (emax > data.fEmax) data.fEmax = emax; 
    }   
  }
  
  //map: created particles in layer 5
  std::map<G4String,ParticleData>::const_iterator itc5;
  for (itc5 = localRun->fParticleDataMap5.begin(); 
       itc5 != localRun->fParticleDataMap5.end(); ++itc5) {

    G4String name = itc5->first;
    const ParticleData& localData = itc5->second;   
    if ( fParticleDataMap5.find(name) == fParticleDataMap5.end()) {
      fParticleDataMap5[name]
       = ParticleData(localData.fCount, 
                      localData.fEmean, 
                      localData.fEmin, 
                      localData.fEmax);
    }
    else {
      ParticleData& data = fParticleDataMap5[name];   
      data.fCount += localData.fCount;
      data.fEmean += localData.fEmean;
      G4double emin = localData.fEmin;
      if (emin < data.fEmin) data.fEmin = emin;
      G4double emax = localData.fEmax;
      if (emax > data.fEmax) data.fEmax = emax; 
    }   
  }
  
  //map: created particles in layer 6 : **world**
  std::map<G4String,ParticleData>::const_iterator itc6;
  for (itc6 = localRun->fParticleDataMap6.begin(); 
       itc6 != localRun->fParticleDataMap6.end(); ++itc6) {

    G4String name = itc6->first;
    const ParticleData& localData = itc6->second;   
    if ( fParticleDataMap6.find(name) == fParticleDataMap6.end()) {
      fParticleDataMap6[name]
       = ParticleData(localData.fCount, 
                      localData.fEmean, 
                      localData.fEmin, 
                      localData.fEmax);
    }
    else {
      ParticleData& data = fParticleDataMap6[name];   
      data.fCount += localData.fCount;
      data.fEmean += localData.fEmean;
      G4double emin = localData.fEmin;
      if (emin < data.fEmin) data.fEmin = emin;
      G4double emax = localData.fEmax;
      if (emax > data.fEmax) data.fEmax = emax; 
    }   
  }

  G4Run::Merge(run); 
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRun::EndOfRun() 
{
  // some variables for structured prints on terminal
  G4int prec = 5, wid = prec + 2;  
  G4int dfprec = G4cout.precision(prec);
  
  // run condition
  //   
  G4String Particle = fParticle->GetParticleName();    
  G4cout << "\n The run is " << numberOfEvent << " "<< Particle << " of "
         << G4BestUnit(fEkin,"Energy") << " through : ";
  

  if (numberOfEvent == 0) { G4cout.precision(dfprec);   return;}
  
  G4cout << G4endl;
  G4cout << G4endl;
  G4cout << "********** PARTICLE COUNTS PER LAYER **********" << G4endl;
  
  // particles count in world
  G4cout << "\n List of generated particles in layer 6 (world):" << G4endl;
     
  std::map<G4String,ParticleData>::iterator itc6;               
  for (itc6 = fParticleDataMap6.begin(); itc6 != fParticleDataMap6.end(); itc6++) {
     G4String name = itc6->first;
     ParticleData data = itc6->second;
     G4int count = data.fCount;
     G4double eMean = data.fEmean/count;
     G4double eMin = data.fEmin;
     G4double eMax = data.fEmax;    
         
    G4cout << "  " << std::setw(13) << name << ": " << std::setw(7) << count
           << "  Emean = " << std::setw(wid) << G4BestUnit(eMean, "Energy")
           << "\t( "  << G4BestUnit(eMin, "Energy")
           << " --> " << G4BestUnit(eMax, "Energy") 
           << ")" << G4endl;           
  }
    
  // particles count in layer 1
  G4cout << "\n List of generated particles in layer 1:" << G4endl;
     
  std::map<G4String,ParticleData>::iterator itc1;               
  for (itc1 = fParticleDataMap1.begin(); itc1 != fParticleDataMap1.end(); itc1++) {
     G4String name = itc1->first;
     ParticleData data = itc1->second;
     G4int count = data.fCount;
     G4double eMean = data.fEmean/count;
     G4double eMin = data.fEmin;
     G4double eMax = data.fEmax;    
         
    G4cout << "  " << std::setw(13) << name << ": " << std::setw(7) << count
           << "  Emean = " << std::setw(wid) << G4BestUnit(eMean, "Energy")
           << "\t( "  << G4BestUnit(eMin, "Energy")
           << " --> " << G4BestUnit(eMax, "Energy") 
           << ")" << G4endl;           
  }
  
  // particles count in layer 2
  G4cout << "\n List of generated particles in layer 2:" << G4endl;
     
  std::map<G4String,ParticleData>::iterator itc2;               
  for (itc2 = fParticleDataMap2.begin(); itc2 != fParticleDataMap2.end(); itc2++) {
     G4String name = itc2->first;
     ParticleData data = itc2->second;
     G4int count = data.fCount;
     G4double eMean = data.fEmean/count;
     G4double eMin = data.fEmin;
     G4double eMax = data.fEmax;    
         
    G4cout << "  " << std::setw(13) << name << ": " << std::setw(7) << count
           << "  Emean = " << std::setw(wid) << G4BestUnit(eMean, "Energy")
           << "\t( "  << G4BestUnit(eMin, "Energy")
           << " --> " << G4BestUnit(eMax, "Energy") 
           << ")" << G4endl;           
  }
  
  // particles count in layer 3
  G4cout << "\n List of generated particles in layer 3:" << G4endl;
     
  std::map<G4String,ParticleData>::iterator itc3;               
  for (itc3 = fParticleDataMap3.begin(); itc3 != fParticleDataMap3.end(); itc3++) {
     G4String name = itc3->first;
     ParticleData data = itc3->second;
     G4int count = data.fCount;
     G4double eMean = data.fEmean/count;
     G4double eMin = data.fEmin;
     G4double eMax = data.fEmax;    
         
    G4cout << "  " << std::setw(13) << name << ": " << std::setw(7) << count
           << "  Emean = " << std::setw(wid) << G4BestUnit(eMean, "Energy")
           << "\t( "  << G4BestUnit(eMin, "Energy")
           << " --> " << G4BestUnit(eMax, "Energy") 
           << ")" << G4endl;           
  }
  
  // particles count in layer 4
  G4cout << "\n List of generated particles in layer 4:" << G4endl;
     
  std::map<G4String,ParticleData>::iterator itc4;               
  for (itc4 = fParticleDataMap4.begin(); itc4 != fParticleDataMap4.end(); itc4++) {
     G4String name = itc4->first;
     ParticleData data = itc4->second;
     G4int count = data.fCount;
     G4double eMean = data.fEmean/count;
     G4double eMin = data.fEmin;
     G4double eMax = data.fEmax;    
         
    G4cout << "  " << std::setw(13) << name << ": " << std::setw(7) << count
           << "  Emean = " << std::setw(wid) << G4BestUnit(eMean, "Energy")
           << "\t( "  << G4BestUnit(eMin, "Energy")
           << " --> " << G4BestUnit(eMax, "Energy") 
           << ")" << G4endl;           
  }
  
  // particles count in layer 5
  G4cout << "\n List of generated particles in layer 5:" << G4endl;
     
  std::map<G4String,ParticleData>::iterator itc5;               
  for (itc5 = fParticleDataMap5.begin(); itc5 != fParticleDataMap5.end(); itc5++) {
     G4String name = itc5->first;
     ParticleData data = itc5->second;
     G4int count = data.fCount;
     G4double eMean = data.fEmean/count;
     G4double eMin = data.fEmin;
     G4double eMax = data.fEmax;    
         
    G4cout << "  " << std::setw(13) << name << ": " << std::setw(7) << count
           << "  Emean = " << std::setw(wid) << G4BestUnit(eMean, "Energy")
           << "\t( "  << G4BestUnit(eMin, "Energy")
           << " --> " << G4BestUnit(eMax, "Energy") 
           << ")" << G4endl;           
  }
  
  //remove all contents
  fParticleDataMap1.clear();
  fParticleDataMap2.clear();
  fParticleDataMap3.clear();
  fParticleDataMap4.clear();
  fParticleDataMap5.clear();
  fParticleDataMap6.clear();
                          
  //restore default format         
  G4cout.precision(dfprec);   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
