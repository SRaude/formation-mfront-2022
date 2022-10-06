# -*- coding:utf8 -*-

import sys
import salome
import random
salome.salome_init()
import GEOM
import SALOMEDS
from salome.geom import geomBuilder
geompy=geomBuilder.New()
gg=salome.ImportComponentGUI("GEOM")

### >>>>>>>>>>>>>>>>>>
### >>> Input data <<<
### <<<<<<<<<<<<<<<<<<

l=30.     # width of the model
h=20.     # height of the model
r=h/l
lf=1.     # width of the foundation
lfb=5.*lf # width of the rectangle below the foundation
hfb=lfb*r # height of the rectangle below the foundation

min_size=lfb/50. # minimum size of the cells
max_size=h/10.   # maximum size of the cells

### >>>>>>>>>>>>>>>>
### >>> Geometry <<<
### <<<<<<<<<<<<<<<<

from math import *
import numpy as np

FaceSoilT=geompy.MakeFaceHW(l,h,1,theName="FaceSoilT")
FaceSoil=geompy.MakeTranslation(FaceSoilT,.5*l,-.5*h,0.,theName="FaceSoil")
FaceFoundationT=geompy.MakeFaceHW(lfb,hfb,1,theName="FaceFoundationT")
FaceFoundation=geompy.MakeTranslation(FaceFoundationT,.5*lfb,-.5*hfb,0.,theName="FaceFoundation")
TheFoundation=geompy.MakeLineTwoPnt(geompy.MakeVertex(0.,0.,0.),geompy.MakeVertex(lf,0.,0.),theName="TheFoundation")

TheModel=geompy.MakePartitionNonSelfIntersectedShape([FaceSoil],[FaceFoundation,TheFoundation],[],[],geompy.ShapeType["FACE"],0,[],0,theName="TheModel")

### >>>>>>>>>>>>>>
### >>> Groups <<<
### <<<<<<<<<<<<<<

ListOfSubFaces=geompy.SubShapeAll(TheModel,geompy.ShapeType["FACE"])
ListOfSubEdges=geompy.SubShapeAll(TheModel,geompy.ShapeType["EDGE"])

###### Groups of faces

dic_of_faces={}
dic_of_faces_groups={}

for obj in ListOfSubFaces:

	cm=geompy.MakeCDG(obj)
	pos=geompy.GetPosition(cm)
	x_cm,y_cm=pos[0],pos[1]
	
	if (round(x_cm,2)==round(.5*lfb,2)):
		key="BelowFoundation"
		dic_of_faces[key]=obj
		dic_of_faces_groups[key]=geompy.CreateGroup(TheModel,geompy.ShapeType["FACE"],theName="GrFace%s"%(key))
		geompy.UnionList(dic_of_faces_groups[key],[dic_of_faces[key]])
	else:
		key="Soil"
		dic_of_faces[key]=obj
		dic_of_faces_groups[key]=geompy.CreateGroup(TheModel,geompy.ShapeType["FACE"],theName="GrFace%s"%(key))
		geompy.UnionList(dic_of_faces_groups[key],[dic_of_faces[key]])

###### Groups of edges

dic_cdg={"BelowFoundationL":(0.,-.5*hfb),
         "BelowFoundationTG":(.5*lf,0.),
         "BelowFoundationTR":(lf+.5*(lfb-lf),0.),
         "BelowFoundationR":(lfb,-.5*hfb),
         "BelowFoundationB":(.5*lfb,-hfb),
         "SoilL":(0.,-hfb-.5*(h-hfb)),
         "SoilB":(.5*l,-h),
         "SoilR":(l,-.5*h),
         "SoilT":(lfb+.5*(l-lfb),0.),}

dic_of_edges={}
dic_of_edges_groups={}

for obj in ListOfSubEdges:
	
	cm=geompy.MakeCDG(obj)
	pos=geompy.GetPosition(cm)
	x_cm,y_cm=round(pos[0],2),round(pos[1],2)
	
	for name,coor in dic_cdg.items():
		
		x,y=round(coor[0],2),round(coor[1],2)

		if ((x_cm==x) and (y==y_cm)):
			
			dic_of_edges[name]=obj
			dic_of_edges_groups[name]=geompy.CreateGroup(TheModel,geompy.ShapeType["EDGE"],theName="GrEdge%s"%(name))
			geompy.UnionList(dic_of_edges_groups[name],[dic_of_edges[name]])

### >>>>>>>>>>>>>>
### Mesh component
### <<<<<<<<<<<<<<

import  SMESH, SALOMEDS
from salome.smesh import smeshBuilder

smesh=smeshBuilder.New()
MeshTheModel=smesh.Mesh(TheModel)
MeshTheModel.SetName("MeshTheModel")

###### 1D algorithms for edges

dic_algo_1d={}
dic_submesh_1d={}

dic_nos={"BelowFoundationL":int(hfb/min_size),
         "BelowFoundationTG":int(lf/min_size),
         "BelowFoundationTR":int((lfb-lf)/min_size),
         "BelowFoundationR":int(hfb/min_size),
         "BelowFoundationB":int(lf/min_size)+int((lfb-lf)/min_size),
         "SoilB":int(l/max_size),
         "SoilR":int(h/max_size),}

dic_sel = {"SoilL":(max_size, min_size),
           "SoilT":(min_size, max_size)}

for k,v in dic_of_edges.items():
	if (k in dic_nos.keys()):
		dic_algo_1d[k]=MeshTheModel.Segment(v)
		dic_algo_1d[k].NumberOfSegments(dic_nos[k])
	if (k in dic_sel.keys()):
		dic_algo_1d[k]=MeshTheModel.Segment(v)
		dic_algo_1d[k].StartEndLength(dic_sel[k][0],dic_sel[k][1])
	dic_submesh_1d[k]=MeshTheModel.GetSubMesh(v,name="SubMesh"+k)
	dic_submesh_1d[k].Compute()

###### 2D algorithms for faces

dic_algo_2d={}
dic_submesh_2d={}

for k,v in dic_of_faces.items():
	if "Soil" in k:
		dic_algo_2d[k]=MeshTheModel.Triangle(smeshBuilder.NETGEN_1D2D,v)
		params=dic_algo_2d[k].Parameters()
		params.SetFineness(4)
		params.SetMaxSize(max_size)
		dic_algo_2d[k].SetName("Triangle2D"+k)
	else:
		dic_algo_2d[k]=MeshTheModel.Quadrangle(v)
		dic_algo_2d[k].SetName("Quadrangle2D"+k)
	dic_submesh_2d[k]=MeshTheModel.GetSubMesh(v,name="SubMesh"+k)
	dic_submesh_2d[k].Compute()

###### Groups

for k,v in dic_of_faces_groups.items():
	MeshTheModel.GroupOnGeom(v)

for k,v in dic_of_edges_groups.items():
	MeshTheModel.GroupOnGeom(v)

###### Export mesh to med file
import os
path=os.getcwd()
MeshTheModel.ExportMED(path+"/mesh_%i_nodes.med"%(MeshTheModel.NbNodes()))