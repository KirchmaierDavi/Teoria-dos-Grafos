#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include <list>
#include <vector>
#include <string>
#include <utility>

class GrafoLista : public Grafo {
private:
    std::vector<std::list<std::pair<int, int>>> listaAdj;

public:
    GrafoLista(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);
    ~GrafoLista();

    int getGrau(int vertice) override;
    bool ehCompleto() override;
    bool ehBipartido() override;
    int nConexo() override;
    bool ehArvore() override;
    bool possuiPonte() override;
    bool possuiArticulacao() override;

    void carregaGrafo(const std::string& arquivo) override;
    void novoGrafo(const std::string& arquivoConfig) override;
};

#endif // GRAFOLISTA_H
