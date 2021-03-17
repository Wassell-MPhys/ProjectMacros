from root_pandas import read_root, to_root
from xgboost import XGBClassifier

# import pickle
import pandas
import sys

# from two_sample_utilities import get_scaler

from two_sample_variables import var_list

# Takes 2 input arguments, simulation data file and output file name

def print_usage():
    print( '\nUsage:' )
    print( '-----' )
    print( '\t python two_sample_apply.py {a_root_file}.root' )
    print( '\nCreate an output file containing BDT response\n' )
    return

print(sys.argv)

if ( 3 == len(sys.argv) ):
    input_file  = sys.argv[1]
    root_tree   = 'Lb_Tuple/DecayTree'
    # root_tree   = 'tree'
    output_file = sys.argv[2]

    # sample = read_root( input_file, root_tree, columns = var_list + [ 'mu1_PT', 'mu2_PT' ] )
    sample = read_root( input_file, root_tree, columns = var_list + [ 'mu1_PT', 'mu2_PT', 'h1_PT', 'h2_PT' ] )

    # Average muon PT
    sample['Average_Mu_PT'] = 0.5*( sample['mu1_PT'] + sample['mu2_PT'] )
    sample['Average_h_PT'] = 0.5*( sample['h1_PT'] + sample['h2_PT'] )

    sample = sample.drop( columns = [ 'mu1_PT', 'mu2_PT', 'h1_PT', 'h2_PT' ] )
    # Average h PT
    # sample['Average_h_PT'] = 0.5*( sample['h1_PT'] + sample['h2_PT'] )
    # sample = sample.drop( columns = [ 'h1_PT', 'h2_PT' ] )


    print( '\nDataset' )
    print( '--------' )
    print( 'Sample contains %i candidates' % len(sample) )

    # print a slice of the data sample
    print ('\nSlice of data sample:')
    print ('------------------------------')
    print (sample[:5])

    # scaler = get_scaler()

    # if ( scaler ):
    #     sample = scaler.transform( sample )

    #with open('xgboost.pickle', 'rb') as f:
    bdt = XGBClassifier()
    bdt.load_model('xgboost.model')
    #pickle.load(f)
    pred = bdt.predict_proba(sample)
    
    to_root( pandas.DataFrame({'MVA_B' : pred[:,0],
                               'MVA_S' : pred[:,1]} ),
             output_file, key = 'Pred' )
else:
    print_usage()
   
