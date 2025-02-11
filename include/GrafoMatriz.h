#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include "No.h"


class GrafoMatriz : public Grafo {
private:
    int** matrizAdj; // Matriz de adjacência
    int numVertices;
    No** nos;

public:
    GrafoMatriz(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);
    void deleta_no(int idNo);
    ~GrafoMatriz();
    int getGrau(int vertice) override;
    bool ehCompleto() override;
    bool ehBipartido() override;
    int nConexo() override;
    bool ehArvore() override;
    bool possuiPonte() override;
    bool possuiArticulacao() override;

    void removeAresta(int idNoOrigem, int idNoDestino, bool direcionado);

    void carregaGrafo(const std::string& arquivo) override;
    void novoGrafo(const std::string& arquivoConfig) override;
    void adicionaNo(int idNo) override;
};

#endif // GRAFOMATRIZ_H
