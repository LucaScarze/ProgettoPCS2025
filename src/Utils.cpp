#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include "Eigen/Eigen"
#include <algorithm>

using namespace std;

namespace PolyhedronLibrary
{
	void Tetraedro(int p,int q,PolyhedronMesh &mesh){
		//formule per ricavare numero vertici, spigoli e facce a partire dai numeri di Schlafli
		mesh.NumCell0Ds = (4*p)/(4-(p-2)*(q-2)); 		//numero vertici poliedro
		mesh.NumCell1Ds = (2*p*q)/(4-(p-2)*(q-2));		//numero lati poliedro
		mesh.NumCell2Ds = (4*q)/(4-(p-2)*(q-2));			//numero facce poliedro
		mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(4, mesh.NumCell0Ds);
		mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
		mesh.Cell1DsExtrema = Eigen::MatrixXi(3, mesh.NumCell1Ds);
		mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		//memorizzo vertici
		vector<vector<int>> Vertici = {{1,1,1},{1,-1,-1},{-1,1,-1},{-1,-1,1}};
		for(unsigned int i=0;i<4;i++)
		{
			for(unsigned int j=0;j<3;j++)
				mesh.Cell0DsCoordinates(j,i) = Vertici[i][j];
			mesh.Cell0DsId.push_back(i);
		}
		
		//memorizzo lati
		vector<vector<int>> Lati = {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}};
		for(unsigned int i=0;i<6;i++)
		{
			for(unsigned int j=0;j<2;j++)
				mesh.Cell1DsExtrema(j,i) = Lati[i][j];
			mesh.Cell1DsId.push_back(i);
		}
		
		//memorizzo facce
		vector<vector<int>> Facce = {{0,1,2},{0,1,3},{0,2,3},{1,2,3}};
		for(unsigned int i=0;i<4;i++)
		{
			mesh.Cell2DsVertices.push_back(vector<unsigned int>(3));
			mesh.Cell2DsEdges.push_back(vector<unsigned int>(3));
			//primo for per memorizzare i vertici della faccia i
			for(unsigned int j=0;j<3;j++)
				mesh.Cell2DsVertices[i][j] = Facce[i][j];
			mesh.Cell2DsId.push_back(i);
			//secondo for per memorizzare i lati della faccia i
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int k=0;k<mesh.NumCell1Ds;k++){
					if(mesh.Cell1DsExtrema(0,k)==Facce[i][j] && mesh.Cell1DsExtrema(1,k) == Facce[i][j+1] || 
						mesh.Cell1DsExtrema(0,k)==Facce[i][j+1] && mesh.Cell1DsExtrema(1,k) == Facce[i][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						mesh.Cell2DsEdges[i][j] = k;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int k=0;k<mesh.NumCell1Ds;k++){
					if(mesh.Cell1DsExtrema(0,k)== Facce[i][2] && mesh.Cell1DsExtrema(1,k) == Facce[i][0] ||
						mesh.Cell1DsExtrema(0,k)==Facce[i][0] && mesh.Cell1DsExtrema(1,k) == Facce[i][2])
					{
						mesh.Cell2DsEdges[i][2] = k;
						break;
					}
			}
		}
	}
	
