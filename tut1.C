void tut1()
{

    double pH_values[5] = {4,5,6,7,8};
    double radon_count[5] = {0,0,0,0,0};

    TFile* input = new TFile("main_pH_output.root", "read");
    
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
             else if(pH == 5)
             {
                 radon_count[1]++;
             }
             else if(pH == 6)
             {
                 radon_count[2]++;
             }
             else if(pH == 7)
             {
                 radon_count[3]++;
             }
             else if(pH == 8)
             {
                 radon_count[4]++;
             }

        }
    }
    
    TGraph* graph =  new TGraph(5, pH_values, radon_count);
    
    graph->SetMarkerStyle(4);
    graph->SetMarkerSize(1);
    
    TCanvas* c1 = new TCanvas();
    graph->Draw("ACP");
    
    for(int i=0;i<5;i++) cout<<radon_count[i]<<endl;
    
    input->Close();
    
}

/*

visit TGraph on root documentation

graph->Draw("ALP")  L = line, P = show points
ACP can be used C = smooth curve 

*/
