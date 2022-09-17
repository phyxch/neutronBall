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
  fEdep1 = fEdep2 = fEdep3 = fEdep4 = fEdep5 = fEdep6 = 0;
  tfEdep1 = tfEdep2 = tfEdep3 = tfEdep4 = tfEdep5 = tfEdep6 = 0; 
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

void nbRun::CountProcesses(const G4VProcess* process, G4int iVol) 
{
  if (process == nullptr) return;  
  G4String procName = process->GetProcessName();
  
  // layer 1
  if (iVol == 1) {
    std::map<G4String,G4int>::iterator it1 = fProcCounter1.find(procName);
    if ( it1 == fProcCounter1.end()) {
      fProcCounter1[procName] = 1;
    }
    else {
      fProcCounter1[procName]++; 
    }
  }
    
  // layer 2
  if (iVol == 2) {
    std::map<G4String,G4int>::iterator it2 = fProcCounter2.find(procName);
    if ( it2 == fProcCounter2.end()) {
      fProcCounter2[procName] = 1;
    }
    else {
      fProcCounter2[procName]++; 
    }    
  }
  
  // layer 3
  if (iVol == 3) {
    std::map<G4String,G4int>::iterator it3 = fProcCounter3.find(procName);
    if ( it3 == fProcCounter3.end()) {
      fProcCounter3[procName] = 1;
    }
    else {
      fProcCounter3[procName]++; 
    }
  }
  
  // layer 4
  if (iVol == 4) {
    std::map<G4String,G4int>::iterator it4 = fProcCounter4.find(procName);
    if ( it4 == fProcCounter4.end()) {
      fProcCounter4[procName] = 1;
    }
    else {
      fProcCounter4[procName]++; 
    }
  }
  
  // layer 5
  if (iVol == 5) {
    std::map<G4String,G4int>::iterator it5 = fProcCounter5.find(procName);
    if ( it5 == fProcCounter5.end()) {
      fProcCounter5[procName] = 1;
    }
    else {
      fProcCounter5[procName]++; 
    }
  }
  
  // world
  if (iVol == 6) {
    std::map<G4String,G4int>::iterator it6 = fProcCounter6.find(procName);
    if ( it6 == fProcCounter6.end()) {
      fProcCounter6[procName] = 1;
    }
    else {
      fProcCounter6[procName]++; 
    }
  }
}
                  
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

