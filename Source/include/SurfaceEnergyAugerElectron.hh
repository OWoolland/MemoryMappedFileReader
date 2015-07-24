#ifndef SurfaceEnergyAugerElectron_h
#define SurfaceEnergyAugerElectron_h 1

#include "AnalysisTool.hh"
#include "StackingTool.hh"

#include <sstream>   // stringstream

using namespace std;

class SurfaceEnergyAugerElectron : public AnalysisTool {
  public:
    SurfaceEnergyAugerElectron();
    ~SurfaceEnergyAugerElectron();

    virtual void PrintTool();

  //using AnalysisTool::getInterest;
    virtual bool getInterest();
    virtual bool getInterest(int particle, int surface);
    virtual bool getInterest(int particle,
			     int sturface,
			     int creationProcess,
			     int flagAugerElectron);
    virtual bool getInterest(int particle,
			     int sturface,
			     int volume);
    virtual bool getInterest(int particle,
			     int surface,
			     double energy);
  
    virtual string processData(); 
    virtual string processData(int id, float energy);
    virtual string processData(int creation_process);
  
  private:
};

#endif
