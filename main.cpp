#include <iostream>
#include <fstream>
#include "PolyhedronMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;
using namespace PolyhedronLibrary;

int main(int argc, char* argv[]){
	PolyhedronMesh mesh;
	//controllo input
	if(argc==5){
		unsigned int p = stoi(argv[1]);
		unsigned int q = stoi(argv[2]);
		int b = stoi(argv[3]);
		int c = stoi(argv[4]);
		if(b<0 || c<0)
		{
			cerr << "errore su b o c" <<endl;
			return 1;
		}
		else
		{
			if(p==3){
				if(q==3 ||q==4 || q==5)
				{
					ConstructorPolyhedronCells(p,q,mesh);
					if(b>1 || c>1)
						Triangulation_Iclass(q,b,c,mesh);
					ProiezioneSfera(mesh);
				}
				else{
					cerr << "errore in input su q con p=3"<<endl;
					return 1;
				}
			}
			else if(q==3){
				if(p==4 || p==5){
					ConstructorPolyhedronCells(q,p,mesh); //scambiati p e q per avere duale di partenza
					if(b>1 || c>1)
						Triangulation_Iclass(p,b,c,mesh);
					mesh = DualConstructorPolyhedronCells(mesh);
					ProiezioneSfera(mesh);
				}
				else{
					cerr << "errore in input su p con q == 3" << endl;
					return 1;
				}
			}
			else
			{
				cerr << "errore su p e q"<<endl;
				return 1;
			}
		}
	}
	else if(argc==7){
		unsigned int p = stoi(argv[1]);
		unsigned int q = stoi(argv[2]);
		int b = stoi(argv[3]);
		int c = stoi(argv[4]);
		int id_origin = stoi(argv[5]);
		int id_end = stoi(argv[6]);
		if(id_origin < 0 || id_end < 0)
		{
			cerr << "errore sugli id dei vertici di cui si vuole cammino minimo, almeno uno dei due negativo" << endl;
			return 1;
		}
		else if(b<0 || c<0)
		{
			cerr << "errore su b o c" <<endl;
			return 1;
		}
		else
		{
			if(p==3){
				if(q==3 ||q==4 || q==5)
				{
					ConstructorPolyhedronCells(p,q,mesh);
					if(b>1 || c>1)
						Triangulation_Iclass(q,b,c,mesh);
					if(id_origin > mesh.NumCell0Ds || id_end >mesh.NumCell0Ds)
					{
						cerr<<"almeno uno tra id dei vertici di cui si vuole cammino minimo non è presente nella lista dei vertici"<<endl;
						return 1;
					}
					else
					{
						ShortestPath(mesh,id_origin,id_end); 
						ProiezioneSfera(mesh);
					}
				}
				else{
					cerr << "errore in input su q con p=3"<<endl;
					return 1;
				}
			}
			else if(q==3){
				if(p==4 || p==5){
					ConstructorPolyhedronCells(q,p,mesh); //scambiati p e q per avere duale di partenza
					if(b>1 || c>1)
						Triangulation_Iclass(p,b,c,mesh);
					mesh = DualConstructorPolyhedronCells(mesh);
 					if(id_origin > mesh.NumCell0Ds || id_end >mesh.NumCell0Ds)
					{
						cerr<<"almeno uno tra id dei vertici di cui si vuole cammino minimo non è presente nella lista dei vertici"<<endl;
						return 1;
					}
					else{
						ShortestPath(mesh,id_origin,id_end);
						ProiezioneSfera(mesh);
					}
				}
				else{
					cerr << "errore in input su p con q == 3" << endl;
					return 1;
				}
			}
			else
			{
				cerr << "errore su p e q"<<endl;
				return 1;
			}
		}		
	}


	//scrittura output
	ofstream file0("./Cell0Ds.txt");
	file0 << "Id,x,y,z" <<endl;
	for(unsigned int i = 0;i<mesh.NumCell0Ds;i++)
	{
		file0 << mesh.Cell0DsId[i] << "," << mesh.Cell0DsCoordinates(0,i) << "," << mesh.Cell0DsCoordinates(1,i) << "," 
			<< mesh.Cell0DsCoordinates(2,i) << endl;
	}
	file0.close();
		
	ofstream file1 ("./Cell1Ds.txt");
	file1 << "Id,Origin,End" <<endl;
	for(unsigned int i = 0;i<mesh.NumCell1Ds;i++)
		file1 << mesh.Cell1DsId[i] << "," << mesh.Cell1DsExtrema(0,i) << "," << mesh.Cell1DsExtrema(1,i) << endl;
	file1.close();
		
	ofstream file2 ("./Cell2Ds.txt");
	file2 << "Id,NumVertices,Vertices,NumEdges,Edges" <<endl;
	for(unsigned int i = 0;i<mesh.NumCell2Ds;i++)
	{
		file2 << mesh.Cell2DsId[i] << ",3";
		for(unsigned int j=0;j<3;j++)
			file2 << "," << mesh.Cell2DsVertices[i][j];
		file2 << ",3";
		for(unsigned int j=0;j<3;j++)
			file2 << ";" << mesh.Cell2DsEdges[i][j];
		file2 << endl;
	}
	file2.close();
		
	ofstream file3 ("./Cell3Ds.txt");
	file3 << "Id,NumVertices,Vertices,NumEdges,Edges,NumFaces,Faces" << endl;
	file3 << "0," << mesh.NumCell0Ds;
	for(unsigned int i = 0;i<mesh.NumCell0Ds;i++)
		file3 << "," << i;
	file3 << "," << mesh.NumCell1Ds;
	for(unsigned int i = 0;i<mesh.NumCell1Ds;i++)
		file3 << "," << i;
 	file3 << "," << mesh.NumCell2Ds;
	for(unsigned int i=0;i<mesh.NumCell2Ds;i++)
		file3 << "," << i ; 
	file3.close();
	
	if(argc == 5)
	{
		Gedim::UCDUtilities utilities;
		utilities.ExportPoints("./Cell0Ds.inp",
							   mesh.Cell0DsCoordinates);

		utilities.ExportSegments("./Cell1Ds.inp",
								 mesh.Cell0DsCoordinates,
								 mesh.Cell1DsExtrema);			
	}
	else if(argc==7)
	{
		vector<Gedim::UCDProperty<double>> VerticiInCamminoMinimo;
		VerticiInCamminoMinimo.resize(1);
		VerticiInCamminoMinimo[0].Label = "VerticiInCamminoMinimo";
		VerticiInCamminoMinimo[0].UnitLabel = "Id";
		VerticiInCamminoMinimo[0].Size = mesh.NumCell0Ds;
		VerticiInCamminoMinimo[0].NumComponents = 1;
		VerticiInCamminoMinimo[0].Data=mesh.VerticesInShortestPath.data();
		
		vector<Gedim::UCDProperty<double>> LatiInCamminoMinimo;
		LatiInCamminoMinimo.resize(1);
		LatiInCamminoMinimo[0].Label = "LatiInCamminoMinimo";
		LatiInCamminoMinimo[0].UnitLabel = "Id";
		LatiInCamminoMinimo[0].Size = mesh.NumCell1Ds;
		LatiInCamminoMinimo[0].NumComponents = 1;
		LatiInCamminoMinimo[0].Data=mesh.EdgesInShortestPath.data(); 
		
		
		Gedim::UCDUtilities utilities;
		utilities.ExportPoints("./Cell0Ds.inp",
							   mesh.Cell0DsCoordinates ,
							   VerticiInCamminoMinimo);

		utilities.ExportSegments("./Cell1Ds.inp",
								 mesh.Cell0DsCoordinates,
								 mesh.Cell1DsExtrema,
								 {},
								 LatiInCamminoMinimo);					 
	}

    return 0;
}
	
