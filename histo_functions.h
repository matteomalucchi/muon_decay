#ifndef HistoFunctionsHfile_
#define HistoFunctionsHfile_




TH1D fill_histo(TFile* tree_file, string name, vector<double> ranges, string type){
    double t;
    TTree* tree = (TTree*) tree_file->Get(&(name)[0]);
    TH1D histo = TH1D(&(name+type)[0],&(name+type)[0], ranges[5], ranges[6], ranges[7]);

    Int_t nentries = (Int_t)tree->GetEntries();
    tree->SetBranchAddress("t",&t);
    for (Int_t i=0; i<nentries; i++) {
        tree->GetEntry(i);
        histo.Fill(t);
    }
    histo.GetXaxis()->SetTitle("time (#mu s)");
    histo.GetYaxis()->SetTitle(&("Entries / "+to_string(histo.GetBinWidth(1)))[0]);
    return histo;
}

void fit_exp(TH1D* histo, vector<double> infos, string type, ofstream & fit_file, string option, double *offset ){

    string name = histo->GetName();
    fit_file << "\n\n####################### " << name << "#######################" << endl;
    TF1 *exp_long, *exp_tot;
    if (type.find("offset") != string::npos) {
        exp_tot = new TF1("exp_tot", "[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]", infos[6], infos[7]);
        exp_tot->SetParNames("norm_short (a.u.)", "tau_short (#mu s)", "norm_long (a.u.)", "tau_long (#mu s)", "offset (a.u.)");
        exp_tot->SetParameter(0, infos[0]);
        exp_tot->SetParameter(1, infos[1]);
        exp_tot->SetParLimits(0, 0, infos[1]+pow(10, 5));
        //exp_tot->SetParLimits(1, infos[1]*3/4, infos[1]*4/3);
        if (type.find("double") != string::npos){
            exp_long = new TF1("exp_long", "[0]*exp(-x/[1])+[2]", infos[8], infos[7]);
            exp_long->SetParNames("norm_long (a.u.)", "tau_long (#mu s)", "offset_long (a.u.)");
            exp_long->SetParameters(infos[2], infos[3], infos[4]);
            exp_long->SetParLimits(0, 0, infos[2]+pow(10, 6));
            //exp_long->SetParLimits(1, infos[3]*3/4, infos[3]*4/3);

            exp_long->SetLineColor(kGreen);
            histo->Fit("exp_long", &(option)[0]);
            exp_tot->FixParameter(2, exp_long->GetParameter(0));
            exp_tot->FixParameter(3, exp_long->GetParameter(1));
            if (type.find("fix") != string::npos) {
                exp_tot->FixParameter(4, exp_long->GetParameter(2));
            }
            else if (type.find("fix") == string::npos) {
                exp_tot->SetParameter(4, infos[4]);
            }
        }
        else if (type.find("single") != string::npos){
            exp_tot->SetParameter(2, infos[2]);
            exp_tot->SetParameter(3, infos[3]);
            exp_tot->SetParameter(4, infos[4]);
            exp_tot->SetParLimits(2, 0, infos[2]+pow(10, 6));
            //exp_tot->SetParLimits(3, infos[3]*3/4, infos[3]*4/3);
        }

    }
    else if (type.find("offset") == string::npos) {
        exp_tot = new TF1("exp_tot", "[0]*exp(-x/[1])+[2]*exp(-x/[3])", infos[6], infos[7]);
        exp_tot->SetParNames("norm_short (a.u.)", "tau_short (#mu s)", "norm_long (a.u.)", "tau_long (#mu s)");
        exp_tot->SetParameter(0, infos[0]);
        exp_tot->SetParameter(1, infos[1]);
        if (type.find("double") != string::npos){
            exp_long = new TF1("exp_long", "[0]*exp(-x/[1])", infos[8], infos[7]);
            exp_long->SetParNames("norm_long (a.u.)", "tau_long (#mu s)");
            exp_long->SetParameters(infos[2], infos[3]);
            exp_long->SetLineColor(kGreen);
            histo->Fit("exp_long", &(option)[0]);
            exp_tot->FixParameter(2, exp_long->GetParameter(0));
            exp_tot->FixParameter(3, exp_long->GetParameter(1));
        }
        else if (type.find("single") != string::npos){
            exp_tot->SetParameter(2, infos[2]);
            exp_tot->SetParameter(3, infos[3]);
        }
    }
    histo->Fit("exp_tot", &(option)[0]);
    if (type.find("offset") != string::npos) *offset =exp_tot->GetParameter(4);

    if (type.find("double") != string::npos){
        fit_file << "\n___________________ exp_long ___________________ " <<endl;
        fit_file << "chi_square / ndof =    " << exp_long->GetChisquare() << "/" << exp_long->GetNDF() <<endl;
        for (int i=0; i<exp_long->GetNpar(); i++) {
            fit_file << exp_long->GetParName(i) << " =   " <<  exp_long->GetParameter(i) << " +- " << exp_long->GetParError(i) <<endl;
        }
    }

    fit_file << "\n___________________ exp_tot ___________________ " <<endl;
    fit_file << "chi_square / ndof =    " << exp_tot->GetChisquare() << "/" << exp_tot->GetNDF() <<endl;
    for (int i=0; i<exp_tot->GetNpar(); i++) {
        fit_file << exp_tot->GetParName(i) << " =   " <<  exp_tot->GetParameter(i) << " +- " << exp_tot->GetParError(i) <<endl;
    }

}

void save_plot(TH1D* histo, string type){
    string name = histo->GetName();
    gStyle->SetOptStat("neou");
    gStyle->SetOptFit(1111);
    TCanvas *c = new TCanvas(&(name)[0], &(name)[0]);
    histo->Draw("HIST");
    c->SaveAs(&("images/"+type+"/"+name+".png")[0]);
    c->Write();
}

void fit_sin(TH1D* histo, string type, string option, ofstream & fit_file){
    string name = histo->GetName();
    cout << histo->GetXaxis()->GetXmin() << endl;
    TF1* sin = new TF1("sin", "[0]*sin([1]*x+[2])+[3]", histo->GetXaxis()->GetXmin(), 5);
    sin->SetParameters(0.09, 4.9, 0.4, -0.2);
    histo->Fit("sin", &(option)[0]);
    fit_file << "\n\n####################### " << name << "#######################" << endl;
    fit_file << "chi_square / ndof =    " << sin->GetChisquare() << "/" << sin->GetNDF() <<endl;
    for (int i=0; i<sin->GetNpar(); i++) {
        fit_file << sin->GetParName(i) << " =   " <<  sin->GetParameter(i) << " +- " << sin->GetParError(i) <<endl;
    }
}

#endif
