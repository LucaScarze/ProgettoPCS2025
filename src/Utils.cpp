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
	void Tetraedro(unsigned int p,unsigned int q,PolyhedronMesh &mesh){
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
	
	void Ottaedro(unsigned int p,unsigned int q,PolyhedronMesh &mesh){
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
	
	void Icosaedro(unsigned int p,unsigned int q,PolyhedronMesh &mesh){
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
	
	
	void ConstructorPolyhedronCells(unsigned int p,unsigned int q,int b,int c,PolyhedronMesh &mesh){
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
			for(unsigned int k=0; k<mesh.NumCell1Ds;k++) //indice colonna matrice Extrema
			{
				if(mesh.Cell1DsExtrema(0,k) == i || mesh.Cell1DsExtrema(1,k) == i)
					LatiVicini.push_back(k);
			}
			for(unsigned int j=0; j<mesh.NumCell2Ds;j++)
			{
				for(unsigned int h=0;h<3;h++)
				{
					if(mesh.Cell2DsVertices[j][h] == i)
					{
						FacceVicine.push_back(j);
						break;
					}
				}
			}
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
	

	
	void Triangulation_Iclass(unsigned int q,int b,int c,PolyhedronMesh &mesh){
		unsigned int n;
		if(b==0 && c>0)
			n=c;
		else
			n=b;	
		unsigned int T = n*n;
		unsigned int NewNumCell0Ds;
		unsigned int NewNumCell1Ds;
		unsigned int NewNumCell2Ds;
		if(q==3)
		{
			NewNumCell0Ds = 2*T+2;
			NewNumCell1Ds = 6*T;
			NewNumCell2Ds = 4*T;
		}
		else if(q==4)
		{
			NewNumCell0Ds = 4*T+2;
			NewNumCell1Ds = 12*T;
			NewNumCell2Ds = 8*T;
		}
		else
		{
			NewNumCell0Ds = 10*T+2;
			NewNumCell1Ds = 30*T;
			NewNumCell2Ds = 20*T;
		}
		vector<unsigned int> LatiTriangolati; //vettore che contiene lati già coinvolti in triangolazione
		vector<unsigned int> LatiSovrascritti; //vettore che contiene lati già sovrasrctitti da "sottolati" 
		unsigned int h = mesh.NumCell0Ds;//indice da cui partire per memorizzare nuovi vertici
		unsigned int k = 0;//indice per memorizzare nuovi lati
		unsigned int t = 0;//indice per memorizzare nuove facce
		unsigned int old_facce = mesh.NumCell2Ds;//memorizzo numero facce su cui iterare
		MatrixXi OrdineTriangolazioneLato = Eigen::MatrixXi::Zero(3,mesh.NumCell1Ds); //matrice in cui prima riga=primo vertice, seconda riga=secondo vertice lati
		MatrixXi FirstNuoviVerticiLato = Eigen::MatrixXi::Zero(n-1,mesh.NumCell1Ds);//prima triangolazione lato
		//prepariamo struttura mesh ad aggiunta nuovi punti,lati e facce
		mesh.Cell0DsId.reserve(NewNumCell0Ds);
		mesh.Cell0DsCoordinates.conservativeResize(4, NewNumCell0Ds);
		mesh.Cell1DsId.reserve(NewNumCell1Ds);
		mesh.Cell1DsExtrema.resize(3, NewNumCell1Ds); //non conservative perchè non salviamo vecchi lati
		mesh.Cell2DsId.reserve(NewNumCell2Ds);
		mesh.Cell2DsVertices.reserve(NewNumCell2Ds);
		mesh.Cell2DsEdges.reserve(NewNumCell2Ds);
		LatiTriangolati.reserve(mesh.NumCell1Ds);
		LatiSovrascritti.reserve(mesh.NumCell1Ds);
		//"scartiamo" id vecchi lati e vecchie facce
		mesh.Cell1DsId.clear();
		mesh.Cell2DsId.clear();
		//per memorizzare nuove facce
		vector<vector<unsigned int>> NewCell2DsVertices;
		vector<vector<unsigned int>> NewCell2DsEdges;
		NewCell2DsEdges.reserve(NewNumCell2Ds);
		NewCell2DsVertices.reserve(NewNumCell2Ds);
		//definiamo variabili per memorizzare i lati e i vertici originali delle facce alleggerendo la scrittura
		unsigned int lato1;
		unsigned int lato2;
		unsigned int lato3;
		unsigned int vertice1;
		unsigned int vertice2;
		unsigned int vertice3;
		//incrementi per definire ciascun punto 
		double delta_x;
		double delta_y;
		double delta_z;
		vector<vector<unsigned int>> VerticiLivelloS; //vertici interni al "livello" s
		VerticiLivelloS.reserve(n-2);//n-2 livelli interni
		vector<unsigned int> livelloS;
		for(unsigned int i=0;i<old_facce;i++)//for su facce 
		{
			MatrixXi NuoviVerticiLato = Eigen::MatrixXi::Zero(n-1, 3); //in colonna contiene id nuovi vertici della triangolazione sul lato nella faccia i
			lato1 = mesh.Cell2DsEdges[i][0];
			lato2 = mesh.Cell2DsEdges[i][1];
			lato3 = mesh.Cell2DsEdges[i][2];
			vertice1 = mesh.Cell2DsVertices[i][0];
			vertice2 = mesh.Cell2DsVertices[i][1];
			vertice3 = mesh.Cell2DsVertices[i][2];
			//definiamo nuovi punti sui lati se non già esistenti
			auto it_1 = find(LatiTriangolati.begin(), LatiTriangolati.end(),lato1);
			if(it_1 == LatiTriangolati.end())
			{
				OrdineTriangolazioneLato(0,lato1) = vertice1;
				OrdineTriangolazioneLato(1,lato1) = vertice2;
				delta_x = (mesh.Cell0DsCoordinates(0,vertice2)-mesh.Cell0DsCoordinates(0,vertice1))/n;
				delta_y = (mesh.Cell0DsCoordinates(1,vertice2)-mesh.Cell0DsCoordinates(1,vertice1))/n;
				delta_z = (mesh.Cell0DsCoordinates(2,vertice2)-mesh.Cell0DsCoordinates(2,vertice1))/n;
				for(unsigned int j=0;j<n-1;j++)
				{
					mesh.Cell0DsId.push_back(h);
					mesh.Cell0DsCoordinates(0,h) = mesh.Cell0DsCoordinates(0,vertice1)+(j+1)*delta_x;
					mesh.Cell0DsCoordinates(1,h) = mesh.Cell0DsCoordinates(1,vertice1)+(j+1)*delta_y;
					mesh.Cell0DsCoordinates(2,h) = mesh.Cell0DsCoordinates(2,vertice1)+(j+1)*delta_z;
					FirstNuoviVerticiLato(j,lato1)=h;//lo memorizzo per confronti futuri
					NuoviVerticiLato(j,0)=h;
					h++;
				}
				LatiTriangolati.push_back(lato1);
			}
			else if(vertice1 == OrdineTriangolazioneLato(0,lato1) && vertice2 == OrdineTriangolazioneLato(1,lato1)) //controllo se ordine è lo stesso di OrdineTriangolazioneLato, sennò bisogna invertire
			{
				for(unsigned int l=0;l<n-1;l++)
					NuoviVerticiLato(l,0)= FirstNuoviVerticiLato(l,lato1); //nuovi vertici salvati con ordine faccia originale
			}
			else
			{
				for(unsigned int l=0;l<n-1;l++)
					NuoviVerticiLato(l,0)= FirstNuoviVerticiLato(n-2-l,lato1);//nuovi vertici salvati in ordine opposto
			}
			auto it_2 = find(LatiTriangolati.begin(), LatiTriangolati.end(),lato2);
			if(it_2 == LatiTriangolati.end())
			{
				OrdineTriangolazioneLato(0,lato2) = vertice2;
				OrdineTriangolazioneLato(1,lato2) = vertice3;
				delta_x = (mesh.Cell0DsCoordinates(0,vertice3)-mesh.Cell0DsCoordinates(0,vertice2))/n;
				delta_y = (mesh.Cell0DsCoordinates(1,vertice3)-mesh.Cell0DsCoordinates(1,vertice2))/n;
				delta_z = (mesh.Cell0DsCoordinates(2,vertice3)-mesh.Cell0DsCoordinates(2,vertice2))/n;
				for(unsigned int j=0;j<n-1;j++)
				{
					mesh.Cell0DsId.push_back(h);
					mesh.Cell0DsCoordinates(0,h) = mesh.Cell0DsCoordinates(0,vertice2)+(j+1)*delta_x;
					mesh.Cell0DsCoordinates(1,h) = mesh.Cell0DsCoordinates(1,vertice2)+(j+1)*delta_y;
					mesh.Cell0DsCoordinates(2,h) = mesh.Cell0DsCoordinates(2,vertice2)+(j+1)*delta_z;
					FirstNuoviVerticiLato(j,lato2)=h;
					NuoviVerticiLato(j,1)=h;
					h++;
				}
			LatiTriangolati.push_back(lato2);
			}
			else if(vertice2 == OrdineTriangolazioneLato(0,lato2) && vertice3 == OrdineTriangolazioneLato(1,lato2))
			{
				for(unsigned int l=0;l<n-1;l++)
					NuoviVerticiLato(l,1)= FirstNuoviVerticiLato(l,lato2);
			}
			else
			{
				for(unsigned int l=0;l<n-1;l++)
					NuoviVerticiLato(l,1)= FirstNuoviVerticiLato(n-2-l,lato2);	
			}
			auto it_3 = find(LatiTriangolati.begin(), LatiTriangolati.end(),lato3);
			if(it_3 == LatiTriangolati.end())
			{
				OrdineTriangolazioneLato(0,lato3) = vertice3;
				OrdineTriangolazioneLato(1,lato3) = vertice1;
				delta_x = (mesh.Cell0DsCoordinates(0,vertice1)-mesh.Cell0DsCoordinates(0,vertice3))/n;
				delta_y = (mesh.Cell0DsCoordinates(1,vertice1)-mesh.Cell0DsCoordinates(1,vertice3))/n;
				delta_z = (mesh.Cell0DsCoordinates(2,vertice1)-mesh.Cell0DsCoordinates(2,vertice3))/n;
				for(unsigned int j=0;j<n-1;j++)
				{
					mesh.Cell0DsId.push_back(h);
					mesh.Cell0DsCoordinates(0,h) = mesh.Cell0DsCoordinates(0,vertice3)+(j+1)*delta_x;
					mesh.Cell0DsCoordinates(1,h) = mesh.Cell0DsCoordinates(1,vertice3)+(j+1)*delta_y;
					mesh.Cell0DsCoordinates(2,h) = mesh.Cell0DsCoordinates(2,vertice3)+(j+1)*delta_z;
					FirstNuoviVerticiLato(j,lato3)=h;
					NuoviVerticiLato(j,2)=h;
					h++;
				}
			LatiTriangolati.push_back(lato3);
			}
			else if(vertice3 == OrdineTriangolazioneLato(0,lato3) && vertice1 == OrdineTriangolazioneLato(1,lato3))
			{
				for(unsigned int l=0;l<n-1;l++)
					NuoviVerticiLato(l,2)= FirstNuoviVerticiLato(l,lato3);
			}
			else
			{
				for(unsigned int l=0;l<n-1;l++)
					NuoviVerticiLato(l,2)= FirstNuoviVerticiLato(n-2-l,lato3);
			}
			//definizione vertici "interni" alla faccia
			//considerando lato1 come base del triangolo, "salendo" verso il vertice opposto(vertice3) ad ogni "livello" vertici triangolazione sugli altri
			//due lati corrisponde un numero di nuovi vertici interni che diminuisce di 1 (a partire da n-1, che è su lato1)
			for(unsigned int s=0;s<n-2;s++) //for sui "livelli"
			{
				delta_x = (mesh.Cell0DsCoordinates(0,NuoviVerticiLato(s,1))-mesh.Cell0DsCoordinates(0,NuoviVerticiLato(n-2-s,2)))/(n-1-s);
				delta_y = (mesh.Cell0DsCoordinates(1,NuoviVerticiLato(s,1))-mesh.Cell0DsCoordinates(1,NuoviVerticiLato(n-2-s,2)))/(n-1-s);
				delta_z = (mesh.Cell0DsCoordinates(2,NuoviVerticiLato(s,1))-mesh.Cell0DsCoordinates(2,NuoviVerticiLato(n-2-s,2)))/(n-1-s);
				for(unsigned int r=0;r<n-2-s;r++)//numero di nuovi punti su "livello" s 
				{ 
					mesh.Cell0DsId.push_back(h);
					//NuoviVerticiLato[lato3][n-2-s] per rispettare l'ordine della numerazione nuovi vertici sui lati
					mesh.Cell0DsCoordinates(0,h) = mesh.Cell0DsCoordinates(0,NuoviVerticiLato(n-2-s,2))+(r+1)*delta_x;
					mesh.Cell0DsCoordinates(1,h) = mesh.Cell0DsCoordinates(1,NuoviVerticiLato(n-2-s,2))+(r+1)*delta_y;
					mesh.Cell0DsCoordinates(2,h) = mesh.Cell0DsCoordinates(2,NuoviVerticiLato(n-2-s,2))+(r+1)*delta_z;
					livelloS.push_back(h);
					h++;
				}
				VerticiLivelloS.push_back(livelloS);
				livelloS.clear();
			}
			//costruzione dei lati: prima definiamo nuovi lati su ciascun lato della faccia originale se non già esistenti
			auto it_1_sovra = find(LatiSovrascritti.begin(),LatiSovrascritti.end(),lato1);
			if(it_1_sovra == LatiSovrascritti.end())
			{
				mesh.Cell1DsId.push_back(k);
				mesh.Cell1DsExtrema(0,k) = vertice1;
				mesh.Cell1DsExtrema(1,k) = NuoviVerticiLato(0,0);
				k++;
				for(unsigned int j=0;j<n-2;j++)
				{
					mesh.Cell1DsId.push_back(k);
					mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(j,0);
					mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(j+1,0);
					k++;
				}
				mesh.Cell1DsId.push_back(k);
				mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(n-2,0);
				mesh.Cell1DsExtrema(1,k)=vertice2;
				k++;
				LatiSovrascritti.push_back(lato1);
			}
			auto it_2_sovra = find(LatiSovrascritti.begin(),LatiSovrascritti.end(),lato2);
			if(it_2_sovra == LatiSovrascritti.end())
			{
				mesh.Cell1DsId.push_back(k);				
				mesh.Cell1DsExtrema(0,k) = vertice2;
				mesh.Cell1DsExtrema(1,k) = NuoviVerticiLato(0,1);
				k++;
				for(unsigned int j=0;j<n-2;j++)
				{
					mesh.Cell1DsId.push_back(k);
					mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(j,1);
					mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(j+1,1);
					k++;
				}
				mesh.Cell1DsId.push_back(k);				
				mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(n-2,1);
				mesh.Cell1DsExtrema(1,k)=vertice3;
				k++;
				LatiSovrascritti.push_back(lato2);
			}
			auto it_3_sovra = find(LatiSovrascritti.begin(),LatiSovrascritti.end(),lato3);
			if(it_3_sovra == LatiSovrascritti.end())
			{
				mesh.Cell1DsId.push_back(k);
				mesh.Cell1DsExtrema(0,k) = vertice3;
				mesh.Cell1DsExtrema(1,k) = NuoviVerticiLato(0,2);
				k++;
				for(unsigned int j=0;j<n-2;j++)
				{
					mesh.Cell1DsId.push_back(k);
					mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(j,2);
					mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(j+1,2);
					k++;
				}
				mesh.Cell1DsId.push_back(k);
				mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(n-2,2);
				mesh.Cell1DsExtrema(1,k)=vertice1;
				k++;
				LatiSovrascritti.push_back(lato3);
			}
			//costruzione lati interni
			//colleghiamo prima lato1 al primo livello
			mesh.Cell1DsId.push_back(k);
			mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(0,0);
			mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(n-2,2);
			k++;
			mesh.Cell1DsId.push_back(k);
			mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(0,0);
			mesh.Cell1DsExtrema(1,k)=VerticiLivelloS[0][0];
			k++;
			for(unsigned int f=0;f<n-3;f++)//for sui vertici centrali di NuoviVerticiLato
			{
				mesh.Cell1DsId.push_back(k);
				mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(f+1,0);
				mesh.Cell1DsExtrema(1,k)=VerticiLivelloS[0][f];
				k++;
				mesh.Cell1DsId.push_back(k);
				mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(f+1,0);
				mesh.Cell1DsExtrema(1,k)=VerticiLivelloS[0][f+1];
				k++;
			}
			mesh.Cell1DsId.push_back(k);
			mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(n-2,0);
			mesh.Cell1DsExtrema(1,k)=VerticiLivelloS[0][n-3];
			k++;
			mesh.Cell1DsId.push_back(k);
			mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(n-2,0);
			mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(0,1);
			k++;			
	 		//costruiamo i lati degli altri livelli(manca ultima "riga orizzontale")
			for(unsigned int s=0;s<n-2;s++)
			{	
				//costruzione lati orizzontali livelloS
				mesh.Cell1DsId.push_back(k);
				mesh.Cell1DsExtrema(0,k) = NuoviVerticiLato(n-2-s,2);
				mesh.Cell1DsExtrema(1,k) = VerticiLivelloS[s][0];
				k++;
				for(unsigned int f=0;f<n-3-s;f++)
				{
					mesh.Cell1DsId.push_back(k);
					mesh.Cell1DsExtrema(0,k)=VerticiLivelloS[s][f];
					mesh.Cell1DsExtrema(1,k)=VerticiLivelloS[s][f+1];
					k++;
				}
				mesh.Cell1DsId.push_back(k);
				mesh.Cell1DsExtrema(0,k) = VerticiLivelloS[s][n-3-s];
				mesh.Cell1DsExtrema(1,k) = NuoviVerticiLato(s,1);
				k++;
			}
			mesh.Cell1DsId.push_back(k);
			mesh.Cell1DsExtrema(0,k)=NuoviVerticiLato(0,2);
			mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(n-2,1);
			k++;
			//costruzione lati obliqui sui livelli(ultimo a parte)
			for(unsigned int s=0;s<n-3;s++)
			{
				for(unsigned int f=0;f<n-2-s;f++) 
				{
					if(f==0)
					{
						mesh.Cell1DsId.push_back(k);
						mesh.Cell1DsExtrema(0,k)=VerticiLivelloS[s][0];
						mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(n-2-s-1,2);
						k++;
 						mesh.Cell1DsId.push_back(k);
						mesh.Cell1DsExtrema(0,k)=VerticiLivelloS[s][0];
						mesh.Cell1DsExtrema(1,k)=VerticiLivelloS[s+1][0];
						k++; 
					}
					else if(f<n-3-s)
					{
						mesh.Cell1DsId.push_back(k);
						mesh.Cell1DsExtrema(0,k)=VerticiLivelloS[s][f];
						mesh.Cell1DsExtrema(1,k)=VerticiLivelloS[s+1][f-1];
						k++;
						mesh.Cell1DsId.push_back(k);
						mesh.Cell1DsExtrema(0,k)=VerticiLivelloS[s][f];
						mesh.Cell1DsExtrema(1,k)=VerticiLivelloS[s+1][f];
						k++;
					}
					else
					{
						mesh.Cell1DsId.push_back(k);
						mesh.Cell1DsExtrema(0,k)=VerticiLivelloS[s][n-3-s];
						mesh.Cell1DsExtrema(1,k)=VerticiLivelloS[s+1][n-3-s-1];
						k++;
						mesh.Cell1DsId.push_back(k);
 						mesh.Cell1DsExtrema(0,k)=VerticiLivelloS[s][n-3-s];
						mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(s+1,1);
						k++; 
					}
				}	
			}
			mesh.Cell1DsId.push_back(k);
			mesh.Cell1DsExtrema(0,k)=VerticiLivelloS[n-3][0];//c'è solo un vertice su ultimo livello
			mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(0,2);
			k++;
			mesh.Cell1DsId.push_back(k);
 			mesh.Cell1DsExtrema(0,k)=VerticiLivelloS[n-3][0];
			mesh.Cell1DsExtrema(1,k)=NuoviVerticiLato(n-2,1);
			k++; 
			//costruzione delle facce
			//costruiamo prime facce da lato1 al livello 0
			//costruzione facce "orientate" come faccia originale
			//costruzione faccia con vertice1
 			mesh.Cell2DsId.push_back(t);
			NewCell2DsVertices.push_back(vector<unsigned int>(3));
			NewCell2DsVertices[t][0] = vertice1;
			NewCell2DsVertices[t][1] = NuoviVerticiLato(0,0);
			NewCell2DsVertices[t][2] = NuoviVerticiLato(n-2,2);
			NewCell2DsEdges.push_back(vector<unsigned int>(3));
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						NewCell2DsEdges[t][j] = l;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
					{
						NewCell2DsEdges[t][2] = l;
						break;
					}
			}
			t++; 
 			//costruzione facce interne
			for(unsigned int f=0;f<n-2;f++)
			{
				mesh.Cell2DsId.push_back(t);
				NewCell2DsVertices.push_back(vector<unsigned int>(3));
				NewCell2DsVertices[t][0] = NuoviVerticiLato(f,0);
				NewCell2DsVertices[t][1] = NuoviVerticiLato(f+1,0);
				NewCell2DsVertices[t][2] = VerticiLivelloS[0][f];
				NewCell2DsEdges.push_back(vector<unsigned int>(3));
				for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
				{
					//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
					for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
						{
							NewCell2DsEdges[t][j] = l;
							break;
						}
					}
				}
				//memorizziamo lato che va da ultimo vertice al primo
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
						{
							NewCell2DsEdges[t][2] = l;
							break;
						}
				}
				t++;
			}
			//costruzione faccia con vertice 2
			mesh.Cell2DsId.push_back(t);
			NewCell2DsVertices.push_back(vector<unsigned int>(3));
			NewCell2DsVertices[t][0] = NuoviVerticiLato(n-2,0);
			NewCell2DsVertices[t][1] = vertice2;
			NewCell2DsVertices[t][2] = NuoviVerticiLato(0,1);
			NewCell2DsEdges.push_back(vector<unsigned int>(3));
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						NewCell2DsEdges[t][j] = l;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
					{
						NewCell2DsEdges[t][2] = l;
						break;
					}
			}
			t++;
			//costruzione facce "orientate" al contrario della faccia originale
			mesh.Cell2DsId.push_back(t);
			NewCell2DsVertices.push_back(vector<unsigned int>(3));
			NewCell2DsVertices[t][0] = NuoviVerticiLato(0,0);
			NewCell2DsVertices[t][1] = VerticiLivelloS[0][0];
			NewCell2DsVertices[t][2] = NuoviVerticiLato(n-2,2);
			NewCell2DsEdges.push_back(vector<unsigned int>(3));
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						NewCell2DsEdges[t][j] = l;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
					{
						NewCell2DsEdges[t][2] = l;
						break;
					}
			}
			t++;
			for(unsigned int f=1;f<n-2;f++)
			{
				mesh.Cell2DsId.push_back(t);
				NewCell2DsVertices.push_back(vector<unsigned int>(3));
				NewCell2DsVertices[t][0] = NuoviVerticiLato(f,0);
				NewCell2DsVertices[t][1] = VerticiLivelloS[0][f];
				NewCell2DsVertices[t][2] = VerticiLivelloS[0][f-1];
				NewCell2DsEdges.push_back(vector<unsigned int>(3));
				for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
				{
					//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
					for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
						{
							NewCell2DsEdges[t][j] = l;
							break;
						}
					}
				}
				//memorizziamo lato che va da ultimo vertice al primo
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
						{
							NewCell2DsEdges[t][2] = l;
							break;
						}
				}
				t++;
			}
			mesh.Cell2DsId.push_back(t);
			NewCell2DsVertices.push_back(vector<unsigned int>(3));
			NewCell2DsVertices[t][0] = NuoviVerticiLato(n-2,0);
			NewCell2DsVertices[t][1] = NuoviVerticiLato(0,1);
			NewCell2DsVertices[t][2] = VerticiLivelloS[0][n-3];
			NewCell2DsEdges.push_back(vector<unsigned int>(3));
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						NewCell2DsEdges[t][j] = l;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
					{
						NewCell2DsEdges[t][2] = l;
						break;
					}
			}
			t++;
			//costruzione facce dal livello 0 all'ultimo livello
			for(unsigned int s=0;s<n-3;s++)
			{
				//costruzione facce "orientate" come faccia originale
				mesh.Cell2DsId.push_back(t);
				NewCell2DsVertices.push_back(vector<unsigned int>(3));
				NewCell2DsVertices[t][0] = NuoviVerticiLato(n-2-s,2);
				NewCell2DsVertices[t][1] = VerticiLivelloS[s][0];
				NewCell2DsVertices[t][2] = NuoviVerticiLato(n-2-s-1,2);
				NewCell2DsEdges.push_back(vector<unsigned int>(3));
				for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
				{
					//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
					for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
						{
							NewCell2DsEdges[t][j] = l;
							break;
						}
					}
				}
				//memorizziamo lato che va da ultimo vertice al primo
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
						{
							NewCell2DsEdges[t][2] = l;
							break;
						}
				}
				t++;
				for(unsigned int f=0;f<n-3-s;f++)
				{
					mesh.Cell2DsId.push_back(t);
					NewCell2DsVertices.push_back(vector<unsigned int>(3));
					NewCell2DsVertices[t][0] = VerticiLivelloS[s][f];
					NewCell2DsVertices[t][1] = VerticiLivelloS[s][f+1];
					NewCell2DsVertices[t][2] = VerticiLivelloS[s+1][f];
					NewCell2DsEdges.push_back(vector<unsigned int>(3));
					for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
					{
						//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
						for(unsigned int l=0;l<NewNumCell1Ds;l++){
							if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
								mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
							{
								NewCell2DsEdges[t][j] = l;
								break;
							}
						}
					}
					//memorizziamo lato che va da ultimo vertice al primo
					for(unsigned int l=0;l<NewNumCell1Ds;l++){
							if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
								mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
							{
								NewCell2DsEdges[t][2] = l;
								break;
							}
					}
					t++;
				}
				mesh.Cell2DsId.push_back(t);
				NewCell2DsVertices.push_back(vector<unsigned int>(3));
				NewCell2DsVertices[t][0] = VerticiLivelloS[s][n-3-s];
				NewCell2DsVertices[t][1] = NuoviVerticiLato(s,1);
				NewCell2DsVertices[t][2] = NuoviVerticiLato(s+1,1);
				NewCell2DsEdges.push_back(vector<unsigned int>(3));
				for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
				{
					//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
					for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
						{
							NewCell2DsEdges[t][j] = l;
							break;
						}
					}
				}
				//memorizziamo lato che va da ultimo vertice al primo
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
						{
							NewCell2DsEdges[t][2] = l;
							break;
						}
				}
				t++;
				//costruzione facce "orientate" al contrario
				mesh.Cell2DsId.push_back(t);
				NewCell2DsVertices.push_back(vector<unsigned int>(3));
				NewCell2DsVertices[t][0] = VerticiLivelloS[s][0];
				NewCell2DsVertices[t][1] = VerticiLivelloS[s+1][0];
				NewCell2DsVertices[t][2] = NuoviVerticiLato(n-2-s-1,2);
				NewCell2DsEdges.push_back(vector<unsigned int>(3));
				for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
				{
					//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
					for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
						{
							NewCell2DsEdges[t][j] = l;
							break;
						}
					}
				}
				//memorizziamo lato che va da ultimo vertice al primo
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
						{
							NewCell2DsEdges[t][2] = l;
							break;
						}
				}
				t++;
				for(unsigned int f=1;f<n-3-s;f++)
				{
					mesh.Cell2DsId.push_back(t);
					NewCell2DsVertices.push_back(vector<unsigned int>(3));
					NewCell2DsVertices[t][0] = VerticiLivelloS[s][f];
					NewCell2DsVertices[t][1] = VerticiLivelloS[s+1][f];
					NewCell2DsVertices[t][2] = VerticiLivelloS[s+1][f-1];
					NewCell2DsEdges.push_back(vector<unsigned int>(3));
					for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
					{
						//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
						for(unsigned int l=0;l<NewNumCell1Ds;l++){
							if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
								mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
							{
								NewCell2DsEdges[t][j] = l;
								break;
							}
						}
					}
					//memorizziamo lato che va da ultimo vertice al primo
					for(unsigned int l=0;l<NewNumCell1Ds;l++){
							if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
								mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
							{
								NewCell2DsEdges[t][2] = l;
								break;
							}
					}
					t++;
				}
				mesh.Cell2DsId.push_back(t);
				NewCell2DsVertices.push_back(vector<unsigned int>(3));
				NewCell2DsVertices[t][0] = VerticiLivelloS[s][n-3-s];
				NewCell2DsVertices[t][1] = NuoviVerticiLato(s+1,1);
				NewCell2DsVertices[t][2] = VerticiLivelloS[s+1][n-3-s-1];
				NewCell2DsEdges.push_back(vector<unsigned int>(3));
				for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
				{
					//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
					for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
						{
							NewCell2DsEdges[t][j] = l;
							break;
						}
					}
				}
				//memorizziamo lato che va da ultimo vertice al primo
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
						if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
							mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
						{
							NewCell2DsEdges[t][2] = l;
							break;
						}
				}
				t++;
			}
			//ultimo livello
			//facce "orientate" come faccia originale
			mesh.Cell2DsId.push_back(t);
			NewCell2DsVertices.push_back(vector<unsigned int>(3));
			NewCell2DsVertices[t][0] = NuoviVerticiLato(1,2);
			NewCell2DsVertices[t][1] = VerticiLivelloS[n-3][0];
			NewCell2DsVertices[t][2] = NuoviVerticiLato(0,2);
			NewCell2DsEdges.push_back(vector<unsigned int>(3));
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						NewCell2DsEdges[t][j] = l;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
					{
						NewCell2DsEdges[t][2] = l;
						break;
					}
			}
			t++;
			mesh.Cell2DsId.push_back(t);
			NewCell2DsVertices.push_back(vector<unsigned int>(3));
			NewCell2DsVertices[t][0] = VerticiLivelloS[n-3][0];
			NewCell2DsVertices[t][1] = NuoviVerticiLato(n-3,1);
			NewCell2DsVertices[t][2] = NuoviVerticiLato(n-2,1);
			NewCell2DsEdges.push_back(vector<unsigned int>(3));
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						NewCell2DsEdges[t][j] = l;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
					{
						NewCell2DsEdges[t][2] = l;
						break;
					}
			}
			t++;
			//faccia "orientata" al contrario
			mesh.Cell2DsId.push_back(t);
			NewCell2DsVertices.push_back(vector<unsigned int>(3));
			NewCell2DsVertices[t][0] = VerticiLivelloS[n-3][0];
			NewCell2DsVertices[t][1] = NuoviVerticiLato(n-2,1);
			NewCell2DsVertices[t][2] = NuoviVerticiLato(0,2);
			NewCell2DsEdges.push_back(vector<unsigned int>(3));
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						NewCell2DsEdges[t][j] = l;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
					{
						NewCell2DsEdges[t][2] = l;
						break;
					}
			}
			t++;				
			//ultima faccia sopra
			mesh.Cell2DsId.push_back(t);
			NewCell2DsVertices.push_back(vector<unsigned int>(3));
			NewCell2DsVertices[t][0] = NuoviVerticiLato(0,2);
			NewCell2DsVertices[t][1] = NuoviVerticiLato(n-2,1);
			NewCell2DsVertices[t][2] = vertice3;
			NewCell2DsEdges.push_back(vector<unsigned int>(3));
			for(unsigned int j=0;j<2;j++) //facciamo a parte il lato che va da ultimo vertice al primo
			{
				//ciclo sulla matrice Extrema per trovare colonna a cui corrisponde mio lato
				for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j+1] || 
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][j+1] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][j]) //non importa origine e fine, basta trovare lati concatenati
					{
						NewCell2DsEdges[t][j] = l;
						break;
					}
				}
			}
			//memorizziamo lato che va da ultimo vertice al primo
			for(unsigned int l=0;l<NewNumCell1Ds;l++){
					if(mesh.Cell1DsExtrema(0,l)== NewCell2DsVertices[t][2] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][0] ||
						mesh.Cell1DsExtrema(0,l)==NewCell2DsVertices[t][0] && mesh.Cell1DsExtrema(1,l) == NewCell2DsVertices[t][2])
					{
						NewCell2DsEdges[t][2] = l;
						break;
					}
			}
			t++;
			VerticiLivelloS.clear();
		}
		mesh.NumCell0Ds = mesh.Cell0DsId.size();
		mesh.NumCell1Ds = mesh.Cell1DsId.size();
		mesh.NumCell2Ds = mesh.Cell2DsId.size();
		mesh.Cell2DsVertices.clear();
		mesh.Cell2DsEdges.clear();
		mesh.Cell2DsVertices = NewCell2DsVertices;
		mesh.Cell2DsEdges = NewCell2DsEdges;
		
	}
	
	void ProiezioneSfera(PolyhedronMesh &mesh)
	{
		double norma = 0;
		for(unsigned int i=0;i<mesh.NumCell0Ds;i++)
		{
			norma = sqrt(mesh.Cell0DsCoordinates(0,i)*mesh.Cell0DsCoordinates(0,i)+
			mesh.Cell0DsCoordinates(1,i)*mesh.Cell0DsCoordinates(1,i)+
			mesh.Cell0DsCoordinates(2,i)*mesh.Cell0DsCoordinates(2,i));
			for(unsigned int j=0;j<3;j++)
				mesh.Cell0DsCoordinates(j,i) = (mesh.Cell0DsCoordinates(j,i))/norma;
		}
	}
}