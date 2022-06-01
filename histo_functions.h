#ifndef HistoFunctionsHfile_
#define HistoFunctionsHfile_


#include "histo_infos.h"


TH1D fill_histo(TFile* tree_file, string name, vector<double> ranges, string type){
    double t;
    TTree* tree = (TTree*) tree_file->Get(&(name)[0]);
    double n_bin =(ranges[7]-ranges[6])/ranges[5];
    TH1D histo = TH1D(&(name+type)[0],&(name+type)[0], n_bin, ranges[6], ranges[7]);

    Int_t nentries = (Int_t)tree->GetEntries();
    tree->SetBranchAddress("t",&t);
    for (Int_t i=0; i<nentries; i++) {
        tree->GetEntry(i);
        histo.Fill(t);
    }
    char bin_w [7];
    snprintf (bin_w, 7, "%.2f", (ranges[7]-ranges[6])/n_bin); 
    string binw(bin_w);
    histo.GetXaxis()->SetTitle("t (#mu s)");
    histo.GetYaxis()->SetTitle(&("Entries / " + binw + " (#mu s)")[0]);
    return histo;
}



TH1D fill_histo_asym(TFile* tree_file, string name, vector<double> ranges, string type){
    double t;
    TTree* tree = (TTree*) tree_file->Get(&(name)[0]);
    double n_bin =(ranges[7]-ranges[6])/ranges[13];
    TH1D histo = TH1D(&(name+type)[0],&(name+type)[0], n_bin, ranges[6], ranges[7]);

    Int_t nentries = (Int_t)tree->GetEntries();
    tree->SetBranchAddress("t",&t);
    for (Int_t i=0; i<nentries; i++) {
        tree->GetEntry(i);
        histo.Fill(t);
    }
    for (auto eff : efficiencies){
        const auto pos = eff.first;
        if (name.find(pos) != string::npos) histo.Scale(1/efficiencies[pos]);
    }
    char bin_w [7];
    snprintf (bin_w, 7, "%.2f", (ranges[7]-ranges[6])/n_bin); 
    string binw(bin_w);
    histo.GetXaxis()->SetTitle("t (#mu s)");
    histo.GetYaxis()->SetTitle(&("Asymmetry / " + binw + " (#mu s)")[0]);
    return histo;
}

