#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include "Lista.h"
#include <string>

class GrafoLista : public Grafo {
private:
    Lista* listaAdj;
    int numVertices;

public:
    GrafoLista(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);
    void deleta_no(int idNo);
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
    void adicionaNo(int idNo) override;
};

#endif // GRAFOLISTA_H
