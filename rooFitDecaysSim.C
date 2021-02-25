#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "RooRealVar.h"
#include "RooAbsReal.h"
#include "RooExponential.h"
#include "RooCBShape.h"
#include "RooGaussian.h"
#include "RooArgusBG.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooArgList.h"
using namespace RooFit;

void rooFitDecaysSimulation(){
    
    // TFile* dataFile = TFile::Open("/run/media/davidwassell/David USB/Reduced Data/merged.root");
    TFile* dataFile = TFile::Open("/run/media/davidwassell/David USB/Lb2JpsipK_magUp2016/Lb_Tuple.root");
    TTree*  tree = (TTree*) dataFile->Get("tree");
    tree->AddFriend("Pred","/run/media/davidwassell/David USB/Macros/Py_Macros/David MVA/DMU2016/apply_output_DMU2016.root");
    tree->AddFriend("Masses","/run/media/davidwassell/David USB/Lb2JpsipK_magUp2016/Lb2JpsipK_sim_mgUp_2016_masses.root");

    gROOT->cd();
    
    //***********************************
    // p pi mu mu decay plot - Jpsi decay
    //***********************************
    // Monte Carlo constraints
    // TTree* tree_copy = tree->CopyTree("BDT > 0.95 && h1_ProbNNp > 0.2 && h1_ProbNNk < 0.05 && h1_ProbNNpi < 0.05 && h2_ProbNNpi > 0.2 && h2_ProbNNk < 0.05 && h2_ProbNNp < 0.05 && mu1_ProbNNmu > 0.2 && mu2_ProbNNmu > 0.2 && Jpsi_MM > 3000 && Jpsi_MM < 3200 && (Mass_KKmumu_p_to_K < 5325 || Mass_KKmumu_p_to_K > 5405 || h1_ProbNNk < 0.1) && (Mass_Kpimumu_p_to_pi < 5240 || Mass_Kpimumu_p_to_pi > 5320 || h2_ProbNNpi < 0.1)"); 
    // Extra Cosntraints
    // TTree* tree_copy = tree->CopyTree("BDT > 0.95 && h1_ProbNNp > 0.2 && h1_ProbNNk < 0.05 && h1_ProbNNpi < 0.05 && h2_ProbNNpi > 0.2 && h2_ProbNNk < 0.05 && h2_ProbNNp < 0.05 && mu1_ProbNNmu > 0.2 && mu2_ProbNNmu > 0.2 && Jpsi_MM > 3000 && Jpsi_MM < 3200 && (Mass_KKmumu_p_to_K < 5325 || Mass_KKmumu_p_to_K > 5405 || h1_ProbNNk < 0.1) && (Mass_Kpimumu_p_to_pi < 5240 || Mass_Kpimumu_p_to_pi > 5320 || h2_ProbNNpi < 0.1)"); 
    // Normal Cosntraints
    // TTree* tree_copy = tree->CopyTree("BDT > 0.95 && h1_ProbNNp > 0.2 && h1_ProbNNk < 0.05 && h1_ProbNNpi < 0.05 && h2_ProbNNpi > 0.2 && h2_ProbNNk < 0.05 && h2_ProbNNp < 0.05 && mu1_ProbNNmu > 0.2 && mu2_ProbNNmu > 0.2 && Jpsi_MM > 3000 && Jpsi_MM < 3200"); 

    //***********************************************
    // p pi mu mu decay plot - Rare Decay (Too Small)
    //***********************************************
    // TTree* tree_copy = tree->CopyTree("BDT > 0.95 && h1_ProbNNp > 0.2 && h1_ProbNNk < 0.05 && h1_ProbNNpi < 0.05 && h2_ProbNNpi > 0.2 && h2_ProbNNk < 0.05 
    // && h2_ProbNNp < 0.05 && mu1_ProbNNmu > 0.2 && mu2_ProbNNmu > 0.2 && ((0.1 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 8) 
    // || (11 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 12.5) || (15 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 19)) && (Lb_M < 5590 || Lb_M > 5650 || h2_ProbNNk < 0.1)");
    
    //***********************************
    // p K mu mu decay plot (Lb_M) - Rare 
    //***********************************
    
    // TTree* tree_copy = tree->CopyTree("Lb_BKGCAT < 60 && MVA_S > 0.95 && h1_ProbNNp * (1 - h1_ProbNNk) * (1 - h1_ProbNNpi) > 0.2 && h2_ProbNNk > 0.5 && ((0.1 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 8) || (11 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 12.5) || (15 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 19)) && (Mass_KKmumu_p_to_K < 5325 || Mass_KKmumu_p_to_K > 5405 || h1_ProbNNk < 0.1) && (Mass_Kpimumu_p_to_pi < 5240 || Mass_Kpimumu_p_to_pi > 5320 || h2_ProbNNpi < 0.1)");
    // TTree* tree_copy = tree->CopyTree("BDT > 0.95 && h1_ProbNNp * (1 - h1_ProbNNk) * (1 - h1_ProbNNpi) > 0.2 && h2_ProbNNk > 0.5 && ((0.1 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 8) || (11 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 12.5) || (15 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 19)) && (Mass_KKmumu_p_to_K < 5325 || Mass_KKmumu_p_to_K > 5405 || h1_ProbNNk < 0.1) && (Mass_Kpimumu_p_to_pi < 5240 || Mass_Kpimumu_p_to_pi > 5320 || h2_ProbNNpi < 0.1)");
    // TTree* tree_copy = tree->CopyTree("BDT > 0.95 && h1_ProbNNp * (1 - h1_ProbNNk) * (1 - h1_ProbNNpi) > 0.2 && h2_ProbNNk > 0.5 && 
    // ((0.1 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 8) || (11 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 12.5) || (15 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 19))");

    //***********************************
    // p K mu mu decay plot (Lb_M) - Jpsi
    //***********************************
    // Extra Constraints
    TTree* tree_copy = tree->CopyTree("Lb_BKGCAT < 60 && MVA_S > 0.95 && h1_ProbNNp * (1 - h1_ProbNNk) * (1 - h1_ProbNNpi) > 0.2 && h2_ProbNNk > 0.5 && Jpsi_MM > 3000 && Jpsi_MM < 3200 && (Mass_KKmumu_p_to_K < 5325 || Mass_KKmumu_p_to_K > 5405 || h1_ProbNNk < 0.1) && (Mass_Kpimumu_p_to_pi < 5240 || Mass_Kpimumu_p_to_pi > 5320 || h2_ProbNNpi < 0.1)");
    // TTree* tree_copy = tree->CopyTree("BDT > 0.95 && h1_ProbNNp * (1 - h1_ProbNNk) * (1 - h1_ProbNNpi) > 0.2 && h2_ProbNNk > 0.5 && Jpsi_MM > 3000 && Jpsi_MM < 3200 && (Mass_KKmumu_p_to_K < 5325 || Mass_KKmumu_p_to_K > 5405 || h1_ProbNNk < 0.1) && (Mass_Kpimumu_p_to_pi < 5240 || Mass_Kpimumu_p_to_pi > 5320 || h2_ProbNNpi < 0.1)");
    // Normal Constraints
    // TTree* tree_copy = tree->CopyTree("BDT > 0.95 && h1_ProbNNp * (1 - h1_ProbNNk) * (1 - h1_ProbNNpi) > 0.2 && h2_ProbNNk > 0.5 && Jpsi_MM > 3000 && Jpsi_MM < 3200");

    // Range
    // RooRealVar x("Mass_ppimumu_K_to_pi","Mass_ppimumu_K_to_pi", 5400, 6000);
    RooRealVar x("Lb_M","Mass", 5300, 6000);
    // Data
    RooDataSet data("data","dataset with x", tree_copy,x);

    // Mean, Value, lower bound, upper bound
    RooRealVar m("mean","mean",5620,5500,5740);
    // Standard Deviation, value, lower bound, upper bound
    RooRealVar s("sigma","sigma",10,0,100);
    // RooRealVar s("sigma","sigma",1.66949e+01);
    // Gaussian takes x, m and s
    RooGaussian gauss("gauss_fit","gauss_fit",x,m,s);
    // Slope for background
    RooRealVar p("slope","slope",0,-0.1,0.1);
    RooExponential EXP_BKG("expo_bkg","expo_bkg",x,p);
    
    /*
    RooAbsReal *CB_m(5620,,Range(5500,5740));
    RooAbsReal *CB_m0("CB_m0","CB_m0",0);
    RooAbsReal *CB_a("CB_a","CB_a",1);
    RooAbsReal *CB_n("CB_n","CB_n",1);
    RooAbsReal *CB_s("CB_s","CB_s",1);
    */

    // Currently BROKEN
    RooRealVar n("n","n",1.,0.,10.);
    RooRealVar a("alpha","alpha",1.,0.,10.);
    RooCBShape CB("CB","CB",x,m,s,a,n);
    
    
    RooRealVar ngauss("ngauss","ngauss",1e4,0.,1e7);
    RooRealVar n_EXP_BKG("nBKG","nBKG",1e4,0.,1e7);
    RooRealVar n_CB("nCB","nCB",1e4,0.,1e7);
    RooAddPdf sum("sum","sum",RooArgList(CB,EXP_BKG),RooArgList(n_CB,n_EXP_BKG));
    sum.fitTo(data);
    
    RooPlot* xframe = x.frame() ;
    // data.plotOn(frame,Binning(200));
    data.plotOn(xframe);
    sum.plotOn(xframe);
    sum.plotOn(xframe,RooFit::Components(EXP_BKG),RooFit::LineColor(kRed));
    data.plotOn(xframe);
    xframe->Draw();

    return;
}