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
    /*
    string dataSet;
    string branchName1;
    string branchName2;
    int bins;
    float xLower;
    float xUpper;
    cout << "Data Set? ";
    cin >> dataSet;
    cout << "First branch? ";
    cin >> branchName1;
    cout << "Second branch? ";
    cin >> branchName2;
    cout << "Number of bins? ";
    cin >> bins;
    cout << "From? ";
    cin >> xLower;
    cout << "To? ";
    cin >> xUpper;
    */

    // Custom file location string from input data
    // string filePath = "/run/media/davidwassell/David USB/" + dataSet + "/Lb_Tuple.root";

    // TFile* rootFile = TFile::Open(filePath.c_str());
    TFile* rootFile = TFile::Open("/run/media/davidwassell/David USB/dataMagUp2016/Lb_Tuple.root");
    TTree* tree = (TTree*) rootFile->Get("tree");

    // Enabling energy and momentum branches
    tree->SetBranchStatus("*",0);
    // Input 1
    tree->SetBranchStatus("mu1_PE",1);
    tree->SetBranchStatus("mu1_PX",1);
    tree->SetBranchStatus("mu1_PY",1);
    tree->SetBranchStatus("mu1_PZ",1);
    // Input 2
    tree->SetBranchStatus("h2_PE",1);
    tree->SetBranchStatus("h2_PX",1);
    tree->SetBranchStatus("h2_PY",1);
    tree->SetBranchStatus("h2_PZ",1);

    double input1PE, input1PX, input1PY, input1PZ, input2PE, input2PX, input2PY, input2PZ;
    // Input 1
    tree->SetBranchAddress("mu1_PE",&input1PE);
    tree->SetBranchAddress("mu1_PX",&input1PX);
    tree->SetBranchAddress("mu1_PY",&input1PY);
    tree->SetBranchAddress("mu1_PZ",&input1PZ);  
    // Input 2
    tree->SetBranchAddress("h2_PE",&input2PE);
    tree->SetBranchAddress("h2_PX",&input2PX);
    tree->SetBranchAddress("h2_PY",&input2PY);
    tree->SetBranchAddress("h2_PZ",&input2PZ);

    // Initialising histograms
    TH1D* massCombinedHist = new TH1D("massCombinedHist","",200,0.,6000);
    // Error Bars
    // massCombinedHist->Sumw2(); 

    for ( Long64_t i = 0; i < tree->GetEntries(); i++ ){
        tree->GetEntry( i );
        double momentumCombined = sqrt(pow((input1PX + input2PX), 2) + pow((input1PY + input2PY), 2) + pow((input1PZ + input2PZ), 2));
        double energyCombined = input1PE + input2PE;
        double massCombined = sqrt(pow(energyCombined, 2) - pow(momentumCombined, 2));
        massCombinedHist->Fill(massCombined);
    }
  
    TCanvas* massCombinedCanvas = new TCanvas("massCombinedCanvas","massCombinedCanvas");
    massCombinedHist->Draw();
    massCombinedHist->SetYTitle("Entries");
    massCombinedHist->SetXTitle("Mass");
  return;


}