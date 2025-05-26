#pragma once

#include <iostream>
#include "PolyhedronMesh.hpp"

using namespace std;

namespace PolyhedronLibrary
{
	void Tetraedro(PolyhedronMesh &mesh);
	void Ottaedro(PolyhedronMesh &mesh);
	void Icosaedro(PolyhedronMesh &mesh);
	void ConstructorPolyhedronCells(int p,int q,int b,int c,PolyhedronMesh &mesh); 		//funzione per costruire poliedri geodetici
	PolyhedronMesh DualConstructorPolyhedronCells(PolyhedronMesh &mesh);	//funzione per costruire poliedri geodetici passando dal duale di quelli di partenza
	void Triangulation_Iclass(PolyhedronMesh &mesh);				//funzione per triangolazione I classe
	void Triangulation_IIclass(PolyhedronMesh &mesh);				//funzione per triangolazione II classe
	
}