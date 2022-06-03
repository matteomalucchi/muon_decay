#include <string>

using namespace std;

/* Map ordered as:
 * pmt
 * Voltage [V]
 * Number of triple coincidences
 * Number of double coincidences
 * Chosen Voltage
*/
void efficiency_plot(){
    map <string, vector<vector<float>>> volt_eff ={ 
        {"pmt1", 
            {{1700,1725, 1750, 1800, 1850, 1900, 1950, 1980, 2000},
            {294., 484., 684., 807., 899., 943., 978., 1014., 1034.},
            {4006, 3960, 4015, 4032, 4053, 4038, 3955, 3985, 4061},
            {1850}}},
        {"pmt2", 
            {{1650, 1675, 1700, 1800, 1900},
            {720., 857., 849., 956,  943},
            {945, 1029, 985, 1092, 1008},
            {1700}}},
        {"pmt3", 
            {{1700, 1750, 1800, 1850, 1900},
            {1576., 1682., 1812., 1784., 1937.},
            {2870, 2665, 2804, 2731, 2801},
            {1750}}},                
        {"pmt4", 
            {{1600, 1650, 1700, 1750, 1850},
            {1532., 1765., 1896., 1803., 1843.},
            {2496, 2415, 2502, 2300, 2308},
            {1750}}},
        {"pmt5", //foto triple, doppie, 4, 5, 6     // V4=1750, v6=1800 // nuove V prova: V4=1650, V6=1700, v5=1900 :eff= 1255/1274
            {{1600, 1700, 1800, 1650, 1900},
            {1345., 1732., 1755., 1673., 1828.},
            {2120, 2000, 1975, 1977, 2006},
            {1650}}},
        {"pmt6", //foto triple, doppie, 5, 6, 7   // V5=1650, v6=1750 //
            {{1700,1725, 1750, 1775, 1800},
            {51., 65., 59., 60., 77. },
            {72, 76, 67, 62, 80},
            {1750}}},
        {"pmt7", //foto triple, doppie, 5, 6, 7   // V5=1650, v6=1750 //
            {{1650, 1700, 1750, 1600},
            {50., 73., 92., 42., },
            {1997, 2015, 2010, 2058},
            {1700}}},            
    };
    TFile *outfile= new TFile("efficiencies.root", "RECREATE");

    for (const auto &pair : volt_eff){
        const auto pmt = pair.first;
        const auto volt = pair.second[0];
        const auto num = pair.second[1];
        const auto den = pair.second[2];
        const auto good_volt = pair.second[3];

        vector<float> eff(num.size());
        vector<float> eff_err(num.size());

        for (int i=0;i<num.size();i++){
            eff[i]=num[i]/den[i];
            eff_err[i]=sqrt(eff[i]*(1-eff[i])/den[i]);
            cout << pmt << "    " <<eff[i] <<" +- " << eff_err[i] <<endl;
        } 
        TCanvas *c = new TCanvas(&("c_" + pmt)[0], &("c_" + pmt)[0]);
        TGraphErrors* gr = new TGraphErrors(volt.size(),&volt[0], &eff[0],nullptr,&eff_err[0]);
        //gr->SetMarkerStyle(1);
        gr->SetTitle(&("Efficiency "+pmt)[0]);
        gr->GetXaxis()->SetTitle(&("Voltage "+ pmt + " [V]")[0]);
        //gr->GetXaxis()->SetLimits(*min_element(volt.begin(), volt.end())-10,*max_element(volt.begin(), volt.end())+10);
        gr->GetXaxis()->SetLimits(1550., 1950.);
        gr->GetYaxis()->SetTitle("Efficiency");
        //gr->GetYaxis()->SetLimits(*min_element(eff.begin(), eff.end())-0.1,*max_element(eff.begin(), eff.end())+0.1);
        gr->GetYaxis()->SetRangeUser(0.5, 1.);

        auto line=new TLine(good_volt[0], 0.5, good_volt[0], 1);
        line->SetLineColor(kBlue);
        line->SetLineStyle(9);
        gr->SetMarkerStyle(kFullDotLarge);
        gr->Draw("AP");
        line->Draw("same");
        TGraphErrors* gr1;
        double a[1] = {1900};
        double b[1]={1255./1274};
        double d[1]= {sqrt(1255./1274*(1-1255./1274)/1274)};
        if (pmt == "pmt5"){
            gr1= new TGraphErrors(1, a, b,nullptr,d);
            gr1->SetMarkerColor(kRed);
            gr1->SetMarkerStyle(kFullDotLarge);
            //gr1->SetMarkerSize();
            gr1->Draw("SAME P");
        }        
        c->SaveAs(&(pmt+"_efficiency.pdf")[0]);
        c->Write();
    }
    outfile->Close();
}
