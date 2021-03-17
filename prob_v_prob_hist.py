import matplotlib
import matplotlib.pyplot as plt
from matplotlib.colors import BoundaryNorm
from matplotlib.colors import LogNorm
from matplotlib.ticker import MaxNLocator
from matplotlib import rcParams
import numpy as np
import unicodedata

from root_pandas import read_root

# Merged Data File
bkg_file = '/run/media/davidwassell/David USB/Reduced Data/merged.root'

# make a pandas data frame
bkg_sample = read_root( bkg_file, 'tree',
                        columns = [ 'h1_ProbNNmu',  'h1_ProbNNpi', 'h1_ProbNNk', 'h1_ProbNNp' ] )

'''
Z = np.random.rand(6, 10)
x = np.arange(-0.5, 10, 1)  # len = 11
y = np.arange(4.5, 11, 1)  # len = 7

fig, ax = plt.subplots()
ax.pcolormesh(x, y, Z)
'''

# Set axis titles
xaxis = 'h1_ProbNNpi'
yaxis = 'h1_ProbNNp'

pi = unicodedata.lookup("GREEK SMALL LETTER PI")

# xaxislabel = 'h2 probability of being a ' + pi + '$^-$'
xaxislabel = 'h1 probability of being a pion'
yaxislabel = 'h1 probability of being a proton'

# Plot details
x=bkg_sample[xaxis]
y=bkg_sample[yaxis]
fig, ax = plt.subplots()
ax.tick_params(axis='both', which='major', pad=15)
h = plt.hist2d(x,y,bins=100, norm=LogNorm(), range=[[0,1],[0.1,1]] )
plt.ylim( 0.1, 1 )
plt.xlim( 0, 1 )
plt.rcParams.update({'font.size': 24})
plt.xlabel(xaxislabel, fontsize=24, labelpad=10)
plt.ylabel(yaxislabel, fontsize=24, labelpad=20)

for label in (ax.get_xticklabels() + ax.get_yticklabels()):
    label.set_fontsize(24)

fig.colorbar(h[3], ax = ax)
plt.show()

