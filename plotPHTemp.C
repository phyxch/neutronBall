void plotPHTemp()
{
    auto c1 = new TCanvas("c1","c1",200,10,600,400);
 
    c1->SetFillColor(42);
    c1->SetGrid();
    
    double pH_values[18] = {4.64, 4.77, 4.98, 5.05, 5.17, 5.27,  5.43, 6.04, 6.23, 6.26, 6.67, 7.17, 7.47, 7.53, 7.57, 7.64, 8.12, 8.20};
    double radon_count[18] = {0.20, 0.25, 0.24, 0.28, 0.30, 0.22, 0.38, 0.16, 0.28, 0.38, 0.20, 0.34, 0.34, 0.30, 0.44, 0.34, 0.38, 0.33};

    TGraph* graph =  new TGraph(18, pH_values, radon_count);
    
    graph->SetMarkerStyle(4);
    graph->SetMarkerSize(1);
    graph->SetLineColor(2);
    graph->SetLineWidth(2);
    graph->SetMarkerColor(4);
    graph->SetMarkerSize(1.5);
    // graph->SetMarkerStyle(21);
    graph->SetTitle("Radon Counts Vs pH");
    graph->GetXaxis()->SetTitle("pH");
    graph->GetYaxis()->SetTitle("Radon Counts");
    graph->Draw("ACP");
    
    c1->Update();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);
    c1->Modified();

    
}

/*

visit TGraph on root documentation

graph->Draw("ALP")  L = line, P = show points
ACP can be used C = smooth curve 

*/
