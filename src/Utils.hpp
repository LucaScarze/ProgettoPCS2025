#pragma once

#include <iostream>
#include "PolyhedronMesh.hpp"

using namespace std;

namespace PolyhedronLibrary
{
	void Tetraedro(unsigned int p, unsigned int q,PolyhedronMesh &mesh);
	void Ottaedro(unsigned int p, unsigned int q,PolyhedronMesh &mesh);
	void Icosaedro(unsigned int p, unsigned int q,PolyhedronMesh &mesh);
	void ConstructorPolyhedronCells(unsigned int p,unsigned int q,PolyhedronMesh &mesh); 		//funzione per costruire poliedri geodetici
	PolyhedronMesh DualConstructorPolyhedronCells(PolyhedronMesh &mesh);	//funzione per costruire poliedri geodetici passando dal duale di quelli di partenza
	void Triangulation_Iclass(unsigned int q,int b, int c,PolyhedronMesh &mesh);				//funzione per triangolazione I classe
	void ProiezioneSfera(PolyhedronMesh &mesh);
	void ShortestPath(PolyhedronMesh &mesh,int id_origin,int id_end);
}
