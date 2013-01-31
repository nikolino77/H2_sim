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
//   cout << "debugging 1 " << endl;
  
  G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
  G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();
  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

  G4double energy = fabs(theStep->GetTotalEnergyDeposit())/GeV;

  // 	cout << "volume: " << thePrePV->GetName() << endl;
  // 	if (thePrePV->GetName() == "Fiber_4") cout << " fiber 4 small contribution = " << energy << endl;

  if (energy > 0)
  {	  
    Int_t counter = CreateTree::Instance() -> depositionCounter;
    CreateTree::Instance() -> depositionCounter++;

    G4ThreeVector pos = thePostPoint->GetPosition();
		
    // cout << " position = " << pos[0]  << endl;
		
    CreateTree::Instance() -> depositionX.push_back(pos[0]);		
    CreateTree::Instance() -> depositionY.push_back(pos[1]);
    CreateTree::Instance() -> depositionZ.push_back(pos[2]);
		
    // cout << " energy deposited in this step: " << energy << endl;

    // G4double energy = fabs(theStep->GetTotalEnergyDeposit())/GeV;
    // cout << "energy =  " << energy << endl;
    // cout << "energy*MeV =  " << energy*GeV << endl;
		
    //char name [60];
		
    for (int iF = 1; iF < 10; iF ++) 
    {
      //sprintf (name, "Fiber_%d" , iF);
      if (atoi(thePrePV->GetName()) == iF)
      {
	CreateTree::Instance()->Total_energy[iF-1] += energy;  
	break;
	// if (thePrePV->GetName() == "Fiber_0") cout << " fiber 4 small contribution = " << energy << endl;
      }	
    }
    
    if (thePrePV->GetName() == "Box_abs_phys")
    {
      CreateTree::Instance()->Total_energy_absorber += energy;   
    }
    CreateTree::Instance()->Total_energy_world += energy;       
  }  

}

