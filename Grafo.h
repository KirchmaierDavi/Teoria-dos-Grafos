#ifndef GRAFO_H
#define GRAFO_H

#include <string>

class Grafo {
protected:
    int ordem;
    int numNos;
    bool direcionado;
    bool ponderadoVertices;
    bool ponderadoArestas;

    No *primeiroNo;
    No *ultimoNo;

public:
    Grafo(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);
    virtual ~Grafo();

    virtual int getGrau(int vertice); 
    virtual int getOrdem(); 
    virtual int getNumNos(); 
    virtual bool ehDirecionado(); 
    virtual bool verticePonderado(); 
    virtual bool arestaPonderada(); 
    virtual bool ehCompleto(); 
    virtual bool ehBipartido(); 
    No *getNoPeloId(int id); 
    virtual int nConexo(); 
    virtual bool ehArvore(); 
    virtual bool possuiPonte(); 
    virtual bool possuiArticulacao();
    virtual void carregaGrafo(const std::string& arquivo);
    virtual void novoGrafo(const std::string& arquivoConfig);
};

#endif // GRAFO_H
