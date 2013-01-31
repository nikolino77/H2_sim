// Martin Goettlich @ DESY
//
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include <vector>

using namespace std;

class CreateTree
{
  private:

  TTree*              ftree;
  TString             fname;

  public:

  CreateTree(TString name);
  ~CreateTree();

  TTree*              GetTree() const { return ftree; };
  TString             GetName() const { return fname;};
  Int_t               Fill() { return this->GetTree()->Fill(); };
  Bool_t              Write();
  void                Clear();
  static CreateTree*  Instance() { return fInstance; };
  static CreateTree*  fInstance;

  Int_t               Run;
  Int_t               Event;

  
  Float_t InitialPositionX;
  Float_t InitialPositionY;
  Float_t InitialPositionZ;
  
  Float_t InitalMomentumDirectionX;
  Float_t InitalMomentumDirectionY;
  Float_t InitalMomentumDirectionZ;

  Int_t		 depositionCounter;
  vector<float> depositionX;
  vector<float> depositionY;
  vector<float> depositionZ;
  
  Float_t Total_energy[9];
  
  Float_t Total_energy_absorber;
  Float_t Total_energy_world;
  
};
