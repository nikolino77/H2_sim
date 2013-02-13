#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "EventAction.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <fstream>
#include "CreateTree.hh"
#include "ExN06DetectorConstruction.hh"
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

using namespace std;

SteppingAction::SteppingAction()
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step * theStep)
{
  if(theStep->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) 
  { 
    theStep->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
  }
  else
  {
    G4StepPoint		*thePrePoint	= theStep      -> GetPreStepPoint();
    G4VPhysicalVolume	*thePrePV	= thePrePoint  -> GetPhysicalVolume();
    G4StepPoint		*thePostPoint	= theStep      -> GetPostStepPoint();
    //G4VPhysicalVolume	*thePostPV	= thePostPoint -> GetPhysicalVolume();
  
    Float_t energy = theStep->GetTotalEnergyDeposit()/GeV;
  
    if (energy > 0)
    {	
      if(CreateTree::Instance() -> Pos_fiber())
      {
        G4ThreeVector pos = thePostPoint -> GetPosition();	
        CreateTree::Instance() -> depositionX.push_back(pos[0]);		
        CreateTree::Instance() -> depositionY.push_back(pos[1]);
        CreateTree::Instance() -> depositionZ.push_back(pos[2]);
        CreateTree::Instance() -> Energy_deposited.push_back(energy);
      }	

      if( CreateTree::Instance() -> Energy_fiber())
      {
        for (int iF = 0; iF < 9; iF++) 
        {
          if (atoi(thePrePV->GetName()) == iF+1)
          {
	    CreateTree::Instance()->Total_energy[iF] += energy;
	    break;
          }	
        }
      }
    
      if (thePrePV->GetName() == "Box_abs_phys")
      {
        CreateTree::Instance()->Total_energy_absorber += energy;   
      }
   
      CreateTree::Instance()->Total_energy_world += energy;       
    }  
  }

}
