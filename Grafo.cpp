#include "Grafo.h"
#include "Aresta.h"
#include "No.h"
#include <iostream>
#include <fstream>

using namespace std;

Grafo::Grafo(int ordem, int totalArestas, bool direcionado, bool pesoArestas, bool pesoNos)
    : ordem(ordem), totalArestas(totalArestas), direcionado(direcionado), pesoArestas(pesoArestas), pesoNos(pesoNos), numArestas(0), primeiroNo(nullptr), ultimoNo(nullptr) {}

Grafo::~Grafo()
{
    No *no = primeiroNo;
    while (no != nullptr)
    {
        No *prox = no->getProxNo();
        delete no;
        no = prox;
    }
}

void Grafo::novoGrafo(const string &configFile)
{
    ifstream file(configFile);
    if (!file.is_open())
    {
        cerr << "Erro ao abrir o arquivo " << configFile << endl;
        return;
    }

    int numNos, direcionado, ponderadoVertices, ponderadoArestas;
    file >> numNos >> direcionado >> ponderadoVertices >> ponderadoArestas;

    int *pesosVertices = nullptr;
    if (ponderadoVertices)
    {
        pesosVertices = new int[numNos];
        for (int i = 0; i < numNos; ++i)
        {
            file >> pesosVertices[i];
        }
    }

    Aresta **arestas = new Aresta *[numNos * numNos];
    int numArestas = 0;

    while (!file.eof())
    {
        int origem, destino;
        float peso = 1.0;
        file >> origem >> destino;
        if (ponderadoArestas)
        {
            file >> peso;
        }
        arestas[numArestas++] = new Aresta(destino, origem, peso);
    }

    delete[] pesosVertices;
    for (int i = 0; i < numArestas; ++i)
    {
        delete arestas[i];
    }
    delete[] arestas;

    file.close();
}

void Grafo::incOrdem()
{
    ordem++;
}

void Grafo::decOrdem()
{
    ordem--;
}

int Grafo::getNumArestas()
{
    return numArestas;
}

No *Grafo::getPrimeiroNo()
{
    return primeiroNo;
}

No *Grafo::getUltimoNo()
{
    return ultimoNo;
}

int Grafo::getOrdem()
{
    return ordem;
}

bool Grafo::arestaPonderada()
{
    No *no = primeiroNo;
    while (no != nullptr)
    {
        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            if (aresta->getPesoAresta() != 0)
            {
                return true;
            }
            aresta = aresta->getProxAresta();
        }
        no = no->getProxNo();
    }
    return false;
}

bool Grafo::verticePonderado()
{
    No *no = primeiroNo;
    while (no != nullptr)
    {
        if (no->getPeso() != 0)
        {
            return true;
        }
        no = no->getProxNo();
    }
    return false;
}

int Grafo::getGrau()
{
    No *no = primeiroNo;
    int grau = no->getGrauEntrada();
    while (no != nullptr)
    {
        if (no->getProxNo()->getGrauEntrada() > grau)
        {
            grau = no->getProxNo()->getGrauEntrada();
        }
        no = no->getProxNo();
    }
    return grau;
}

bool Grafo::ehDirecionado()
{
    if (direcionado == 1)
    {
        return true;
    }
    return false;
}
