#include <iostream>
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

void dataVsSim() {
    // Data input assigned to variables
    string dataSet, simSet, branchName;
    int bins;
    float xLower, xUpper;
    cout << "Data Set? ";
    cin >> dataSet;
    cout << "Simulation Data Set? ";
    cin >> simSet;
    cout << "Branch? ";
    cin >> branchName;
    cout << "Number of bins? ";
    cin >> bins;
    cout << "From? ";
    cin >> xLower;
    cout << "To? ";
    cin >> xUpper;
    
    // Custom data file location string from input data
    string dataFilePath = "/run/media/davidwassell/David USB/" + dataSet + "/Lb_Tuple.root";
    // Custom simulation data file location string from input data
    string simFilePath = "/run/media/davidwassell/David USB/" + simSet + "/Lb_Tuple.root";

    // Open data file path and create a tree
    TFile* rootDataFile = TFile::Open(dataFilePath.c_str());
    TTree* treeData = (TTree*) rootDataFile->Get("tree");

    // Open sim file path and create a tree
    TFile* rootSimFile = TFile::Open(simFilePath.c_str());
    TTree* treeSim = (TTree*) rootSimFile->Get("tree");

    // Custom Canvas title string from input
    string canvasTitle = "Canvas: " + dataSet + " & " + simSet + " - " + branchName; 
    
    // Canvas made so multiple plots can be opened at once
    TCanvas* canvas = new TCanvas(canvasTitle.c_str(),canvasTitle.c_str()); 

    // 1st histogram for actual data
    TH1D* dataHist = new TH1D("dataHist","",bins,xLower,xUpper);

    // Data drawn to histogram
    // treeData->Draw((branchName + ">>dataHist").c_str(), "Lb_MM > 5800");
    treeData->Draw((branchName + ">>dataHist").c_str());
    dataHist->SetLineColor( kBlue );

    // 2nd histogram for simulation data
    TH1D* simHist = new TH1D("simHist","",bins,xLower,xUpper);

    // Simulation drawn to histogram
    // treeSim->Draw((branchName + ">>simHist").c_str(), "Lb_BKGCAT < 31");
    treeSim->Draw((branchName + ">>simHist").c_str());
    simHist->SetLineColor( kRed );

    // Both data sets drawn to canvas
    
    // For testing
    // printf("simHist Max: %f\n",simHist->GetMaximum());
    // printf("dataHist Max: %f\n",dataHist->GetMaximum());
    
    // Uncomment and do manually if below if and else statements don't give correct axis scaling
    // dataHist->DrawNormalized();
    // simHist->DrawNormalized("SAME");
    // simHist->DrawNormalized();
    // dataHist->DrawNormalized("SAME");
    

    if (simHist->GetBinContent(simHist->GetMaximumBin()) > dataHist->GetBinContent(dataHist->GetMaximumBin()) ){ 
        simHist->DrawNormalized();
        dataHist->DrawNormalized("SAME");
        simHist->SetMaximum(simHist->GetMaximumBin());
    } else {
        dataHist->DrawNormalized();
        simHist->DrawNormalized("SAME");
        dataHist->SetMaximum(dataHist->GetMaximumBin());
    }

    // Legend created
    TLegend* leg = new TLegend();
    leg->SetHeader("Legend");
    leg->AddEntry("dataHist",(branchName + " - " + dataSet).c_str(),"l");
    leg->AddEntry("simHist",(branchName + " - " + simSet).c_str(),"l");
    leg->Draw();

    return;
}



