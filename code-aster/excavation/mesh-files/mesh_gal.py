# -*- coding: utf-8 -*-
import sys
import salome
import random
salome.salome_init()
import GEOM
import SALOMEDS
from salome.geom import geomBuilder
geompy=geomBuilder.New()
gg=salome.ImportComponentGUI("GEOM")

### >>>>>>>>>>
### Input data
### <<<<<<<<<<

r=2.6         # radius of the gallery
r_edz=2.5 * r # radius of the EDZ
h=50.*r       # height of the model
l=25.*r       # width of the model
y_gal=-490.   # position of the center of the gallery

### >>>>>>>>>>>>>>>>>>
### Geometry component
### <<<<<<<<<<<<<<<<<<

from math import *
import numpy as np

###### Plane with a hole for the gallery (TheModel)
TheFace=geompy.MakeFaceHW(l,h,1)
TheFaceT=geompy.MakeTranslation(TheFace,.5*l,0.,0.)
TheCircleForWall=geompy.MakeDiskR(r,1,)
TheCircleForEdz=geompy.MakeDiskR(r_edz,1)
TheModelT=geompy.MakePartition([TheFaceT],[TheCircleForEdz,TheCircleForWall],[],[],geompy.ShapeType["FACE"],0,[],0)
TheModel=geompy.MakeTranslation(TheModelT,0.,y_gal,0.,theName="TheModel")

###### Groups
SubFaceList=geompy.SubShapeAll(TheModel,geompy.ShapeType["FACE"])
SubEdgeList=geompy.SubShapeAll(TheModel,geompy.ShapeType["EDGE"])
SubVertexList=geompy.SubShapeAll(TheModel,geompy.ShapeType["VERTEX"])

######### Faces
DicOfFaces={}
DicGroupOfFaces={}

def f_cond_faces(d):
	
	dic={
		"FaceCOx":1 if(d>r_edz) else 0,
		"FaceVoid":1 if(0.<d<r) else 0,
		"FaceEdz":1 if(r<d<r_edz) else 0,
	}

	return dic

for obj in SubFaceList:
	
	pcdg=geompy.MakeCDG(obj)
	coords=np.array(geompy.PointCoordinates(pcdg))-np.array([0.,y_gal,0.])
	d_pcdg=sqrt(np.dot(coords,coords))
	d_faces=f_cond_faces(d_pcdg)

	for name,b in d_faces.items():
		if b==1:
			DicOfFaces[name]=obj
			DicGroupOfFaces["Gr%s"%(name)]=geompy.CreateGroup(TheModel,geompy.ShapeType["FACE"],theName="Gr%s"%(name))
			geompy.UnionList(DicGroupOfFaces["Gr%s"%(name)],[DicOfFaces[name]])

######### Edges
DicOfEdges={}
DicGroupOfEdges={}

tol=.01
d_r=2.*r/pi        # center of mass for an arc of radius r
d_redz=2.*r_edz/pi # center of mass for an arc of radius r_edz

def f_cond_edges(d,coor):
	
	dic={
		"EdgeGal":1 if (d_r-tol<=d<=d_r+tol) else 0,
		"EdgeEdz": 1 if (d_redz-tol<=d<=d_redz+tol) else 0,
		"EdgeLeftVoid": 1 if (-tol<=d<=tol) else 0,
		"EdgeLeftEdzT": 1 if ((r<d<r_edz) and (coor[1]>0)) else 0,
		"EdgeLeftEdzB": 1 if ((r<d<r_edz) and (coor[1]<0)) else 0,
		"EdgeLeftCOxT": 1 if ((coor[1]>r_edz) and (-tol<coor[0]<tol)) else 0,
		"EdgeLeftCOxB": 1 if ((coor[1]<-r_edz) and (-tol<coor[0]<tol)) else 0,
		"EdgeTop": 1 if (.5*h-tol<coor[1]<.5*h+tol) else 0,
		"EdgeBottom": 1 if (-.5*h-tol<coor[1]<-.5*h+tol) else 0,
		"EdgeRight": 1 if (l-tol<coor[0]<l+tol) else 0,
	}

	return dic

for obj in SubEdgeList:
	
	pcdg=geompy.MakeCDG(obj)
	coords=np.array(geompy.PointCoordinates(pcdg))-np.array([0.,y_gal,0.])
	d_pcdg=sqrt(np.dot(coords,coords))
	d_edges=f_cond_edges(d_pcdg,coords)

	for name,b in d_edges.items():
		if b==1:
			DicOfEdges[name]=obj
			DicGroupOfEdges["Gr%s"%(name)]=geompy.CreateGroup(TheModel,geompy.ShapeType["EDGE"],theName="Gr%s"%(name))
			geompy.UnionList(DicGroupOfEdges["Gr%s"%(name)],[DicOfEdges[name]])