void fit_exp(TH1D* histo, vector<double> infos, string type, ofstream & fit_file, string option, double flu_inf=0., double flu_sup=0., double flu_short=0., int print =1){

    string name = histo->GetName();
    TF1 *exp_long, *exp_tot;
    if (type.find("offset") != string::npos) {
        /*if (name.find("pb") != string::npos) {
            exp_tot = new TF1("exp_tot", "[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]+[5]*exp(-x/[6])", infos[6]+flu_short, infos[7]+flu_sup);
            exp_tot->SetParNames("#Lambda_{Pb}", "#tau_{Pb} (#mu s)", "#Lambda_{+}", "#tau_{+} (#mu s)", "#Lambda_{0}", "#Lambda_{Al}", "#tau_{Al} (#mu s)");
            exp_tot->SetParameter(5, infos[0]);
            exp_tot->SetParameter(6, 0.88);
            exp_tot->SetParLimits(5, 0, infos[0]+pow(10, 4));
            exp_tot->SetParLimits(6, 0, 2);            
        }*/
        //else{
            exp_tot = new TF1("exp_tot", "[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]", infos[6]+flu_short, infos[7]+flu_sup);
            exp_tot->SetParNames("#Lambda_{-}", "#tau_{-} (#mu s)", "#Lambda_{+}", "#tau_{+} (#mu s)", "#Lambda_{0}");
        //}
        exp_tot->SetParameter(0, infos[0]);
        exp_tot->SetParameter(1, infos[1]);
        exp_tot->SetParameter(2, infos[2]);

        exp_tot->SetParLimits(0, 0, infos[1]+pow(10, 4));
        exp_tot->SetParLimits(1, infos[1]*0, infos[1]*2);
        exp_tot->SetParLimits(2,  0, infos[1]+pow(10, 4));

        if (type.find("double") != string::npos){
            exp_long = new TF1("exp_long", "[0]*exp(-x/[1])+[2]", infos[8]+flu_inf, infos[7]+flu_sup);
            exp_long->SetParNames("#Lambda_{+}", "#tau_{+} (#mu s)", "#Lambda_{0}");
            exp_long->SetParameters(infos[2], infos[3], infos[4]);

            exp_long->SetParLimits(0, 0, infos[2]+pow(10, 4));
            exp_long->SetParLimits(1, infos[3]*1/3, infos[3]*3);
            exp_long->SetParLimits(2, 0, infos[4]*1000);

            exp_long->SetLineColor(kGreen);
            histo->Fit("exp_long", &(option + "")[0]);
            

            exp_tot->FixParameter(2, exp_long->GetParameter(0));
            //exp_tot->SetParameter(2, exp_long->GetParameter(0));
            exp_tot->FixParameter(3, exp_long->GetParameter(1)/*2.197*/);
            //exp_tot->FixParameter(1, /*infos[1]*/0.29);

            if (type.find("fix") != string::npos) {
                exp_tot->FixParameter(4, exp_long->GetParameter(2));
            }
            else if (type.find("fix") == string::npos) {
                exp_tot->SetParameter(4, infos[4]);
                exp_tot->SetParLimits(4,  0, infos[4]*1000);
            }
        }
        
        else if (type.find("single") != string::npos){
            exp_tot->SetParameter(2, infos[2]);
            exp_tot->SetParameter(3, infos[3]);
            exp_tot->SetParameter(4, infos[4]);
            exp_tot->SetParLimits(2,  0, infos[1]+pow(10, 4));
            exp_tot->SetParLimits(4, 0, infos[4]+pow(10, 3));
            exp_tot->SetParLimits(3, infos[3]*1/3, infos[3]*3);
        }

    }
    else if (type.find("offset") == string::npos) {
        exp_tot = new TF1("exp_tot", "[0]*exp(-x/[1])+[2]*exp(-x/[3])", infos[6], infos[7]);
        exp_tot->SetParNames("#Lambda_{-}", "#tau_{-} (#mu s)", "#Lambda_{+}", "#tau_{+} (#mu s)");
        exp_tot->SetParameter(0, infos[0]);
        exp_tot->SetParameter(1, infos[1]);
        if (type.find("double") != string::npos){
            exp_long = new TF1("exp_long", "[0]*exp(-x/[1])", infos[8], infos[7]);
            exp_long->SetParNames("#Lambda_{+}", "#tau_{+} (#mu s)");
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
    
    histo->Fit("exp_tot", &(option+ " ")[0]);

    if (print == 1){
        fit_file << "\n\n####################### " << name << "#######################" << endl;
        if (type.find("double") != string::npos){
            cout << "chi_square / ndof =    " << exp_long->GetChisquare() << "/" << exp_long->GetNDF() <<endl;
            fit_file << "\n___________________ exp_long ___________________ " <<endl;
            fit_file << "chi_square / ndof =    " << exp_long->GetChisquare() << "/" << exp_long->GetNDF() <<endl;
            for (int i=0; i<exp_long->GetNpar(); i++) {
                fit_file << exp_long->GetParName(i) << " =   " <<  exp_long->GetParameter(i) << " +- " << exp_long->GetParError(i) <<endl;
            }
        }
        cout << "chi_square / ndof =    " << exp_tot->GetChisquare() << "/" << exp_tot->GetNDF() <<endl;
        fit_file << "\n___________________ exp_tot ___________________ " <<endl;
        fit_file << "chi_square / ndof =    " << exp_tot->GetChisquare() << "/" << exp_tot->GetNDF() <<endl;
        for (int i=0; i<exp_tot->GetNpar(); i++) {
            fit_file << exp_tot->GetParName(i) << " =   " <<  exp_tot->GetParameter(i) << " +- " << exp_tot->GetParError(i) <<endl;
        }
    }
}


void fit_exp_asym (TH1D* histo, vector<double> infos, string type, string option, double *offset){

    string name = histo->GetName();
    TF1 *exp_long;
    exp_long = new TF1("exp_long", "[0]*exp(-x/[1])+[2]", infos[8], infos[7]);
    exp_long->SetParNames("#Lambda+", "#tau+ (#mu s)", "#Lambda0");
    exp_long->SetParameters(infos[2], infos[3], infos[4]);
    exp_long->SetParLimits(0, 0, infos[2]+pow(10, 6));
    exp_long->SetParLimits(1, infos[3]*1/2, infos[3]*3/2);
    exp_long->SetParLimits(2, 0, infos[4]*1000);

    exp_long->SetLineColor(kGreen);
    histo->Fit("exp_long", &(option)[0]);

    *offset =exp_long->GetParameter(2);

}

void fit_cos(TH1D* histo, string type, string option, ofstream & fit_file, vector<double> infos, int fix =0){
    string name = histo->GetName();
    TF1* cos_func = new TF1("cos_func", "[0]*cos([1]*x+[2])+[3]", histo->GetXaxis()->GetXmin(),histo->GetXaxis()->GetXmax());
    cos_func->SetParameters(infos[9], infos[10], infos[11], infos[12]);
    cos_func->SetParNames("#rho", "#omega (rad/#mu s)", "#phi", "#psi");
    cos_func->SetParLimits(0, 0.01, 2);
    cos_func->SetParLimits(1, 0, 50);
    cos_func->SetParLimits(2, -4, 4);
    cos_func->FixParameter(2, 0);
    cos_func->SetParLimits(3, -2, 1);
    if(fix==1) cos_func->FixParameter(3, 0);
    histo->Fit("cos_func", &(option)[0]);
    cout << "chi_square / ndof =    " << cos_func->GetChisquare() << "/" << cos_func->GetNDF() <<endl;
    fit_file << "\n\n####################### " << name << "cos_func " << "#######################" << endl;
    fit_file << "chi_square / ndof =    " << cos_func->GetChisquare() << "/" << cos_func->GetNDF() <<endl;
    for (int i=0; i<cos_func->GetNpar(); i++) {
        fit_file << cos_func->GetParName(i) << " =   " <<  cos_func->GetParameter(i) << " +- " << cos_func->GetParError(i) <<endl;
    }
}

void fit_constant(TH1D* histo, string type, string option, ofstream & fit_file){
    string name = histo->GetName();
    cout << histo->GetXaxis()->GetXmin() << endl;
    TF1* constant = new TF1("const", "[0]", histo->GetXaxis()->GetXmin(), histo->GetXaxis()->GetXmax());
    constant->SetParName(0, "offset");
    constant->SetParameter(0, -0.1);
    constant->SetParLimits(0, -2, 2);
    histo->Fit("const", &(option)[0]);
    cout << "chi_square / ndof =    " << constant->GetChisquare() << "/" << constant->GetNDF() <<endl;
    fit_file << "\n\n####################### " << name << "_constant " << "#######################" << endl;
    fit_file << "chi_square / ndof =    " << constant->GetChisquare() << "/" << constant->GetNDF() <<endl;
    for (int i=0; i<constant->GetNpar(); i++) {
        fit_file << constant->GetParName(i) << " =   " <<  constant->GetParameter(i) << " +- " << constant->GetParError(i) <<endl;
    }
}

TH1D* subtract_histo(TH1D* histo_mag, TH1D* histo_nacl){
    TH1D* histo_sub;
    histo_sub = (TH1D*)histo_mag->Clone();
    histo_sub->Sumw2();
    histo_sub->Add(histo_nacl, -1);
    return histo_sub;
}

void sys_unc(TH1D histo, ofstream & fit_file, string material, string type){
    double min_l =10, max_l=-10, min_s =10, max_s=-10, tau_l, tau_s;
    TF1* func;
    fit_file << histo.GetName() << endl;
    for (double flu_inf=-0.2; flu_inf<= 0.21; flu_inf=flu_inf+0.1){
        for (double flu_sup=-4; flu_sup<= 0.1; flu_sup++){
            for (double flu_short=-0.03; flu_short<= 0.03; flu_short = flu_short+0.02){
                fit_exp(&histo, materials_dict_pos[material], type, fit_file, " Q L R I", flu_inf, flu_sup, flu_short, 0);
                func = histo.GetFunction("exp_tot");
                tau_l = func->GetParameter(3);
                tau_s = func->GetParameter(1);

                max_l = (tau_l>max_l) ? tau_l : max_l;
                min_l = (tau_l<min_l) ? tau_l : min_l;

                max_s = (tau_s>max_s) ? tau_s : max_s;
                min_s = (tau_s<min_s) ? tau_s : min_s;
                //fit_file << flu_inf <<"  "<< flu_sup <<"  "<< flu_short << endl;
                //cout << flu_inf <<"  "<< flu_sup <<"  "<< flu_short << endl;
            }
        }
    }
    double span_l = max_l-min_l;
    cout << "\n\n" << min_l <<  endl;
    cout << max_l <<  endl;
    cout << span_l << "\n\n" << endl;

    
    double span_s = max_s-min_s;
    cout << "\n\n" << min_s <<endl;
    cout << max_s << endl;
    cout <<span_s << "\n\n" << endl;

    fit_file << "\n\nlong:\n" << min_l << "\n\n" << endl;
    fit_file << "\n\n" << max_l << "\n\n" << endl;
    fit_file << "\n\n" << span_l << "\n\n" << endl;                    

    fit_file << "\n\nshort: \n" << min_s << "\n\n" << endl;
    fit_file << "\n\n" << max_s << "\n\n" << endl;
    fit_file << "\n\n" << span_s << "\n\n" << endl;    

}
void save_plot(TH1D* histo, string type){
    string name = histo->GetName();
    cout << name << endl;
    TCanvas *c = new TCanvas(&(name)[0], &(name)[0]);
    
    histo->Draw("E");
    c->Update();
    TPaveStats *st = (TPaveStats*)c->GetPrimitive("stats");
    
    //histo->SetMarkerStyle(kFullCircle);
    TF1* func;
    if (name.find("asym_cos") != string::npos) {
        func = histo->GetFunction("cos_func");
        gStyle->SetOptStat("0");
        gStyle->SetOptFit(111);
        st->SetX1NDC(0.7); //new x start position
        st->SetX2NDC(0.9); //new x end position
        st->SetY1NDC(0.7); //new x start position
        st->SetY2NDC(0.9); //new x end position
    }
    else if (name.find("asym_const") != string::npos) {
        func = histo->GetFunction("const");
        gStyle->SetOptStat("0");
        gStyle->SetOptFit(111);
        st->SetX1NDC(0.7); //new x start position
        st->SetX2NDC(0.9); //new x end position
        st->SetY1NDC(0.7); //new x start position
        st->SetY2NDC(0.9); //new x end position
    }
    else  {
        func = histo->GetFunction("exp_tot");
        //gPad-> SetLogy();
        gStyle->SetOptStat("neou");
        gStyle->SetOptFit(112);
        st->SetX1NDC(0.3); //new x start position
        st->SetX2NDC(0.9); //new x end position
        st->SetY1NDC(0.3); //new x start position
        st->SetY2NDC(0.9); //new x end position
    }
    
    func->Draw("SAME");




    /*auto legend = new TLegend(0.4,0.7,0.6,0.85);
    gStyle->SetLegendBorderSize(0);
    //legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
    legend->AddEntry(histo, &(name)[0],"l");
    if (name.find("asym") != string::npos) legend->AddEntry(func, "cos","l");
    else legend->AddEntry(func, "exp","l");
    legend->Draw();*/

    //c->BuildLegend(0.7,0.6,0.9,0.7);

    c->SaveAs(&("images/"+type+"/"+name+".pdf")[0]);
    c->Write();
}



#endif
