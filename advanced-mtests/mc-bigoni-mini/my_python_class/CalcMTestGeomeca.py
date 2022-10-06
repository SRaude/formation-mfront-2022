# -*- coding:utf8 -*-

### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
###                                                        o
### Python class for basic tests in geomechanics via MTest o
###                                                        o
### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

import os
from collections import OrderedDict
import pandas as pd
import numpy as np

class CalcMTestGeomeca:

	### >>>>>>>>>>>>>>
	### Initialisation
	### <<<<<<<<<<<<<<

	def __init__(self):

		### Sources config.
		### <<<<<<<<<<<<<<<

		self.PathToSRC="./sources"                                                   # path to MFront source files 
		self.NameOfTheModel="NameOfTheModel"                                         # name of the constitutive models
		self.DStateVariables=OrderedDict()                                           # dictionary where the keys are the MFront names of the state variables and the values are their components
		self.AuxiliaryStateVariables=[]                                              # list of auxiliary state variables
		self.EpsComp=['EPXX','EPYY','EPZZ','EPXY','EPXZ','EPYZ']                     # list of strain components
		self.SigComp=['SIXX','SIYY','SIZZ','SIXY','SIXZ','SIYZ']                     # list of stress components
		self.EpsELComp=['EPXX_EL','EPYY_EL','EPZZ_EL','EPXY_EL','EPXZ_EL','EPYZ_EL'] # list of elastic strain components

		### MTest config.
		### <<<<<<<<<<<<<

		self.MTestsBinary="mtest-3.4.0"                                  # path to your mtest exec.
		self.MTestOptions=""                                             # exemple of options : --verbose="quiet"
		self.MTestNumberOfLoadingSteps=1                                 # number of loading phases
		self.MTestNumberOfTimeSteps=[100]*self.MTestNumberOfLoadingSteps # number of time steps
		self.MTestConvergenceCriterion=1.e-14                            # convergence criterion
		self.MTestMaximumNumberOfSubSteps=20                             # maximum number of sub steps in cas of non-convergence
		self.MTestOutputFilePrecision=15                                 # precision for numbers in the output file

		### Available test types >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		###
		###    o "StressOedometricCompressionTest" : MTestNumberOfLoadingSteps=1
		###    o "StrainOedometricCompressionTest" : MTestNumberOfLoadingSteps=1
		###    o "IsotropicCompressionTest"        : MTestNumberOfLoadingSteps=1
		###    o "TriaxialCompressionTest"         : MTestNumberOfLoadingSteps=2
		###    o "TriaxialCreepCompressionTest"    : MTestNumberOfLoadingSteps=3
		###
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		self.TestType="TriaxialCompressionTest"

		### Test conditions
		### <<<<<<<<<<<<<<<

		self.LoadingConditions=OrderedDict()
		self.LoadingConditions["PrescribedConfiningPressure"]=-.1e6
		self.LoadingConditions["PrescribedStrain"]=-1.e-2
		self.LoadingConditions["PrescribedStress"]=-10.e6
		self.LoadingConditions["PrescribedStrainRate"]=-1.e-6
		self.LoadingConditions["PrescribedStressRate"]=-.1e6
		self.LoadingConditions["Duration"]=30.*86400.

		### Options for output files
		### <<<<<<<<<<<<<<<<<<<<<<<<
		
		self.NameOfOutputFile="OutputTable"
		self.NameOfFileToFormat="OutputTable"
		self.PathToOuputFiles=os.getcwd()+"/OutputFiles"

	### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	### Function to format output files with pandas and numpy
	### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	def FormatOutputFiles(self):
		Tab=np.genfromtxt('%s'%(self.PathToOuputFiles+'/'+self.NameOfFileToFormat))
		PandasCol=["INST"]+self.EpsComp+self.SigComp+self.EpsELComp
		for v in self.DStateVariables.values():
			PandasCol+=v
		PandasCol+=self.AuxiliaryStateVariables+['E_STORED','E_DISSIPATED']
		PandasTab=pd.DataFrame(Tab,columns=PandasCol)
		PandasTab.to_csv('{}'.format(self.PathToOuputFiles+'/'+self.NameOfFileToFormat+'.csv'),sep=',')
		os.system('rm -rf %s'%(self.PathToOuputFiles+'/'+self.NameOfFileToFormat))
		return PandasTab

	### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	### Function to write what is independent of the loading conditions in the MTest file
	### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	def WriteMTestFilePreamble(self,DMaterialParameters):
		
		### DMaterialParameters must be a Python dictionary given by the user
		### DMaterialParameters["NameOfTheParameter"]=ValueOfTheParameter

		### The MTest file is created in the /tmp directory
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		
		if "mfile.mtest" in os.listdir("/tmp/"):
			os.system("rm -rf /tmp/mfile.mtest")
			f=open("/tmp/mfile.mtest","a")
		else:
			f=open("/tmp/mfile.mtest","a")

		### Specify the @Behaviour MTest keyword
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		f.write("@Behaviour<aster> '{pathSRC}/src/libAsterBehaviour.so'  'aster{nMODEL}';\n".format(pathSRC=self.PathToSRC,nMODEL=self.NameOfTheModel.lower()))

		### Write material parameters in the MTest file
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		for name,value in DMaterialParameters.items():
			f.write("@MaterialProperty<constant> '{name}' {val:e};\n".format(name=name,val=value))

		### Write other keywords
		### <<<<<<<<<<<<<<<<<<<<

		f.write("@ExternalStateVariable 'Temperature' 293.15;\n")
		f.write("@OutputFilePrecision {:d};\n".format(self.MTestOutputFilePrecision))
		f.write("@MaximumNumberOfSubSteps {};\n".format(self.MTestMaximumNumberOfSubSteps))
		f.write("@StrainEpsilon {:e};\n".format(self.MTestConvergenceCriterion))
		f.close()

	### >>>>>>>>>
	### Run MTest
	### <<<<<<<<<

	def RunMTest(self,DMaterialParameters):

		### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		### 1. Monotonic Oedometric Compression Test - Stress
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		if (self.TestType=="StressOedometricCompressionTest"):

			### 1.1 Check the NumberOfLoadingSteps and the NumberOfTimeSteps
			NumberOfLoadingSteps=self.MTestNumberOfLoadingSteps
			NumberOfTimeSteps=self.MTestNumberOfTimeSteps
			assert(NumberOfLoadingSteps==1)
			assert(len(NumberOfTimeSteps)==1)

			### 1.2 Write the preamble
			self.WriteMTestFilePreamble(DMaterialParameters)
			
			### 1.3 Get loading conditions
			Stress=self.LoadingConditions["PrescribedStress"]
			StressRate=self.LoadingConditions["PrescribedStressRate"]
			TStep=Stress/StressRate
			
			### 1.4 Write the loading conditions in the MTest file
			f=open("/tmp/mfile.mtest","a")
			f.write("@ImposedStrain 'EXX' {{0:0,{TEnd}:0.}};\n".format(TEnd=TStep))
			f.write("@ImposedStrain 'EYY' {{0:0,{TEnd}:0.}};\n".format(TEnd=TStep))
			f.write("@ImposedStress 'SZZ' {{0:0,{TEnd}:{StressV}}};\n".format(TEnd=TStep,StressV=Stress))
			f.write("@Times {{0,{TEnd} in {NbSteps}}};\n".format(TEnd=TStep,NbSteps=self.MTestNumberOfTimeSteps[0]))
			f.write("@OutputFile '{}';\n".format(self.PathToOuputFiles+'/'+self.NameOfOutputFile))
			f.close()

			### 1.5 Create the output directory
			if (os.path.exists(self.PathToOuputFiles)==False):
				os.makedirs(self.PathToOuputFiles)
			
			### 1.6 Run the test
			os.system("{} {} /tmp/mfile.mtest".format(self.MTestsBinary,self.MTestOptions))

			### 1.7 Format the output file to a .csv file via pandas
			self.NameOfFileToFormat=self.NameOfOutputFile
			Tab=self.FormatOutputFiles()

			### 1.8 Return the output pandas table
			return Tab

		### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		### 2. Monotonic Oedometric Compression Test - Strain
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		if (self.TestType=="StrainOedometricCompressionTest"):

			### 2.1 Check the NumberOfLoadingSteps and the NumberOfTimeSteps
			NumberOfLoadingSteps=self.MTestNumberOfLoadingSteps
			NumberOfTimeSteps=self.MTestNumberOfTimeSteps
			assert(NumberOfLoadingSteps==1)
			assert(len(NumberOfTimeSteps)==1)

			### 2.2 Write the preamble
			self.WriteMTestFilePreamble(DMaterialParameters)
			
			### 2.3 Get loading conditions
			Strain=self.LoadingConditions["PrescribedStrain"]
			StrainRate=self.LoadingConditions["PrescribedStrainRate"]
			TStep=Strain/StrainRate
			
			### 2.4 Write the loading conditions in the MTest file
			f=open("/tmp/mfile.mtest","a")
			f.write("@ImposedStrain 'EXX' {{0:0,{TEnd}:0.}};\n".format(TEnd=TStep))
			f.write("@ImposedStrain 'EYY' {{0:0,{TEnd}:0.}};\n".format(TEnd=TStep))
			f.write("@ImposedStrain 'EZZ' {{0:0,{TEnd}:{StrainV}}};\n".format(TEnd=TStep,StrainV=Strain))
			f.write("@Times {{0,{TEnd} in {NbSteps}}};\n".format(TEnd=TStep,NbSteps=self.MTestNumberOfTimeSteps[0]))
			f.write("@OutputFile '{}';\n".format(self.PathToOuputFiles+'/'+self.NameOfOutputFile))
			f.close()

			### 2.5 Create the output directory
			if (os.path.exists(self.PathToOuputFiles)==False):
				os.makedirs(self.PathToOuputFiles)
			
			### 2.6 Run the test
			os.system("{} {} /tmp/mfile.mtest".format(self.MTestsBinary,self.MTestOptions))

			### 2.7 Format the output file to a .csv file via pandas
			self.NameOfFileToFormat=self.NameOfOutputFile
			Tab=self.FormatOutputFiles()

			### 2.8 Return the output pandas table
			return Tab

		### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		### 3. Monotonic Isotropic Compression Test
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		if (self.TestType=="IsotropicCompressionTest"):

			### 3.1 Check the NumberOfLoadingSteps and the NumberOfTimeSteps
			NumberOfLoadingSteps=self.MTestNumberOfLoadingSteps
			NumberOfTimeSteps=self.MTestNumberOfTimeSteps
			assert(NumberOfLoadingSteps==1)
			assert(len(NumberOfTimeSteps)==1)

			### 3.2 Write the preamble
			self.WriteMTestFilePreamble(DMaterialParameters)
			
			### 3.3 Get the loading conditions
			Stress=self.LoadingConditions["PrescribedStress"]
			StressRate=self.LoadingConditions["PrescribedStressRate"]
			TStep=Stress/StressRate
			
			### 3.4 Write the loading conditions in the MTest file
			f=open("/tmp/mfile.mtest","a")
			f.write("@ImposedStress 'SXX' {{0:0,{TEnd}:{StressV}}};\n".format(TEnd=TStep,StressV=Stress))
			f.write("@ImposedStress 'SYY' {{0:0,{TEnd}:{StressV}}};\n".format(TEnd=TStep,StressV=Stress))
			f.write("@ImposedStress 'SZZ' {{0:0,{TEnd}:{StressV}}};\n".format(TEnd=TStep,StressV=Stress))
			f.write("@Times {{0,{TEnd} in {NbSteps}}};\n".format(TEnd=TStep,NbSteps=self.MTestNumberOfTimeSteps[0]))
			f.write("@OutputFile '{}';\n".format(self.PathToOuputFiles+'/'+self.NameOfOutputFile))
			f.close()

			### 3.5 Create the output directory
			if (os.path.exists(self.PathToOuputFiles)==False):
				os.makedirs(self.PathToOuputFiles)
			
			### 3.6 Run the test
			os.system("{} {} /tmp/mfile.mtest".format(self.MTestsBinary,self.MTestOptions))

			### 3.7 Format the output file to a .csv file via pandas
			self.NameOfFileToFormat=self.NameOfOutputFile
			Tab=self.FormatOutputFiles()

			### 3.8 Return the output pandas table
			return Tab

		### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		### 4. Monotonic Triaxial Compression Test
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		if (self.TestType=="TriaxialCompressionTest"):

			NumberOfLoadingSteps=self.MTestNumberOfLoadingSteps
			NumberOfTimeSteps=self.MTestNumberOfTimeSteps
			assert(NumberOfLoadingSteps==2)
			assert(len(NumberOfTimeSteps)==2)

			### 4.1 First step: apply the confining pressure
			### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			
			### 4.1.1 Write the preamble
			self.WriteMTestFilePreamble(DMaterialParameters)
			
			### 4.1.2 Get the loading conditions
			ConfiningPressure=self.LoadingConditions["PrescribedConfiningPressure"]
			StressRate=self.LoadingConditions["PrescribedStressRate"]
			TStepConf=ConfiningPressure/StressRate

			### 4.1.3 Write the loading conditions in the MTest file
			f=open("/tmp/mfile.mtest","a")
			f.write("@ImposedStress 'SXX' {{0:0,{TConf}:{VConf}}};\n".format(TConf=TStepConf,VConf=ConfiningPressure))
			f.write("@ImposedStress 'SYY' {{0:0,{TConf}:{VConf}}};\n".format(TConf=TStepConf,VConf=ConfiningPressure))
			f.write("@ImposedStress 'SZZ' {{0:0,{TConf}:{VConf}}};\n".format(TConf=TStepConf,VConf=ConfiningPressure))
			f.write("@Times {{0,{TConf} in {NbStepsConf}}};\n".format(TConf=TStepConf,NbStepsConf=self.MTestNumberOfTimeSteps[0]))
			f.write("@OutputFile '{}';\n".format(self.PathToOuputFiles+'/'+self.NameOfOutputFile+'ConfiningStep'))
			f.close()

			### 4.1.4 Create the output directory
			if (os.path.exists(self.PathToOuputFiles)==False):
				os.makedirs(self.PathToOuputFiles)
						
			### 4.1.5 Run the confining step
			os.system("{} {} /tmp/mfile.mtest".format(self.MTestsBinary,self.MTestOptions))

			### 4.1.6 Format the output file to a .csv file via pandas
			self.NameOfFileToFormat=self.NameOfOutputFile+'ConfiningStep'
			TabConf=self.FormatOutputFiles()

			### 4.2 Second step: apply the deviatoric strain
			### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			
			### 4.2.1 Create a new MTest file and write the preamble
			os.system("rm -rf /tmp/mfile.mtest")
			f=open("/tmp/mfile.mtest","a")
			self.WriteMTestFilePreamble(DMaterialParameters)

			### 4.2.2 Get the initial conditions from the end of the confining step
			IFields=TabConf.iloc[-1]                                # Get the last row of the pandas table created during the confining step
			EpzzIni=IFields["EPZZ"]                                 # Strain component along the vertical axis at the end of the confining step
			EpzzMax=self.LoadingConditions["PrescribedStrain"]      # Strain to be prescribed at the end of the test
			EpzzRate=self.LoadingConditions["PrescribedStrainRate"] # Strain rate
			TEnd=TStepConf+EpzzMax/EpzzRate                         # Time at the end of the test
			assert(abs(EpzzMax)>abs(EpzzIni))
			assert(TStepConf<TEnd)

			### 4.2.3 Apply the initial conditions
			f=open("/tmp/mfile.mtest","a")
			f.write("@Strain {{{epsTensor}}};\n".format(epsTensor=str([IFields[comp] for comp in self.EpsComp])[1:-1]))
			f.write("@Stress {{{sigTensor}}};\n".format(sigTensor=str([IFields[comp] for comp in self.SigComp])[1:-1]))
			f.write("@InternalStateVariable 'ElasticStrain' {{{epsELTensor}}};\n".format(epsELTensor=str([IFields[comp] for comp in self.EpsELComp])[1:-1]))
			for svNAME,svCMP in self.DStateVariables.items():
				if (len(svCMP)>1):
					f.write("@InternalStateVariable '{name}' {{{isvTensor}}};\n".format(name=svNAME,isvTensor=str([IFields[comp] for comp in svCMP])[1:-1]))
				else:
					f.write("@InternalStateVariable '{name}' {isvTensor};\n".format(name=svNAME,isvTensor=str([IFields[comp] for comp in svCMP])[1:-1]))
			
			### 4.2.4 Write the deviatoric loading conditions in the MTest file
			f.write("@ImposedStress 'SXX' {{{TConf}:{VConf},{TEnd}:{VConf}}};\n".format(TConf=TStepConf,VConf=ConfiningPressure,TEnd=TEnd))
			f.write("@ImposedStress 'SYY' {{{TConf}:{VConf},{TEnd}:{VConf}}};\n".format(TConf=TStepConf,VConf=ConfiningPressure,TEnd=TEnd))
			f.write("@ImposedStrain 'EZZ' {{{TConf}:{VEzzConf},{TEnd}:{VEzzMax}}};\n".format(TConf=TStepConf,VEzzConf=IFields["EPZZ"],TEnd=TEnd,VEzzMax=EpzzMax))
			f.write("@Times {{{TConf},{TEnd} in {NbStepsDev}}};\n".format(TConf=TStepConf,TEnd=TEnd,NbStepsDev=self.MTestNumberOfTimeSteps[1]))
			f.write("@OutputFile '{}';\n".format(self.PathToOuputFiles+'/'+self.NameOfOutputFile+'DeviatoricStep'))
			f.close()
			
			### 4.2.5 Run the deviatoric step
			os.system("{} {} /tmp/mfile.mtest".format(self.MTestsBinary,self.MTestOptions))

			### 4.2.6 Format the output file to a .csv file via pandas
			self.NameOfFileToFormat=self.NameOfOutputFile+'DeviatoricStep'
			TabDev=self.FormatOutputFiles()

			### 4.2.7 Concatenate the two .csv files
			Tab=pd.concat([TabConf,TabDev.iloc[1:]],ignore_index=True)
			self.NameOfFileToFormat=self.NameOfOutputFile
			Tab.to_csv('{}'.format(self.PathToOuputFiles+'/'+self.NameOfFileToFormat+'.csv'),sep=',')
			os.system("rm -rf {}".format(self.PathToOuputFiles+'/'+self.NameOfFileToFormat+'ConfiningStep'+'.csv'))
			os.system("rm -rf {}".format(self.PathToOuputFiles+'/'+self.NameOfFileToFormat+'DeviatoricStep'+'.csv'))

			### 4.2.8 Return the output pandas tables
			return (TabConf,TabDev,Tab)

		### >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		### 5. Monotonic Triaxial Creep Compression Test
		### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		if (self.TestType=="TriaxialCreepCompressionTest"):

			NumberOfLoadingSteps=self.MTestNumberOfLoadingSteps
			NumberOfTimeSteps=self.MTestNumberOfTimeSteps
			assert(NumberOfLoadingSteps==3)
			assert(len(NumberOfTimeSteps)==3)

			### 5.1 First step: apply the confining pressure
			### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			
			### 5.1.1 Write the preamble
			self.WriteMTestFilePreamble(DMaterialParameters)
			
			### 5.1.2 Get loading conditions
			ConfiningPressure=self.LoadingConditions["PrescribedConfiningPressure"]
			StressRate=self.LoadingConditions["PrescribedStressRate"]
			TStepConf=ConfiningPressure/StressRate

			### 5.1.3 Write the loading conditions in the MTest file
			f=open("/tmp/mfile.mtest","a")
			f.write("@ImposedStress 'SXX' {{0:0,{TConf}:{VConf}}};\n".format(TConf=TStepConf,VConf=ConfiningPressure))
			f.write("@ImposedStress 'SYY' {{0:0,{TConf}:{VConf}}};\n".format(TConf=TStepConf,VConf=ConfiningPressure))
			f.write("@ImposedStress 'SZZ' {{0:0,{TConf}:{VConf}}};\n".format(TConf=TStepConf,VConf=ConfiningPressure))
			f.write("@Times {{0,{TConf} in {NbStepsConf}}};\n".format(TConf=TStepConf,NbStepsConf=self.MTestNumberOfTimeSteps[0]))
			f.write("@OutputFile '{}';\n".format(self.PathToOuputFiles+'/'+self.NameOfOutputFile+'ConfiningStep'))
			f.close()

			### 5.1.4 Create the output directory
			if (os.path.exists(self.PathToOuputFiles)==False):
				os.makedirs(self.PathToOuputFiles)
			
			### 5.1.5 Run the confining step
			os.system("{} {} /tmp/mfile.mtest".format(self.MTestsBinary,self.MTestOptions))

			### 5.1.6 Format the output file to a .csv file via pandas
			self.NameOfFileToFormat=self.NameOfOutputFile+'ConfiningStep'
			TabConf=self.FormatOutputFiles()

			### 5.2 Second step: apply the deviatoric stress
			### <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			### 5.2.1 Create a new MTest file and write the preamble
			os.system("rm -rf /tmp/mfile.mtest")
			f=open("/tmp/mfile.mtest","a")
			self.WriteMTestFilePreamble(DMaterialParameters)

			### 5.2.2 Get the initial conditions frome the confining step
			IFields=TabConf.iloc[-1]                          # Get the last row of the pandas table created during the confining step
			Stress=self.LoadingConditions["PrescribedStress"] # Get the stress state to be prescribed during the creep step
			TStepDev=TStepConf+Stress/StressRate              # Time at the end of step in which the deviatoric stress is increasing
			TEnd=TStepDev+self.LoadingConditions["Duration"]  # Time at the end of the test
			assert(abs(ConfiningPressure)<abs(Stress))
			assert(TStepConf<TStepDev)
			assert(TStepDev<TEnd)

			### 5.2.3 Write the initial conditions in the MTest file
			f=open("/tmp/mfile.mtest","a")
			f.write("@Strain {{{epsTensor}}};\n".format(epsTensor=str([IFields[comp] for comp in self.EpsComp])[1:-1]))
			f.write("@Stress {{{sigTensor}}};\n".format(sigTensor=str([IFields[comp] for comp in self.SigComp])[1:-1]))
			f.write("@InternalStateVariable 'ElasticStrain' {{{epsELTensor}}};\n".format(epsELTensor=str([IFields[comp] for comp in self.EpsELComp])[1:-1]))
			for svNAME,svCMP in self.DStateVariables.items():
				if (len(svCMP)>1):
					f.write("@InternalStateVariable '{name}' {{{isvTensor}}};\n".format(name=svNAME,isvTensor=str([IFields[comp] for comp in svCMP])[1:-1]))
				else:
					f.write("@InternalStateVariable '{name}' {isvTensor};\n".format(name=svNAME,isvTensor=str([IFields[comp] for comp in svCMP])[1:-1]))
			
			### 5.2.4 Write the deviatoric loading conditions in the MTest file
			f.write("@ImposedStress 'SXX' {{{TConf}:{VConf},{TDev}:{VConf},{TEnd}:{VConf}}};\n".format(TConf=TStepConf,TDev=TStepDev,TEnd=TEnd,VConf=ConfiningPressure))
			f.write("@ImposedStress 'SYY' {{{TConf}:{VConf},{TDev}:{VConf},{TEnd}:{VConf}}};\n".format(TConf=TStepConf,TDev=TStepDev,TEnd=TEnd,VConf=ConfiningPressure))
			f.write("@ImposedStress 'SZZ' {{{TConf}:{VConf},{TDev}:{VDevi},{TEnd}:{VDevi}}};\n".format(TConf=TStepConf,TDev=TStepDev,TEnd=TEnd,VConf=ConfiningPressure,VDevi=Stress))
			f.write("@Times {{{TConf},{TDev} in {NbStepsDev}, {TEnd} in {NbStepsCreep}}};\n".format(TConf=TStepConf,TDev=TStepDev,TEnd=TEnd,NbStepsDev=self.MTestNumberOfTimeSteps[1],NbStepsCreep=self.MTestNumberOfTimeSteps[2]))
			f.write("@OutputFile '{}';\n".format(self.PathToOuputFiles+'/'+self.NameOfOutputFile+'DeviatoricStep'))
			f.close()
			
			### 5.2.5 Run the deviatoric step
			os.system("{} {} /tmp/mfile.mtest".format(self.MTestsBinary,self.MTestOptions))

			### 5.2.6 Format the output file to a .csv file via pandas
			self.NameOfFileToFormat=self.NameOfOutputFile+'DeviatoricStep'
			TabDev=self.FormatOutputFiles()

			### 5.2.7 Concatenate the two .csv files
			Tab=pd.concat([TabConf,TabDev.iloc[1:]],ignore_index=True)
			self.NameOfFileToFormat=self.NameOfOutputFile
			Tab.to_csv('{}'.format(self.PathToOuputFiles+'/'+self.NameOfFileToFormat+'.csv'),sep=',')
			os.system("rm -rf {}".format(self.PathToOuputFiles+'/'+self.NameOfFileToFormat+'ConfiningStep'+'.csv'))
			os.system("rm -rf {}".format(self.PathToOuputFiles+'/'+self.NameOfFileToFormat+'DeviatoricStep'+'.csv'))

			### 5.2.8 Return the output pandas tables
			return (TabConf,TabDev,Tab)