lst_left_edges_exc=[]
lst_left_edges_equ=[]
for name,obj in DicOfEdges.items():
	if (("Left" in name) and ("Void" not in name)):
		lst_left_edges_exc.append(obj)
	if ("Left" in name):
		lst_left_edges_equ.append(obj)

DicGroupOfEdges["GrEdgeLeftEqu"]=geompy.CreateGroup(TheModel,geompy.ShapeType["EDGE"],theName="GrEdgeLeftEqu")
geompy.UnionList(DicGroupOfEdges["GrEdgeLeftEqu"],lst_left_edges_equ)

DicGroupOfEdges["GrEdgeLeftExc"]=geompy.CreateGroup(TheModel,geompy.ShapeType["EDGE"],theName="GrEdgeLeftExc")
geompy.UnionList(DicGroupOfEdges["GrEdgeLeftExc"],lst_left_edges_exc)

######### Get the reversed edges for mesh hypothesis
LstRevEdges = []
for k,v in DicOfEdges.items():
	if (("LeftEdz" in k) or ("LeftCOx" in k)):
		ps,pe=geompy.SubShapeAll(v,geompy.ShapeType["VERTEX"])
		c_ps=np.array(geompy.PointCoordinates(ps))-np.array([0.,y_gal,0.])
		c_pe=np.array(geompy.PointCoordinates(pe))-np.array([0.,y_gal,0.])
		d_ps=sqrt(np.dot(c_ps,c_ps))
		d_pe=sqrt(np.dot(c_pe,c_pe))
		if (d_ps>d_pe):
			LstRevEdges.append(k)

### >>>>>>>>>>>>>>
### Mesh component
### <<<<<<<<<<<<<<

import  SMESH,SALOMEDS
from salome.smesh import smeshBuilder

smesh=smeshBuilder.New()
MeshTheModel=smesh.Mesh(TheModel)
MeshTheModel.SetName("MeshTheModel")

###### Define some characteristic sizes
SizeCellGal=25.e-2
MaxSize=h/10.
NOSGal=int(pi*r/SizeCellGal)

###### 2D algorithms for faces
DicAlgo2D={}
DicSubMesh2D={}

for k, v in DicOfFaces.items():
	if "Edz" in k:
		DicAlgo2D[k]=MeshTheModel.Quadrangle(v)
		DicAlgo2D[k].SetName("Quadrangle2D"+k)
	else:
		DicAlgo2D[k]=MeshTheModel.Triangle(smeshBuilder.NETGEN_1D2D,v)
		DicAlgo2D[k].SetMaxSize(MaxSize)
		DicAlgo2D[k].SetFineness(smeshBuilder.VeryFine)
		DicAlgo2D[k].SetName("Triangle2D"+k)
	DicSubMesh2D[k]=MeshTheModel.GetSubMesh(v,name="SubMesh"+k)

###### 1D algorithms for edges
DicAlgo1D={}

for k,v in DicOfEdges.items():
	if ((("Gal" in k) or ("Edz" in k)) and ("LeftEdz" not in k)):
		DicAlgo1D[k]=MeshTheModel.Segment(v)
		DicAlgo1D[k].NumberOfSegments(NOSGal)
	elif (("LeftEdz" in k) and (k not in LstRevEdges)):
		DicAlgo1D[k]=MeshTheModel.Segment(v)
		DicAlgo1D[k].StartEndLength(SizeCellGal,SizeCellGal*r_edz/r)
	elif (("LeftEdz" in k) and (k in LstRevEdges)):
		DicAlgo1D[k]=MeshTheModel.Segment(v)
		DicAlgo1D[k].StartEndLength(SizeCellGal*r_edz/r,SizeCellGal)
	elif (("LeftCOx" in k) and (k not in LstRevEdges)):
		DicAlgo1D[k]=MeshTheModel.Segment(v)
		DicAlgo1D[k].StartEndLength(SizeCellGal*r_edz/r,MaxSize)
	elif (("LeftCOx" in k) and (k in LstRevEdges)):
		DicAlgo1D[k]=MeshTheModel.Segment(v)
		DicAlgo1D[k].StartEndLength(MaxSize,SizeCellGal*r_edz/r)
	else:
		DicAlgo1D[k] = MeshTheModel.Segment(v)
		DicAlgo1D[k].NumberOfSegments(int(h/MaxSize))
	DicAlgo1D[k].SetName("Algo1D"+k)

MeshTheModel.Compute()

###### Groups
for k,v in DicGroupOfFaces.items():
	MeshTheModel.GroupOnGeom(v)

for k,v in DicGroupOfEdges.items():
	MeshTheModel.GroupOnGeom(v)

###### Export mesh to med file
###### Export mesh to med file
import os
path=os.getcwd()
MeshTheModel.ExportMED(path+"/mesh_%i_nodes.med"%(MeshTheModel.NbNodes()))