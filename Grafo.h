#include <iostream>
#include <stdlib.h>
#include "No.h"
#include "Aresta.h"

using namespace std;

class No;
class Aresta;

class Grafo
{

private:
    int ordem;
    int numArestas;
    int numNos;
    int totalArestas;
    bool pesoNos;
    bool pesoArestas;
    bool direcionado;

    No *primeiroNo;
    No *ultimoNo;

public:
    Grafo(int ordem, int totalArestas, bool direcionado, bool pesoArestas, bool pesoNos);
    virtual ~Grafo();

    virtual void incOrdem();
    virtual void decOrdem();

    virtual int getNumArestas();
    virtual int getNumNos();
    virtual No *getPrimeiroNo();
    virtual No *getUltimoNo();
    virtual int getOrdem();
    virtual int getGrau();

    virtual bool ehDigrafo();

    virtual void imprimeGrafo();

    virtual bool ehBipartido();
    virtual No *getNoPeloId(int id);
    virtual int nConexo();
    virtual bool ehDirecionado();
    virtual bool verticePonderado();
    virtual bool arestaPonderada();
    virtual bool ehCompleto();
    virtual bool ehArvore();
    virtual bool possuiArticulacao();
    virtual bool possuiPonte();
    virtual void carregaGrafo(const string &filename);
    virtual void novoGrafo(const string &configFile);
};