void nbRun::AddEdep(G4double edep1, G4double edep2, G4double edep3, G4double edep4, G4double edep5, G4double edep6)
{ 
  fEdep1  += edep1;
  tfEdep1 += edep1*edep1;
  
  fEdep2  += edep2;
  tfEdep2 += edep2*edep2; 
  
  fEdep3  += edep3;
  tfEdep3 += edep3*edep3;
  
  fEdep4  += edep4;
  tfEdep4 += edep4*edep4;
  
  fEdep5  += edep5;
  tfEdep5 += edep5*edep5;
  
  fEdep6  += edep6;
  tfEdep6 += edep6*edep6;
}
                 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nbRun::Merge(const G4Run* run)
{
  const nbRun* localRun = static_cast<const nbRun*>(run);
  
  //primary particle info
  //
  fParticle = localRun->fParticle;
  fEkin     = localRun->fEkin;
  
  // accumulate sums
  fEdep1  += localRun->fEdep1; 
  tfEdep1 += localRun->tfEdep1; 
  
  fEdep2  += localRun->fEdep2;
  tfEdep2 += localRun->tfEdep2;
  
  fEdep3  += localRun->fEdep3;
  tfEdep3 += localRun->tfEdep3;
  
  fEdep4  += localRun->fEdep4;
  tfEdep4 += localRun->tfEdep4;
  
  fEdep5  += localRun->fEdep5;
  tfEdep5 += localRun->tfEdep5;
  
  fEdep6  += localRun->fEdep6;
  tfEdep6 += localRun->tfEdep6;  
      
  //map: processes count in layer 1
  
  std::map<G4String,G4int>::const_iterator itp1;
  for ( itp1 = localRun->fProcCounter1.begin();
        itp1 != localRun->fProcCounter1.end(); ++itp1 ) {

    G4String procName = itp1->first;
    G4int localCount = itp1->second;
    if ( fProcCounter1.find(procName) == fProcCounter1.end()) {
      fProcCounter1[procName] = localCount;
    }
    else {
      fProcCounter1[procName] += localCount;
    }  
  }
  
  //map: processes count in layer 2
  
  std::map<G4String,G4int>::const_iterator itp2;
  for ( itp2 = localRun->fProcCounter2.begin();
        itp2 != localRun->fProcCounter2.end(); ++itp2 ) {

    G4String procName = itp2->first;
    G4int localCount = itp2->second;
    if ( fProcCounter2.find(procName) == fProcCounter2.end()) {
      fProcCounter2[procName] = localCount;
    }
    else {
      fProcCounter2[procName] += localCount;
    }  
  }
  
  //map: processes count in layer 3
  std::map<G4String,G4int>::const_iterator itp3;
  for ( itp3 = localRun->fProcCounter3.begin();
        itp3 != localRun->fProcCounter3.end(); ++itp3 ) {

    G4String procName = itp3->first;
    G4int localCount = itp3->second;
    if ( fProcCounter3.find(procName) == fProcCounter3.end()) {
      fProcCounter3[procName] = localCount;
    }
    else {
      fProcCounter3[procName] += localCount;
    }  
  }
  
  //map: processes count in layer 4
  std::map<G4String,G4int>::const_iterator itp4;
  for ( itp4 = localRun->fProcCounter4.begin();
        itp4 != localRun->fProcCounter4.end(); ++itp4 ) {

    G4String procName = itp4->first;
    G4int localCount = itp4->second;
    if ( fProcCounter4.find(procName) == fProcCounter4.end()) {
      fProcCounter4[procName] = localCount;
    }
    else {
      fProcCounter4[procName] += localCount;
    }  
  }
  
  //map: processes count in layer 5
  std::map<G4String,G4int>::const_iterator itp5;
  for ( itp5 = localRun->fProcCounter5.begin();
        itp5 != localRun->fProcCounter5.end(); ++itp5 ) {

    G4String procName = itp5->first;
    G4int localCount = itp5->second;
    if ( fProcCounter5.find(procName) == fProcCounter5.end()) {
      fProcCounter5[procName] = localCount;
    }
    else {
      fProcCounter5[procName] += localCount;
    }
  }

  //map: processes count in layer 6 **world**
  std::map<G4String,G4int>::const_iterator itp6;
  for ( itp6 = localRun->fProcCounter6.begin();
        itp6 != localRun->fProcCounter6.end(); ++itp6 ) {

    G4String procName = itp6->first;
    G4int localCount = itp6->second;
    if ( fProcCounter6.find(procName) == fProcCounter6.end()) {
      fProcCounter6[procName] = localCount;
    }
    else {
      fProcCounter6[procName] += localCount;
    }
  }


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
  
  // we will print these later; currently commented
  // G4cout << "\n Target   : Length = " 
  //        << G4BestUnit(fDetector->GetTargetLength(),"Length")
  //        << " Radius    = " 
  //        << G4BestUnit(fDetector->GetTargetRadius(),"Length")  
  //        << " Material = " 
  //        << fDetector->GetTargetMaterial()->GetName();
  // G4cout << "\n Detector : Length = " 
  //        << G4BestUnit(fDetector->GetDetectorLength(),"Length")
  //        << " Thickness = " 
  //        << G4BestUnit(fDetector->GetDetectorThickness(),"Length")  
  //        << " Material = " 
  //        << fDetector->GetDetectorMaterial()->GetName() << G4endl;

  if (numberOfEvent == 0) { G4cout.precision(dfprec);   return;}
  
  G4int TotNbofEvents = numberOfEvent;
  
  G4cout << G4endl;
  G4cout << "********** TOTAL ENERGY AND RMS **********" << G4endl;
  
  // total energy & rms deposited in layer 1
  fEdep1 /= TotNbofEvents; tfEdep1 /= TotNbofEvents;
  G4double rmsEdep1 = tfEdep1 - fEdep1*fEdep1;
  if (rmsEdep1>0.) rmsEdep1 = std::sqrt(rmsEdep1);
  else            rmsEdep1 = 0.;
  
  G4cout << "\n Mean energy deposit in layer 1,   in time window = "
         << G4BestUnit(fEdep1,"Energy") << ";  rms = "
         << G4BestUnit(rmsEdep1,    "Energy") 
         << G4endl;
         
  // total energy & rms deposited in layer 2
  fEdep2 /= TotNbofEvents; tfEdep2 /= TotNbofEvents;
  G4double rmsEdep2 = tfEdep2 - fEdep2*fEdep2;
  if (rmsEdep2>0.) rmsEdep2 = std::sqrt(rmsEdep2);
  else            rmsEdep2 = 0.;
  
  G4cout << "\n Mean energy deposit in layer 2,   in time window = "
         << G4BestUnit(fEdep2,"Energy") << ";  rms = "
         << G4BestUnit(rmsEdep2,    "Energy") 
         << G4endl;
         
  // total energy & rms deposited in layer 3
  fEdep3 /= TotNbofEvents; tfEdep3 /= TotNbofEvents;
  G4double rmsEdep3 = tfEdep3 - fEdep3*fEdep3;
  if (rmsEdep2>0.) rmsEdep3 = std::sqrt(rmsEdep3);
  else            rmsEdep3 = 0.;
  
  G4cout << "\n Mean energy deposit in layer 3,   in time window = "
         << G4BestUnit(fEdep3,"Energy") << ";  rms = "
         << G4BestUnit(rmsEdep3,    "Energy") 
         << G4endl;
         
  // total energy & rms deposited in layer 4
  fEdep4 /= TotNbofEvents; tfEdep4 /= TotNbofEvents;
  G4double rmsEdep4 = tfEdep4 - fEdep4*fEdep4;
  if (rmsEdep2>0.) rmsEdep4 = std::sqrt(rmsEdep4);
  else            rmsEdep4 = 0.;
  
  G4cout << "\n Mean energy deposit in layer 4,   in time window = "
         << G4BestUnit(fEdep3,"Energy") << ";  rms = "
         << G4BestUnit(rmsEdep3,    "Energy") 
         << G4endl;
  
  // total energy & rms deposited in layer 5
  fEdep5 /= TotNbofEvents; tfEdep5 /= TotNbofEvents;
  G4double rmsEdep5 = tfEdep5 - fEdep5*fEdep5;
  if (rmsEdep2>0.) rmsEdep5 = std::sqrt(rmsEdep5);
  else            rmsEdep5 = 0.;
  
  G4cout << "\n Mean energy deposit in layer 5,   in time window = "
         << G4BestUnit(fEdep5,"Energy") << ";  rms = "
         << G4BestUnit(rmsEdep5,    "Energy") 
         << G4endl;
         
  // total energy & rms deposited in layer 6 (world)
  fEdep6 /= TotNbofEvents; tfEdep6 /= TotNbofEvents;
  G4double rmsEdep6 = tfEdep6 - fEdep6*fEdep6;
  if (rmsEdep2>0.) rmsEdep6 = std::sqrt(rmsEdep6);
  else            rmsEdep6 = 0.;
  
  G4cout << "\n Mean energy deposit in layer 6 (world),   in time window = "
         << G4BestUnit(fEdep6,"Energy") << ";  rms = "
         << G4BestUnit(rmsEdep6,    "Energy") 
         << G4endl;
  
  
  G4cout << G4endl;
  G4cout << "********** PROCESS COUNTS PER LAYER **********" << G4endl;
  
  G4int index = 0;
  
  // frequency of processes in layer 1
  G4cout << "\n Process calls frequency in layer 1 :" << G4endl;
  std::map<G4String,G4int>::iterator it1;    
  for (it1 = fProcCounter1.begin(); it1 != fProcCounter1.end(); it1++) {
     G4String procName = it1->first;
     G4int    count    = it1->second;
     G4String space = " "; if (++index%3 == 0) space = "\n";
     G4cout << " " << std::setw(20) << procName << "="<< std::setw(7) << count
            << space;
  }
  G4cout << G4endl;
  
  // frequency of processes in layer 2
  G4cout << "\n Process calls frequency in layer 2 :" << G4endl;
  std::map<G4String,G4int>::iterator it2;    
  for (it2 = fProcCounter2.begin(); it2 != fProcCounter2.end(); it2++) {
     G4String procName = it2->first;
     G4int    count    = it2->second;
     G4String space = " "; if (++index%3 == 0) space = "\n";
     G4cout << " " << std::setw(20) << procName << "="<< std::setw(7) << count
            << space;
  }
  G4cout << G4endl;
  
  // frequency of processes in layer 3
  G4cout << "\n Process calls frequency in layer 3 :" << G4endl;
  std::map<G4String,G4int>::iterator it3;    
  for (it3 = fProcCounter3.begin(); it3 != fProcCounter3.end(); it3++) {
     G4String procName = it3->first;
     G4int    count    = it3->second;
     G4String space = " "; if (++index%3 == 0) space = "\n";
     G4cout << " " << std::setw(20) << procName << "="<< std::setw(7) << count
            << space;
  }
  G4cout << G4endl;
  
  // frequency of processes in layer 4
  G4cout << "\n Process calls frequency in layer 4 :" << G4endl;
  std::map<G4String,G4int>::iterator it4;    
  for (it4 = fProcCounter4.begin(); it4 != fProcCounter4.end(); it4++) {
     G4String procName = it4->first;
     G4int    count    = it4->second;
     G4String space = " "; if (++index%3 == 0) space = "\n";
     G4cout << " " << std::setw(20) << procName << "="<< std::setw(7) << count
            << space;
  }
  G4cout << G4endl;
  
  // frequency of processes in layer 5
  G4cout << "\n Process calls frequency in layer 5 :" << G4endl;
  std::map<G4String,G4int>::iterator it5;    
  for (it5 = fProcCounter5.begin(); it5 != fProcCounter5.end(); it5++) {
     G4String procName = it5->first;
     G4int    count    = it5->second;
     G4String space = " "; if (++index%3 == 0) space = "\n";
     G4cout << " " << std::setw(20) << procName << "="<< std::setw(7) << count
            << space;
  }
  G4cout << G4endl;
  
  // frequency of processes in layer 6 : **world**
  G4cout << "\n Process calls frequency in layer 6 (world) :" << G4endl;
  std::map<G4String,G4int>::iterator it6;    
  for (it6 = fProcCounter6.begin(); it6 != fProcCounter6.end(); it6++) {
     G4String procName = it6->first;
     G4int    count    = it6->second;
     G4String space = " "; if (++index%3 == 0) space = "\n";
     G4cout << " " << std::setw(20) << procName << "="<< std::setw(7) << count
            << space;
  }
  
  G4cout << G4endl;
  G4cout << G4endl;
  G4cout << "********** PARTICLE COUNTS PER LAYER **********" << G4endl;
    
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
  
  // particles count in layer 6 - **world**
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
 
  // activities in VR mode
  WriteActivity(numberOfEvent);
 
  //remove all contents in fProcCounter, fCount 
  fProcCounter1.clear();
  fProcCounter2.clear();
  fProcCounter3.clear();
  fProcCounter4.clear();
  fProcCounter5.clear();
  fProcCounter6.clear();
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

void nbRun::WriteActivity(G4int nevent)
{
 G4ProcessTable *pTable = G4ProcessTable::GetProcessTable();
 G4Radioactivation* rDecay = (G4Radioactivation *)
         pTable->FindProcess("Radioactivation", "GenericIon");
   
 // output the induced radioactivities (in VR mode only)
 //
 if ((rDecay == 0) || (rDecay->IsAnalogueMonteCarlo())) return;
 
 G4String fileName = G4AnalysisManager::Instance()->GetFileName() + ".activity";
 std::ofstream outfile (fileName, std::ios::out );
 
 std::vector<G4RadioactivityTable*> theTables =
                              rDecay->GetTheRadioactivityTables();

 for (size_t i = 0 ; i < theTables.size(); i++) {
    G4double rate, error;
    outfile << "Radioactivities in decay window no. " << i << G4endl;
    outfile << "Z \tA \tE \tActivity (decays/window) \tError (decays/window) "
            << G4endl;

    map<G4ThreeVector,G4TwoVector> *aMap = theTables[i]->GetTheMap();
    map<G4ThreeVector,G4TwoVector>::iterator iter;
    for (iter=aMap->begin(); iter != aMap->end(); iter++) {
       rate = iter->second.x()/nevent;
       error = std::sqrt(iter->second.y())/nevent;
       if (rate < 0.) rate = 0.;                // statically it can be < 0.
       outfile << iter->first.x() <<"\t"<< iter->first.y() <<"\t"
               << iter->first.z() << "\t" << rate <<"\t" << error << G4endl;
    }
    outfile << G4endl;
 }
 outfile.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

/*
void nbSteppingAction::UserSteppingAction(const G4Step* aStep)
{ 
    // instance of analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // instance of run class
    // nbRun* run = static_cast<nbRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    
    // get particle information
    G4ParticleDefinition* particle = aStep->GetTrack()->GetDefinition();
    G4String particleName   = particle->GetParticleName();    	
    
    G4bool isFirstStep = aStep->IsFirstStepInVolume();
    G4String volumeName = aStep->GetTrack()->GetVolume()->GetName();
    
    G4double x=aStep->GetPreStepPoint()->GetPosition().x();
    G4double y=aStep->GetPreStepPoint()->GetPosition().y();
    G4double z=aStep->GetPreStepPoint()->GetPosition().z();
    G4double px=aStep->GetPostStepPoint()->GetPosition().x();
    G4double py=aStep->GetPostStepPoint()->GetPosition().y();
    G4double pz=aStep->GetPostStepPoint()->GetPosition().z();

    if(isFirstStep)
    {
        // store the particle data
        // fill columns of ntuple id 1
    	analysisManager->FillNtupleSColumn(1, 0, volumeName);
        analysisManager->FillNtupleSColumn(1, 1, particleName);
        analysisManager->FillNtupleDColumn(1, 2, x);
        analysisManager->FillNtupleDColumn(1, 3, y);
        analysisManager->FillNtupleDColumn(1, 4, z);
        analysisManager->FillNtupleDColumn(1, 5, px);
        analysisManager->FillNtupleDColumn(1, 6, py);
        analysisManager->FillNtupleDColumn(1, 7, pz);
        // add this row to ntuple id 1
        analysisManager->AddNtupleRow(1);
    }
}
*/
