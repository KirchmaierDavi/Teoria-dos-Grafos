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

    virtual int* construcaoGulosaRandomizada(float alpha, int* tamanhoCobertura) override;
    virtual int* buscaLocal(int* solucao, int tamanhoSolucao, int* tamanhoMelhorSolucao) override;
    virtual bool verificarCobertura(int* cobertura, int tamanhoCobertura) override;
    virtual int* construcaoGulosa(int* tamanhoCobertura) override;

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

    virtual int* coberturaArestas(float alpha, int maxIteracoes, int* tamanhoCobertura) override;
};

#endif // GRAFOMATRIZ_H
