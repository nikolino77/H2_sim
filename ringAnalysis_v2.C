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
  TFile RunFile("sim_out.root","READ");
//   TFile RunFile("./data/NTUPLE_FIBER_En_80GeV.root","READ");
  TTree* TreeRun = (TTree*) RunFile.Get("tree");

  std::vector<float> depositionX;
  std::vector<float> depositionY;
  std::vector<float> depositionZ; 
  
  double Total_energy1;


  TreeRun->SetBranchAddress("depositionX",&depositionX);
  TreeRun->SetBranchAddress("depositionY",&depositionY);
  TreeRun->SetBranchAddress("depositionZ",&depositionZ);
  TreeRun->SetBranchAddress("Total_energy1",&Total_energy1);
  
  
  
  
  
  int NBIN = 1000;
  double min = -1000;
  double max = 1000;
  
  TH1F * histoX  = new TH1F("histoX", "histoX", NBIN, min, max);
  TH1F * histoY  = new TH1F("histoY", "histoY", NBIN, min, max);
  TH1F * histoZ  = new TH1F("histoZ", "histoZ", NBIN, min, max);
  
  
  int NFIBERS = 4;
  TH1F * hFiberEn[NFIBERS];
  
  for (int iFiber = 0; iFiber < NFIBERS; iFiber++){
    char name[100];
    sprintf(name, "hFiberEn_%d", iFiber);
    
    hFiberEn[iFiber] = new TH1F(name, name, 10000, 0, 100);
    
  }
  

  
   for (Int_t iEvt= 0; iEvt<TreeRun->GetEntries(); iEvt++) {
    
   if (iEvt%1 == 0)  cout << "iEvent ::: " << iEvt << endl;
   
   TreeRun->GetEntry(iEvt);   
//    Total_energy1 = 0;
   cout << " energy = " << Total_energy1 << endl;
   
   hFiberEn[0] -> Fill(Total_energy1);
   
   
//     for (int i = 0; i < depositionX.size(); i++){
     
//        cout << "X = " << depositionX.at(i) << endl;
      /*
	histoX->Fill(depositionX.at(i));
	histoY->Fill(depositionY.at(i));
	histoZ->Fill(depositionZ.at(i));
     
     */
//     }
    
    
   
   }
   
   
   
   
    //DRAWING PLOTS
    TCanvas* cPosition = new TCanvas("cPosition","cPosition",600,600);
    cPosition->Divide(3,1);
    cPosition->cd(1);
    histoX->Draw();
    
    cPosition->cd(2);
    histoY->Draw();
    
    cPosition->cd(3);
    histoZ->Draw();
    
}