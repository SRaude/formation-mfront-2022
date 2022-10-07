# -*- coding:utf8 -*-

from math import *
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os

plt.rcParams.update({
	"text.usetex":True,
	"font.family":"serif",
	"text.latex.preamble":r"\usepackage[T1]{fontenc}\usepackage[utf8]{inputenc}\usepackage{amsmath}\usepackage{amssymb}\usepackage{amsfonts}\usepackage{fourier}",
	"font.size":16,
})

MyCMap=plt.get_cmap("hot")
MyCMapUP=MyCMap(np.arange(MyCMap.N))

fig,ax=plt.subplots(1,1,figsize=(8,6),constrained_layout=True)

lLABEL=[]
lFILES=[]

for root,dirs,files in os.walk(os.getcwd()):
	for f in files:
		ext=f.split('.')[-1]
		if (ext=='resu'):
			lFILES.append(f)
	lFILES.sort()
	i=0
	for f in lFILES:
		tab=pd.read_csv(f,header=4)
		ic=float(i)/max(1.,float(len(lFILES)-1.))
		ic=int(ic*(len(MyCMapUP)-1.))
		ax.plot(tab["INST"],-2.*tab["DY"]/1.e6,c=MyCMapUP[ic],zorder=11,lw=2)
		lLABEL.append(f.split('_')[-2])
		i+=1

ax.set_xlabel(r"$t$ (s)")
ax.set_ylabel(r"$\sum{F_i}$ (MN/m)")
ax.minorticks_on()
ax.axhline(0.,c='k',lw=1.,zorder=3)
ax.axhline(300.6,c='w',lw=1.,ls='--',zorder=3)
ax.axhline(308.8,c='w',lw=1.,ls='--',zorder=3)
ax.axvline(1.,c='k',lw=1.,zorder=3)
ax.grid(lw=1,ls=':',c='.5',zorder=0)
ax.set_facecolor('.7')

fig.set_facecolor('.9')

### >>> The colorbar
norm=mpl.colors.Normalize(vmin=0.,vmax=1.)
cb=fig.colorbar(mpl.cm.ScalarMappable(norm=norm,cmap=MyCMap),ax=ax,location='top',shrink=.5,aspect=30)
cb.set_ticks(np.linspace(0.,1.,len(lFILES)))
cb.set_ticklabels(['{level:d}'.format(level=int(l)) for l in lLABEL])
t=cb.set_label(r"Number of nodes (linear)",va="bottom")

plt.savefig('bc.pdf',dpi=600,bbox_inches='tight')