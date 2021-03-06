#ifndef AllPass_h
#define AllPass_h 1

#include "AnalysisTool.hh"
#include "StackingTool.hh"

#include <sstream>   // stringstream

using namespace std;

class AllPass : public AnalysisTool {
  public:
    AllPass();
    ~AllPass();

    virtual void PrintTool();

  //using AnalysisTool::getInterest;
    virtual bool getInterest();
    virtual bool getInterest(int particle, int sturface);
    virtual bool getInterest(int particle,
			     int sturface,
			     int creationProcess,
			     int flagPhotoElectron);
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
