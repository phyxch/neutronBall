// learning resource: https://www.slac.stanford.edu/xorg/geant4/SLACTutorial14/HandsOn1/
// learning resource: https://www.slac.stanford.edu/xorg/geant4/SLACTutorial14/Agenda.html
// learning resource: https://indico.cern.ch/event/647154/contributions/2714212/attachments/1529029/2397032/BookForApplicationDevelopers.pdf

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Types.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4SteppingVerbose.hh"
#include "Randomize.hh"

#include "nbDetectorConstruction.hh"
#include "nbActionInitialization.hh"

#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

// #include "QGSP_BERT.hh"
// #include "QGSP_BERT_HP.hh"
// #include "LBE.hh"
// #include "Shielding.hh"

// #include "nbDriftPhysics.hh"
// #include "G4ProcessManager.hh"
// #include "G4PhysListFactory.hh"
// #include "G4ParticleTable.hh"
// #include "G4StepLimiter.hh"

#include "nbPhysicsList.hh"


// #include "src/nbCustomPhysicsProcess.cc"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//namespace {
//  void PrintUsage() {
//    G4cerr << " Usage: " << G4endl;
//    G4cerr << " neutronBhttps://www.slac.stanford.edu/xorg/geant4/SLACTutorial14/HandsOn1/#ex1aall [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
//    G4cerr << "   note: -t option is available only for multi-threaded mode."
//           << G4endl;
//  }
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {

  //detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if (argc == 1) ui = new G4UIExecutive(argc,argv);

  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  //use G4SteppingVerboseWithUnits
  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);

  //construct the run manager
  auto runManager = G4RunManagerFactory::CreateRunManager();  
  if (argc==3) {
    G4int nThreads = G4UIcommand::ConvertToInt(argv[2]);
    runManager->SetNumberOfThreads(nThreads);
  }  

  //set mandatory initialization classes
  nbDetectorConstruction* det= new nbDetectorConstruction;
  runManager->SetUserInitialization(det);
  
  nbPhysicsList* phys = new nbPhysicsList;
  runManager->SetUserInitialization(phys);

  //////////////////// physics lists code /////////////
  // G4PhysListFactory physFactory;
  // auto qgsp_hp_bert = "QGSP_BERT_HP";
  // auto phys = physFactory.GetReferencePhysList(qgsp_hp_bert);
  // include more physics process from nbPhysicsList class 
  // auto physList = new nbPhysicsList;
  // phys->RegisterPhysics(new nbPhysicsList);
  // runManager->SetUserInitialization(new nbPhysicsList);
  
  //////////////////// OLD CODE ///////////////////////
  // auto physicsList = new QGSP_BERT_HP;
  // runManager->SetUserInitialization(physicsList);
  // code for physics list ends here
  //////////////////// OLD CODE ENDS //////////////////
 
  // G4PhysListFactory physFactory;
  // auto qgsp_hp_bert = "QGSP_BERT_HP";
  // G4VModularPhysicsList* phys = physFactory.GetReferencePhysList(qgsp_hp_bert); // return G4VModularPhysicsList (has RegisterPhysics func)
  // 
  // nbDriftPhysics* driftPhysicsProcess = new nbDriftPhysics();
  
  // G4ParticleTable::G4PTblDicIterator* particleIterator
  // = G4ParticleTable::GetParticleTable()->GetIterator();
  // 
  // G4cout << "particleIterator is created" << G4endl;
  // 
  // while ((*particleIterator)()){
  //   
  //   G4cout << "particleIterator is iterating.." << G4endl;
  //   
  //   // get particle
  //   G4ParticleDefinition* particle = particleIterator->value();
  //   
  //   // create processManager instance
  //   G4ProcessManager* pmanager = particle->GetProcessManager();
  //   
  //   G4cout << "process manager created.." << G4endl;
  //   
  //   // check if process is applicable to this particle    
  //   if (driftPhysicsProcess->IsApplicable(*particle) && pmanager)
  //   {
  //       G4cout << "pName: " << particle->GetParticleName() << " ADDED TRUE" << G4endl;
  //       // add process for that particle
	 //       pmanager ->AddContinuousProcess(driftPhysicsProcess);
  //   }
  // }
  
  //////////////////////// ANOTHER IMPLEMENTATION OF PARTICLE ITERATOR ///////////////////////////
  // // Get a pointer to the particle table
  // G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  // // Get a vector of all of the particles in the table
  // G4int entries = particleTable::entries();
  // 
  // G4cout << "entries: " << entries << G4endl;
  // 
  // for(G4int i=0;i<entries;i++)
  // {
  //   G4ParticleDefinition* particle = particleTable->GetParticle(i);
  //   G4ProcessManager* pmanager = particle->GetProcessManager();
  //   if (driftPhysicsProcess->IsApplicable(*particle) && pmanager)
  //   {
  //       G4cout << "pName: " << particle->GetParticleName() << " ADDED TRUE" << G4endl;
  //       // add process for that particle
	 //       pmanager ->AddContinuousProcess(driftPhysicsProcess);
  //   }
  // }
  // 
  // runManager->SetUserInitialization(phys);
  // 
  // G4cout << "******* drift physics added successfully *******" << G4endl;
  
  

  // include detector geometry
  runManager->SetUserInitialization(new nbActionInitialization(det));
  

  //initialize G4 kernel
  runManager->Initialize();

  //initialize visualization
  G4VisManager* visManager = nullptr;

  //get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui)  {
   //interactive mode
   visManager = new G4VisExecutive;
   visManager->Initialize();
   UImanager->ApplyCommand("/control/execute vis.mac");
   ui->SessionStart();
   delete ui;
  }
  else  {
   //batch mode
   G4String command = "/control/execute ";
   G4String fileName = argv[1];
   UImanager->ApplyCommand(command+fileName);
  }

  //job termination
  delete visManager;
  delete runManager;
}
