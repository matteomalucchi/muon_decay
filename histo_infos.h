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
                        "mag_top_up_run14",
                        "mag_top_down_run14",
                        "nacl_bottom_up_run14",
                        "nacl_bottom_down_run14",                                                                         
};


double bin_width = 0.08;
double inf = 0.3;
double sup = 30;
double n_bin = (sup-inf)/bin_width;
double norm_pos = 200;
double bin_asym = 0.1;
double upper_asym = 4.;

// name of the material |
// norm exp_short | tau exp_short | norm exp_long | tau exp_long | offset exp |
// bin width | range inf histo | range sup histo | start exp_long
// norm sin | omega sin | phase sin | offset sin | bin width asymmetry

map <string, vector<double>>  materials_dict_pos = {
    {"fe_top", {norm_pos/1.8, 0.201, norm_pos, 2.197, 10,
                    bin_width, 0.185, sup, 0.9,
                    //0.05, 8.8, -2.7, -0.18, bin_asym*
                    0.04, 9.2, 0, -0.15, bin_asym, upper_asym}},
    /*{"al_bottom", {norm_pos/1.8, 0.88, norm_pos, 2.197, 10,
                    bin_width, 0.3, sup, 2.5,
                    //0.05, 8.8, -2.7, -0.18, bin_asym
                    0.04, 9.2, 0, -0.15, bin_asym, upper_asym}},*/
    /*{"mag_bottom", {norm_pos/1.8, 0.201, 200, 2.2, 10,
                    bin_width, 0.19, sup, 1,
                    //0.05, 8.8, -2.7, -0.18, bin_asym
                    0.04, 9.2, 0, -0.15, bin_asym, 3.}},
    {"mag_top", {norm_pos/1.8, 0.201, 200, 2.2, 10,
                    bin_width, 0.19, sup, 1.,
                    //0.05, 8.8, -2.7, -0.18, bin_asym
                    0.04, 9.2, 0, -0.15, bin_asym, upper_asym}},
    {"mag", {norm_pos/1.8, 0.201, 200, 2.2, 10,
                    bin_width, 0.19, sup, 1.1,
                    //0.05, 8.8, -2.7, -0.18, bin_asym
                    0.04, 9.2, 0, -0.15, bin_asym, 3.8}}, */
    /*{"nacl_top", {norm_pos/1.8, 0.7, 200, 2.2, 10,
                    bin_width, 0.17, sup, 3,
                    //0.05, 8.8, -2.7, -0.18, bin_asym
                    0.04, 9.2, 0, -0.15, bin_asym, upper_asym}},
    {"nacl_bottom", {100, 0.7, 200, 2.2, 10,
                    bin_width, 0.17, sup, 3,
                    //0.05, 8.8, -2.7, -0.18, bin_asym
                    0.04, 9.2, 0, -0.15, bin_asym, 3.}},
    {"nacl", {norm_pos/1.8, 0.7, 200, 2.2, 10,
                    bin_width, 0.17, sup, 3,
                    //0.05, 8.8, -2.7, -0.18, bin_asym
                    0.04, 9.2, 0, -0.15, bin_asym, 3.8}},
    {"pb_bottom", {norm_pos/1.8, 0.08, 200, 2.2, 10,
                    0.02, 0.08, sup, 3.5,
                    //0.05, 8.8, -2.7, -0.18, bin_asym
                    0.1, 4, 0, -0.17, bin_asym, upper_asym}},
    {"ap", {norm_pos/1.8, 0.7, 200, 2.2, 10,
                    0.02, 0.0, sup, 4,
                    //0.05, 8.8, -2.7, -0.18, bin_asym
                    0.04, 9.2, 0, -0.15, bin_asym, upper_asym}},   */        
                             
};


map  <string, double> efficiencies{
    {"top_up", 0.88},
    {"top_down", 0.95},
    {"bottom_up", 0.95},
    {"bottom_down", 0.94},
};

#endif