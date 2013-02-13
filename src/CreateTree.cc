#include "CreateTree.hh"
#include <vector>

CreateTree* CreateTree::fInstance = NULL;

using namespace std;

CreateTree::CreateTree(TString name, Bool_t energy_fiber, Bool_t init_data, Bool_t pos_fiber, Bool_t optical)
{
	if(fInstance) 
	{
    	  return;
  	}
  	
  	this -> ENERGY_FIBER 	= energy_fiber;
	this -> INIT_DATA    	= init_data;
	this -> POS_FIBER    	= pos_fiber;
	this -> OPTICAL		= optical;
	
  	this -> fInstance = this;
  	this -> fname     = name;
  	this -> ftree     = new TTree("tree","name");

  	this->GetTree()->Branch("Event",&this->Event,"Event/I");

	if( this -> OPTICAL )
	{
	  this->GetTree()->Branch("Num_phot_cer",&this->Num_phot_cer,"Num_phot_cer[9]/I");
	  if( !this -> ENERGY_FIBER )
	  {
            this->GetTree()->Branch("Total_energy",&this->Total_energy,"Total_energy[9]/F");
	  } 
	}
	
	if( this -> INIT_DATA )
	{
	  this->GetTree()->Branch("InitialPositionX",&this->InitialPositionX,"InitialPositionX/F");
	  this->GetTree()->Branch("InitialPositionY",&this->InitialPositionY,"InitialPositionY/F");
	  this->GetTree()->Branch("InitialPositionZ",&this->InitialPositionZ,"InitialPositionZ/F");
	
	  this->GetTree()->Branch("InitalMomentumDirectionX",&this->InitalMomentumDirectionX,"InitalMomentumDirectionX/F");
	  this->GetTree()->Branch("InitalMomentumDirectionY",&this->InitalMomentumDirectionY,"InitalMomentumDirectionY/F");
	  this->GetTree()->Branch("InitalMomentumDirectionZ",&this->InitalMomentumDirectionZ,"InitalMomentumDirectionZ/F");
	}
	
	if( this -> POS_FIBER)
	{ 
	  this->GetTree()->Branch("depositionX",&this->depositionX);
	  this->GetTree()->Branch("depositionY",&this->depositionY);
	  this->GetTree()->Branch("depositionZ",&this->depositionZ);  
	  this->GetTree()->Branch("Energy_deposited",&this->Energy_deposited);
	}
	
	if( this -> ENERGY_FIBER)
	{
	  this->GetTree()->Branch("Total_energy",&this->Total_energy,"Total_energy[9]/F");
	}
	 
	this->GetTree()->Branch("Total_energy_absorber",&this->Total_energy_absorber,"Total_energy_absorber/F");
	this->GetTree()->Branch("Total_energy_world",&this->Total_energy_world,"Total_energy_world/F");

  	this->Clear();
}

CreateTree::~CreateTree()
{
}

Bool_t CreateTree::Write()
{
  	TString filename = this->GetName();
  	filename+=".root";
  	TFile* file = new TFile(filename,"RECREATE");
  	this->GetTree()->Write();
  	file->Write();
  	file->Close();
  	return true;
}

void CreateTree::Clear()
{
  	Event			= 0;
	
	Total_energy_absorber	= 0;
	Total_energy_world	= 0;
	
	if( this -> OPTICAL )
	{
	  for (int iF = 0; iF < 9; iF++) 
	  {
	    Num_phot_cer[iF] = 0;
	    if(!this -> ENERGY_FIBER)
	    {
	      Total_energy[iF] = 0;	  
	    }  
	  }	  
	}
	
	if( this -> INIT_DATA )
	{
	  InitialPositionX 	= 0;
	  InitialPositionY 	= 0;
	  InitialPositionZ 	= 0;
	
	  InitalMomentumDirectionX = 0;
	  InitalMomentumDirectionY = 0;
	  InitalMomentumDirectionZ = 0;
	}
	
	if( this -> ENERGY_FIBER)
	{
	  for (int iF = 0; iF < 9; iF++) 
	  {
	    Total_energy[iF] = 0;	  
	  }
	}
	  
	if( this -> POS_FIBER)
	{
	  depositionX.clear();		
	  depositionY.clear();		
	  depositionZ.clear();
	  Energy_deposited.clear();
	}
}
