// learning resource: https://www.slac.stanford.edu/xorg/geant4/SLACTutorial14/HandsOn1/
// learning resource: https://www.slac.stanford.edu/xorg/geant4/SLACTutorial14/Agenda.html
// learning resource: https://indico.cern.ch/event/647154/contributions/2714212/attachments/1529029/2397032/BookForApplicationDevelopers.pdf

// Created on 10/13/2021:  hexc, Mayur, Tien, Weisen, Austin
// This GEANT4 simulation is to study Bonne Ball efficiency

// last updated on 07/06/2022: Mayur Aitavadekar
// added physics list code in the main itself so that we do not need to created physicsList.cc code 

#include "nbDetectorConstruction.hh"
#include "nbActionInitialization.hh"
#include "nbPhysicsList.hh"

#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"
#include "G4SteppingVerbose.hh"
#include "G4UIcommand.hh"

// header files for physics list
#include "FTFP_BERT.hh"
#include "G4PhysListFactory.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4Radioactivation.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

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
  //
  runManager->SetUserInitialization(new nbDetectorConstruction);
  runManager->SetUserInitialization(new nbPhysicsList);

  runManager->SetUserInitialization(new nbActionInitialization);

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


//int main(int argc,char** argv)
//{

//  /* old code
//  // Evaluate arguments
//  //
//  if ( argc > 7 ) {
//    PrintUsage();
//    return 1;
//  }
//  
//  G4String macro;
//  G4String session;
//  #ifdef G4MULTITHREADED
//  G4int nThreads = 0;
//  #endif
//  for ( G4int i=1; i<argc; i=i+2 ) {
//    if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
//    else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
//  #ifdef G4MULTITHREADED
//    else if ( G4String(argv[i]) == "-t" ) {
//      nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
//    }
//  #endif
//    else {
//      PrintUsage();
//      return 1;
//    }
//  }

//  // Detect interactive mode (if no macro provided) and define UI session
//  G4UIExecutive* ui = nullptr;
//  if ( ! macro.size() ) {
//    ui = new G4UIExecutive(argc, argv, session);
//  }
//  */
//  
//  G4UIExecutive* ui = 0;
//  if (argc == 1) ui = new G4UIExecutive(argc,argv);


//  // Optionally: choose a different Random engine...
//  //
//  // G4Random::setTheEngine(new CLHEP::MTwistEngine);

//  // Construct the default run manager
//  auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
//  if (argc==3) {
//    G4int nThreads = G4UIcommand::ConvertToInt(argv[2]);
//    runManager->SetNumberOfThreads(nThreads);
//  }  

//  /*
//  #ifdef G4MULTITHREADED
//  if ( nThreads > 0 ) {
//    runManager->SetNumberOfThreads(nThreads);
//  }
//  #endif
//  */

//  // Set mandatory initialization classes
//  //
//  // Set detector class
//  auto detConstruction = new nbDetectorConstruction();
//  runManager->SetUserInitialization(detConstruction);
//  // 
//  // Set physicsLists
//  runManager->SetUserInitialization(new nbPhysicsList);

//  // Create instance of G4PhysListFactory
//  G4PhysListFactory *physListFactory = new G4PhysListFactory();
//  //  G4VModularPhysicsList* phys = NULL;	
//  //  phys = physListFactory->GetReferencePhysList("FTFP_BERT");
//  //  // now let's add radioactivation physics list  
//  //  auto* rd1 = new G4DecayPhysics();
//  //  auto* rd2 = new G4RadioactiveDecayPhysics();
//  //  phys->RegisterPhysics(rd1);
//  //  phys->RegisterPhysics(rd2);
//  //  phys->DumpList();
// 
//  //  runManager->SetUserInitialization(phys);
//  // print added physics lists
//  const std::vector<G4String> v = physListFactory->AvailablePhysLists();
//  G4cout<<"following are added physics lists in the simulation : "<<G4endl;
//  for (auto i: v) {
//	G4cout << i <<" ";
//  }

//  // setup for action initialization
//  auto actionInitialization = new nbActionInitialization();
//  runManager->SetUserInitialization(actionInitialization);

//  // Initialize visualization
//  auto visManager = new G4VisExecutive;
//  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
//  // G4VisManager* visManager = new G4VisExecutive("Quiet");
//  visManager->Initialize();

//  // Get the pointer to the User Interface manager
//  auto UImanager = G4UImanager::GetUIpointer();

//  // Process macro or start UI session
//  //
//  /*
//  if ( macro.size() ) {
//    // batch mode
//    G4String command = "/control/execute ";
//    UImanager->ApplyCommand(command+macro);
//  }
//  else  {
//    // interactive mode : define UI session
//    UImanager->ApplyCommand("/control/execute init_vis.mac");
//    if (ui->IsGUI()) {
//      UImanager->ApplyCommand("/control/execute gui.mac");
//    }
//    ui->SessionStart();
//    delete ui;
//  }
//  */
//  if (ui)  {
//   //interactive mode
//   visManager = new G4VisExecutive;
//   visManager->Initialize();
//   UImanager->ApplyCommand("/control/execute vis.mac");
//   ui->SessionStart();
//   delete ui;
//  }
//  else  {
//   //batch mode
//   G4String command = "/control/execute ";
//   G4String fileName = argv[1];
//   UImanager->ApplyCommand(command+fileName);
//  }


//  // Job termination
//  // Free the store: user actions, physics_list and detector_description are
//  // owned and deleted by the run manager, so they should not be deleted 
//  // in the main() program !

//  delete visManager;
//  delete runManager;
//}

////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
