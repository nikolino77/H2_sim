
{

  #include <cstdlib>
//   #include <iostream>
  #include <fstream>
  
  using namespace std;

  gROOT->Reset();
  gROOT->SetStyle("Plain");

  
 
   char filenames[150];
   
   strcpy(filenames , "./mioFile.txt");	
   double energy;
   TH1F * histo = new TH1F ("histo", "histo", 1000, 0, 10);
   

   cout << "filenames = " << filenames<< endl;
   
   ifstream fp(filenames);	//legge un file esterno
   
   cout<< "Ho letto il file:"<< filenames<< endl;
    

   while (!fp.eof() ){			//svolge il ciclo fintatno che non giunge alla fine del file

    fp >> energy;
    histo->Fill(energy);
    
    }
  
   

     TCanvas *c1 = new TCanvas ("c1","c1",600,600);

     histo->Draw();
   


  
   leg = new TLegend(0.6,0.7,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(42);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);


//    leg->AddEntry(gr[0], "Before irradiation", "lp");
//    leg->Draw();
   
   gPad->SetGrid();

   
     
}
