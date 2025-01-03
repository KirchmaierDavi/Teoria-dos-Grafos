#include <iostream>
#include <stdlib.h>
#include "No.h"
#include "Aresta.h"

using namespace std;


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
    ~Grafo();


    void incOrdem();
    void decOrdem();

    int getNumArestas();
    No *getPrimeiroNo();
    No *getUltimoNo();
    int getOrdem();
    int getGrau();


    void printGrau();
    bool ehDigrafo();

    void imprimeGrafo();

    bool ehBipartido();
    int nConexo();
    bool ehDirecionado();
    bool verticePonderado();
    bool arestaPonderada();
    bool ehCompleto();
    bool ehArvore();
    bool possuiArticulacao();
    bool possuiPonte();
    void carregaGrafo(const string &filename);
    void novoGrafo(const string &configFile);
};
