#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<double>> read_time(string name, int numb){
    ifstream myfile;
    myfile.open(name+".dat", ios::in | ios::out);  
    vector<vector<double>> v (7);
    vector<vector<double>> w (numb);    

    if (myfile.is_open()){
        string tp;
        while(getline(myfile, tp)){ //read data from file object and put it into string.
            int ch_numb = stoi(tp.substr(0));
            //cout <<ch_numb << tp.substr(8, tp.length()-8)<<endl;
            v[ch_numb-1].push_back(stod(tp.substr(8, tp.length()-8))); 
            if (ch_numb != 1){
                w[ch_numb-2].push_back(v[ch_numb-1][v[ch_numb-1].size()-1]-v[0][v[0].size()-1]);
            }
        }
        myfile.close(); //close the file object.
    }    
    return w;
}
string create_branches(int numb){
    string branches="t1";
    for (int i=1; i<numb; i++){
        branches.append(":t"+to_string(i+1));
    }
    return branches;
}
void create_ntuple(string name, vector<vector<double>> diff_time, string branches){
    TTree *data= new TTree(&(name)[0], &(name)[0]);
    string branch_name;
    //TBranch *b;
    for (int i=0; i<diff_time.size(); i++){
        double t[diff_time[i].size()];
        branch_name = "t"+to_string(i);
        TBranch *b=data->Branch(&(branch_name)[0], t, "t[diff_time[i].size()]/D");
        //TBranch *b=data->Branch(&(branch_name)[0], &t, &(branch_name+"/D")[0]);
        for (int j=0; j<diff_time[i].size(); j++){
            t[j]=diff_time[i][j];
            //cout << t <<endl;
            b->Fill();
        }
        data->SetEntries(1);
        cout <<endl;
        data->Scan();
        //data->Print();
    }
    data->Write();
}

void main_func(){

    map <string, vector<int>> datasets ={
                        {"prova", {2}},
    };
    vector<vector<double>> diff_time;  
    string branches;  
    TFile *ntuple_file= new TFile(&("ntuples.root")[0], "RECREATE");
    for (const auto &dataset : datasets){
        const auto name = dataset.first;
        const auto numb = dataset.second[0];
        diff_time = read_time(name, numb);
        //branches = create_branch(numb);
        create_ntuple(name, diff_time, branches);

    }
    ntuple_file->Close();
}

    /*for (int i=0; i<2; i++){
        for (int j=0; j<10; j++){
            cout << w[i][j] <<endl;
        }
        cout << endl;
    }*/



/*

    TH1D* h1= new TH1D("exp", "exp", 20000, 0, 1);

    for (int i=0; i<1; i++){
        TCanvas *c = new TCanvas("exp", "exp");
        TH1D* h= new TH1D("exp", "exp", 200, 0, 0.03);        
        for (int j=0; j<w[i].size(); j++){
            h->Fill(w[i][j]);
            h1->Fill(w[i][j]);
        }
        h->Draw();
        c->SaveAs(&("exp_channel"+to_string(i+1)+".pdf")[0]);
    }
    TCanvas *c1 = new TCanvas("exp1", "exp1");
    h1->Draw();
    c1->SaveAs(&("exp_tot.pdf")[0]);
*/


