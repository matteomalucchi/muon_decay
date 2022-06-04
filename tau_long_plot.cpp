void tau_long_plot(){
    double tau [] = {2.20,  2.1, 2.1, 2.12,1.8, 2.0,};
    double tau_stat [] = {0.03, 0.1, 0.1, 0.06, 0.1, 0.1,};
    double tau_sys [] = {0.01, 0.04, 0.1, 0.02, 0.02, 0.05,};
    const int dimension = sizeof(tau)/sizeof(tau[0]);
    double tau_sum [dimension] = {};
    double idx [dimension] ={};
    double idx_stat [dimension] ={};
    double idx_sum [dimension] ={};


    map <string, vector<double>> names = {
        {"fe_top_tot", {1}},
        {"nacl_top_tot", {2}},
        {"nacl_bottom_tot", {3}},
        {"mag_top_tot", {4}},
        {"al_bottom_tot", {5}},
        {"pb_bottom_tot", {6}},
    };

    for (int i=0; i < sizeof(idx)/sizeof(idx[0]); i++){
        idx[i]= i+1;
        idx_stat[i]= 0.1;
        idx_sum[i]= 0.2;
        tau_sum[i] = sqrt(tau_stat[i]*tau_stat[i]+tau_sys[i]*tau_sys[i]);
    }


    TCanvas *c = new TCanvas("tau_long", "tau_long",200,10,600,400);
    c->DrawFrame(1., 0., 3., names.size()+0.5);
    auto legend = new TLegend(0.6,0.6,0.9,0.9);

    // Now we have to somehow depict the sum of errors
    /*TGraphErrors* gr_sum = new TGraphErrors(dimension,tau, idx, tau_sum, idx_sum);
    gr_sum->SetLineColor(kViolet);
    gr_sum->SetLineWidth(1);
    gr_sum->SetFillColorAlpha(kWhite, 0);
    gr_sum->Draw("A 5");
    gr_sum->SetTitle("Combined Measurements of #tau_{+}");
    gr_sum->GetXaxis()->SetTitle("#tau_{+} (#mu s)");
    gr_sum->GetYaxis()->SetTitle("Measuremets");
    gr_sum->GetXaxis()->SetLimits(1., 3.);
    gr_sum->GetYaxis()->SetLimits(0., names.size()+0.5);*/

    // We first have to draw it only with the stat errors
    TGraphErrors* gr_stat = new TGraphErrors(dimension,tau, idx, tau_stat,idx_stat);
    gr_stat->SetLineColor(kBlue);
    gr_stat->SetFillColorAlpha(kWhite, 1);
    gr_stat->SetLineWidth(1);
    gr_stat->SetMarkerStyle(20);
    gr_stat->SetTitle("Measurements of #tau_{+}");
    gr_stat->GetXaxis()->SetTitle("#tau_{+} (#mu s)");
    gr_stat->GetYaxis()->SetTitle("Measuremets");
    gr_stat->GetXaxis()->SetLimits(1., 3.);
    gr_stat->GetYaxis()->SetLimits(0., names.size()+0.5);
    gr_stat->Draw("A 5 ");
    
    // Now we have to somehow depict the sys errors
    TGraphErrors* gr_sys = new TGraphErrors(dimension,tau, idx, tau_sys,nullptr);
    gr_sys->SetLineColor(kRed);
    gr_sys->SetLineWidth(3);

    gr_sys->Draw("P");

    // draw points
    TGraphErrors* gr_point = new TGraphErrors(dimension,tau, idx, nullptr,nullptr);
    gr_point->SetMarkerSize(0.5);
    gr_point->SetMarkerStyle(20);
    gr_point->Draw("P");

    // PDG value
    auto tau_pdg=new TLine(2.197, 0.5, 2.197, names.size()+0.5);
    tau_pdg->SetLineColor(kGreen);
    tau_pdg->SetLineStyle(9);
    tau_pdg->SetLineWidth(1);
    tau_pdg->Draw();


    for (const auto & info : names){
        const auto name = info.first;
        const auto numb = info.second;
        // Add labels
        TPaveLabel *title = new TPaveLabel(1.05, numb[0]-0.2, 1.4, numb[0]+0.2, &(name)[0]);
        title->SetFillColor(0);
        title->SetBorderSize(0);
        //title->SetTextFont(1);
        title->SetTextSize(0.55);
        title->Draw();

        TArrow *ar1 = new TArrow(1.45, numb[0], 1.6, numb[0]);
        ar1->SetArrowSize(0.02);
        ar1->Draw();
    }

    /*
    // weighted average 
    float weights[dimension];
    float tau_ave=0;
    float weights_sum=0;
    for(int k=0; k<dimension;k++){
        weights[k]=1/(tau_sum[k]*tau_sum[k]);
        weights_sum+=weights[k];
    }
    for(int k=0; k<dimension;k++){
        tau_ave+=tau[k]*weights[k]/weights_sum;
    }
    float tau_ave_err=sqrt(1/weights_sum);
    double tau_ave_arr[dimension];
    double tau_ave_err_arr[dimension];
    for(int k=0; k<dimension;k++){
        tau_ave_arr[k]= tau_ave;
        tau_ave_err_arr[k]= tau_ave_err;
    }

    auto meanline=new TLine(tau_ave, 0.8, tau_ave,names.size()+0.2);
    meanline->SetLineColor(7);
    meanline->SetLineWidth(1);
    meanline->SetLineStyle(9);
    meanline->Draw("SAME");

    auto meanlinesx=new TLine(tau_ave-tau_ave_err, 0.8, tau_ave-tau_ave_err, names.size()+0.2);
    meanlinesx->SetLineColor(7);
    meanlinesx->SetLineWidth(1);
    meanlinesx->Draw("SAME");

    auto meanlinedx=new TLine(tau_ave+tau_ave_err, 0.8, tau_ave+tau_ave_err, names.size()+0.2);
    meanlinedx->SetLineColor(7);
    meanlinedx->SetLineWidth(1);
    meanlinedx->Draw("SAME");*/


    legend->AddEntry(gr_point, "Value","p");
    legend->AddEntry(gr_stat, "Statistical uncertainty","f");
    legend->AddEntry(gr_sys, "Systematic uncertainty","l");
    //legend->AddEntry(gr_sum, "Sum of uncertainties","f");
    //legend->AddEntry(meanline,"Weighted average","l");
    legend->AddEntry(tau_pdg, "#tau_{#mu} PDG = 2.197 #mu s","l");

    legend->Draw();

    c->SaveAs("tau_long_tot.pdf");
}

