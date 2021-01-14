from root_pandas import read_root

import numpy as np

import matplotlib.pyplot as plt
import pickle
import pandas


bkg_file = '/run/media/davidwassell/David USB/dataMagUp2016/Lb_Tuple.root'

# make a pandas data frame
bkg_sample = read_root( bkg_file, 'tree',
                        columns = [ 'h1_ProbNNmu',  'h1_ProbNNk', 'h1_ProbNNpi' ] )


ax = bkg_sample.plot.scatter( x='h1_ProbNNmu', y='h1_ProbNNk', c='r', s=0.1 )
bkg_sample.plot.scatter( x='h1_ProbNNpi', y='h1_ProbNNk', c='b', s=0.1 )

plt.ylim( 0, 1 )
plt.xlim( 0, 1 )

plt.show()

