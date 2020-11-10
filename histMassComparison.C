#include <iostream>
#include "TH1D.h" 
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include <stdio.h>
#include <string.h>

using namespace std;

void histMassComparison() {
    // Data input assigned to variables
    string dataSet;
    string branchName;
    int bins;
    float xLower;
    float xUpper;
    int massMinimum; 
    cout << "Data Set? ";
    cin >> dataSet;
    cout << "Branch? ";
    cin >> branchName;
    cout << "Number of bins? ";
    cin >> bins;
    cout << "From? ";
    cin >> xLower;
    cout << "To? ";
    cin >> xUpper;
    cout << "Minimum Mass? ";
    cin >> massMinimum;

    // Custom file location string from input data
    string filePath = "/run/media/davidwassell/David USB/" + dataSet + "/Lb_Tuple.root";

    TFile* rootFile = TFile::Open(filePath.c_str());
    TTree* tree = (TTree*) rootFile->Get("tree");

    // Custom Canvas title string from input
    string canvasTitle = "Canvas: " + dataSet + " - " + branchName; 
    
    // Canvas made so multiple plots can be opened at once
    TCanvas* canvas = new TCanvas(canvasTitle.c_str(),canvasTitle.c_str()); 

    // 1st histogram for data made using custom input
    TH1D* myHist = new TH1D(branchName.c_str(),"",bins,xLower,xUpper);

    // Data drawn to histogram
    tree->Draw((branchName+">>"+branchName).c_str());
    myHist->SetLineColor( kBlue );
 
    // 2nd histogram for data with mass values above input
    TH1D* myHistCut = new TH1D("histCut","",bins,xLower,xUpper);
    // Data drawn to the same histogram
    tree->Draw((branchName+">>histCut").c_str(),"Lb_MM > 5800");
    myHistCut->SetLineColor( kRed );
    myHist->Draw();
    myHistCut->Draw("SAME");
    
   return;
}
    

