#include "TFile.h" 
#include "TTree.h"
#include "TH1D.h"
#include "TLorentzVector.h" 
#include "TCanvas.h"

#include "particleFromTree.hpp" 

#include <iostream>

void massCombinations( const std::string filename = "/run/media/davidwassell/David USB/dataMagUp2016/Lb_Tuple.root", const std::string outputfile = "mass.root" ){ 

  TFile* root_file = TFile::Open( filename.c_str() );
  TTree* root_tree = (TTree*) root_file->Get("tree");
  
  root_tree->SetBranchStatus("*",0);

  Particle<Double_t> mu1( "mu1", root_tree );
  Particle<Double_t> mu2( "mu2", root_tree );
  Particle<Double_t> h1 ( "h1" , root_tree );
  Particle<Double_t> h2 ( "h2" , root_tree );

  const double kaon_mass = 493.677;
  const double muon_mass = 105.658;
  const double pion_mass = 139.570;
  
  TFile* output_file = new TFile(outputfile.c_str(),"RECREATE");
  TTree* output_tree = new TTree("Masses","Masses");
    
  Double_t mPMu1, mPMu2, mKMu1, mKMu2; 

  output_tree->Branch("Mass_pmu1", &mPMu1, "Mass_pmu1/D"); 
  output_tree->Branch("Mass_pmu2", &mPMu2, "Mass_pmu2/D"); 
  output_tree->Branch("Mass_Kmu1", &mKMu1, "Mass_Kmu1/D"); 
  output_tree->Branch("Mass_Kmu2", &mKMu2, "Mass_Kmu2/D"); 

  Double_t mPKMu1, mPKMu2;
  output_tree->Branch("Mass_pKmu1", &mPKMu1, "Mass_pKmu1/D"); 
  output_tree->Branch("Mass_pKmu2", &mPKMu2, "Mass_pKmu2/D");
  
  Double_t mPKMuMu; 
  output_tree->Branch("Mass_pKmumu", &mPKMuMu, "Mass_pKmumu/D"); 

  Double_t mKK_PtoK, mKKMuMu_PtoK; 
  output_tree->Branch("Mass_KK_p_to_K", &mKK_PtoK, "Mass_KK_p_to_K/D"); 
  output_tree->Branch("Mass_KKmumu_p_to_K", &mKKMuMu_PtoK, "Mass_KKmumu_p_to_K/D"); 

  Double_t mPPi_KtoPi, mPPiMuMu_KtoPi;
  output_tree->Branch("Mass_ppi_K_to_pi", &mPPi_KtoPi, "Mass_ppi_K_to_pi/D"); 
  output_tree->Branch("Mass_ppimumu_K_to_pi", &mPPiMuMu_KtoPi, "Mass_ppimumu_K_to_pi/D"); 
  
  std::cout 
    << root_tree->GetName() << ", entries = " 
    << root_tree->GetEntries() << std::endl;

  for ( Long64_t i = 0; i < root_tree->GetEntries(); i++ ){ 
    root_tree->GetEntry(i);
    
    TLorentzVector pp1  = h1.getVec(); 
    TLorentzVector pK2  = h2.getVec();
    TLorentzVector pmu1 = mu1.getVec(); 
    TLorentzVector pmu2 = mu2.getVec();
    
    // 2-body cross-combinations
    mPMu1 = ( pp1 + pmu1 ).M();
    mPMu2 = ( pp1 + pmu2 ).M();
    mKMu1 = ( pK2 + pmu1 ).M();
    mKMu2 = ( pK2 + pmu2 ).M();

    // 3-body cross-combinations
    mPKMu1 = ( pp1 + pK2 + pmu1 ).M();
    mPKMu2 = ( pp1 + pK2 + pmu2 ).M();

    // 4-body combination
    mPKMuMu = ( pp1 + pK2 + pmu1 + pmu2 ).M(); 

    // Swap mass hypothesis on h1/h2
    TLorentzVector pK1  = h1.getHypothesis( kaon_mass );
    TLorentzVector ppi2 = h2.getHypothesis( pion_mass );

    mKK_PtoK     = ( pK1 + pK2 ).M();
    mKKMuMu_PtoK = ( pK1 + pK2 + pmu1 + pmu2 ).M(); 

    mPPi_KtoPi     = ( pp1 + ppi2 ).M();
    mPPiMuMu_KtoPi = ( pp1 + ppi2 + pmu1 + pmu2 ).M();
    
    output_tree->Fill();
  }

  std::cout 
    << output_tree->GetName() << ", entries = " 
    << output_tree->GetEntries() << std::endl;

  output_file->cd();
  output_tree->Write();
  output_file->Close();
  
  return ; 
}
