#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include "No.h"

// Evitar duplicar 'ordem' e 'numVertices'; usar 'ordem' como base
class GrafoMatriz : public Grafo
{
private:
    int **matrizAdj;
    No **nos;
    int capacidade;

public:
    GrafoMatriz(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);
    virtual ~GrafoMatriz();
    void deleta_no(int idNo);
    bool ehCompleto() override;
    int nConexo() override;
    bool ehArvore() override;
    bool possuiPonte() override;
    bool possuiArticulacao() override;
    void removeAresta(int idNoOrigem, int idNoDestino, bool direcionado);
    void carregaGrafo(const std::string &arquivo) override;
    void novoGrafo(const std::string &arquivoConfig) override;
    void adicionaNo(int idNo) override;
    void novaAresta(int origem, int destino, float peso = 1.0) override;
};

#endif // GRAFOMATRIZ_H
