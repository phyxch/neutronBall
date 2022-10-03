void plotPH()
{
    auto c1 = new TCanvas("c1","c1",200,10,600,400);
 
    c1->SetFillColor(42);
    c1->SetGrid();
    
    double pH_values[9] = {4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8};
    double radon_count[9] = {0,0,0,0,0,0,0,0,0};

    TFile* input = new TFile("main_pH_root_file", "read");
    
    TTree* t = (TTree*) input->Get("RDecayProducts");
    
    int entries = t->GetEntries();
    
    cout<<"entries : "<<entries<<endl;
    
    Double_t        pID;
    Double_t        Z;
    Double_t        A;
    Double_t        energy;
    Double_t        time;
    Double_t        pH;
    Char_t          pName[16];
    
    t->SetBranchAddress("A", &A);
    t->SetBranchAddress("pH", &pH);
    t->SetBranchAddress("pName", &pName);

    for(int i=0;i<entries;i++)
    {
        t->GetEntry(i);
        if(strncmp(pName, "Rn222", 5) == 0)
        {
             if(pH == 4)
             {
                 radon_count[0]++;
             }
             else if(pH == 4.5)
             {
                 radon_count[1]++;
             }
             else if(pH == 5)
             {
                 radon_count[2]++;
             }
             else if(pH == 5.5)
             {
                 radon_count[3]++;
             }
             else if(pH == 6)
             {
                 radon_count[4]++;
             }
             else if(pH == 6.5)
             {
                 radon_count[5]++;
             }
             else if(pH == 7)
             {
                 radon_count[6]++;
             }
             else if(pH == 7.5)
             {
                 radon_count[7]++;
             }
             else if(pH == 8)
             {
                 radon_count[8]++;
             }

        }
        
    }
    
    TGraph* graph =  new TGraph(9, pH_values, radon_count);
    
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
    
    for(int i=0;i<9;i++) cout<<radon_count[i]<<endl;
    
    input->Close();
    
}

/*

visit TGraph on root documentation

graph->Draw("ALP")  L = line, P = show points
ACP can be used C = smooth curve 

*/
