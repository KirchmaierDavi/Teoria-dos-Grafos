#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"

class GrafoMatriz : public Grafo {
private:
    static const int MAX_VERTICES = 100;
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
    bool direcionado;
    bool vertices_ponderados;
    bool arestas_ponderadas;

public:
    GrafoMatriz(int num_vertices, bool direcionado, bool vertices_ponderados, bool arestas_ponderadas);

    bool ehBipartido() const override;
    int nConexo() const override;
    int getGrau() const override;
    int getOrdem() const override;
    bool ehDirecionado() const override;
    bool verticePonderado() const override;
    bool arestaPonderada() const override;
    bool ehCompleto() const override;
    bool ehArvore() const override;
    bool possuiArticulacao() const override;
    bool possuiPonte() const override;
    void carregaGrafo(const std::string& filename) override;
    void novoGrafo(const std::string& config_filename) override;
};

#endif // GRAFOMATRIZ_H