	void Ottaedro(int p,int q,PolyhedronMesh &mesh){
		//formule per ricavare numero vertici, spigoli e facce a partire dai numeri di Schlafli
		mesh.NumCell0Ds = (4*p)/(4-(p-2)*(q-2)); 		//numero vertici poliedro
		mesh.NumCell1Ds = (2*p*q)/(4-(p-2)*(q-2));		//numero lati poliedro
		mesh.NumCell2Ds = (4*q)/(4-(p-2)*(q-2));			//numero facce poliedro
		mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(4, mesh.NumCell0Ds);
		mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
		mesh.Cell1DsExtrema = Eigen::MatrixXi(3, mesh.NumCell1Ds);
		mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		vector<vector<int>> Vertici = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
		for(unsigned int i=0;i<6;i++)
		{
			for(unsigned int j=0;j<3;j++)
				mesh.Cell0DsCoordinates(j,i) = Vertici[i][j];
			mesh.Cell0DsId.push_back(i);
		}
		vector<vector<int>> Lati = {{0,2},{2,1},{1,3},{3,0},{0,4},{2,4},{1,4},{3,4},{0,5},{2,5},{1,5},{3,5}};
		for(unsigned int i=0;i<12;i++)
		{
			for(unsigned int j=0;j<2;j++)
				mesh.Cell1DsExtrema(j,i) = Lati[i][j];
			mesh.Cell1DsId.push_back(i);
		}
		//memorizzo facce
		vector<vector<int>> Facce = {{0,2,4},{2,1,4},{1,3,4},{3,0,4},{0,5,2},{2,5,1},{1,5,3},{3,5,0}};
		for(unsigned int i=0;i<8;i++)
		{	
			(mesh.Cell2DsVertices).push_back(vector<unsigned int>(3));
			(mesh.Cell2DsEdges).push_back(vector<unsigned int>(3));
			//primo for per memorizzare i vertici della faccia i
			for(unsigned int j=0;j<3;j++)
				mesh.Cell2DsVertices[i][j] = Facce[i][j];
			mesh.Cell2DsId.push_back(i);
			//secondo for per memorizzare i lati della faccia i
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int k=0;k<mesh.NumCell1Ds;k++){
					if(mesh.Cell1DsExtrema(0,k)==Facce[i][j] && mesh.Cell1DsExtrema(1,k) == Facce[i][j+1] || 
						mesh.Cell1DsExtrema(0,k)==Facce[i][j+1] && mesh.Cell1DsExtrema(1,k) == Facce[i][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						mesh.Cell2DsEdges[i][j] = k;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int k=0;k<mesh.NumCell1Ds;k++){
					if(mesh.Cell1DsExtrema(0,k)== Facce[i][2] && mesh.Cell1DsExtrema(1,k) == Facce[i][0] ||
						mesh.Cell1DsExtrema(0,k)==Facce[i][0] && mesh.Cell1DsExtrema(1,k) == Facce[i][2])
					{
						mesh.Cell2DsEdges[i][2] = k;
						break;
					}
			}
		}
	}
	
	void Icosaedro(int p,int q,PolyhedronMesh &mesh){
		//formule per ricavare numero vertici, spigoli e facce a partire dai numeri di Schlafli
		mesh.NumCell0Ds = (4*p)/(4-(p-2)*(q-2)); 		//numero vertici poliedro
		mesh.NumCell1Ds = (2*p*q)/(4-(p-2)*(q-2));		//numero lati poliedro
		mesh.NumCell2Ds = (4*q)/(4-(p-2)*(q-2));			//numero facce poliedro
		mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(4, mesh.NumCell0Ds);
		mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
		mesh.Cell1DsExtrema = Eigen::MatrixXi(3, mesh.NumCell1Ds);
		mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		double phi = (1.0+sqrt(5.0))/2.0;
		vector<vector<double>> Vertici = {{1, phi, 0},{-1, phi, 0},{1, -phi, 0},{-1, -phi, 0},{0, 1, phi},{0, -1, phi},{0, 1, -phi},{0, -1, -phi},
			{phi, 0, 1},{+phi, 0, -1},{-phi, 0, 1},{-phi,0,-1}};
		for(unsigned int i=0;i<12;i++)
		{
			for(unsigned int j=0;j<3;j++)
				mesh.Cell0DsCoordinates(j,i) = Vertici[i][j];
			mesh.Cell0DsId.push_back(i);
		}
		vector<vector<int>> Lati = {{0,1},{0,4},{0,6},{0,8},{0,9},{1,4},{1,6},{1,10},{1,11},{2,3},{2,5},{2,7},{2,8},{2,9},{3,5},
			{3,7},{3,10},{3,11},{4,5},{4,8},{4,10},{5,8},{5,10},{6,7},{6,9},{6,11},{7,9},{7,11},{8,9},{10,11}};
		for(unsigned int i=0;i<30;i++)
		{
			for(unsigned int j=0;j<2;j++)
				mesh.Cell1DsExtrema(j,i) = Lati[i][j];
			mesh.Cell1DsId.push_back(i);
		}
				//memorizzo facce
		vector<vector<int>> Facce = {{0,1,4},{0,4,8},{0,8,9},{0,9,6},{0,6,1},{1,6,11},{1,11,10},{1,10,4},{2,3,5},{2,5,8},{2,8,9},{2,9,7},
			{2,7,3},{3,7,11},{3,11,10},{3,10,5},{4,10,5},{4,5,8},{6,9,7},{6,7,11}};
		for(unsigned int i=0;i<20;i++)
		{
			(mesh.Cell2DsVertices).push_back(vector<unsigned int>(3));
			(mesh.Cell2DsEdges).push_back(vector<unsigned int>(3));
			//primo for per memorizzare i vertici della faccia i
			for(unsigned int j=0;j<3;j++)
				mesh.Cell2DsVertices[i][j] = Facce[i][j];
			mesh.Cell2DsId.push_back(i);
			//secondo for per memorizzare i lati della faccia i
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int k=0;k<mesh.NumCell1Ds;k++){
					if(mesh.Cell1DsExtrema(0,k)==Facce[i][j] && mesh.Cell1DsExtrema(1,k) == Facce[i][j+1] || 
						mesh.Cell1DsExtrema(0,k)==Facce[i][j+1] && mesh.Cell1DsExtrema(1,k) == Facce[i][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						mesh.Cell2DsEdges[i][j] = k;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int k=0;k<mesh.NumCell1Ds;k++){
					if(mesh.Cell1DsExtrema(0,k)== Facce[i][2] && mesh.Cell1DsExtrema(1,k) == Facce[i][0] ||
						mesh.Cell1DsExtrema(0,k)==Facce[i][0] && mesh.Cell1DsExtrema(1,k) == Facce[i][2])
					{
						mesh.Cell2DsEdges[i][2] = k;
						break;
					}
			}
		}
	}
	
	
	void ConstructorPolyhedronCells(int p,int q,int b,int c,PolyhedronMesh &mesh){
		if(q==3)
			Tetraedro(p,q,mesh);
		else if(q==4)
			Ottaedro(p,q,mesh);
		else if(q==5)
			Icosaedro(p,q,mesh);
		
	}



	PolyhedronMesh DualConstructorPolyhedronCells(PolyhedronMesh &mesh){
		PolyhedronMesh dualmesh;
		//costruiamo baricentri
		dualmesh.NumCell0Ds = mesh.NumCell2Ds; //c'è un baricentro per faccia, hanno lo stesso ID
		dualmesh.Cell0DsId.reserve(mesh.NumCell2Ds);
		dualmesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(4, mesh.NumCell2Ds);
		unsigned int id_vertice = 0;
		for(unsigned int i=0;i<mesh.NumCell2Ds;i++) //iteriamo su facce mesh di partenza
		{
			dualmesh.Cell0DsId.push_back(i);
			double x_bar = 0;
			for(unsigned int j=0;j<3;j++)
			{
				id_vertice = mesh.Cell2DsVertices[i][j];
				x_bar += mesh.Cell0DsCoordinates(0,id_vertice);
			}
			dualmesh.Cell0DsCoordinates(0,i) = x_bar/3.0;
			double y_bar = 0;
			for(unsigned int j=0;j<3;j++)
			{
				id_vertice = mesh.Cell2DsVertices[i][j];
				y_bar += mesh.Cell0DsCoordinates(1,id_vertice);
			}
			dualmesh.Cell0DsCoordinates(1,i) = y_bar/3.0;
			double z_bar = 0;
			for(unsigned int j=0;j<3;j++)
			{
				id_vertice = mesh.Cell2DsVertices[i][j];
				z_bar += mesh.Cell0DsCoordinates(2,id_vertice);
			}
			dualmesh.Cell0DsCoordinates(2,i) = z_bar/3.0;
		}
		//costruzione del vicinato di mesh
		mesh.Cell0DsEdgesAdj.reserve(mesh.NumCell0Ds);
		mesh.Cell0DsFacesAdj.reserve(mesh.NumCell0Ds);
		vector<unsigned int> LatiVicini;
		vector<unsigned int> FacceVicine;
		for(unsigned int i=0;i<mesh.NumCell0Ds;i++)
		{
			cout << "lati vicini di " << i <<endl;
			for(unsigned int k=0; k<mesh.NumCell1Ds;k++) //indice colonna matrice Extrema
			{
				if(mesh.Cell1DsExtrema(0,k) == i || mesh.Cell1DsExtrema(1,k) == i)
				{
					LatiVicini.push_back(k);
					cout << k << " ";
				}
			}
			cout << endl;
			cout << "facce vicine di " << i << endl;
			for(unsigned int j=0; j<mesh.NumCell2Ds;j++)
			{
				for(unsigned int h=0;h<3;h++)
				{
					if(mesh.Cell2DsVertices[j][h] == i)
					{
						FacceVicine.push_back(j);
						cout << j << " ";
						break;
					}
				}
			}
			cout << endl;
			mesh.Cell0DsEdgesAdj.push_back(LatiVicini);
			mesh.Cell0DsFacesAdj.push_back(FacceVicine);
			LatiVicini.clear();
			FacceVicine.clear();
		}
		//costruzione Duale
		dualmesh.NumCell1Ds = mesh.NumCell1Ds;
		dualmesh.NumCell2Ds = mesh.NumCell0Ds;
		dualmesh.Cell1DsId.reserve(dualmesh.NumCell1Ds);
		dualmesh.Cell1DsId = mesh.Cell1DsId;
		dualmesh.Cell2DsId.reserve(dualmesh.NumCell2Ds);
		dualmesh.Cell2DsId = mesh.Cell0DsId;
		dualmesh.Cell1DsExtrema = Eigen::MatrixXi::Zero(3, dualmesh.NumCell1Ds);
		dualmesh.Cell2DsVertices.reserve(dualmesh.NumCell2Ds);
		dualmesh.Cell2DsEdges.reserve(dualmesh.NumCell2Ds);
		unsigned int tmp_primo_bar;//variabile per memorizzare primo baricentro
		vector<unsigned int> LatiVisitati; //se lato qua dentro è stato visitato
		LatiVisitati.reserve(mesh.NumCell1Ds);
		unsigned int tmp_secondo_bar; //variabile per memorizzare baricentro successivo per avere l'ordine nella memorizzazione
		unsigned int tmp_lato; //variabile per memorizzare lato adiacente sia a faccia che a vertice
		unsigned int tmp_faccia; //variabile per memorizzare la 2a faccia adiacente a vertice e faccia adiacente trovata nel for
		unsigned int tmp_id_lato; //variabile per memorizzare lato da inserire in dualmesh.Cell2DsEdges di una certa faccia 
		for(unsigned int i=0;i<mesh.NumCell0Ds;i++) //itero su vertici mesh di cui voglio duale
		{
			dualmesh.Cell2DsId.push_back(i);
			dualmesh.Cell2DsVertices.push_back(vector<unsigned int>(mesh.Cell0DsFacesAdj[i].size()));
			dualmesh.Cell2DsEdges.push_back(vector<unsigned int>(mesh.Cell0DsFacesAdj[i].size()));//numero lati faccia nel duale = numero facce vicine a vertice in originale
			for(unsigned int j=0; j<mesh.Cell0DsFacesAdj[i].size();j++) //for su facce vicine
			{
				if(j == 0)
					tmp_primo_bar = mesh.Cell0DsFacesAdj[i][0]; //primo vertice memorizzato
				else
					tmp_primo_bar=tmp_secondo_bar;//così da 2a iterazione in poi i baricentri sono ordinati, primo segue ordine di memorizzazione i facce adiacenti(non ordinata)
				dualmesh.Cell2DsVertices[i][j] = tmp_primo_bar;
				for(unsigned int k=0;k<mesh.Cell2DsEdges[tmp_primo_bar].size();k++)//for su lati faccia tmp_primo_bar per trovare lato adiacente a faccia e vertice i (mi fermo al primo che trovo)
				{
					auto it = find(LatiVisitati.begin(), LatiVisitati.end(),mesh.Cell2DsEdges[tmp_primo_bar][k]);
					if(it == LatiVisitati.end())
					{
						auto it_1 = find(mesh.Cell0DsEdgesAdj[i].begin(), mesh.Cell0DsEdgesAdj[i].end(),mesh.Cell2DsEdges[tmp_primo_bar][k]);
						if(it_1!=mesh.Cell0DsEdgesAdj[i].end())
						{
							tmp_lato = mesh.Cell2DsEdges[tmp_primo_bar][k];
							LatiVisitati.push_back(mesh.Cell2DsEdges[tmp_primo_bar][k]);
							break;
						}
					}
				}
				//altro for per trovare altra faccia vicina con stesso lato adiacente al vertice
				for(unsigned int h=0;h<mesh.Cell0DsFacesAdj[i].size();h++)//h indica faccia adiacente a vertice i
				{
					if(mesh.Cell0DsFacesAdj[i][h]!=tmp_primo_bar)
					{
						auto it_2 = find(mesh.Cell2DsEdges[mesh.Cell0DsFacesAdj[i][h]].begin(), mesh.Cell2DsEdges[mesh.Cell0DsFacesAdj[i][h]].end(),tmp_lato);
						if(it_2!=mesh.Cell2DsEdges[mesh.Cell0DsFacesAdj[i][h]].end())
						{
							tmp_faccia = mesh.Cell0DsFacesAdj[i][h]; //è indice baricentro adiacente
							break;
						}
					}
				}
				//bisogna iterare su matrice dualmesh.Cell1DsExtrema per aggiungere lato se non è già esistente, altrimenti per memorizzare id
				for(unsigned int s=0;s<dualmesh.NumCell1Ds; s++)
				{
					if(dualmesh.Cell1DsExtrema(0,s)==0 && dualmesh.Cell1DsExtrema(1,s) == 0)
					{
						dualmesh.Cell1DsExtrema(0,s) = tmp_primo_bar;
						dualmesh.Cell1DsExtrema(1,s) = tmp_faccia;
						tmp_id_lato = s;
						break;
					}
					else if(dualmesh.Cell1DsExtrema(0,s)==tmp_primo_bar && dualmesh.Cell1DsExtrema(1,s) == tmp_faccia || 
							dualmesh.Cell1DsExtrema(0,s)==tmp_faccia && dualmesh.Cell1DsExtrema(1,s) == tmp_primo_bar)
					{
						tmp_id_lato = s;
						break;
					}
				}
				dualmesh.Cell2DsEdges[i][j]=tmp_id_lato; //aggiungo lato trovato alla faccia i
				tmp_secondo_bar = tmp_faccia;
			}
			LatiVisitati.clear();
		}
		return dualmesh;
	}
}