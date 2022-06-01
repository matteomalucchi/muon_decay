#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// top: start 40, stop up 40 ns, stop down -1 ns 
// bottom: start 40, stop up 40 ns, stop down +5 ns 

vector<vector<double>> read_time(string name, int numb){
    ifstream myfile;
    myfile.open("data/"+name+".dat", ios::in | ios::out);
    vector<double> v1, v4;
    vector<vector<double>> w (numb);
    vector<int> idx;

    if (myfile.is_open()){
        string tp;
        double number;
        while(getline(myfile, tp)){ //read data from file object and put it into string.
            number = stod(tp.substr(2, tp.length()-2));
            int ch_numb = stoi(tp.substr(0));
            idx.push_back(ch_numb);
            if (ch_numb==1) v1.push_back(number);
            else if (ch_numb==4) v4.push_back(number);
            else if (ch_numb ==2 || ch_numb ==3){
                    /*if ((number-v1[v1.size()-2])*pow(10, 6) >3000000){
                        cout << setprecision(12)<<  w[ch_numb-2][w[ch_numb-2].size()-1] <<endl;
                        cout << setprecision(12)<< v1[v1.size()-2] <<"      "<< v1[v1.size()-1] <<"      " <<number<<"      " <<  endl;
                    }*/
                if (number > v1[v1.size()-1]){
                    w[ch_numb-2].push_back((number-v1[v1.size()-1])*pow(10, 6));
                }
                else if (number-v1[v1.size()-1] == 0 && idx[idx.size()-2]==1 && idx[idx.size()-3]==1) {
                    w[ch_numb-2].push_back((number-v1[v1.size()-2])*pow(10, 6));
                }
            }
            if (numb==4){
                if (ch_numb ==5 || ch_numb ==6){
                    if (number > v4[v4.size()-1]){
                        w[ch_numb-3].push_back((number-v4[v4.size()-1])*pow(10, 6));
                    }
                    else if (number-v4[v4.size()-1] == 0 && idx[idx.size()-2]==4 && idx[idx.size()-3]==4) {
                        w[ch_numb-3].push_back((number-v4[v4.size()-2])*pow(10, 6));
                        /*if (number < v4[v4.size()-1]){
                            cout << setprecision(12)<<  w[ch_numb-3][w[ch_numb-3].size()-1] <<endl;
                            cout << setprecision(12)<< v1[v1.size()-2] <<"      "<< v1[v1.size()-1] <<"      " <<number<<"      " <<  endl;
                        }*/
                    }
                }
            }

        }
        myfile.close(); //close the file object.
    }
    return w;
}

void create_tree(vector<string> materials, string run, vector<vector<double>> diff_time){

    // top/bottom refers to the upper or lower half of the telescope
    // up/down refers to the pmt above or below the studied material
    vector<string> positions = {"_top_up","_top_down","_bottom_up","_bottom_down"};
    for (int i=0; i<diff_time.size(); i++){
        string name=materials[i]+positions[i]+run;
        TTree *data= new TTree(&(name)[0], &(name)[0]);
        double t;
        TBranch *b=data->Branch("t", &t,"t/D");
        for (int j=0; j<diff_time[i].size(); j++){
            t=diff_time[i][j];
            data->Fill();
        }
        //data->Scan();
        data->Write();
    }
}


void create_tree(){
    map <string, vector<string>> datasets ={
                        {"fe4_run1", {"fe", "fe"}},
                        {"fe4_run2", {"fe", "fe"}},
                        {"fe4_pb4_run3", {"fe", "fe", "pb", "pb"}},
                        {"fe4_pb4_run4", {"fe", "fe", "pb", "pb"}},
                        {"nacl_mag_run5", {"nacl", "nacl", "mag", "mag"}},
                        {"nacl_mag_run6", {"nacl", "nacl", "mag", "mag"}},
                        {"fe2_al2_run7", {"fe", "fe", "al", "al"}},
                        {"nacl_mag_run8", {"nacl", "nacl", "mag", "mag"}},
                        {"nacl_mag_run9", {"nacl", "nacl", "mag", "mag"}},
                        {"mag_nacl_run10", {"mag", "mag", "nacl", "nacl"}},
                        {"fe4_al4_run11", {"fe", "fe", "al", "al"}},
                        {"mag_nacl_run12", {"mag", "mag", "nacl", "nacl"}},
                        {"afterpulse_run13", {"ap", "ap", "ap", "ap"}},
                        {"mag_nacl_run14", {"mag", "mag", "nacl", "nacl"}},
    };
    vector<vector<double>> diff_time;
    map <string, vector<TTree*>>  tree_map = {
        {"fe", {}},
        {"pb", {}},
        {"al", {}},
        {"nacl", {}},
        {"mag", {}},
        {"ap", {}}
    };
    TFile *tree_file= new TFile(&("tree.root")[0], "RECREATE");
    for (const auto &dataset : datasets){
        const auto name = dataset.first;
        const auto materials = dataset.second;
        int numb = materials.size();
        string run = name.substr(name.find("_run"));
        cout << "Processing : " << name << endl;
        diff_time = read_time(name, numb);
        create_tree(materials, run, diff_time);
        cout << endl;
    }
    tree_file->Close();
}
