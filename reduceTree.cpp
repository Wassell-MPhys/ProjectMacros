#include "TFile.h"
#include "TTree.h"
#include "TEventList.h"
#include <string>
#include <iostream> 

void reduceTree( const std::string input_file_name,
		 const std::string input_tree_name, 
		 const std::string mass_file_name, 
		 const std::string mass_tree_name,
     const std::string BDT_file_name, 
		 const std::string BDT_tree_name,
		 const std::string output_file_name,
		 const std::string output_tree_name = "tree" ,
		 Int_t Year = 2016,
     Int_t Polarity = 1,
     const std::string selection = "" ){ 

  // The set of branches you want to appear in the new file
  std::vector< std::string > branches = { 
    "Lb_M", "Lres_MM", "Lb_ID", "h1_ProbNNp", "h1_ProbNNmu", "h1_ProbNNk", "h1_ProbNNpi", "h2_ProbNNp", "h2_ProbNNmu", "h2_ProbNNk", "h2_ProbNNpi", "mu1_ProbNNmu", "mu2_ProbNNmu", "Jpsi_MM"
  }; 

  std::vector< std::string > mass_branches = { 
    "Mass_KKmumu_p_to_K", "Mass_Kpimumu_p_to_K_and_K_to_pi", "Mass_Kpimumu_p_to_pi", "Mass_ppimumu_K_to_pi" 
  };
  
  std::cout 
    << " Reducing input file:" << "\n"
    << " ------------------- " << "\n" 
    << " Input file  = " << input_file_name  << "\n" 
    << " Input tree  = " << input_tree_name  << "\n" 
    << " Output file = " << output_file_name << "\n" 
    << " Output tree = " << output_tree_name << "\n"
    << " Selection   = " << selection << std::endl;

  TFile* input_file = TFile::Open( input_file_name.c_str() );
  TTree* input_tree = (TTree*) input_file->Get( input_tree_name.c_str() );

  TFile* mass_file  = TFile::Open( mass_file_name.c_str() );
  TTree* mass_tree  = (TTree*) mass_file ->Get( mass_tree_name.c_str()  );

  TFile* BDT_file  = TFile::Open( BDT_file_name.c_str() );
  TTree* BDT_tree  = (TTree*) BDT_file ->Get( BDT_tree_name.c_str()  );

  // Can use AddFriend here to pull in e.g.
  // masses or the BDT output so that they 
  // can also be copied
  input_tree->AddFriend( mass_tree );
  input_tree->AddFriend( BDT_tree );
  
  TEventList evts("evts","evts");
  input_tree->Draw(">>evts",selection.c_str());
  
  input_tree->SetBranchStatus("*",0);

  for ( auto & branch: branches ){ 
    input_tree->SetBranchStatus( branch.c_str(), 1 );
  }
  
  TFile* output_file = new TFile( output_file_name.c_str(), "RECREATE" );
  TTree* output_tree = input_tree->CloneTree(0);
  
  // Change the tree name
  output_tree->SetName( output_tree_name.c_str() );
  
  const unsigned int nfriends = mass_branches.size();

  std::vector< double > values( nfriends );
  
  for ( unsigned int i = 0; i < nfriends; i++ ){ 
    output_tree->Branch( mass_branches[i].c_str(), &values[i], 
			 (mass_branches[i] + "/D").c_str() );

    input_tree ->SetBranchStatus ( mass_branches[i].c_str(), 1 );
    input_tree ->SetBranchAddress( mass_branches[i].c_str(), &values[i] );
  }

  input_tree ->SetBranchStatus ( "MVA_S", 1);

  Double_t dimuon_mass, qsquare;
  Float_t BDT;
  
  BDT_tree ->SetBranchAddress("MVA_S",&BDT);
  output_tree->Branch("BDT",&BDT,"BDT/F");

  output_tree->Branch("Year",&Year,"Year/I");
  output_tree->Branch("Polarity",&Polarity,"Polarity/I");
  
  input_tree ->SetBranchStatus ("Jpsi_M",1);
  input_tree ->SetBranchAddress("Jpsi_M",&dimuon_mass); 
  
  output_tree->Branch("qsquare",&qsquare,"qsquare/D");
  

  for ( Int_t i = 0; i < evts.GetN(); i++ ){ 
    input_tree->GetEntry( evts.GetEntry( i ) );
    
    qsquare = 1e-6*dimuon_mass*dimuon_mass;
    
    output_tree->Fill();
  }
  
  output_file->Close();
  
  return ; 
}