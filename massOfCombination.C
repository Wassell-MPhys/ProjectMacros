#include <iostream>
#include "TH1D.h" 
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

void massOfCombination() {

    // Data input assigned to variables
    string dataSet;
    string branch1;
    string branch2;
    int bins;
    float xLower;
    float xUpper;
    cout << "Data Set? ";
    cin >> dataSet;
    cout << "First branch? ";
    cin >> branch1;
    cout << "Second branch? ";
    cin >> branch2;
    cout << "Number of bins? ";
    cin >> bins;
    cout << "From? ";
    cin >> xLower;
    cout << "To? ";
    cin >> xUpper;

    // Custom file location string from input data
    string filePath = "/run/media/davidwassell/David USB/" + dataSet + "/Lb_Tuple.root";

    // TFile* rootFile = TFile::Open(filePath.c_str());
    TFile* rootFile = TFile::Open(filePath.c_str());
    TTree* tree = (TTree*) rootFile->Get("tree");

    // Enabling energy and momentum branches
    tree->SetBranchStatus("*",0);
    // Input 1 - Use branch1 = mu1 for testing
    tree->SetBranchStatus((branch1+"_PE").c_str(),1);
    tree->SetBranchStatus((branch1+"_PX").c_str(),1);
    tree->SetBranchStatus((branch1+"_PY").c_str(),1);
    tree->SetBranchStatus((branch1+"_PZ").c_str(),1);
    // Input 2 - use branch2 = h2 for testing
    tree->SetBranchStatus((branch2+"_PE").c_str(),1);
    tree->SetBranchStatus((branch2+"_PX").c_str(),1);
    tree->SetBranchStatus((branch2+"_PY").c_str(),1);
    tree->SetBranchStatus((branch2+"_PZ").c_str(),1);

    double branch1PE, branch1PX, branch1PY, branch1PZ, branch2PE, branch2PX, branch2PY, branch2PZ;
    // Input 1
    tree->SetBranchAddress((branch1+"_PE").c_str(),&branch1PE);
    tree->SetBranchAddress((branch1+"_PX").c_str(),&branch1PX);
    tree->SetBranchAddress((branch1+"_PY").c_str(),&branch1PY);
    tree->SetBranchAddress((branch1+"_PZ").c_str(),&branch1PZ);  
    // Input 2
    tree->SetBranchAddress((branch2+"_PE").c_str(),&branch2PE);
    tree->SetBranchAddress((branch2+"_PX").c_str(),&branch2PX);
    tree->SetBranchAddress((branch2+"_PY").c_str(),&branch2PY);
    tree->SetBranchAddress((branch2+"_PZ").c_str(),&branch2PZ);  

    // Custom histogram title
    string histTitle = "Mass Combination Histogram of " + branch1 + " and " + branch2; 
    // Initialising histograms - for testing bins = 200, xLower = 0.0, xUpper = 6000
    TH1D* massCombinedHist = new TH1D(histTitle.c_str(),"",bins,xLower,xUpper);
    // Error Bars
    // massCombinedHist->Sumw2(); 

    for ( Long64_t i = 0; i < tree->GetEntries(); i++ ){
        tree->GetEntry( i );
        double momentumCombined = sqrt(pow((branch1PX + branch2PX), 2) + pow((branch1PY + branch2PY), 2) + pow((branch1PZ + branch2PZ), 2));
        double energyCombined = branch1PE + branch2PE;
        double massCombined = sqrt(pow(energyCombined, 2) - pow(momentumCombined, 2));
        massCombinedHist->Fill(massCombined);
    }
  
    TCanvas* massCombinedCanvas = new TCanvas(histTitle.c_str(),histTitle.c_str());
    massCombinedHist->Draw();
    massCombinedHist->SetYTitle("Entries");
    massCombinedHist->SetXTitle("Mass");
  return;
}

