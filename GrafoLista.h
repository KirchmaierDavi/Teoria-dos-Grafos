#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include "No.h"
#include "ListaEncadeada.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

class GrafoLista : public Grafo {
private:
    ListaEncadeada* listaAdj;
    int numVertices;
    bool direcionado;
    bool verticesPonderados;
    bool arestasPonderadas;

public:
    GrafoLista(int num_vertices, bool direcionado, bool vertices_ponderados, bool arestas_ponderadas);
    ~GrafoLista();

    bool ehBipartido() override;
    int nConexo() override;
    int getGrau() override;
    int getOrdem() override;
    bool ehDirecionado() override;
    bool verticePonderado() override;
    bool arestaPonderada() override;
    bool ehCompleto() override;
    bool ehArvore() override;
    bool possuiArticulacao() override;
    bool possuiPonte() override;
    void carregaGrafo(const std::string& filename) override;
    void novoGrafo(const std::string& config_filename) override;

    void addNo(int id, float peso = 0);
    void addAresta(int origem, int destino, float peso = 0);
};

#endif // GRAFOLISTA_H