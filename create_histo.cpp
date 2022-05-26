#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#include "histo_functions.h"

using namespace std;


void create_histo(){
    // name of the trees
    list <string> datasets ={
                        "fe_top_up_run1",
                        "fe_top_down_run1",
                        "fe_top_up_run2",
                        "fe_top_down_run2",
                        "fe_top_up_run3",
                        "fe_top_down_run3",
                        "pb_bottom_up_run3",
                        "pb_bottom_down_run3",
                        "fe_top_up_run4",
                        "fe_top_down_run4",
                        "pb_bottom_up_run4",
                        "pb_bottom_down_run4",
                        "nacl_top_up_run5",
                        "nacl_top_down_run5",
                        "mag_bottom_up_run5",
                        "mag_bottom_down_run5",
                        "nacl_top_up_run6",
                        "nacl_top_down_run6",
                        "mag_bottom_up_run6",
                        "mag_bottom_down_run6",
                        "fe_top_up_run7",
                        "fe_top_down_run7",
                        "al_bottom_up_run7",
                        "al_bottom_down_run7",
                        "nacl_top_up_run8",
                        "nacl_top_down_run8",
                        "mag_bottom_up_run8",
                        "mag_bottom_down_run8",
                        "nacl_top_up_run9",
                        "nacl_top_down_run9",
                        "mag_bottom_up_run9",
                        "mag_bottom_down_run9",
                        "mag_top_up_run10",
                        "mag_top_down_run10",
                        "nacl_bottom_up_run10",
                        "nacl_bottom_down_run10",                        
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
                        //"_single_offset",
                        //"_single",
                    };
    double bin_width = 0.08;
    double inf = 0.3;
    double sup = 30;
    double n_bin = (sup-inf)/bin_width;
    double norm_pos = 200;

    // name of the material |
    // norm exp_short | tau exp_short | norm exp_long | tau exp_long | offset exp |
    // number of bins | range inf histo | range sup histo | start exp_long
    map <string, vector<double>>  materials_dict_pos = {
        {"fe_top", {norm_pos/1.8, 0.201, norm_pos, 2.197, 10,
                     n_bin, 0.15, sup, 2}},
        {"pb_bottom", {100, 0.08, 200, 2.2, 10,
                     n_bin, 0.1, sup, 1}},
        {"al_bottom", {norm_pos/1.8, 0.88, norm_pos, 2.197, 10,
                     n_bin, 0.6, sup, 4}},
        {"nacl_top", {100, 0.7, 200, 2.2, 10,
                     n_bin, 0.5, sup, 4}},
        {"mag_bottom", {100, 0.201, 200, 2.2, 10,
                     n_bin, 0.15, sup, 2}},
        {"mag_top", {100, 0.201, 200, 2.2, 10,
                     n_bin, 0.15, sup, 2}},
        {"nacl_bottom", {100, 0.7, 200, 2.2, 10,
                     n_bin, 0.5, sup, 4}},
    };

    map <string, vector<double>>  materials_dict_tot = {
        {"fe_top", {norm_pos/1.8, 0.201, norm_pos, 2.197, 10,
                     n_bin, 0.15, sup, 2}},
        {"pb_bottom", {100, 0.88, 200, 2.2, 10,
                     n_bin, inf, sup, 5}},
        {"al_bottom", {norm_pos/1.8, 0.88, norm_pos, 2.197, 10,
                     n_bin, 0.6, sup, 4}},
        {"nacl_top", {100, 0.7, 200, 2.2, 10,
                     n_bin, inf, sup, 5}},
        {"mag_bottom", {100, 0.201, 200, 2.2, 10,
                     n_bin, inf, sup, 5}},
        {"mag_top", {100, 0.201, 200, 2.2, 10,
                     n_bin, inf, sup, 5}},
        {"nacl_bottom", {100, 0.7, 200, 2.2, 10,
                     n_bin, inf, sup, 5}},
    };

    TH1D histo;
    TH1D histo_tot ;
    TH1D histo_pos ;
    TH1D histo_off ;
    TH1D histo_sub ;
    TH1D histo_sum ;

    double offset;
    

    TFile *tree_file= new TFile("new_tree.root", "READ");

    for(list<string>::const_iterator type = fit_types.begin(); type != fit_types.end(); ++type){
        cout << "\n################## Processing : " << *type <<" ##################" << endl;
        int q=0;
        ofstream fit_file("fit_params/fit"+*type+".txt");
        TFile *histo_single_file= new TFile(&("histos_single/histo"+*type+".root")[0], "RECREATE");
        TFile *histo_combined_file= new TFile(&("histos_combined/histo"+*type+".root")[0], "RECREATE");

        map <string, vector<TH1D>> histos_material = {
            {"fe_top", {}},
            {"pb_bottom", {}},
            {"al_bottom", {}},
            {"nacl_top", {}},
            {"mag_bottom", {}},
            {"mag_top", {}},
            {"nacl_bottom", {}},
        };
        map <string, TH1D> histos_pos = {
            {"up", TH1D()},
            {"down", TH1D() },
        };
        map <string, TH1D> offset_pos = {
            {"up", TH1D()},
            {"down", TH1D()},
        };

        histo_single_file->cd();
        for(list<string>::const_iterator name = datasets.begin(); name != datasets.end(); ++name){
            cout << " \n Processing : " << *name << endl;
            string material = "";
            for (const auto & elem : materials_dict_pos){
                const auto mat = elem.first;
                if (name->find(mat) != string::npos){
                    material = mat;
                }
            }
            if (material != ""){
                histo = fill_histo(tree_file, *name, materials_dict_pos[material], *type);
                gROOT->SetBatch(kTRUE);
                fit_exp(&histo, materials_dict_pos[material], *type, fit_file, "Q L R", &offset);
                save_plot(&histo, *type);
                histos_material[material].push_back(histo);
            }
        }
        histo_combined_file->cd();
        for (const auto & h_m : histos_material){
            const auto material = h_m.first;
            const auto histos_m = h_m.second;
            if (histos_m.size()>0){
                for (const auto & h_p : histos_pos){
                    gROOT->SetBatch(kFALSE);
                    const auto position = h_p.first;
                    auto histos_p = h_p.second;
                    cout << "\n Processing : " << material << "_" << position << endl;
                    q=0;
                    for (int j=0; j< histos_m.size(); j++){
                        string name = histos_m[j].GetName();
                        if (name.find(position) != string::npos){
                            if (q==0) histos_m[j].Copy(histos_p);
                            q++;
                            if (q!=0) histos_p.Add(&histos_m[j]);
                        }
                    }
                    histos_p.SetNameTitle(&(material+"_"+position+*type)[0], &(material+"_"+position+*type)[0]);
                    fit_exp(&histos_p, materials_dict_pos[material], *type, fit_file, " L R", &offset);
                    save_plot(&histos_p, *type);
                    histos_pos[position]=histos_p;
                    histos_pos[position].Sumw2();
                    TH1D histo_off =  TH1D("histo_off","histo_off", materials_dict_pos[material][5], materials_dict_pos[material][6], materials_dict_pos[material][7]);
                    for(int i=0; i< histo_off.GetNbinsX(); i++){
                        histo_off.SetBinContent(i, offset);
                    }
                    offset_pos[position] = histo_off;
                }

                // histo total
                cout << "\n Processing : " << material << "_tot" << endl;
                histos_pos["up"].Copy(histo_tot);
                histo_tot.Add(&histos_pos["down"]);
                histo_tot.SetNameTitle(&(material+"_tot"+*type)[0], &(material+"_tot"+*type)[0]);
                fit_exp(&histo_tot, materials_dict_pos[material], *type, fit_file, " L R", &offset);
                save_plot(&histo_tot, *type);


                // histo asimmetry
                if ((material.find("nacl") != string::npos ) || (material.find("mag") != string::npos )){
                    gROOT->SetBatch(kTRUE);

                    histos_pos["up"].Add(&offset_pos["up"], -1);
                    histos_pos["down"].Add(&offset_pos["down"], -1);
                    //save_plot(&histos_pos["up"], *type);
                    //save_plot(&histos_pos["down"], *type);
                    //gROOT->SetBatch(kTRUE);

                    cout << "\n Processing : " << material << "_sub" << endl;
                    histos_pos["up"].Copy(histo_sub);
                    histos_pos["up"].Copy(histo_sum);
                    histo_sub.SetNameTitle(&(material+"_sub"+*type)[0], &(material+"_sub"+*type)[0]);
                    histo_sum.SetNameTitle(&(material+"_sum"+*type)[0], &(material+"_sum"+*type)[0]);
                    histo_sub.Add(&histos_pos["down"], -1);
                    histo_sum.Add(&histos_pos["down"], +1);
                    save_plot(&histo_sub, *type);
                    //save_plot(&histo_sum, *type);
                    histo_sub.Divide(&histo_sum);
                    histo_sub.SetNameTitle(&(material+"_asym"+*type)[0], &(material+"_asym"+*type)[0]);
                    save_plot(&histo_sub, *type);
                }
            }
        }
        histo_single_file->Close();
        histo_combined_file->Close();
    }
    getchar();
}
