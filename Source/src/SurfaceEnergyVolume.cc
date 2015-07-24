#include "SurfaceEnergyVolume.hh"
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

SurfaceEnergyVolume::SurfaceEnergyVolume() : AnalysisTool() {}

SurfaceEnergyVolume::~SurfaceEnergyVolume() {}

void SurfaceEnergyVolume::PrintTool() {
  cout << "The analysis tool in use is SurfaceEnergyVolume" << endl;
}

bool SurfaceEnergyVolume::getInterest() {}

bool SurfaceEnergyVolume::getInterest(int particle, int surface) {}

bool SurfaceEnergyVolume::getInterest(int particle,
				      int surface,
				      int creationProcess,
				      int flagPhotoElectron) {}


bool SurfaceEnergyVolume::getInterest(int particle,
				      int surface,
				      int volume) {
  if (particle == 1 && surface == 1 && volume == 3) return true;
  else return false;				       
}

bool SurfaceEnergyVolume::getInterest(int particle,
				      int surface,
				      double energy) {}

string SurfaceEnergyVolume::processData() {}

string SurfaceEnergyVolume::processData(int id, float energy) {
  stringstream outLine;
  outLine << energy;
  return outLine.str();
}

string SurfaceEnergyVolume::processData(int creation_process) {}

