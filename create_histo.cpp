#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;



TH1D* fill_histo(TFile* tree_file, string name, vector<double> ranges, string type){
    double t;
    TTree* tree = (TTree*) tree_file->Get(&(name)[0]);
    TH1D *histo = new TH1D(&(name+type)[0],&(name+type)[0], ranges[5], ranges[6], ranges[7]);

    Int_t nentries = (Int_t)tree->GetEntries();
    tree->SetBranchAddress("t",&t);
    for (Int_t i=0; i<nentries; i++) {
        tree->GetEntry(i);
        histo->Fill(t);
    }
    histo->GetXaxis()->SetTitle("time (#mu s)");
    histo->GetYaxis()->SetTitle(&("Entries / "+to_string(histo->GetBinWidth(1)))[0]);
    cout << "Filled histogram" <<endl;
    gStyle->SetOptStat("neou");
    return histo;
}

TH1D* fit_exp(TH1D* histo, vector<double> infos, string type, ofstream & fit_file, string option){
    string name = histo->GetName();
    fit_file << "\n\n####################### " << name << "#######################" << endl;
    TCanvas *c = new TCanvas(&(name)[0], &(name)[0]);
    TF1 *exp_long, *exp_tot;
    if (type.find("offset") != string::npos) {
        exp_tot = new TF1("exp_tot", "[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]", infos[6], infos[7]);
        exp_tot->SetParNames("norm_short (a.u.)", "tau_short (#mu s)", "norm_long (a.u.)", "tau_long (#mu s)", "offset (a.u.)"); 
        exp_tot->SetParameter(0, infos[0]);
        exp_tot->SetParameter(1, infos[1]);
        if (type.find("double") != string::npos){
            exp_long = new TF1("exp_long", "[0]*exp(-x/[1])+[2]", infos[8], infos[7]);
            exp_long->SetParNames("norm_long (a.u.)", "tau_long (#mu s)", "offset_long (a.u.)"); 
            exp_long->SetParameters(infos[2], infos[3], infos[4]);
            exp_long->SetLineColor(kGreen);
            histo->Fit("exp_long", &(option)[0]);
            exp_tot->FixParameter(2, exp_long->GetParameter(0));
            exp_tot->FixParameter(3, exp_long->GetParameter(1));
            if (type.find("fix") != string::npos) {
                exp_tot->FixParameter(4, exp_long->GetParameter(2));
            }
            else if (type.find("fix") == string::npos) {
                exp_tot->SetParameter(4, infos[4]);
            }
        }
        else if (type.find("single") != string::npos){
            exp_tot->SetParameter(2, infos[2]);
            exp_tot->SetParameter(3, infos[3]);
            exp_tot->SetParameter(4, infos[4]);
        }
    }
    else if (type.find("offset") == string::npos) {
        exp_tot = new TF1("exp_tot", "[0]*exp(-x/[1])+[2]*exp(-x/[3])", infos[6], infos[7]);
        exp_tot->SetParNames("norm_short (a.u.)", "tau_short (#mu s)", "norm_long (a.u.)", "tau_long (#mu s)"); 
        exp_tot->SetParameter(0, infos[0]);
        exp_tot->SetParameter(1, infos[1]);
        if (type.find("double") != string::npos){
            exp_long = new TF1("exp_long", "[0]*exp(-x/[1])", infos[8], infos[7]);
            exp_long->SetParNames("norm_long (a.u.)", "tau_long (#mu s)"); 
            exp_long->SetParameters(infos[2], infos[3]);
            exp_long->SetLineColor(kGreen);
            histo->Fit("exp_long", &(option)[0]);
            exp_tot->FixParameter(2, exp_long->GetParameter(0));
            exp_tot->FixParameter(3, exp_long->GetParameter(1));
        }
        else if (type.find("single") != string::npos){
            exp_tot->SetParameter(2, infos[2]);
            exp_tot->SetParameter(3, infos[3]);
        }
    }

    histo->Fit("exp_tot", &(option)[0]);

    histo->Draw();
    gStyle->SetOptFit(1111);
    if (type.find("double") != string::npos){
        exp_long->Draw("same");
        fit_file << "\n___________________ exp_long ___________________ " <<endl;
        fit_file << "chi_square / ndof =    " << exp_long->GetChisquare() << "/" << exp_long->GetNDF() <<endl;
        for (int i=0; i<exp_long->GetNpar(); i++) {
            fit_file << exp_long->GetParName(i) << " =   " <<  exp_long->GetParameter(i) << " +- " << exp_long->GetParError(i) <<endl;
        }
    }
    exp_tot->Draw("same");

    fit_file << "\n___________________ exp_tot ___________________ " <<endl;
    fit_file << "chi_square / ndof =    " << exp_tot->GetChisquare() << "/" << exp_tot->GetNDF() <<endl;
    for (int i=0; i<exp_tot->GetNpar(); i++) {
        fit_file << exp_tot->GetParName(i) << " =   " <<  exp_tot->GetParameter(i) << " +- " << exp_tot->GetParError(i) <<endl;
    }
    c->SaveAs(&("histos_images/"+type+"/"+name+".png")[0]);
    //histo->Write();
    c->Write();
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
                        "fe4_top_up_run4",
                        "fe4_top_down_run4",
                        "al4_bottom_up_run4",
                        "al4_bottom_down_run4",
                    };
    vector<TTree*> trees;  

    /* fit_types:
    * single/double - if the fit is done with just one function exp_tot or with first the exp_long and after the exp_tot
    * offset - if add an offset to the fit
    * fix - if the offset of the second exp_tot is fixed to the value found in the first exp_long fit
    */
    list <string> fit_types = {
                        //"_double_offset",
                        "_double_offset_fix",
                        //"_double",
                        "_single_offset",
                        //"_single",  
                    };

    // name of the material |
    // norm exp_short | tau exp_short | norm exp_long | tau exp_long | offset exp |
    // number of bins | range inf histo | range sup histo | start exp_long
    map <string, vector<double>>  materials_dict = {
        {"fe", {100, 0.2, 200, 2.2, 10,
                     300, 0.15, 30, 1}},
        {"al", {100, 0.88, 200, 2.2, 10,
                     300, 0.4, 30, 5}},
    };
    list <string> positions ={"up", "down"};  

    TH1D* histo;
    TH1D* histo_tot;
    TH1D* histo_pos;
    TFile *tree_file= new TFile("new_tree.root", "READ");

    for(list<string>::const_iterator type = fit_types.begin(); type != fit_types.end(); ++type){
        cout << "\n################## Processing : " << *type <<" ##################" << endl;
        int q=0;
        ofstream fit_file("fit_params/fit"+*type+".txt");
        TFile *histo_file= new TFile(&("histos_files/histo"+*type+".root")[0], "RECREATE");
        map <string, vector<TH1D*>> histos_material = {
                {"fe", {}},
                {"al", {}},
        };
        map <string, TH1D*> histos_pos = {
                {"up", nullptr},
                {"down", nullptr},
        };

        for(list<string>::const_iterator name = datasets.begin(); name != datasets.end(); ++name){
            cout << " \n Processing : " << *name << endl;
            string material;
            for (const auto & elem : materials_dict){
                const auto mat = elem.first;
                if (name->find(mat) != string::npos){
                    material = mat;
                }
            }

            histo = fill_histo(tree_file, *name, materials_dict[material], *type);   
            gROOT->SetBatch(kTRUE);
            histo = fit_exp(histo, materials_dict[material], *type, fit_file, "Q L R");
            histos_material[material].push_back(histo);
        }
        for (const auto & h_m : histos_material){
            const auto material = h_m.first;
            const auto histos_m = h_m.second;
            gROOT->SetBatch(kFALSE);
            if (histos_m.size()>0){
                for (const auto & h_p : histos_pos){
                    const auto position = h_p.first;
                    auto histos_p = h_p.second;  
                    cout << "\n Processing : " << material << "_" << position << endl;
                    q=0;
                    for (int j=0; j< histos_m.size(); j++){
                        string name = histos_m[j]->GetName();
                        if (name.find(position) != string::npos){
                            if (q==0) histos_p = (TH1D*)histos_m[j]->Clone();
                            q++;
                            if (q!=0) histos_p->Add(histos_m[j]);
                        }
                    }
                    histos_p->SetNameTitle(&(material+"_"+position+*type)[0], &(material+"_"+position+*type)[0]);
                    histos_p = fit_exp(histos_p, materials_dict[material], *type, fit_file, "L R");      
                    histos_pos[position]=histos_p;  
                }
                gROOT->SetBatch(kTRUE);
                cout << "\n Processing : " << material << "_tot" << endl;                    
                histo_tot = (TH1D*)histos_pos["up"]->Clone();
                histo_tot->Add(histos_pos["down"]);
                histo_tot->SetNameTitle(&(material+"_tot"+*type)[0], &(material+"_tot"+*type)[0]);
                histo_tot = fit_exp(histo_tot, materials_dict[material], *type, fit_file, "Q L R");        
            }

        }

        histo_file->Close();
    }
    getchar();
}
