#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include <vector>

class ListaEncadeada {
public:
    struct No {
        int vertice;
        No* proximo;
        No(int v) : vertice(v), proximo(nullptr) {}
    };

    No* cabeca;

    ListaEncadeada() : cabeca(nullptr) {}

    void adicionar(int vertice) {
        No* novoNo = new No(vertice);
        novoNo->proximo = cabeca;
        cabeca = novoNo;
    }

    ~ListaEncadeada() {
        while (cabeca) {
            No* temp = cabeca;
            cabeca = cabeca->proximo;
            delete temp;
        }
    }
};

class GrafoLista : public Grafo {
private:
    std::vector<ListaEncadeada> lista_adj;
    int numVertices;
    bool direcionado;
    bool verticesPonderados;
    bool arestasPonderadas;

public:
    GrafoLista(int num_vertices, bool direcionado, bool vertices_ponderados, bool arestas_ponderadas);

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
    void carregaGrafo(std::string& filename);
    void novoGrafo(std::string& config_filename);
};

#endif // GRAFOLISTA_H