r"""
### >>>>>
### Tests
### <<<<<

DMatPara=OrderedDict()
DMatPara["YoungModulus"]=1.e9
DMatPara["PoissonRatio"]=.3
DMatPara["pci"]=20.e6
DMatPara["ci"]=.1e6
DMatPara["M"]=.6
DMatPara["Nd"]=1.
DMatPara["mB"]=3.
DMatPara["aB"]=.75
DMatPara["om"]=15.
DMatPara["nv"]=2.
DMatPara["tau"]=2.e3
DMatPara["Hp"]=1.*DMatPara["YoungModulus"]
DMatPara["Hv"]=.025*DMatPara["YoungModulus"]

ggm=CalcMTestGeomeca()
ggm.PathToSRC="/home/F91271/dev/mfront/pvnkh_gmrocks/sources"
ggm.PathToOuputFiles="/home/F91271/dev/mfront/pvnkh_gmrocks/new_tests/triaxOUTPUTS"
ggm.NameOfTheModel="VP_KH_CSRM_Sym"
ggm.MTestOptions="--verbose=quiet"

# ggm.TestType="IsotropicCompressionTest"
ggm.TestType="TriaxialCompressionTest"
# ggm.TestType="StressOedometricCompressionTest"
# ggm.TestType="StrainOedometricCompressionTest"
# ggm.TestType="TriaxialCreepCompressionTest"

ggm.LoadingConditions["PrescribedConfiningPressure"]=-2.e6
# ggm.LoadingConditions["PrescribedStress"]=-9.e6
# ggm.LoadingConditions["Duration"]=30.*86400.
ggm.LoadingConditions["PrescribedStrain"]=-2.e-1

ggm.DStateVariables=OrderedDict()
ggm.DStateVariables["la"]=["LAMBDA"]
ggm.DStateVariables["ep"]=["EPLXX","EPLYY","EPLZZ","EPLXY","EPLXZ","EPLYZ"]
ggm.DStateVariables["ev"]=["EVXX","EVYY","EVZZ","EVXY","EVXZ","EVYZ"]
ggm.DStateVariables["ap"]=["APXX","APYY","APZZ","APXY","APXZ","APYZ"]
ggm.DStateVariables["av"]=["AVXX","AVYY","AVZZ","AVXY","AVXZ","AVYZ"]

ggm.AuxiliaryStateVariables=['NITER','DOMAIN','CHECK','IP','IV']

ggm.MTestNumberOfLoadingSteps=2
ggm.MTestNumberOfTimeSteps=[1,250]
ggm.MTestsBinary='mtest-3.4.0'

import matplotlib.pyplot as plt

LisOfConf=np.linspace(-10.e6,-2.e6,8)
ListOfStrainRate=np.array([-1.e-8,-5.e-8,-1.e-7,-5.e-7,-1.e-6,-1.e-5])

fig=plt.figure()

for pc in LisOfConf:
	ggm.LoadingConditions["PrescribedConfiningPressure"]=pc
	tupleTAB=ggm.RunMTest(DMatPara)
	devTAB=tupleTAB[1]
	plt.plot(-(devTAB["EPZZ"]-devTAB["EPZZ"][0])*1.e2,-(devTAB["SIZZ"]-devTAB["SIZZ"][0]-(devTAB["SIXX"]-devTAB["SIXX"][0]))/1.e6)

ggm.LoadingConditions["PrescribedConfiningPressure"]=-4.e6

fig=plt.figure()

for sr in ListOfStrainRate:
	ggm.LoadingConditions["PrescribedStrainRate"]=sr
	tupleTAB=ggm.RunMTest(DMatPara)
	devTAB=tupleTAB[1]
	plt.plot(-(devTAB["EPZZ"]-devTAB["EPZZ"][0])*1.e2,-(devTAB["SIZZ"]-devTAB["SIZZ"][0]-(devTAB["SIXX"]-devTAB["SIXX"][0]))/1.e6)

plt.show()
"""
