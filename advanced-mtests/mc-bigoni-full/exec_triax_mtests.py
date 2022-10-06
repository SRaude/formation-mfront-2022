# -*- coding:utf8 -*-

exec(open("./config_script.py").read())

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
### Loop on the keys of SensiDicPara
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

for para,dico in SensiDicPara.items():
	ggm.PathToOuputFiles="{}/{}".format(RootToOutputFiles,para)
	if "Prescribed" in para:
		DefaultV=ggm.LoadingConditions[para]
		for vp in dico["list"]:
			ggm.NameOfOutputFile="{name}_{value:g}".format(name=para,value=vp)
			ggm.NameOfFileToFormat="{name}_{value:g}".format(name=para,value=vp)
			ggm.LoadingConditions[para]=vp
			TTab=ggm.RunMTest(DefaultDicPara)
		ggm.LoadingConditions[para]=DefaultV
	else:
		CopyDicPara=DefaultDicPara.copy()
		for vp in dico["list"]:
			ggm.NameOfOutputFile="{name}_{value:g}".format(name=para,value=vp)
			ggm.NameOfFileToFormat="{name}_{value:g}".format(name=para,value=vp)
			CopyDicPara[para]=vp
			TTab=ggm.RunMTest(CopyDicPara)
