#include "PlottingTool.hh"
#include "StackingTool.hh"
#include "MemMapRead.hh"
#include "WorkerManager.hh"
#include "WritingTool.hh"

#include "AllPass.hh"
#include "AnalysisTool.hh"
#include "SurfaceEnergy.hh"
#include "SurfaceEnergyPhotoElectron.hh"
#include "SurfaceEnergyAugerElectron.hh"
#include "SurfaceEnergyVolume.hh"

#include <iostream>  // printing
#include <fstream>   // reading file
#include <unistd.h>  // delay (usleep) , geopt
#include <string.h>  // strcmp
#include <stdlib.h>  // abort

using namespace std;

/**************************************************
Flow of class:
  - Process the command line parameters
  - Create the stacking tool
  - Create the analysis tool
  - Create the worker threads
  - Create the file reader
  - At EOF ensure the stack is empty
  - Destroy all objects
  - Call the plotting tool
**************************************************/

int main(int argc, char* argv[])
{
  // Process command line parameters

  if (argc < 2) {
    cerr << "Usage: (NOT IMPLIMENTED)" << argv[0] << " <options> DATAFILE OUTFILE\n"
	 << "Options:\n"
	 << "\t-h,--help\t\tShow this help message\n"
	 << "\t-t,--tool TOOL\t\tSelect an analysis tool\n"
	 << endl;
    return 0;
  }

  const char * fileName = "defaultFileIn.csv";
  const char * outFileName = "defaultFileOut.csv";

  // Declare all possible analysis tools
  
  AllPass* allPass = new AllPass();
  AnalysisTool* analysisTool = new AnalysisTool();
  SurfaceEnergy* surfaceEnergy = new SurfaceEnergy();
  SurfaceEnergyPhotoElectron* surfaceEnergyPhotoElectron = new SurfaceEnergyPhotoElectron();
  SurfaceEnergyAugerElectron* surfaceEnergyAugerElectron = new SurfaceEnergyAugerElectron();
  SurfaceEnergyVolume* surfaceEnergyVolume = new SurfaceEnergyVolume();

  // Select analysis tool based on command line switch
  
  int opt;
  while ((opt = getopt(argc, argv, "t:")) != -1) {
    switch(opt) {
    case 't': 
      if (strcmp(optarg, "SurfaceEnergy")==0) {
	analysisTool = surfaceEnergy;
      } else if (strcmp(optarg, "SurfaceEnergyPhotoElectron")==0) {
	analysisTool = surfaceEnergyPhotoElectron;
      } else if (strcmp(optarg, "SurfaceEnergyAugerElectron")==0) {
	analysisTool = surfaceEnergyAugerElectron;
      }	else if (strcmp(optarg, "SurfaceEnergyVolume")==0) {
	analysisTool = surfaceEnergyVolume;
      } else if (strcmp(optarg, "AllPass")==0) {
	analysisTool = allPass;
      } else {
	cout << "No tool specified" << endl;
      }
      break;
    default :
      abort();
    }
  }

  // Parse file names from command line switch
  
  if ((argc-optind)==2) {
    fileName = argv[optind];
    outFileName = argv[optind+1];
  } else {
    printf("Input and output file must be specified\n");
    abort();
  }
  analysisTool->PrintTool();
  cout << "fileName: " << fileName << " outFileName: " << outFileName << endl;

  usleep(1000);
  
  // Create stacking tool 
  StackingTool* stackTool = new StackingTool;
  
  // Create file reader thread
  MemMapRead* memMapReader = new MemMapRead(fileName, analysisTool, stackTool);
  memMapReader->beginReader();

  // Create the writing stack
  WritingTool* writeTool = new WritingTool(outFileName, stackTool, memMapReader);
  writeTool->beginWriter();  

  // Create worker threads
  WorkerManager* workerMan = new WorkerManager(analysisTool, stackTool, writeTool);
  workerMan->beginThreads(22);
  
  // Main loop
  usleep(100000); 
  while((memMapReader->getFinished()==0)||
	(stackTool->getStackSize()>0)||
	(writeTool->getWriteStackSize()>0)
	) {
    //cout << "In: " << stackTool->getStackSize()
    //	 << " Out: " << writeTool->getWriteStackSize()
    //	 << endl;
    memMapReader->printCurrentProgress();
    usleep(60000000);
  }

  // Call plotting tool

  PlottingTool* plotter = new PlottingTool();
  // plotter->setTitle("10^7 Photons");
  //plotter->setXLabel("Energy (eV)");
  //plotter->setYLabel("Count");

  plotter->setFile(outFileName);
  
  plotter->setPlotParameters("");
  
  //plotter->plotXY(1,  // xCol
  //		  2); // yCol

  plotter->setPlotParameters("smooth freq with boxes notitle");

  plotter->plotHist(1458, // nBins
  		    1458,     // minValue
  		    0, // maxValue
		    1);    // file column
}

