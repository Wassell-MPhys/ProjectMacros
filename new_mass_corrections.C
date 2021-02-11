#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TCanvas.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

void new_mass_corrections() {

    TFile* rootDataFile = TFile::Open("/run/media/davidwassell/David USB/dataMagDown2016/Lb2pKmm_mgDn_2016.root");
    TTree* tree = (TTree*) rootDataFile->Get("Lb_Tuple/DecayTree");
    tree->AddFriend("Masses","/run/media/davidwassell/David USB/dataMagDown2016/Lb2pKmm_mgDn_2016_masses.root");
    tree->AddFriend("Pred","/run/media/davidwassell/David USB/Macros/Py_Macros/David MVA/DMD2016/apply_output_DMD2016.root");
    
    // Canvas made for Lb_M
    TCanvas* canvas_Lb_M = new TCanvas("Lb_M","Lb_M"); 
    
    // histogram for raw data - BLUE
    TH1D* dataHist = new TH1D("dataHist","",200,5000,7000);
    tree->Draw("Lb_MM>>dataHist");
    dataHist->SetLineColor( kBlue );
    dataHist->SetLineWidth( 3 );
    dataHist->SetStats(0);

    // histogram with MVA constraint - RED
    TH1D* dataHistCutByMacro = new TH1D("dataHistCutByMacro","",200,5000,7000);
    tree->Draw("Lb_MM>>dataHistCutByMacro", "MVA_S > 0.95");
    // tree->Draw("Lb_MM>>dataHistCutByMacro", "h1_ProbNNp > 0.5 && h2_ProbNNk > 0.5 && h2_ProbNNpi < 0.2");
    dataHistCutByMacro->SetLineColor( kRed );
    dataHistCutByMacro->SetLineWidth( 3 );

    dataHist->Draw();
    dataHist->SetTitle("Lb_M");
    dataHist->SetXTitle("LbMM (MeV/c^2)");
    dataHist->SetYTitle("Counts");
    dataHistCutByMacro->Draw("SAME");

    // Canvas made for mass combination
    TCanvas* canvas_mass_combinations = new TCanvas("Mass_Combination","Mass_Combination");

    // Raw mass combination data histogram
    TH1D* massHist = new TH1D("massHist","",200,0,7000);
    tree->Draw("Mass_ppimumu_K_to_pi>>massHist");
    massHist->SetLineColor( kBlue );
    massHist->SetLineWidth( 3 );
    massHist->SetStats(0); 

    // histogram with MVA constraint - RED
    TH1D* massHistConstraint = new TH1D("massHistConstraint","",200,0,7000);
    tree->Draw("Mass_ppimumu_K_to_pi>>massHistConstraint", "MVA_S>0.95");
    // tree->Draw("Mass_Kpimumu_p_to_K_and_K_to_pi>>massHistConstraint", "h2_ProbNNp > 0.5");
    massHistConstraint->SetLineColor( kRed );
    massHistConstraint->SetLineWidth( 3 );

    massHist->Draw();
    massHist->SetTitle("Mass Combination");
    massHist->SetXTitle("Mass");
    massHist->SetYTitle("Counts");
    massHistConstraint->Draw("SAME");

    

}