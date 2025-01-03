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
    int totalArestas;
    bool pesoNos;
    bool pesoArestas;
    bool direcionado;

    No *primeiroNo;
    No *ultimoNo;

public:
    Grafo(int ordem, int totalArestas, bool direcionado, bool pesoArestas, bool pesoNos);
    virtual ~Grafo();

    virtual void incOrdem() const = 0;
    virtual void decOrdem() const = 0;

    virtual int getNumArestas() const = 0;
    virtual No *getPrimeiroNo() const = 0;
    virtual No *getUltimoNo() const = 0;
    virtual int getOrdem() const = 0;
    virtual int getGrau() const = 0;

    virtual void printGrau() const = 0;
    virtual bool ehDigrafo() const = 0;

    virtual void imprimeGrafo() const = 0;

    virtual bool ehBipartido() const = 0;
    virtual int nConexo() const = 0;
    virtual bool ehDirecionado() const = 0;
    virtual bool verticePonderado() const = 0;
    virtual bool arestaPonderada() const = 0;
    virtual bool ehCompleto() const = 0;
    virtual bool ehArvore() const = 0;
    virtual bool possuiArticulacao() const = 0;
    virtual bool possuiPonte() const = 0;
    virtual void carregaGrafo(const string &filename) = 0;
    virtual void novoGrafo(const string &configFile) = 0;
};
