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

void LbMM() {
    // Data input assigned to variables
    string dataSet, simSet, branchName;
    int bins;
    float xLower, xUpper;
    cout << "Data Set? ";
    cin >> dataSet;
    cout << "Number of bins? ";
    cin >> bins;
    cout << "From? ";
    cin >> xLower;
    cout << "To? ";
    cin >> xUpper;
    
    // Custom data file location string from input data
    string dataFilePath = "/run/media/davidwassell/David USB/" + dataSet + "/Lb_Tuple.root";

    // Open data file path and create a tree
    TFile* rootDataFile = TFile::Open(dataFilePath.c_str());
    TTree* tree = (TTree*) rootDataFile->Get("tree");
    tree->AddFriend("Pred", "/run/media/davidwassell/David USB/Macros/Py_Macros/David MVA/Lb_Tuple-mva_sig.root");

    // Custom Canvas title string from input
    string canvasTitle = "Canvas: Lb_MM Comparison"; 
    
    // Canvas made so multiple plots can be opened at once
    TCanvas* canvas = new TCanvas(canvasTitle.c_str(),canvasTitle.c_str()); 

    // 1st histogram for raw data - BLUE
    TH1D* dataHist = new TH1D("dataHist","",bins,xLower,xUpper);
    tree->Draw("Lb_MM>>dataHist");
    dataHist->SetLineColor( kBlue );

    // 2nd histogram with Lb_ENDBERTEX_CHI2 < 10 - RED
    TH1D* dataHistCut = new TH1D("dataHistCut","",bins,xLower,xUpper);
    // tree->Draw("Lb_MM>>dataHistCut", "Lb_ENDVERTEX_CHI2<15 && Lb_PT>4500 && Lb_IPCHI2_OWNPV<4 && h1_PT>750 && h2_PT>750 && mu1_PT>750 && mu2_PT>750 && Lb_FDCHI2_OWNPV>500");
    tree->Draw("Lb_MM>>dataHistCut", "MVA_S > 0.96");
    dataHistCut->SetLineColor( kRed );
    
    dataHist->Draw();
    dataHistCut->Draw("SAME");
    // dataHistCut2->Draw("SAME");

    return;
}



