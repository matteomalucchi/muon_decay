#include <iostream>

using namespace std;

void create_prova(){

    ofstream out_file("prova.dat");
    double numb = 100.;
    vector <double> t;
    //iota(begin(t), end(t), 0);
    double eps = 0.0000001f, a=0., inc=1. ;
    for(double n = a; n <= numb + eps; n += inc){
        t.push_back(n);
    }

    TRandom *r0 = new TRandom1();
    TCanvas *c1 = new TCanvas("exp", "exp");
    TH1D* h1= new TH1D("exp", "exp", 200, 0, 0.01);
    for (int j=0; j<1000; j++){
        h1->Fill(r0->Exp(0.003));
    }
    h1->Draw();

    for(int i=0; i<numb; i++){
        out_file << 1 << setprecision(6) <<"          " << t[i]<<endl;
        cout << t[i] <<endl;
        if(i%10==0 && i%30!=0){
            out_file << 2 << "          " << t[i]+r0->Exp(0.03) <<endl;
        }
        if(i%30==0){
            out_file << 3 << "          " << t[i]+r0->Exp(0.03)<<endl;
        }
    }

}