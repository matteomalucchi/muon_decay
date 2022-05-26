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
};


double bin_width = 0.02;
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
                    n_bin, 0.15, sup, 2,
                    0.09, 4.9, 0.4, -0.2}},
    {"mag_top", {100, 0.201, 200, 2.2, 10,
                    n_bin, 0.15, sup, 2}},
    {"nacl_bottom", {100, 0.7, 200, 2.2, 10,
                    n_bin, 0.5, sup, 4}},
};

#endif