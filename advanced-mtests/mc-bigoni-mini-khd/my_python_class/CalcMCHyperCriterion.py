# -*- coding:utf8 -*-

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
###                                                               o
### Python class for the use of hyperbolic Morh-Coulomb criterion o
###                                                               o
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

from scipy import optimize
from math import *
import numpy as np

class CalcMCHyperbolicCriterion:

	### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	###  Initialisation of some parameters
	### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	def __init__(self):
		### Dictionary for material parameters
		self.DPara={}
		self.DPara["FrictionAngle"]=32.07
		self.DPara["Cohesion"]=4.21e6
		self.DPara["TensionCutOff"]=0.
		### Maximum value for Xeq
		self.XeqMAX=10.e6

	### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	### Function to build the Initial Elastic Limit of the plastic mechanism
	### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	def BuildElasticLimit(self):
		### Get material parameters
		phi=self.DPara["FrictionAngle"]*pi/180.
		C=self.DPara["Cohesion"]
		a=self.DPara["TensionCutOff"]
		THETAm=atan(-sin(phi)/sqrt(3.))
		KFm=cos(THETAm)-sin(phi)*sin(THETAm)/sqrt(3.)
		### Define the lists of sigma_m and sigma_eq
		lsm=[]
		lseq=np.linspace(0.,self.XeqMAX,1000)
		### Compute sigma_m
		for seq in lseq:
			sm=-sqrt((seq*KFm)**2/3.+(a*sin(phi))**2)/sin(phi)+C/tan(phi)
			lsm.append(sm)
		### Output
		return (-np.array(lsm),lseq)