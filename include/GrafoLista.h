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

    bool ehCompleto();
    int nConexo();
    bool ehArvore();
    bool possuiPonte();
    bool possuiArticulacao();
    void carregaGrafo(const std::string& arquivo);
    void novoGrafo(const std::string& arquivoConfig);
    void deleta_no(int idNo);
    void adicionaNo(int idNo);
    void removeAresta(int idNoOrigem, int idNoDestino, bool direcionado);
    void novaAresta(int origem, int destino, float peso);
    bool verificarCobertura(int* cobertura, int tamanhoCobertura);
    int* coberturaArestas(float alpha, int maxIteracoes, int* tamanhoCobertura);

private:
    int* construcaoGulosaRandomizada(float alpha, int* tamanhoCobertura);
    int* buscaLocal(int* solucao, int tamanhoSolucao, int* tamanhoMelhorSolucao);
    No* getNoPeloId(int id) { return nos[id]; }
    int* algoritmoGuloso(int* tamanhoCobertura);
};

#endif