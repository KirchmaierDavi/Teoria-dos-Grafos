#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"
#include "Aresta.h"
#include <string>
#include <vector>

class Grafo
{
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
    virtual void deleta_no(int idNo) = 0;
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
    virtual void carregaGrafo(const std::string& arquivo) = 0;
    virtual void novoGrafo(const std::string& arquivoConfig) = 0;
    virtual void adicionaNo(int idNo) = 0;
    virtual float getPesoAresta(int origem, int destino);
    virtual int menorDistancia(int origem, int destino);
    virtual void novaAresta(int origem, int destino, float peso);
};

#endif // GRAFO_H
