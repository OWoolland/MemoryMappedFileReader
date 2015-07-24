#include "SurfaceEnergyEnergyRange.hh"
#include "AnalysisTool.hh"

#include <fstream>   // reading file
#include <iostream>  // printing
#include <pthread.h> // multithreading
#include <unistd.h>  // delay (usleep)
#include <sstream>   // stringsream
#include <vector>    // stacking
#include <sstream>   // stringstream

using namespace std;

/**************************************************
Flow of class:
  - Receive relevant variables from worker thread
  - Check for interest
  - Process data and format for outputting
**************************************************/

SurfaceEnergyEnergyRange::SurfaceEnergyEnergyRange() : AnalysisTool() {}

SurfaceEnergyEnergyRange::~SurfaceEnergyEnergyRange() {}

void SurfaceEnergyEnergyRange::PrintTool() {
  cout << "The analysis tool in use is SurfaceEnergyEnergyRange" << endl;
}

bool SurfaceEnergyEnergyRange::getInterest() {}

bool SurfaceEnergyEnergyRange::getInterest(int particle, int surface) {}

bool SurfaceEnergyEnergyRange::getInterest(int particle,
				      int surface,
				      int creationProcess,
				      int flagPhotoElectron) {}

bool SurfaceEnergyEnergyRange::getInterest(int particle,
				      int surface,
				      int volume) {
  if (particle == 1 && surface == 1 && volume == 3) return true;
  else return false;				       
}

bool SurfaceEnergyEnergyRange::getInterest(int particle,
				      int surface,
				      double energy) {
  if (particle == 1 && surface == 1 &&
      energy >= 1120 && energy <= 1124) return true;
  else return false;				       
}

string SurfaceEnergyEnergyRange::processData() {}

string SurfaceEnergyEnergyRange::processData(int id, float energy) {}

string SurfaceEnergyEnergyRange::processData(int creation_process) {
  stringstream outLine;
  outLine << creation_process;
  return outLine.str();
}

