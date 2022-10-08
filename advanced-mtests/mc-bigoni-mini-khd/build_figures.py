# -*- coding:utf8 -*-

exec(open("./config_script.py").read())

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
### Loop on the keys of SensiDicPara
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

for para,dico in SensiDicPara.items():

	### >>> Define the subplots
	fig,ax=plt.subplots(2,3,figsize=(20,10),constrained_layout=True)
	fig.set_constrained_layout_pads(hspace=.05,wspace=.05)
	fx=ax.flatten()
	
	### >>> Define empty lists to save the maximum value of q
	lqmax,lpmax=([],[])
	lxeqmax,lxmmax=([],[])
		
	### >>>>>>>>>>>>>>>>>>>>>>>>>>>>
	### >>> Loop on parameter values
	### <<<<<<<<<<<<<<<<<<<<<<<<<<<<
	
	i=0
	for vp in dico["list"]:
		
		### >>>>>> Read the csv file as a pandas table
		PTab=pd.read_csv(RootToOutputFiles+"/{name}".format(name=para)+"/{name}_{value:g}".format(name=para,value=vp)+".csv")
		
		### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		### >>>>>> Loop on curves to be plotted
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		
		j=0
		for k,d in DefineDicForCurves(PTab).items():
			
			ic=float(i)/max(1.,float(len(dico["list"])-1.))
			ic=int(ic*(len(MyCMapUP)-1.))
			fx[j].plot(d["x"],d["y"],c=MyCMapUP[ic],lw=2,zorder=10)
			
			# ### >>>>>>>>> Plot the initial elastic limit in the PQ plane if para is in DPara.keys()
			if ((k=="XmXeq") and (para in mcc.DPara.keys())):
				dv=mcc.DPara[para]
				mcc.DPara[para]=vp
				mcc.XeqMAX=max(d["y"])*1.e6
				p,q=mcc.BuildElasticLimit()
				fx[j].plot(p/1.e6,q/1.e6,c=MyCMapUP[ic],lw=2,ls='--',zorder=8)
				mcc.DPara[para]=dv

			if i==0:
				### >>>>>>>>> Plot the initial elastic limit in the PQ plane if para is not in DPara.keys()
				if ((k=="XmXeq") and ((para not in mcc.DPara.keys()))):
					mcc.XeqMAX=80.*1.e6
					p,q=mcc.BuildElasticLimit()
					fx[j].plot(p/1.e6,q/1.e6,c='w',lw=2,ls='--',zorder=8)
				
				### >>>>>>>>> Axes parameters
				fx[j].set_xlabel(d["xlabel"])
				fx[j].set_ylabel(d["ylabel"])
				fx[j].minorticks_on()
				fx[j].axhline(0.,c='k',lw=1.,zorder=3)
				fx[j].axvline(0.,c='k',lw=1.,zorder=3)
				fx[j].grid(lw=1,ls=':',c='.5',zorder=0)
				fx[j].set_facecolor('.7')
			
			### >>>>>> Plot the points from the maxima in the PQ plane
			if (k=="PQ"):
				m=j
				lqmax.append(max(d["y"]))
				lpmax.append(d["x"][np.where(d["y"]==max(d["y"]))[0][0]])
				fx[j].plot([lpmax[-1]],[lqmax[-1]],c=MyCMapUP[ic],marker='o',ls='-',mec='w',ms=10,zorder=12)
			### >>>>>> Plot the points from the maxima in the PQ plane
			if (k=="XmXeq"):
				n=j
				lxeqmax.append(max(d["y"]))
				lxmmax.append(d["x"][np.where(d["y"]==max(d["y"]))[0][0]])
				fx[j].plot([lxmmax[-1]],[lxeqmax[-1]],c=MyCMapUP[ic],marker='o',ls='-',mec='w',ms=10,zorder=12)
			j+=1

		i+=1

		fx[m].plot(lpmax,lqmax,c='w',lw=2,zorder=11)
		fx[n].plot(lxmmax,lxeqmax,c='w',lw=2,zorder=11)

	fig.set_facecolor('.9')

	### >>> The colorbar
	norm=mpl.colors.Normalize(vmin=0.,vmax=1.)
	cb=fig.colorbar(mpl.cm.ScalarMappable(norm=norm,cmap=MyCMap),ax=ax,location='top',shrink=.5,aspect=40)
	cb.set_ticks(np.linspace(0.,1.,len(dico["list"])))
	cb.set_ticklabels(['{level:.2g}'.format(level=l/dico["scale"]) for l in dico["list"]])
	t=cb.set_label(dico["label"],va="bottom")

	### >>> Save the figure
	plt.savefig(RootToOutputFiles+"/{name}".format(name=para)+"/fig.pdf",dpi=600,bbox_inches='tight')