/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[6]={1800, 1850, 1900, 1950, 2000, 1930};
    float y[sizeof(x)/sizeof(x[0])]={0.892, 0.905, 0.926, 0.931, 0.912, 0.926};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");
}*/

/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[5]={1800, 1900, 1950, 1930, 1970};
    float y[sizeof(x)/sizeof(x[0])]={0.559,0.620,0.631, 0.619, 0.605};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}*/
/*
void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[5]={1850, 1900, 1950, 2000, 1930};
    float y[sizeof(x)/sizeof(x[0])]={0.72, 0.73, 0.75, 0.74, 0.74};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}*/


void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[6]={1850, 1900, 1950, 2000, 1930, 1880};
    float y[sizeof(x)/sizeof(x[0])]={0.88, 0.88, 0.86, 0.88, 0.87,0.89 };
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}