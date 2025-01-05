#include "Grafo.h"
#include "Aresta.h"
#include <iostream>
#include <fstream>

using namespace std;

void Grafo::novoGrafo(const string &configFile) {
    ifstream file(configFile);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo " << configFile << endl;
        return;
    }

    int numNos, direcionado, ponderadoVertices, ponderadoArestas;
    file >> numNos >> direcionado >> ponderadoVertices >> ponderadoArestas;

    int* pesosVertices = nullptr;
    if (ponderadoVertices) {
        pesosVertices = new int[numNos];
        for (int i = 0; i < numNos; ++i) {
            file >> pesosVertices[i];
        }
    }

    Aresta** arestas = new Aresta*[numNos * numNos];
    int numArestas = 0;

    while (!file.eof()) {
        int origem, destino;
        float peso = 1.0;
        file >> origem >> destino;
        if (ponderadoArestas) {
            file >> peso;
        }
        arestas[numArestas++] = new Aresta(destino, origem, peso);
    }

    delete[] pesosVertices;
     for (int i = 0; i < numArestas; ++i) {
        delete arestas[i];
    }
    delete[] arestas;

    file.close();
}
