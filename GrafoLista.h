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
        No* novo_no = new No(vertice);
        novo_no->proximo = cabeca;
        cabeca = novo_no;
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
    int num_vertices;
    bool direcionado;
    bool vertices_ponderados;
    bool arestas_ponderadas;

public:
    GrafoLista(int num_vertices, bool direcionado, bool vertices_ponderados, bool arestas_ponderadas);

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

#endif // GRAFOLISTA_H