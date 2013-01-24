{
  
  
  #include <cstdlib>
//   #include <iostream>
  #include <fstream>
  #include <stdio.h>
  #include <string.h>
  #include <vector>
  #include <math.h>
  


  
  using namespace std;

  gROOT->Reset();
  gROOT->SetStyle("Plain");

  // DEFINING FILE AND TREE VARIABLES
  TFile RunFile("50GeV_NOV_TB.root","READ");
//   TFile RunFile("./data/NTUPLE_FIBER_En_80GeV.root","READ");
  TTree* TreeRun = (TTree*) RunFile.Get("tree");

  std::vector<float> depositionX;
  std::vector<float> depositionY;
  std::vector<float> depositionZ; 
  
  Float_t Total_energy[9];
  
  Float_t InitialPositionX;
  Float_t InitialPositionY;
  Float_t InitialPositionZ;


//   TreeRun->SetBranchAddress("depositionX",&depositionX);
//   TreeRun->SetBranchAddress("depositionY",&depositionY);
//   TreeRun->SetBranchAddress("depositionZ",&depositionZ);
  
  TreeRun->SetBranchAddress("InitialPositionX",&InitialPositionX);
  TreeRun->SetBranchAddress("InitialPositionY",&InitialPositionY);
  TreeRun->SetBranchAddress("InitialPositionZ",&InitialPositionZ);
  
  TreeRun->SetBranchAddress("Total_energy",&Total_energy);
  
  
//   TreeRun->SetBranchAddress("Total_energy1",&Total_energy1);
  
  
  
  
  
  int NBIN_pos = 30;
  double minPos = -15.;
  double maxPos = 15.;
  
  
  
  
  int NFIBERS = 9;
  
  TH2D * hBeamProfile = new TH2D ("hBeamProfile", "hBeamProfile", NBIN_pos,  minPos, maxPos, NBIN_pos,  minPos, maxPos);

  
  TProfile * pContX[NFIBERS];
  TH1F * hFiberEn[NFIBERS];
  
  for (int iFiber = 0; iFiber < NFIBERS; iFiber++){
    char name[100];
    
    sprintf(name, "hFiberEn_%d", iFiber);
    hFiberEn[iFiber] = new TH1F(name, name, 1000, 0, 10);
    
    sprintf(name, "pContX_%d", iFiber);
    pContX[iFiber] = new TProfile (name, name, NBIN_pos, minPos, maxPos);
    
  }
  

  
  for (Int_t iEvt= 0; iEvt<TreeRun->GetEntries(); iEvt++) {
    
//    if (iEvt%1 == 0)  cout << "iEvent ::: " << iEvt << endl;
   
   TreeRun->GetEntry(iEvt);   
//    Total_energy1 = 0;
    cout << " energy central fiber = " << Total_energy[4] << endl;
   
   for (int iFiber = 0; iFiber < NFIBERS; iFiber++){
   
    hFiberEn[iFiber] -> Fill(Total_energy[iFiber]);
    pContX[iFiber] -> Fill(InitialPositionX, Total_energy[iFiber]);
   
   }
   
   hBeamProfile->Fill(InitialPositionX, InitialPositionY);
   
    
   
  }
   
   
   
   
    //DRAWING PLOTS

    TCanvas * cEnergies = new TCanvas ("cEnergies", "cEnergies");
    cEnergies->Divide(3,3);
    for (int iFiber = 0; iFiber < NFIBERS; iFiber++){
      cEnergies->cd(iFiber+1);
      hFiberEn[iFiber] ->Draw();
      gPad->SetGrid();
      gPad->SetLogy();
    }
    
    
    TCanvas * cContX = new TCanvas ("cContX", "cContX");
    cContX->Divide(3,3);
    for (int iFiber = 0; iFiber < NFIBERS; iFiber++){
      cContX->cd(iFiber+1);
      pContX[iFiber] ->Draw();
      gPad->SetGrid();
      
    }
    
    
    TCanvas * cBeamProfile = new TCanvas ("cBeamProfile", "cBeamProfile");
    hBeamProfile->Draw("COLZ");
    
    
    
}