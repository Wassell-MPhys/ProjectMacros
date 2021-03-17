import ROOT 
import math
import numpy as np
import matplotlib.pyplot as plt
from ROOT import TCanvas, TGraph
from array import array

# Simulation / Monte Carlo
root_file_sig = ROOT.TFile.Open('/run/media/davidwassell/David USB/Lb2pKmm_magUp2016/Lb_Tuple.root')
root_tree_sig = root_file_sig.Get('tree')

# Background / Real Data
root_file_bkg = ROOT.TFile.Open('/run/media/davidwassell/David USB/dataMagUp2018/Lb2pKmm_mgUp_2018.root')
root_tree_bkg = root_file_bkg.Get('Lb_Tuple/DecayTree')

# make the response available as part of the tree
root_tree_sig.AddFriend('Pred', '/run/media/davidwassell/David USB/Macros/Py_Macros/David MVA/SMU2018/apply_output_SMU2018.root') 
root_tree_bkg.AddFriend('Pred', '/run/media/davidwassell/David USB/Macros/Py_Macros/David MVA/DMU2018/apply_output_DMU2018.root')

canvas1 = TCanvas('Canvas1','Canvas1',200,10,700,500)
# Histogram for Simulation / Monte Carlo
hist_sig = ROOT.TH1D( 'hist_MVA_sig', 'MVA',100,0,1.0)
root_tree_sig.Draw('MVA_S>>hist_MVA_sig','Lb_BKGCAT < 60')

canvas2 = TCanvas('Canvas2','Canvas2',200,10,700,500)
# Histogram for Background / Real Data
hist_bkg = ROOT.TH1D( 'hist_MVA_bkg', 'MVA',100,0,1.0)
root_tree_bkg.Draw('MVA_S>>hist_MVA_bkg','Lb_M > 5580 && Lb_M < 5660 && ((0.1 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 8) || (11 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 12.5) || (15 < 1e-6*Jpsi_MM*Jpsi_MM && 1e-6*Jpsi_MM*Jpsi_MM < 19))')

MVA_S_Array = np.linspace(0, 1, 100)
effOverRootNArray = []

x, y = array('f'), array('f')
# For Testing - RootNArray = []
# For Testing - effArray = []

max = 0.0
cut_value = 0.0

# Calculating efficiency over root N
for i in range(1,101):
    val= hist_sig.GetBinLowEdge(i)
    totalNSig = hist_sig.Integral()
    totalNBkg = hist_bkg.Integral(i,100) 
    eff = hist_sig.Integral(i,100)/totalNSig
    # For Testing - effArray.append(eff)
    effOverRootN = eff/math.sqrt(totalNBkg)
    effOverRootNArray.append(effOverRootN)
    if (effOverRootN > max):
        max = effOverRootN
        cut_value = val
    # For Testing - RootNArray.append(math.sqrt(totalNBkg))
    print('cut', val, 'eff', eff, 'eff/sqrt(N)', effOverRootN)

print("Max: ", cut_value)

for i in range(0,100):
    x.append(MVA_S_Array[i])
    y.append(effOverRootNArray[i])

canvas3 = TCanvas('Canvas3','Canvas3',200,10,700,500)
gr = TGraph(100, x, y)
gr.Draw()

# Plotting and setting axis labels
plt.plot(MVA_S_Array, effOverRootNArray)
plt.xlabel('Signal MVA', fontsize=16)
plt.ylabel('$\epsilon/\sqrt{N}$', fontsize=16)
plt.show()



