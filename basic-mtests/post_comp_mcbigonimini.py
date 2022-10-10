# -*- coding:utf8 -*-

from math import *
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

plt.rcParams.update({
	"text.usetex":True,
	"font.family":"serif",
	"text.latex.preamble":r"\usepackage[T1]{fontenc}\usepackage[utf8]{inputenc}\usepackage{amsmath}\usepackage{amssymb}\usepackage{amsfonts}\usepackage{fourier}",
	"font.size":16,
})

Tab=np.loadtxt("comp_mcbigonimini.resu",skiprows=27,delimiter=' ')

fig,ax=plt.subplots(1,2,constrained_layout=True,figsize=(15,6))
fig.set_constrained_layout_pads(hspace=.05,wspace=.05)
fx=ax.flatten()

ax[0].plot(-(Tab.T[3][1:]+Tab.T[3][1])*100.,(Tab.T[10][1:]-Tab.T[9][1:])/1.e6)
ax[1].plot(-(Tab.T[3][1:]+Tab.T[3][1])*100.,(-(Tab.T[1][1:]+Tab.T[1][1])-(Tab.T[2][1:]+Tab.T[2][1])-(Tab.T[3][1:]+Tab.T[3][1]))*100.)

ax[0].set_xlabel(r"$-\epsilon_{zz}$ (\%)")
ax[0].set_ylabel(r"$-\left(\sigma_{zz}-\sigma_{yy}\right)$ (MPa)")

ax[1].set_xlabel(r"$-\epsilon_{zz}$ (\%)")
ax[1].set_ylabel(r"$-\epsilon_v$ (\%)")

plt.savefig("post_comp_mcbigonimini.pdf",bbox_inches='tight',dpi=600)