 
 
 
void prova(){
   gROOT->Reset();
   TFile *f = new TFile("prova.root","RECREATE");
   TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
   TTree *T = new TTree("ntuple","data from ascii file");
   Long64_t nlines = T->ReadFile("data/fe4_al4_run3.dat","x:y");
   printf(" found %lld pointsn",nlines);
   T->Draw("y");
   T->Write();
}