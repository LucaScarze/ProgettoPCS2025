#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

namespace PolyhedronLibrary{
	
	struct PolyhedronMesh{
		unsigned int NumCell0Ds; //Cell0Ds:elenco vertici
		unsigned int NumCell1Ds; //Cell1Ds:elenco lati
		unsigned int NumCell2Ds; //Cell2Ds:elenco facce
		
		vector<unsigned int> Cell0DsId;
		vector<unsigned int> Cell1DsId;
		vector<unsigned int> Cell2DsId;
		
		Eigen::MatrixXd Cell0DsCoordinates;
		vector<vector<unsigned int>> Cell0DsVerticesAdj; //vertici adiacenti, usato per ShortestPath
		vector<vector<unsigned int>> Cell0DsEdgesAdj; //lati adiacenti a vertici,usato per duale
		vector<vector<unsigned int>> Cell0DsFacesAdj; //facce adiacenti ai vertici,usato per duale
		Eigen::MatrixXi Cell1DsExtrema;
		vector<vector<unsigned int>> Cell2DsVertices;//vertici delle facce
		vector<vector<unsigned int>> Cell2DsEdges; // lati delle facce
		vector<double> VerticesInShortestPath; //=1 se vertice in cammino minimo, 0 altrimenti (double per tipo di export)
		vector<double> EdgesInShortestPath; //=1 se lato in cammino minimo, 0 altrimenti (double per tipo di export)
	};
}
