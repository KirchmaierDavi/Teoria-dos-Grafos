#ifndef GRAFO_H
#define GRAFO_H

#include <string>

class Grafo {
protected:
    int ordem;
    bool direcionado;
    bool ponderadoVertices;
    bool ponderadoArestas;

public:
    Grafo(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);
    virtual ~Grafo();

    virtual int getGrau(int vertice) = 0;
    virtual int getOrdem();
    virtual bool ehDirecionado();
    virtual bool verticePonderado();
    virtual bool arestaPonderada();
    virtual bool ehCompleto() = 0;
    virtual bool ehBipartido() = 0;
    virtual int nConexo() = 0;
    virtual bool ehArvore() = 0;
    virtual bool possuiPonte() = 0;
    virtual bool possuiArticulacao() = 0;
    virtual void carregaGrafo(const std::string& arquivo) = 0;
    virtual void novoGrafo(const std::string& arquivoConfig) = 0;
};

#endif // GRAFO_H
