#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "histo_functions.h"
#include "histo_infos.h"

using namespace std;


void create_asym(){

    /* fit_types:
    * single/double - if the fit is done with just one function exp_tot or with first the exp_long and after the exp_tot
    * offset - if add an offset to the fit
    * fix - if the offset of the second exp_tot is fixed to the value found in the first exp_long fit
    */
    list <string> fit_types = {
                        "_double_offset_fix",

                    };

    TH1D histo;
    TH1D histo_pos ;
    TH1D histo_off ;
    TH1D histos_up ;
    TH1D histos_p;

    double offset;

    

    TFile *tree_file= new TFile("new_tree.root", "READ");

    for(list<string>::const_iterator type = fit_types.begin(); type != fit_types.end(); ++type){
        cout << "\n################## Processing : " << *type <<" ##################" << endl;
        int q=0;
        ofstream fit_file_sin("fit_params/fit_sin"+*type+".txt");

        TFile *histo_asym_file= new TFile(&("histo_asym"+*type+".root")[0], "RECREATE");

        map <string, vector<TH1D>> histos_material = {
            {"fe_top", {}},
            {"pb_bottom", {}},
            {"al_bottom", {}},
            {"nacl_top", {}},
            {"mag_bottom", {}},
            {"mag_top", {}},
            {"nacl_bottom", {}},
            {"mag", {}},
            {"nacl", {}},
            {"ap", {}}
        };
        map <string, TH1D> histos_pos = {
            {"up", TH1D()},
            {"down", TH1D()},
        };
        map <string, double> offset_pos = {
            {"up", 0},
            {"down", 0},
        };

        // histo single
        for(list<string>::const_iterator name = datasets.begin(); name != datasets.end(); ++name){
            cout << " \n Processing : " << *name << endl;
            for (const auto & elem : materials_dict_pos){
                const auto material = elem.first;
                if (name->find(material) != string::npos){
                    histo = fill_histo_asym(tree_file, *name, materials_dict_pos[material], *type);
                    histos_material[material].push_back(histo);
                }
            }
        }
        // histo up and down
        for (const auto & h_m : histos_material){
            const auto material = h_m.first;
            const auto histos_m = h_m.second;
            if (histos_m.size()>0){
                for (const auto & h_p : histos_pos){
                    gROOT->SetBatch(kTRUE);
                    const auto position = h_p.first;
                    cout << "\n Processing : " << material << "_" << position << endl;
                    q=0;
                    for (int j=0; j< histos_m.size(); j++){
                        string name = histos_m[j].GetName();
                        if (name.find(position) != string::npos){
                            if (q==0) {
                                histos_p = histos_m[j];
                                histos_p.Sumw2();
                            }
                            else if (q!=0) histos_p.Add(&histos_m[j]);
                            q++;
                        }
                    }
                    histos_p.SetNameTitle(&(material+"_"+position+*type)[0], &(material+"_"+position+*type)[0]);
                    fit_exp_asym(&histos_p, materials_dict_pos[material], *type, " L R I", &offset);
                    cout << "\n\n" << offset<< "\n\n" ;
                    histos_pos[position] = histos_p;
                    histos_pos[position].Sumw2();

                    offset_pos[position] = offset;
                }


                //if (material.find("mag") != string::npos || material.find("fe") != string::npos || material.find("pb") != string::npos || material.find("nacl") != string::npos){
                    // histo asimmetry
                gROOT->SetBatch(kFALSE);
                cout << "\n Processing : " << material << " asymmetry" << endl;
                int a = max(1,2);

                for (auto & h_p : histos_pos){
                    const auto position = h_p.first;
                    for(int i=0; i< histos_pos[position].GetNbinsX(); i++){
                        histos_pos[position].SetBinContent(i, max(0., histos_pos[position].GetBinContent(i)-offset_pos[position]));
                    }
                    
                }
                TH1D* histo_asym_sin;
                TH1D* histo_asym_const;
                histo_asym_file->cd();
                histo_asym_sin= (TH1D*)histos_pos["up"].GetAsymmetry(&histos_pos["down"]);

                histo_asym_sin->SetNameTitle(&(material+"_asym_sin"+*type)[0], &(material+"_asym_sin"+*type)[0]);
                histo_asym_sin->GetXaxis()->SetRangeUser(0.5, 3.5);
                fit_sin(histo_asym_sin, *type, "R I", fit_file_sin, materials_dict_pos[material]);
                save_plot(histo_asym_sin, *type);

                histo_asym_const = histo_asym_sin;
                histo_asym_const->SetNameTitle(&(material+"_asym_const"+*type)[0], &(material+"_asym_const"+*type)[0]);
                fit_constant(histo_asym_const, *type, "R I", fit_file_sin);
                save_plot(histo_asym_const, *type);
                histo_asym_const->Reset();
                histo_asym_sin->Reset();

                //}
            }
        }
        histo_asym_file->Close();
    }
    getchar();
}

