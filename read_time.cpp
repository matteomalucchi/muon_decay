#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void read_time(){
    ifstream myfile;
    myfile.open("prova1.dat", ios::in | ios::out);  
    vector<vector<double>> v (7);
    vector<vector<double>> w (2);    


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

    for (int i=0; i<2; i++){
        for (int j=0; j<10; j++){
            cout << w[i][j] <<endl;
        }
        cout << endl;
    }
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

}
    