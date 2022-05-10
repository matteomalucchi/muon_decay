#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


vector<vector<double>> read_time(string name, int numb){
    ifstream myfile;
    myfile.open("data/"+name+".dat", ios::in | ios::out);  
    vector<vector<double>> v (7);
    vector<vector<double>> w (numb);    

    if (myfile.is_open()){
        string tp;
        while(getline(myfile, tp)){ //read data from file object and put it into string.
            int ch_numb = stoi(tp.substr(0));
            //cout <<ch_numb << tp.substr(8, tp.length()-8)<<endl;
            v[ch_numb-1].push_back(stod(tp.substr(2, tp.length()-1))); 
            //cout << v[0][1] <<endl;
            if (ch_numb == 2 || ch_numb == 3){
                w[ch_numb-2].push_back(v[ch_numb-1][v[ch_numb-1].size()-1]-v[0][v[0].size()-1]);
                cout << setprecision(8)<<w[1][w[1].size()-1]<<endl;

            }
        }
        myfile.close(); //close the file object.
    }    
    return w;
} 

vector<TH1D*> fill_histo(vector<vector<double>> diff_time, string name, vector<double> range){
    vector<TH1D*> histo;
    string name_tot = name+"exp_tot";
    TH1D* h_tot= new TH1D(&(name_tot)[0], &(name_tot)[0], range[0], range[1], range[2]);
    
    for (int i=0; i<diff_time.size(); i++){
        string name_ch = name+"_exp_channel"+to_string(i+1);
        TH1D* h= new TH1D(&(name_ch)[0], &(name_ch)[0], range[0], range[1], range[2]);        
        for (int j=0; j<diff_time[i].size(); j++){
            h->Fill(diff_time[i][j]);
            h_tot->Fill(diff_time[i][j]);
        }
        histo.push_back(h);
    }
    histo.push_back(h_tot);
    return histo;
}

void fit_exp(TH1D* hist, vector<double>range, vector<double> exp_param){
    string name =hist->GetName();
    TCanvas *c = new TCanvas(&(name)[0], &(name)[0]);
    TF1 *f = new TF1("f", "[0]*exp(-x/[1])", range[1], range[2]);
    f->SetParNames("norm", "tau"); 
    f->SetParameters(exp_param[0], exp_param[1]);
    hist->Fit("f");
    hist->Draw();
    c->SaveAs(&("exp/"+name+".png")[0]);
    hist->Write();
}
    
void create_histo(){
    // name of file | number of channels for the time difference | number of bin | range inf exp | range sup exp | norm exp | tau exp
    map <string, vector<double>> datasets ={
                        //{"prova", {2, 0, 1, 1, 1}},
                        //{"prova1", {2, 0, 1, 1000, 0.03}},
                        {"5_5_weekend_4fe", {2, 500, 0, 10*pow(10,-6), 1000, 0.3}},
    };
    vector<vector<double>> diff_time;  
    vector<TH1D*> histos;
    TFile *histo_file= new TFile(&("exp/histos_exp.root")[0], "RECREATE");
    for (const auto &dataset : datasets){
        const auto name = dataset.first;
        const auto numb = dataset.second[0];
        const auto range = {dataset.second[1], dataset.second[2],dataset.second[3]};
        const auto exp_param = {dataset.second[4], dataset.second[5]};

        diff_time = read_time(name, numb);
        histos=fill_histo(diff_time, name, range);  
        for (int i=0; i<histos.size();i++){
            fit_exp(histos[i], range, exp_param);
        }
    }
    histo_file->Close();
    getchar();

}