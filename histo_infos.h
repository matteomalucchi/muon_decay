#ifndef HistoInfosHfile_
#define HistoInfosHfile_


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
                        "fe_top_up_run11",
                        "fe_top_down_run11",
                        "al_bottom_up_run11",
                        "al_bottom_down_run11",
                        "mag_top_up_run12",
                        "mag_top_down_run12",
                        "nacl_bottom_up_run12",
                        "nacl_bottom_down_run12", 
                        "ap_top_up_run13",
                        "ap_top_down_run13",
                        "ap_bottom_up_run13",
                        "ap_bottom_down_run13",                                                 
};


double bin_width = 0.02;
double inf = 0.3;
double sup = 30;
double n_bin = (sup-inf)/bin_width;
double norm_pos = 200;
double bin_asym = 0.2;

// name of the material |
// norm exp_short | tau exp_short | norm exp_long | tau exp_long | offset exp |
// bin width | range inf histo | range sup histo | start exp_long
// norm sin | omega sin | phase sin | offset sin | bin width asymmetry

map <string, vector<double>>  materials_dict_pos = {
    {"fe_top", {norm_pos/1.8, 0.201, norm_pos, 2.197, 10,
                    bin_width, 0.18, sup, 1,
                    0.054, 8.8, -3.8, -0.19, bin_asym}},
    {"mag_bottom", {norm_pos/1.8, 0.201, 200, 2.2, 10,
                    bin_width, 0.18, sup, 1,
                    0.05, 8.8, -2.7, -0.18, bin_asym}},
    {"mag_top", {norm_pos/1.8, 0.201, 200, 2.2, 10,
                    bin_width, 0.18, sup, 1,
                    0.037, 5.9, -2.1, -0.18, bin_asym}},
    {"mag", {norm_pos/1.8, 0.201, 200, 2.2, 10,
                    bin_width, 0.18, sup, 1,
                    0.05, 8.8, -2.7, -0.18, bin_asym}},
    {"al_bottom", {norm_pos/1.8, 0.88, norm_pos, 2.197, 10,
                    bin_width, 0.6, sup, 4,
                    0.054, 8.8, -3.8, -0.19, bin_asym}},
    {"nacl_top", {norm_pos/1.8, 0.7, 200, 2.2, 10,
                    bin_width, 0.4, sup, 4,
                    0.05, 2.5, -0.8, -0.03, bin_asym}},
    {"nacl_bottom", {100, 0.7, 200, 2.2, 10,
                    bin_width, 0.4, sup, 4,
                    0.054, 8.8, -3.8, -0.19, bin_asym}},
    {"nacl", {norm_pos/1.8, 0.7, 200, 2.2, 10,
                    bin_width, 0.4, sup, 4,
                    0.054, 8.8, -3.8, -0.19, bin_asym}},
    {"pb_bottom", {norm_pos/1.8, 0.08, 200, 2.2, 10,
                    bin_width, 0.1, sup, 1,
                    0.085, 5.1, -0.9, -0.17, bin_asym}},
    {"ap", {norm_pos/1.8, 0.7, 200, 2.2, 10,
                    bin_width, 0.05, sup, 4,
                    0.01, 7.5, -4.2, -0.9, bin_asym}},
};

#endif