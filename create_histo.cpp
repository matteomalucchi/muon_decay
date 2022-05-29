#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#include "histo_functions.h"
#include "histo_infos.h"

using namespace std;


void create_histo(){

    /* fit_types:
    * single/double - if the fit is done with just one function exp_tot or with first the exp_long and after the exp_tot
    * offset - if add an offset to the fit
    * fix - if the offset of the second exp_tot is fixed to the value found in the first exp_long fit
    */
    list <string> fit_types = {
                        "_double_offset_fix",
                        //"_double_offset",
                        //"_double",
                        //"_single_offset",
                        //"_single",
                    };

    TH1D histo;
    TH1D histo_tot ;
    TH1D histo_pos ;
    TH1D histo_off ;
    TH1D histo_sub ;
    TH1D histo_sum ;
    TH1D* histo_asym;
    TH1D histos_p;

    double offset;
    

    TFile *tree_file= new TFile("new_tree.root", "READ");

    for(list<string>::const_iterator type = fit_types.begin(); type != fit_types.end(); ++type){
        cout << "\n################## Processing : " << *type <<" ##################" << endl;
        int q=0;
        ofstream fit_file_exp("fit_params/fit_exp"+*type+".txt");
        ofstream fit_file_exp_fe("fit_params/fit_exp_fe"+*type+".txt");

        TFile *histo_single_file= new TFile(&("histos_single/histo"+*type+".root")[0], "RECREATE");
        TFile *histo_combined_file= new TFile(&("histo_combined"+*type+".root")[0], "RECREATE");

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
        map <string, TH1D> offset_pos = {
            {"up", TH1D()},
            {"down", TH1D()},
        };

        // histo single
        histo_single_file->cd();
        for(list<string>::const_iterator name = datasets.begin(); name != datasets.end(); ++name){
            cout << " \n Processing : " << *name << endl;
            for (const auto & elem : materials_dict_pos){
                const auto material = elem.first;
                if (name->find(material) != string::npos){
                    histo = fill_histo(tree_file, *name, materials_dict_pos[material], *type);
                    gROOT->SetBatch(kTRUE);
                    //fit_exp(&histo, materials_dict_pos[material], *type, fit_file_exp, "Q L R I ", &offset);
                    //save_plot(&histo, *type);
                    histos_material[material].push_back(histo);
                }
            }
        }
        // histo up and down
        for (const auto & h_m : histos_material){
            const auto material = h_m.first;
            const auto histos_m = h_m.second;
            histo_combined_file->cd();
            if (histos_m.size()>0){
                for (const auto & h_p : histos_pos){
                    gROOT->SetBatch(kFALSE);
                    const auto position = h_p.first;
                    cout << "\n Processing : " << material << "_" << position << endl;
                    q=0;
                    for (int j=0; j< histos_m.size(); j++){
                        string name = histos_m[j].GetName();
                        if (name.find(position) != string::npos){
                            if (q==0) {
                                histos_m[j].Copy(histos_p);
                                histos_p.Sumw2();
                            }
                            else if (q!=0) histos_p.Add(&histos_m[j]);
                            q++;
                        }
                    }
                    histos_p.SetNameTitle(&(material+"_"+position+*type)[0], &(material+"_"+position+*type)[0]);
                    //fit_exp(&histos_p, materials_dict_pos[material], *type, fit_file_exp, " L R I", &offset);
                    //save_plot(&histos_p, *type);
                    histos_p.Copy(histos_pos[position]);
                    //histos_pos[position].Sumw2();
                }

                // histo total
                cout << "\n Processing : " << material << "_tot" << endl;
                histos_pos["up"].Copy(histo_tot);
                histo_tot.Sumw2();
                histo_tot.Add(&histos_pos["down"]);
                histo_tot.SetNameTitle(&(material+"_tot"+*type)[0], &(material+"_tot"+*type)[0]);
                if (material == "fe_top" || material.find("mag") != string::npos){
                    double min =10, max=-10, tau, tau_err;
                    TF1* func;
                    for (double flu_inf=-0.3; flu_inf<= 0.31; flu_inf=flu_inf+0.1){
                        for (double flu_sup=-7; flu_sup<= 0.1; flu_sup++){
                            fit_exp(&histo_tot, materials_dict_pos[material], *type, fit_file_exp_fe, "Q L R I ", &offset, flu_inf, flu_sup);
                            func = histo_tot.GetFunction("exp_tot");
                            tau = func->GetParameter(3);

                            //cout << tau << endl;

                            max = (tau>max) ? tau : max;
                            min = (tau<min) ? tau : min;
                        }
                    }
                    double span = max-min;
                    cout << "\n\n" << min << "\n\n" << endl;
                    cout << "\n\n" << max << "\n\n" << endl;
                    cout << "\n\n" << span << "\n\n" << endl;
                    fit_file_exp_fe << "\n\n" << span << "\n\n" << endl;

                }

                fit_exp(&histo_tot, materials_dict_pos[material], *type, fit_file_exp, "L R I", &offset);
                save_plot(&histo_tot, *type);

            }
        }
        histo_single_file->Close();
        histo_combined_file->Close();
    }
    getchar();
}
