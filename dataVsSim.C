#include <iostream>
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;


void dataVsSim() {
    // Setting plotting style
    gStyle->SetTitleFont(132, "X");
    gStyle->SetTitleFont(132, "Y");
    gStyle->SetLabelFont(132, "X");
    gStyle->SetLabelFont(132, "Y");
    gStyle->SetTitleSize(0.04, "X");
    gStyle->SetTitleSize(0.04, "Y");
    gStyle->SetLabelSize(0.04, "X");
    gStyle->SetLabelSize(0.04, "Y");
    gStyle->SetLegendFont(132);  
    // Data input assigned to variables
    string dataSet = "dataMagUp2018";
    string simSet = "Lb2pKmm_magUp2016";
    string dataFilePath = "/run/media/davidwassell/David USB/dataMagUp2018/Lb2pKmm_mgUp_2018.root";
    string simFilePath = "/run/media/davidwassell/David USB/Lb2pKmm_magUp2016/Lb_Tuple.root";
    string branchName = "Lb_PT";
    int bins = 100;
    float xLower = 0.0; 
    float xUpper = 25000.0;



    // Open data file path and create a tree
    TFile* rootDataFile = TFile::Open(dataFilePath.c_str());
    TTree* treeData = (TTree*) rootDataFile->Get("Lb_Tuple/DecayTree");

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
    // treeData->Draw((branchName + ">>dataHist").c_str(), "Lb_PT > 4500");
    treeData->Draw((branchName + ">>dataHist").c_str());
    dataHist->SetLineColor( kBlue );

    // 2nd histogram for simulation data
    TH1D* simHist = new TH1D("simHist","",bins,xLower,xUpper);

    // Simulation drawn to histogram
    // treeSim->Draw((branchName + ">>simHist").c_str(), "Lb_BKGCAT < 11");
    treeSim->Draw((branchName + ">>simHist").c_str());
    simHist->SetLineColor( kRed );

    // Both data sets drawn to ca
    
    // Setting axis labels
    dataHist->SetXTitle("#it{#Lambda}_{b}^{0} transverse momentum [MeV/#it{c}^{2}]");
    dataHist->SetYTitle("Candidates / [25 MeV/#it{c}^{2}]");
    dataHist->SetStats(0);
    dataHist->DrawNormalized();
    simHist->DrawNormalized("SAME");
    

    // Setting Legend
    TLegend* leg = new TLegend();
    leg->AddEntry("dataHist","Real Data","l");
    leg->AddEntry("simHist","MC Data","l");
    leg->Draw();

    return;
}



