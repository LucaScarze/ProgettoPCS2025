#pragma once
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "../src/PolyhedronMesh.hpp"
#include "../src/Utils.hpp"
// https://google.github.io/googletest/

namespace PolyhedronLibrary {

TEST(PolyhedronMeshTest, NoVerticiRipetutiInFacce) //verifichiamo che le facce non presentino vertici ripetuti
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	bool Ripetizione = false;
	unsigned int n=0;
	for(unsigned int i=0;i<mesh.NumCell0Ds;i++)
	{
		if(Ripetizione==false)
		{
			for(unsigned int j=0;j<mesh.NumCell2Ds;j++)
			{
				if(Ripetizione==false)
				{
					n=0;
					for(unsigned int k=0;k<3;k++)
					{
						if(mesh.Cell2DsVertices[j][k]==i)
							n++;
					}
					if(n>1)
					{
						Ripetizione = true;
					}
				}
				else 
					break;
			}
		}
		else
			break;
	}
    ASSERT_EQ(Ripetizione, false); 
}

TEST(PolyhedronMeshTest, NoLatiRipetutiInFacce) //verifichiamo che le facce non presentino lati ripetuti
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	bool Ripetizione = false;
	unsigned int n=0;
	for(unsigned int l=0;l<mesh.NumCell1Ds;l++)
	{
		if(Ripetizione==false)
		{
			for(unsigned int j=0;j<mesh.NumCell2Ds;j++)
			{
				if(Ripetizione==false)
				{
					n=0;
					for(unsigned int k=0;k<3;k++)
					{
						if(mesh.Cell2DsEdges[j][k]==l)
							n++;
					}
					if(n>1)
					{
						Ripetizione = true;
					}
				}
				else 
					break;
			}
		}
		else
			break;
	}
    ASSERT_EQ(Ripetizione, false); 
}

//Ripetiamo gli stessi test per la triangolazione
TEST(PolyhedronMeshTest, NoVerticiRipetutiInFacceTriangolazione) 
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	Triangulation_Iclass(5,4,0,mesh);
	bool Ripetizione = false;
	unsigned int n=0;
	for(unsigned int i=0;i<mesh.NumCell0Ds;i++)
	{
		if(Ripetizione==false)
		{
			for(unsigned int j=0;j<mesh.NumCell2Ds;j++)
			{
				if(Ripetizione==false)
				{
					n=0;
					for(unsigned int k=0;k<3;k++)
					{
						if(mesh.Cell2DsVertices[j][k]==i)
							n++;
					}
					if(n>1)
					{
						Ripetizione = true;
					}
				}
				else 
					break;
			}
		}
		else
			break;
	}
    ASSERT_EQ(Ripetizione, false); 
}

TEST(PolyhedronMeshTest, NoLatiRipetutiInFacceTriangolazione) 
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	Triangulation_Iclass(5,4,0,mesh);
	bool Ripetizione = false;
	unsigned int n=0;
	for(unsigned int l=0;l<mesh.NumCell1Ds;l++)
	{
		if(Ripetizione==false)
		{
			for(unsigned int j=0;j<mesh.NumCell2Ds;j++)
			{
				if(Ripetizione==false)
				{
					n=0;
					for(unsigned int k=0;k<3;k++)
					{
						if(mesh.Cell2DsEdges[j][k]==l)
							n++;
					}
					if(n>1)
					{
						Ripetizione = true;
					}
				}
				else 
					break;
			}
		}
		else
			break;
	}
    ASSERT_EQ(Ripetizione, false); 
}

//controlliamo che il numero di facce,di lati e di vertici della triangolazione sia corretto
TEST(PolyhedronMeshTest, NumeroVerticiTriangolazione) 
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	Triangulation_Iclass(5,4,0,mesh);
	bool Correttezza = true;
	unsigned int V = 162;
	if(mesh.Cell0DsId.size() != V)
		Correttezza = false;
	else if(mesh.NumCell0Ds != V)
		Correttezza = false;
    ASSERT_EQ(Correttezza, true); 
}

TEST(PolyhedronMeshTest, NumeroLatiTriangolazione) 
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	Triangulation_Iclass(5,4,0,mesh);
	bool Correttezza = true;
	unsigned int E = 480;
	if(mesh.Cell1DsId.size() != E)
		Correttezza = false;
	else if(mesh.NumCell1Ds != E)
		Correttezza = false;
    ASSERT_EQ(Correttezza, true); 
}

TEST(PolyhedronMeshTest, NumeroFacceTriangolazione) 
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	Triangulation_Iclass(5,4,0,mesh);
	bool Correttezza = true;
	unsigned int F = 320;
	if(mesh.Cell2DsId.size() != F)
		Correttezza = false;
	else if(mesh.NumCell2Ds != F)
		Correttezza = false;
    ASSERT_EQ(Correttezza, true); 
}

