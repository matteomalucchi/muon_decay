/*
void efficiency_plot(){
    map(v:e)
    for v,e in map{
        TCanvas *c = new TCanvas(&("c"+to_string(i))[0], &("c"+to_string(i))[0]);
        TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),v, e,nullptr,nullptr);
        gr->SetMarkerStyle(2);
        gr->Draw("AP");
    }
}
*/



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


void efficiency_plot(){
    TCanvas *c = new TCanvas("c", "c");
    float x[]={1700, 1750, 1800, 1850, 1900};
    float y[sizeof(x)/sizeof(x[0])]={1576./2870, 1682./2665, 1812./2804, 1784./2731, 1937./2801};
    TGraphErrors* gr = new TGraphErrors(sizeof(x)/sizeof(x[0]),x,y,nullptr,nullptr);
    gr->SetMarkerStyle(2);
    gr->Draw("AP");

}

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