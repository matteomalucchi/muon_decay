#include <string>

using namespace std;

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
        {"pmt5", 
            {{1850, 1900, 1950, 2000, 1930, 1880},
            {1794., 1786., 1834., 1812., 1822., 1880.},
            {2030, 2038, 2139, 2058, 2085, 2108},
            {1800}}},
        {"pmt6", 
            {{1850, 1900, 1950, 2000},
            {104., 98., 109., 97.},
            {114, 108, 120, 108},
            {1800}}},
    };
    TFile *outfile= new TFile("efficiency/efficiencies.root", "RECREATE");

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
        }
        TCanvas *c = new TCanvas(&("c_" + pmt)[0], &("c_" + pmt)[0]);
        TGraphErrors* gr = new TGraphErrors(volt.size(),&volt[0], &eff[0],nullptr,&eff_err[0]);
        gr->SetMarkerStyle(1);
        gr->SetTitle(&("Efficiency "+pmt)[0]);
        gr->GetXaxis()->SetTitle(&("Voltage "+ pmt + " [V]")[0]);
        //gr->GetXaxis()->SetLimits(*min_element(volt.begin(), volt.end())-10,*max_element(volt.begin(), volt.end())+10);
        gr->GetXaxis()->SetLimits(1550., 2050.);
        gr->GetYaxis()->SetTitle("Efficiency");
        //gr->GetYaxis()->SetLimits(*min_element(eff.begin(), eff.end())-0.1,*max_element(eff.begin(), eff.end())+0.1);
        gr->GetYaxis()->SetRangeUser(0., 1.);
        auto line=new TLine(good_volt[0], 0, good_volt[0], 1);
        line->SetLineColor(2);
        line->SetLineStyle(9);
        gr->Draw("AP");
        line->Draw("same");
        c->SaveAs(&("efficiency/"+pmt+"_efficiency.pdf")[0]);
        c->Write();
    }
}




// efficiency pmt2 (27/04/22) 

/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[]={1650, 1675, 1700, 1800, 1850, 1900, 1950, 2000, 1930};
    float y[sizeof(x)/sizeof(x[0])]={720./945, 857./1029, 849./985, 0.892, 0.905, 0.926, 0.931, 0.912, 0.926};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");
}
*/
// efficiency pmt3 (27/04/22)

/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[]={1700,1750, 1800, 1850, 1880, 1900, 1950, 1930, 1970};
    float y[sizeof(x)/sizeof(x[0])]={1526./3562, 1804./3725, 0.559, 1920./3652, 2029./3773, 0.620,0.631, 0.619, 0.605};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}
*/

// efficiency pmt3 (28/04/22)

/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[]={1700, 1750, 1800, 1850, 1900};
    float y[sizeof(x)/sizeof(x[0])]={1576./2870, 1682./2665, 1812./2804, 1784./2731, 1937./2801};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}
*/
// efficiency pmt4 (27/04/22)

/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[]={1700, 1850, 1900, 1950, 2000, 1930};
    float y[sizeof(x)/sizeof(x[0])]={1896./2502, 0.72, 0.73, 0.75, 0.74, 0.74};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}*/

// efficiency pmt4 (28/04/22)
/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[]={1600, 1650, 1700, 1750, 1850};
    float y[sizeof(x)/sizeof(x[0])]={1532./2496, 1765./2415, 1896./2502, 1803./2300, 1843./2308 };
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}
*/
// efficiency pmt5 (27/04/22)
/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[6]={1850, 1900, 1950, 2000, 1930, 1880};
    float y[sizeof(x)/sizeof(x[0])]={0.88, 0.88, 0.86, 0.88, 0.87,0.89 };
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}*/

// efficiency pmt5 (28/04/22)
/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[6]={1850, 1900, 1950, 2000, 1930, 1880};
    float y[sizeof(x)/sizeof(x[0])]={0.88, 0.88, 0.86, 0.88, 0.87,0.89 };
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}*/

// efficiency pmt6 (27/04/22)
/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[]={1850, 1900, 1950, 2000};
    float y[sizeof(x)/sizeof(x[0])]={0.91, 0.91, 0.91, 0.9};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}*/
/*
// efficiency pmt1 with coinc 123 and 23 (28/04/22)
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[]={1700,1725, 1750, 1800, 1850, 1900, 1950, 1980, 2000};
    float y[sizeof(x)/sizeof(x[0])]={294./4006, 484./3960, 684./4015, 807./4032, 899./4053, 943./4038, 978./3955, 1014./3985, 1034./4061};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}*/


/*
1850
1800
1850
1750*/