//controllo valenze dei vertici dopo la triangolazione
TEST(PolyhedronMeshTest, ValenzaVerticiTriangolazione) 
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	Triangulation_Iclass(5,4,0,mesh);
	unsigned int n_five_teo = 12; //numero vertici con valenza 5
	unsigned int n_six_teo = 150; //numero vertici con valenza 6
	unsigned int n_five = 0;
	unsigned int n_six = 0;
	unsigned int n = 0;
	for(unsigned int i = 0;i<mesh.NumCell0Ds;i++)
	{
		n=0;
		for(unsigned int k=0;k<mesh.NumCell1Ds;k++)
		{
			if(mesh.Cell1DsExtrema(0,k)==i || mesh.Cell1DsExtrema(1,k)==i)
				n++;
		}
		if(n==5)
			n_five++;
		else if(n==6)
			n_six++;
	}
	ASSERT_EQ(n_five,n_five_teo);
	ASSERT_EQ(n_six,n_six_teo);
}

//controllo che nel duale non ci siano lati che abbiano origine = fine
TEST(PolyhedronMeshTest, ControlloOrigineFineLatiDuale) 
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	Triangulation_Iclass(5,4,0,mesh);
	mesh = DualConstructorPolyhedronCells(mesh);
	bool NoRipetizione=true;
	for(unsigned int k=0;k<mesh.NumCell1Ds;k++)
	{
		if(mesh.Cell1DsExtrema(0,k)==mesh.Cell1DsExtrema(1,k))
		{
			NoRipetizione=false;
			break;
		}
	}
	ASSERT_EQ(NoRipetizione,true);
}

//verifichiamo che punti siano proiettati sulla sfera
TEST(PolyhedronMeshTest, ControlloProiezioneSfera) 
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	Triangulation_Iclass(5,4,0,mesh); //triangolazione per avere maggior numero di punti su cui avviene il controllo
	ProiezioneSfera(mesh);
	bool PuntiSuSfera = true;
	double x=0;
	double y=0;
	double z=0;
	double norma = 0;
	for(unsigned int i=0;i<mesh.NumCell0Ds;i++)
	{
		x = mesh.Cell0DsCoordinates(0,i);
		y = mesh.Cell0DsCoordinates(1,i);
		z = mesh.Cell0DsCoordinates(2,i);
		norma = sqrt(x*x+y*y+z*z);
		if(abs(norma-1)>1e-12)
		{
			PuntiSuSfera = false;
			break;
		}
	}
	ASSERT_EQ(PuntiSuSfera,true);
}

//controllo che il cammino trovato da ShortestPath sia esistente e coerente(cioè numero vertici = numero lati +1 e lati scelti coerenti con vertici scelti)
TEST(PolyhedronMeshTest, ControlloShortestPath) 
{
	PolyhedronMesh mesh;
	ConstructorPolyhedronCells(3,5,mesh);
	Triangulation_Iclass(5,4,0,mesh); //triangolazione per avere maggior numero di punti su cui avviene il controllo
	ShortestPath(mesh,0,13);
	bool Corretto = true;
	unsigned int n_vertici = 0;
	unsigned int n_lati = 0;
	for(unsigned int i=0;i<mesh.NumCell0Ds;i++)
	{
		if(mesh.VerticesInShortestPath[i]==1)
			n_vertici++;
	}
	for(unsigned int k=0;k<mesh.NumCell1Ds;k++)
	{
		if(mesh.EdgesInShortestPath[k]==1)
			n_lati++;
	}
	if(n_vertici!=(n_lati+1))
		Corretto = false;
 	vector<bool> trovato;
	trovato.reserve(n_vertici);
	if(Corretto==true)
	{
		for(unsigned int i=0;i<mesh.NumCell0Ds;i++)//ciclo su tutti vertici
		{
			if(mesh.VerticesInShortestPath[i]==1)//cerco solo quelli in shortestpath
			{
				for(unsigned int k=0;k<mesh.NumCell1Ds;k++)//ciclo su lati
				{
					if(mesh.EdgesInShortestPath[k]==1)//cerco solo quelli in shortestpath
					{
						if(mesh.Cell1DsExtrema(0,k)==i || mesh.Cell1DsExtrema(1,k)==i)//controllo se vertice è in un estremo
							trovato.push_back(true);
					}
				}
			}
		}
	}
	if(trovato.size()!=(2*n_vertici-2))
		Corretto=false; 
	ASSERT_EQ(Corretto,true);
	
}
}
