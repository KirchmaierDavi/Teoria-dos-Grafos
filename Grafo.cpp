#include "Grafo.h"
#include "No.h"
#include "Aresta.h"
#include <iostream>

Grafo::Grafo(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas)
    : ordem(ordem), direcionado(direcionado), ponderadoVertices(ponderadoVertices), ponderadoArestas(ponderadoArestas) {}

Grafo::~Grafo() {}

int Grafo::getOrdem()
{
    return ordem;
}

int Grafo::getNumNos()
{
    return numNos;
}

int Grafo::getGrau(int vertice)
{
    No *no = primeiroNo;
    while (no != nullptr)
    {
        if (no->getIdNo() == vertice)
        {
            return no->getGrauSaida();
        }
        no = no->getProxNo();
    }
    std::cout <<"Vértice não encontrado";
    return -1;
}


bool Grafo::ehDirecionado()
{
    if (direcionado == 1)
    {
        return true;
    }
    return false;
}

bool Grafo::ehBipartido()
{
    if (primeiroNo == nullptr)
    {
        return true;
    }

    struct Fila
    {
        No *no;
        Fila *prox;
    };

    Fila *inicio = nullptr;
    Fila *fim = nullptr;

    auto enfileirar = [&](No *no)
    {
        Fila *novo = new Fila;
        novo->no = no;
        novo->prox = nullptr;
        if (inicio == nullptr)
        {
            inicio = novo;
            fim = novo;
        }
        else
        {
            fim->prox = novo;
            fim = novo;
        }
    };

    auto desenfileirar = [&]() -> No*
    {
        if (inicio == nullptr)
        {
            return nullptr;
        }
        No *no = inicio->no;
        Fila *temp = inicio;
        inicio = inicio->prox;
        if (inicio == nullptr)
        {
            fim = nullptr;
        }
        delete temp;
        return no;
    };

    // Utilizando coloração para verificar se é bipartido, nesse caso utilizaremos 2 cores, 0 e 1, -1 para não colorido

    int cores[getNumNos()];
    for (int i = 0; i < getNumNos(); i++)
    {
        cores[i] = -1;
    }

    No *noInicial = primeiroNo;
    enfileirar(noInicial);
    cores[noInicial->getIdNo()] = 1;

    while (inicio != nullptr)
    {
        No *noAtual = desenfileirar();

        Aresta *aresta = noAtual->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            No *noAdjacente = getNoPeloId(aresta->getIdDestino());
            if (cores[noAdjacente->getIdNo()] == -1)
            {
                cores[noAdjacente->getIdNo()] = 1 - cores[noAtual->getIdNo()];
                enfileirar(noAdjacente);
            }
            else if (cores[noAdjacente->getIdNo()] == cores[noAtual->getIdNo()])
            {
                return false;
            }
            aresta = aresta->getProxAresta();
        }
    }

    return true;
}

No* Grafo::getNoPeloId(int id) {
    No* no = primeiroNo;
    while (no != nullptr) {
        if (no->getIdNo() == id) {
            return no;
        }
        no = no->getProxNo();
    }
    return nullptr;
}

int Grafo::nConexo() {
    bool* visitado = new bool[ordem];
    for (int i = 0; i < ordem; i++) {
        visitado[i] = false;
    }

    int componentes = 0;

    auto dfs = [&](No* no, auto& dfsRef) -> void {
        visitado[no->getIdNo()] = true;
        Aresta* aresta = no->getPrimeiraAresta();
        while (aresta != nullptr) {
            No* noAdjacente = getNoPeloId(aresta->getIdDestino());
            if (!visitado[noAdjacente->getIdNo()]) {
                dfsRef(noAdjacente, dfsRef);
            }
            aresta = aresta->getProxAresta();
        }
    };

    No* no = primeiroNo;
    while (no != nullptr) {
        if (!visitado[no->getIdNo()]) {
            componentes++;
            dfs(no, dfs);
        }
        no = no->getProxNo();
    }

    delete[] visitado;
    return componentes;
}

