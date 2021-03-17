#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TStyle.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

void report_mass_combinations() {

    // Plot styling
    gStyle->SetTitleFont(132, "X");
    gStyle->SetTitleFont(132, "Y");
    gStyle->SetLabelFont(132, "X");
    gStyle->SetLabelFont(132, "Y");
    gStyle->SetTitleSize(0.06, "X");
    gStyle->SetTitleSize(0.06, "Y");
    gStyle->SetLabelSize(0.06, "X");
    gStyle->SetLabelSize(0.06, "Y");

    // Data file
    TFile* rootDataFile = TFile::Open("/run/media/davidwassell/David USB/Reduced Data/merged.root");
    TTree* tree = (TTree*) rootDataFile->Get("tree");

    // Canvas 
    TCanvas* canvas = new TCanvas("Canvas","Canvas"); 
    
    // histogram for raw data - BLUE
    TH1D* dataHist = new TH1D("dataHist","",400,3000,7000);
    tree->Draw("Mass_ppimumu_K_to_pi>>dataHist");
    dataHist->SetLineColor( kBlue );
    dataHist->SetLineWidth( 5 );
    dataHist->SetStats(0);
    

    // histogram with constraints - RED
    // TH1D* dataHistCutByMacro = new TH1D("dataHistCutByMacro","",200,5000,7000);
    // tree->Draw("Mass_ppimumu_K_to_pi>>dataHistCutByMacro", "h1_ProbNNp > 0.2 && h1_ProbNNk < 0.05 && h1_ProbNNpi < 0.05 && h2_ProbNNpi > 0.2 && h2_ProbNNk < 0.05 && h2_ProbNNp < 0.05 && mu1_ProbNNmu > 0.2 && mu2_ProbNNmu > 0.2 && Jpsi_MM > 3000 && Jpsi_MM < 3200 && (Mass_KKmumu_p_to_K < 5325 || Mass_KKmumu_p_to_K > 5405 || h1_ProbNNk < 0.1) && (Mass_Kpimumu_p_to_pi < 5240 || Mass_Kpimumu_p_to_pi > 5320 || h2_ProbNNpi < 0.1)");
    // dataHistCutByMacro->SetLineColor( kRed );
    // dataHistCutByMacro->SetLineWidth( 3 );

    // Plot details
    dataHist->Draw();
    dataHist->SetMinimum(0.1);
    dataHist->SetTitle("");
    dataHist->SetXTitle("#it{m}(#it{K}^{+}#it{#pi}^{#minus}#it{#mu}^{+}#it{#mu}^{#minus}) [MeV/#it{c}^{2}]");
    dataHist->SetYTitle("Candidates / [10 MeV/#it{c}^{2}]");
    // dataHistCutByMacro->Draw("SAME");

}

