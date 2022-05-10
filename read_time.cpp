#include <iostream>
#include <fstream>
#include <vector>
//#include<stdio>
#include<cctype>
using namespace std;


void read_time(){
    ifstream myfile;
    myfile.open("5_5_weekend_4fe.dat", ios::in | ios::out);  
    vector<vector<double>> v (7);
    vector<vector<double>> w (2);    

    TFile *histo_file= new TFile(&("histos.root")[0], "RECREATE");
    if (myfile.is_open()){
        string tp;
        int i=0;
        while(getline(myfile, tp)){ //read data from file object and put it into string.
            int ch_numb = stoi(tp.substr(0, 1));
            //cout << ch_numb<< endl;
            int idx;
            for(int j=1; j<tp.size(); j++){
                char ch = tp[j];
                if (isdigit(ch)) {
                    idx=j;
                    //cout<< idx <<endl;
                    break;
                }
            }
            //cout << i <<endl;
            i++;
            //cout <<ch_numb << tp.substr(8, tp.length()-8)<<endl;
            v[ch_numb-1].push_back(stod(tp.substr(2, tp.length()-idx))); 
            if (ch_numb == 2 || ch_numb == 3){
                w[ch_numb-2].push_back(v[ch_numb-1][v[ch_numb-1].size()-1]-v[0][v[0].size()-1]);
            }
        }
        myfile.close(); //close the file object.
    }    

    /*for (int i=0; i<2; i++){
        for (int j=0; j<10; j++){
            cout << w[i][j] <<endl;
        }
        cout << endl;
    }*/
    TH1D* h1= new TH1D("exp_tot", "exp_tot", 200, 0, 30*pow(10,-6));
    

    for (int i=0; i<2; i++){
        TCanvas *c = new TCanvas(&("exp_channel"+to_string(i+1))[0], &("exp_channel"+to_string(i+1))[0]);
        TH1D* h= new TH1D(&("exp_channel"+to_string(i+1))[0], &("exp_channel"+to_string(i+1))[0], 200, 0, 30*pow(10,-6));        
        for (int j=0; j<w[i].size(); j++){
            h->Fill(w[i][j]);
            h1->Fill(w[i][j]);
        }
        h->Draw();
        c->SaveAs(&("exp/exp_channel"+to_string(i+1)+".pdf")[0]);
        c->Write();
    }
    TCanvas *c1 = new TCanvas("exp1", "exp1");
    h1->Draw();
    c1->SaveAs(&("exp/exp_tot.pdf")[0]);
    c1->Write();
    histo_file->Close();

}
    