bool Grafo::arestaPonderada()
{
    No *no = primeiroNo;
    while (no != nullptr)
    {
        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            if (aresta->getPeso() != 0)
            {
                return true;
            }
            aresta = aresta->getProxAresta();
        }
        no = no->getProxNo();
    }
    return false;
}

bool Grafo::ehCompleto() {
    No* no = primeiroNo;
    while (no != nullptr) {
        No* noAdjacente = primeiroNo;
        while (noAdjacente != nullptr) {
            if (no != noAdjacente) {
                Aresta* aresta = no->getPrimeiraAresta();
                bool conectado = false;
                while (aresta != nullptr) {
                    if (aresta->getIdDestino() == noAdjacente->getIdNo()) {
                        conectado = true;
                        break;
                    }
                    aresta = aresta->getProxAresta();
                }
                if (!conectado) {
                    return false;
                }
            }
            noAdjacente = noAdjacente->getProxNo();
        }
        no = no->getProxNo();
    }
    return true;
}

bool Grafo::ehArvore() {
    return (nConexo() == 1 && (ordem - 1) == getNumNos());
}

bool Grafo::possuiPonte() {
    No* no = primeiroNo;
    while (no != nullptr) {
        Aresta* aresta = no->getPrimeiraAresta();
        while (aresta != nullptr) {
            int origem = no->getIdNo();
            int destino = aresta->getIdDestino();

            bool* visitado = new bool[ordem];
            for (int i = 0; i < ordem; i++) {
                visitado[i] = false;
            }

            auto dfs = [&](No* noAtual, auto& dfsRef) -> void {
                visitado[noAtual->getIdNo()] = true;
                Aresta* arestaAtual = noAtual->getPrimeiraAresta();
                while (arestaAtual != nullptr) {
                    int adj = arestaAtual->getIdDestino();
                    if ((noAtual->getIdNo() == origem && adj == destino) || (noAtual->getIdNo() == destino && adj == origem)) {
                        arestaAtual = arestaAtual->getProxAresta();
                        continue;
                    }
                    No* noAdjacente = getNoPeloId(adj);
                    if (!visitado[noAdjacente->getIdNo()]) {
                        dfsRef(noAdjacente, dfsRef);
                    }
                    arestaAtual = arestaAtual->getProxAresta();
                }
            };

            dfs(no, dfs);

            if (!visitado[destino]) {
                delete[] visitado;
                return true;
            }

            delete[] visitado;
            aresta = aresta->getProxAresta();
        }
        no = no->getProxNo();
    }
    return false;
}

bool Grafo::possuiArticulacao() {
    int componentesOriginais = nConexo();

    No* no = primeiroNo;
    while (no != nullptr) {
        int idNo = no->getIdNo();

        bool* visitado = new bool[ordem];
        for (int i = 0; i < ordem; i++) {
            visitado[i] = false;
        }

        No* noInicial = (no == primeiroNo) ? no->getProxNo() : primeiroNo;
        auto dfs = [&](No* noAtual, auto& dfsRef) -> void {
            visitado[noAtual->getIdNo()] = true;
            Aresta* aresta = noAtual->getPrimeiraAresta();
            while (aresta != nullptr) {
                No* noAdjacente = getNoPeloId(aresta->getIdDestino());
                if (noAdjacente->getIdNo() != idNo && !visitado[noAdjacente->getIdNo()]) {
                    dfsRef(noAdjacente, dfsRef);
                }
                aresta = aresta->getProxAresta();
            }
        };

        dfs(noInicial, dfs);

        int componentes = 0;
        for (int i = 0; i < ordem; i++) {
            if (!visitado[i] && getNoPeloId(i) != nullptr) {
                componentes++;
                dfs(getNoPeloId(i), dfs);
            }
        }

        delete[] visitado;

        if (componentes > componentesOriginais) {
            return true;
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
        if (no->getPesoNo() != 0)
        {
            return true;
        }
        no = no->getProxNo();
    }
    return false;
}
