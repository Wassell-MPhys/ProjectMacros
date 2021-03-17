from xgboost import XGBClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

from root_pandas import read_root

import pickle
import pandas
import numpy

from two_sample_utilities import xgboost_variable_importance, xgboost_roc_curve
from two_sample_utilities import xgboost_overtraining_check


from two_sample_variables import var_list

#the signal input file
sig_file = '/run/media/davidwassell/David USB/Lb2pKmm_magUp2018/Lb_Tuple.root'
bkg_file = '/run/media/davidwassell/David USB/dataMagUp2016/Lb2pKmm_mgUp_2016.root' 

root_tree_bkg  = 'Lb_Tuple/DecayTree'
root_tree_sig = 'tree'

bkg_sample = read_root( bkg_file, root_tree_bkg, columns = var_list + [ 'Lb_M', 'mu1_PT', 'mu2_PT', 'Jpsi_MM', 'h1_PT', 'h2_PT' ] )
sig_sample = read_root( sig_file, root_tree_sig, columns = var_list + [ 'Lb_M', 'Lb_BKGCAT', 'mu1_PT', 'mu2_PT', 'Jpsi_MM', 'h1_PT', 'h2_PT' ] )

# bkg_sample = bkg_sample.query('Lb_M > 6000' and (('1e8 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 8e9') or ('11e9 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 12.5e9') or ('15e9 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 19e9')))
# sig_sample = sig_sample.query('Lb_BKGCAT < 60' and (('1e8 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 8e9') or ('11e9 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 12.5e9') or ('15e9 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 19e9')))

bkg_sample = bkg_sample.query('Lb_M > 6000' and (('0.1 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 8') or ('11 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 12.5') or ('15 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 19')))
sig_sample = sig_sample.query('Lb_BKGCAT < 60' and (('0.1 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 8') or ('11 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 12.5') or ('15 < 1e-6*Jpsi_MM*Jpsi_MM' and '1e-6*Jpsi_MM*Jpsi_MM < 19')))

bkg_sample['Average_Mu_PT'] = 0.5*( bkg_sample['mu1_PT'] + bkg_sample['mu2_PT'] )
sig_sample['Average_Mu_PT'] = 0.5*( sig_sample['mu1_PT'] + sig_sample['mu2_PT'] )
bkg_sample['Average_h_PT'] = 0.5*( bkg_sample['h1_PT'] + bkg_sample['h2_PT'] )
sig_sample['Average_h_PT'] = 0.5*( sig_sample['h1_PT'] + sig_sample['h2_PT'] )

# Create a 'Signal' column in each data frame,
# which has the value 0 for background and 1
# for signal
bkg_sample['Signal'] = 0
sig_sample['Signal'] = 1


# Drop columns that aren't needed
sig_sample = sig_sample.drop( columns = ['Lb_M', 'Lb_BKGCAT', 'mu1_PT', 'mu2_PT', 'Jpsi_MM', 'h1_PT', 'h2_PT' ] )[:200000] # Can remove :100000
bkg_sample = bkg_sample.drop( columns = ['Lb_M', 'mu1_PT', 'mu2_PT', 'Jpsi_MM', 'h1_PT', 'h2_PT' ] )[:200000] # Can remove :100000


# print how many events of each type we have
print('\nDatasets')
print('--------')
print('Sig. sample contains {0} candidates'.format(len(sig_sample)))
print('Bkg. sample contains {0} candidates'.format(len(bkg_sample)))


# Merge the total sig and bkg samples into one data frame
merged_sample = pandas.concat((sig_sample, bkg_sample))


# Split the data
X_train, X_test, y_train, y_test = train_test_split(merged_sample,
                                                    merged_sample['Signal'],
                                                    test_size=0.5,
                                                    random_state=101)


# print a slice of the data sample
print ('\nSlice of training data sample:')
print ('------------------------------')
print (X_train[:5])

X_train = X_train.drop( columns = ['Signal'] )
X_test  = X_test.drop( columns = ['Signal'] )

# The variables have very different scales, so to help the
# classifier, re-scale these to be more comparable.

# scaler  = StandardScaler()
# X_train = scaler.fit_transform(X_train)
# X_test  = scaler.transform(X_test)

# Save scaler so that this can be re-used when
# applying the BDT
# with open('scaler.pickle','wb') as f:
#     pickle.dump(scaler, f)

# fit model to the training data
bdt = XGBClassifier()
bdt.fit(X_train, y_train)

# save the classifier
#with open('xgboost.pickle', 'wb') as f:
#    pickle.dump(bdt, f)

bdt.save_model('xgboost.model')

# print variable importances
print('\nVariable importance')
print('--------------------' )
xgboost_variable_importance( bdt, var_list + ['Average_Mu_PT', 'Average_h_PT']  )
# xgboost_variable_importance( bdt, var_list + ['Average_h_PT']  )
# xgboost_variable_importance( bdt, var_list + ['Average_Mu_PT']  )

# draw a ROC curve
xgboost_roc_curve( bdt, X_test, y_test )
xgboost_overtraining_check(bdt, X_train, y_train, X_test, y_test)
