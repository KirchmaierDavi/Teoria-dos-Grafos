#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include "Lista.h"
#include "No.h"
#include <string>

class GrafoLista : public Grafo {
private:
    Lista* listaAdj;
    No** nos;
    int numArestas;

public:
    GrafoLista(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);
    ~GrafoLista();

    bool ehCompleto() override;
    int nConexo() override;
    bool ehArvore() override;
    bool possuiPonte() override;
    bool possuiArticulacao() override;
    void carregaGrafo(const std::string& arquivo) override;
    void novoGrafo(const std::string& arquivoConfig) override;
    void deleta_no(int idNo) override;
    void adicionaNo(int idNo) override;
    void novaAresta(int origem, int destino, float peso) override;
    bool verificarCobertura(int* cobertura, int tamanhoCobertura) override;
    int* coberturaArestas(float alpha, int maxIteracoes, int* tamanhoCobertura) override;
    int* construcaoGulosa(int* tamanhoCobertura) override;
    void removeAresta(int idNoOrigem, int idNoDestino, bool direcionado) override;
    virtual int* coberturaArestasReativa(int maxIteracoes, int tamanhoListaAlpha, int* tamanhoCobertura) override;
    
private:
    int* construcaoGulosaRandomizada(float alpha, int* tamanhoCobertura) override;
    int* buscaLocal(int* solucao, int tamanhoSolucao, int* tamanhoMelhorSolucao) override;
    No* getNoPeloId(int id) { return nos[id]; }
    int* algoritmoGuloso(int* tamanhoCobertura);
    virtual void atualizaProbabilidades(float* alphas, float* probabilidades, float* valores, int tamanhoLista) override;
};

#endif