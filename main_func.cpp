#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<double>> read_time(string name, int numb){
    ifstream myfile;
    myfile.open("data/"+name+".dat", ios::in | ios::out);  
    double v1, v4;
    vector<vector<double>> w (numb);

    if (myfile.is_open()){
        string tp;
        double number;
        while(getline(myfile, tp)){ //read data from file object and put it into string.
            number = stod(tp.substr(2, tp.length()-2));
            int ch_numb = stoi(tp.substr(0));
            if (ch_numb==1) v1=number;
            else if (ch_numb==4) v4=number;
            else if (ch_numb >1 && ch_numb < 4){
                w[ch_numb-2].push_back((number-v1)*pow(10, 6));
            }
            if (numb==4){
                if (ch_numb >4 && ch_numb < 7){
                    w[ch_numb-3].push_back((number-v4)*pow(10, 6));
                    //cout <<w[ch_numb-3][w[ch_numb-3].size()-1]<<endl;
                    //cout << setprecision(12)<<v4<< endl;
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


void main_func(){
    map <string, vector<string>> datasets ={
                        {"fe4_run1", {"fe4", "fe4"}},
                        {"fe4_run2", {"fe4", "fe4"}},
                        {"fe4_al4_run3", {"fe4", "fe4", "al4", "al4"}}

    };
    vector<vector<double>> diff_time;  
    map <string, vector<TTree*>>  tree_map = {
        {"fe", {}},
        {"al", {}},
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
