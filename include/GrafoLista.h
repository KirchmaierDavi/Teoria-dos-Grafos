#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include "Lista.h"
#include <string>

class GrafoLista : public Grafo
{
private:
    Lista listaAdj;

public:
    GrafoLista(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);
    virtual ~GrafoLista();
    void deleta_no(int idNo);
    bool ehCompleto() override;
    int nConexo() override;
    bool ehArvore() override;
    bool possuiPonte() override;
    bool possuiArticulacao() override;
    void removeAresta(int idNoOrigem, int idNoDestino, bool direcionado);
    void carregaGrafo(const std::string& arquivo) override;
    void novoGrafo(const std::string& arquivoConfig) override;
    void adicionaNo(int idNo) override;
    void novaAresta(int origem, int destino, float peso = 1.0) override;
};

#endif // GRAFOLISTA_H
