#include <iostream>
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegend.h"
#include "TStyle.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

void LbMM() {
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
    int bins = 100;
    float xLower = 5301.0;
    float xUpper = 6001.0;

    // Open data file path and create a tree
    TFile* rootDataFile = TFile::Open("/run/media/davidwassell/David USB/dataMagDown2016/Lb2pKmm_mgDn_2016.root");
    TTree* tree = (TTree*) rootDataFile->Get("Lb_Tuple/DecayTree");
    tree->AddFriend("Pred", "/run/media/davidwassell/David USB/Macros/Py_Macros/David MVA/DMD2016/apply_output_DMD2016.root");

    // Custom Canvas title string from input
    string canvasTitle = "Canvas: Lb_MM Comparison"; 
    
    // Canvas made so multiple plots can be opened at once
    TCanvas* canvas = new TCanvas(canvasTitle.c_str(),canvasTitle.c_str()); 

    // 1st histogram for raw data - BLUE
    TH1D* dataHist = new TH1D("dataHist","dataHist",bins,xLower,xUpper);
    tree->Draw("Lb_MM>>dataHist");
    dataHist->SetLineColor( kBlue );
    dataHist->SetLineWidth( 4 );
    dataHist->SetStats(0);
    dataHist->SetMaximum(30000.0);
    dataHist->SetMinimum(0.0);

    // 2nd histogram with Visual Analysis Constraints - GREEN
    TH1D* dataHistCutByEye = new TH1D("dataHistCutByEye","dataHistCutByEye",bins,xLower,xUpper);
    tree->Draw("Lb_MM>>dataHistCutByEye", "Lb_ENDVERTEX_CHI2<15 && Lb_PT>4500 && Lb_IPCHI2_OWNPV<4 && h1_PT>750 && h2_PT>750 && mu1_PT>750 && mu2_PT>750 && Lb_FDCHI2_OWNPV>500");
    // tree->Draw("Lb_MM>>dataHistCut", "MVA_S > 0.96");
    dataHistCutByEye->SetLineColor( kGreen+1 );
    dataHistCutByEye->SetLineWidth( 4 );
    dataHistCutByEye->SetStats(0);
    
    // 2nd histogram with BDT Constraint - RED
    TH1D* dataHistCutByMacro = new TH1D("dataHistCutByMacro","dataHistCutByMacro",bins,xLower,xUpper);
    // tree->Draw("Lb_MM>>dataHistCut", "Lb_ENDVERTEX_CHI2<15 && Lb_PT>4500 && Lb_IPCHI2_OWNPV<4 && h1_PT>750 && h2_PT>750 && mu1_PT>750 && mu2_PT>750 && Lb_FDCHI2_OWNPV>500");
    tree->Draw("Lb_MM>>dataHistCutByMacro", "MVA_S > 0.95");
    dataHistCutByMacro->SetLineColor( kRed );
    dataHistCutByMacro->SetLineWidth( 4 );
    dataHistCutByMacro->SetStats(0);
    
    // Drawing Plots & setting axis labels
    dataHist->Draw("");
    dataHist->SetTitle(" ");
    dataHist->SetXTitle("#it{m}(#it{p}#it{K}^{#minus}#it{J}/#it{#Psi}) [MeV/#it{c}^{2}]");
    dataHist->SetYTitle("Candidates / [7 MeV/#it{c}^{2}]");
    dataHistCutByEye->Draw("SAME");
    dataHistCutByMacro->Draw("SAME");


    // Creating Legend
    TLegend* leg = new TLegend();
    leg->AddEntry("dataHist","Unconstrained","l");
    leg->AddEntry("dataHistCutByEye","Visual Analysis Constraints","l");
    leg->AddEntry("dataHistCutByMacro","BDT Constraints","l");
    leg->Draw();

    return;
}



