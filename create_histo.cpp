#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


TH1D* fill_histo(TFile* tree_file, string name, vector<double> ranges){
    double t;
    TTree* tree = (TTree*) tree_file->Get(&(name)[0]);
    TH1D *histo = new TH1D(&(name)[0],&(name)[0], ranges[0], ranges[1], ranges[4]);

    Int_t nentries = (Int_t)tree->GetEntries();
    tree->SetBranchAddress("t",&t);
    for (Int_t i=0; i<nentries; i++) {
        tree->GetEntry(i);
        if (t<35 && t>0) histo->Fill(t);
    }
    histo->GetXaxis()->SetTitle("time [#mu s]");
    histo->GetYaxis()->SetTitle(&("Entries / "+to_string(histo->GetBinWidth(1)))[0]);
    return histo;
}

TH1D* fit_exp(TH1D* histo, vector<double> infos){
    string name =histo->GetName();
    TCanvas *c = new TCanvas(&(name)[0], &(name)[0]);
    TF1 *exp_trial = new TF1("exp_trial", "[0]*exp(-x/[1])", infos[3], infos[4]);
    exp_trial->SetParNames("norm", "tau"); 
    exp_trial->SetParameters(infos[4], infos[5]);
    histo->Fit("exp_trial");
    TF1 *exp_long = new TF1("exp_long", "[0]*exp(-x/[1])+[2]*exp(-x/[3])", infos[3], infos[4]);
    exp_long->SetParNames("norm", "tau"); 
    exp_long->FixParameters(infos[4], infos[5]);
    histo->Fit("exp_long");

    TF1 *exp_short = new TF1("exp_short", "[0]*exp(-x/[1])", infos[2], infos[3]);
    exp_short->SetParNames("norm", "tau"); 
    exp_short->SetParameters(infos[6], infos[7]);
    histo->Fit("exp_short");
    histo->Draw();
    exp_long->Draw("same");
    c->SaveAs(&("histos/"+name+".png")[0]);
    histo->Write();
    return histo;
}
    
void create_histo(){
    // name of the trees
    list <string> datasets ={
                        "fe4_top_up_run1",
                        "fe4_top_down_run1",
                        "fe4_top_up_run2",
                        "fe4_top_down_run2",
                        "fe4_top_up_run3",
                        "fe4_top_down_run3",
                        "al4_bottom_up_run3",
                        "al4_bottom_down_run3",
                    };
    vector<TTree*> trees;  
    // name of the material | number of bins | range inf exp_long | 
    // range sup exp_long | range inf exp_short | range sup exp_short |
    // norm exp_long | tau exp_long | norm exp_short | tau exp_short
    map <string, vector<double>>  materials_dict = {
        {"fe", {300, 0.002, 0.5, 1, 30, 100, 0.2, 100, 2.2}},
        {"al", {300, 0.002, 0.5, 1, 30, 100, 0.88, 100, 2.2}},
    };
    map <string, vector<TH1D*>>  histos_dict = {
        {"fe", {}},
        {"al", {}},
    };
    TH1D* histo;

    TFile *tree_file= new TFile("tree.root", "READ");
    TFile *histo_file= new TFile("histo.root", "RECREATE");
    for(list<string>::const_iterator name = datasets.begin(); name != datasets.end(); ++name){
        cout << " \n Processing : " << *name << endl;
        string material;
        for (const auto & elem : materials_dict){
            const auto mat = elem.first;
            if (name->find(mat) != string::npos){
                material = mat;
            }
        }

        histo = fill_histo(tree_file, *name, materials_dict[material]);              
        histo = fit_exp(histo, materials_dict[material]);
        histos_dict[material].push_back(histo);
    }
    for (const auto & elem : histos_dict){
        const auto material = elem.first;
        const auto histos = elem.second;
        cout << "\n Processing : " << material <<" total" << endl;
        if (histos.size()>0){
            TH1D *histo_tot = (TH1D*)histos[0]->Clone(&("histo_tot_"+material)[0]);
            for (int i=1; i < histos.size(); i++){
                histo_tot->Add(histos[i]);
            }
            histo_tot = fit_exp(histo_tot, materials_dict[material]);
        }
    }

    histo_file->Close();
    getchar();
}