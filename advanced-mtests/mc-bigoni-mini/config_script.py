# -*- coding:utf8 -*-

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>
### Specify paths for my classes
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<

### Python packages
from math import *
from collections import OrderedDict
import matplotlib as mpl
import matplotlib.pyplot as plt
import os
import sys

PACKAGE_PARENT='.'
SCRIPT_DIR=os.path.dirname(os.path.realpath(os.path.join(os.getcwd(),os.path.expanduser(__file__))))
sys.path.append(os.path.normpath(os.path.join(SCRIPT_DIR,PACKAGE_PARENT)))

### Load my classes
from my_python_class.CalcMTestGeomeca import *
from my_python_class.CalcMCHyperCriterion import *

plt.rcParams.update({
	"text.usetex":True,
	"font.family":"serif",
	"text.latex.preamble":r"\usepackage[T1]{fontenc}\usepackage[utf8]{inputenc}\usepackage{amsmath}\usepackage{amssymb}\usepackage{amsfonts}\usepackage{fourier}",
	"font.size":18,
})

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
### Define a default dictionary of material parameters
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

DefaultDicPara=OrderedDict()
DefaultDicPara["YoungModulus"]=9.e9
DefaultDicPara["PoissonRatio"]=.25
DefaultDicPara["FrictionAngle"]=32.07
DefaultDicPara["DilationAngle"]=32.07
DefaultDicPara["Cohesion"]=4.21e6
DefaultDicPara["TensionCutOff"]=0.

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
### Define an alias for CalcMCHyperbolicCriterion()
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

mcc=CalcMCHyperbolicCriterion()

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
### Define some basic parameters of the class CalcMTestGeomeca
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

ggm=CalcMTestGeomeca()

### Paths
ggm.PathToSRC="/home/simon/dev/formation-mfront-2022/mfront-src-files/"
RootToOutputFiles="/home/simon/dev/formation-mfront-2022/advanced-mtests/mc-bigoni-mini/triax_output_files"

### Model specifications
ggm.NameOfTheModel="MCBigoniMini"
ggm.DStateVariables=OrderedDict()
ggm.DStateVariables["PlastMultiplier"]=["LAMBDA"]
ggm.AuxiliaryStateVariables=['NITER','IP','EVP','GAMMAP','TIME']

### MTest options
ggm.MTestNumberOfLoadingSteps=2
ggm.MTestNumberOfTimeSteps=[1,250]
ggm.MTestsBinary='mtest-3.4.0'
ggm.MTestOptions="--verbose=quiet"
ggm.MTestConvergenceCriterion=1.e-14

### Test type
ggm.TestType="TriaxialCompressionTest"

### Default loading conditions
DPConf=-4.e6
DPStressRate=-.1e6
DPStrain=-3.e-2
DPStrainRate=-1.e-4
ggm.LoadingConditions["PrescribedConfiningPressure"]=DPConf
ggm.LoadingConditions["PrescribedStrain"]=DPStrain
ggm.LoadingConditions["PrescribedStrainRate"]=DPStrainRate

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
### Define a dictionary for sensibility analysis
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

SensiDicPara=OrderedDict()
SensiDicPara["PrescribedConfiningPressure"]={"list":np.linspace(-20.e6,-1.e6,8),"label":r"$\sigma_3$ (MPa)","scale":1.e6}
SensiDicPara["YoungModulus"]={"list":np.logspace(9,10,8),"label":r"$E$ (GPa)","scale":1.e9}
SensiDicPara["PoissonRatio"]={"list":np.linspace(.1,.35,8),"label":r"$\nu$ (-)","scale":1.}
SensiDicPara["FrictionAngle"]={"list":np.linspace(20.,45.,8),"label":r"$\phi$ (??)","scale":1.}
SensiDicPara["DilationAngle"]={"list":np.linspace(1.,30.,8),"label":r"$\psi$ (??)","scale":1.}
SensiDicPara["Cohesion"]={"list":np.linspace(.1,10.,8)*1.e6,"label":r"$C$ (MPa)","scale":1.e6}
SensiDicPara["TensionCutOff"]={"list":np.linspace(.01,.9,8)*DefaultDicPara["Cohesion"]/tan(DefaultDicPara["FrictionAngle"]*pi/180.),"label":r"$a$ (MPa)","scale":1.e6}

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
### Define a dictionary for the curves to be plotted
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

def DefineDicForCurves(tab):
	DicCurves=OrderedDict()
	DicCurves["EaxDev"]={
		"x":-(tab["EPZZ"][1:]-tab["EPZZ"][1])*100.,
		"y":-(tab['SIZZ'][1:]-tab['SIZZ'][1])/1.e6+(tab['SIXX'][1:]-tab['SIXX'][1])/1.e6,
		"xlabel":r"$-\left(\epsilon_{zz}-\epsilon_{zz}^h\right)$ (\%)",
		"ylabel":r"$\sigma_{eq}$ (MPa)",
	}
	DicCurves["PQ"]={
		"x":-(tab["SIXX"][1:]+tab["SIYY"][1:]+tab["SIZZ"][1:])/3.e6,
		"y":-(tab['SIZZ'][1:]-tab['SIZZ'][1])/1.e6+(tab['SIXX'][1:]-tab['SIXX'][1])/1.e6,
		"xlabel":r"$-\sigma_m=-\sigma_{kk}/3$ (MPa)",
		"ylabel":r"$\sigma_{eq}$ (MPa)",
	}
	DicCurves["EaxEv"]={
		"x":-(tab["EPZZ"][1:]-tab["EPZZ"][1])*100.,
		"y":(tab["EPZZ"][1:]+tab["EPXX"][1:]+tab["EPYY"][1:])*100.-(tab["EPZZ"][1]+tab["EPXX"][1]+tab["EPYY"][1])*100.,
		"xlabel":r"$-\left(\epsilon_{zz}-\epsilon_{zz}^h\right)$ (\%)",
		"ylabel":r"$\epsilon_v-\epsilon_v^h$ (\%)",
	}
	DicCurves["EaxEvP"]={
		"x":-(tab["EPZZ"][1:]-tab["EPZZ"][1])*100.,
		"y":tab["EVP"][1:]*100.,
		"xlabel":r"$-\left(\epsilon_{zz}-\epsilon_{zz}^h\right)$ (\%)",
		"ylabel":r"$\epsilon_v^p$ (\%)",
	}
	DicCurves["EaxNiter"]={
		"x":-(tab["EPZZ"][1:]-tab["EPZZ"][1])*100.,
		"y":tab["NITER"][1:],
		"xlabel":r"$-\left(\epsilon_{zz}-\epsilon_{zz}^h\right)$ (\%)",
		"ylabel":r"Newton iterations (-)",
	}
	DicCurves["EaxIP"]={
		"x":-(tab["EPZZ"][1:]-tab["EPZZ"][1])*100.,
		"y":tab["IP"][1:],
		"xlabel":r"$-\left(\epsilon_{zz}-\epsilon_{zz}^h\right)$ (\%)",
		"ylabel":r"Plastic Index (-)",
	}
	return DicCurves

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
### Define the color map for plots
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

MyCMap=plt.get_cmap("jet")
MyCMapUP=MyCMap(np.arange(MyCMap.N))
MyCMapIEL=plt.get_cmap("Blues")
MyCMapIELUP=MyCMapIEL(np.arange(MyCMapIEL.N))
MyCMapCSL=plt.get_cmap("Greens")
MyCMapCSLUP=MyCMapCSL(np.arange(MyCMapCSL.N))