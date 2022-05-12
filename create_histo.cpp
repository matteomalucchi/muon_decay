#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


TH1D* fill_histo(TFile* tree_file, string name, vector<double> ranges){
    double t;
    TTree* tree = (TTree*) tree_file->Get(&(name)[0]);
    TH1D *histo = new TH1D(&(name)[0],&(name)[0], ranges[0], ranges[1], ranges[2]);

    Int_t nentries = (Int_t)tree->GetEntries();
    cout << nentries << endl;
    tree->SetBranchAddress("t",&t);
    for (Int_t i=0; i<nentries; i++) {
        tree->GetEntry(i);
        histo->Fill(t);
    }
    histo->GetXaxis()->SetTitle("time [#mu s]");
    histo->GetYaxis()->SetTitle(&("Entries / "+to_string(histo->GetBinWidth(1)))[0]);
    return histo;
}

void fit_exp(TH1D* histo, vector<double>range, vector<double> exp_param){
    string name =histo->GetName();
    TCanvas *c = new TCanvas(&(name)[0], &(name)[0]);
    TF1 *f = new TF1("f", "[0]*exp(-x/[1])", range[1], range[2]);
    f->SetParNames("norm", "tau"); 
    f->SetParameters(exp_param[0], exp_param[1]);
    histo->Fit("f");
    histo->Draw();
    //c->SaveAs(&("exp/"+name+".png")[0]);
    //histo->Write();
}
    
void create_histo(){
    // name of file | number of channels for the time difference | number of bin | range inf exp | range sup exp | norm exp | tau exp
    map <string, vector<double>> datasets ={
                        {"4fe_above_up_run1", {500, 0, 10, 1000, 0.3, 1000, 0.3}},
                        {"4fe_above_down_run1", {500, 0, 3, 1000, 0.3, 1000, 0.3}},
                        {"4fe_above_up_run2", {500, 0, 10, 1000, 0.3, 1000, 0.3}},
                        {"4fe_above_down_run2", {500, 0, 3, 1000, 0.3, 1000, 0.3}},
    };
    vector<TTree*> trees;  
    vector<TH1D*> histos;
    TH1D* histo;

    TFile *tree_file= new TFile("tree.root", "READ");
    //TFile *histo_file= new TFile("histo.root", "RECREATE");
    for (const auto &dataset : datasets){
        const auto name = dataset.first;
        const auto ranges = {dataset.second[0], dataset.second[1], dataset.second[2]};
        const auto exp_param = {dataset.second[3], dataset.second[4], dataset.second[5], dataset.second[6]};

        histo = fill_histo(tree_file, name, ranges);  

        for (int i=0; i<histos.size();i++){
            fit_exp(histo, ranges, exp_param);
        }
        histos.push_back(histo);
    }

    //histo_file->Close();
    getchar();
}