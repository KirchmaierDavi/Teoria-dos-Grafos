#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"

class GrafoMatriz : public Grafo
{
private:
    static const int MAX_VERTICES = 100;
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
    bool direcionado;
    bool vertices_ponderados;
    bool arestas_ponderadas;

public:
    GrafoMatriz(int num_vertices, bool direcionado, bool vertices_ponderados, bool arestas_ponderadas);

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
    void carregaGrafo(std::string &filename);
    void novoGrafo(std::string &config_filename);
};

#endif // GRAFOMATRIZ_H