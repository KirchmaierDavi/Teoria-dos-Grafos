/**
 * @file Grafo.cpp
 * @brief Implementação das funções da classe abstrata Grafo.
 */

#include "../include/Grafo.h"
#include "../include/No.h"
#include "../include/Aresta.h"
#include <iostream>
#include <climits>

using namespace std;

/**
 * @brief Construtor da classe Grafo.
 *
 * Este construtor inicializa um grafo com base na ordem (número de vértices),
 * se o grafo é direcionado ou não, se os vértices são ponderados e se as arestas são ponderadas.
 *
 * @param ordem Número de vértices do grafo.
 * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
 * @param ponderadoVertices Indica se os vértices são ponderados (true) ou não (false).
 * @param ponderadoArestas Indica se as arestas são ponderadas (true) ou não (false).
 */
Grafo::Grafo(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas)
    : ordem(ordem), direcionado(direcionado), ponderadoVertices(ponderadoVertices), ponderadoArestas(ponderadoArestas) {}

/**
 * @brief Destrutor da classe Grafo.
 *
 * Este destrutor é responsável por liberar os recursos alocados pelo grafo.
 */
Grafo::~Grafo() {}

int* Grafo::construcaoGulosa(int* tamanhoCobertura) {
    return nullptr; // Implementação vazia para evitar erro de vtable
}

void Grafo::deleta_no(int idNo) {
    // Implementação vazia
}

/**
 * @brief Obtém a ordem do grafo.
 *
 * @return A ordem (número de vértices) do grafo.
 */
int Grafo::getOrdem()
{
    return ordem;
}

/**
 * @brief Obtém o número de nós do grafo.
 *
 * @return O número de nós do grafo.
 */
int Grafo::getNumNos()
{
    return numNos;
}

/**
 * @brief Verifica se o grafo é direcionado.
 *
 * @return true se o grafo for direcionado, false caso contrário.
 */
bool Grafo::ehDirecionado()
{
    if (direcionado == 1)
    {
        return true;
    }
    return false;
}

/**
 * @brief Verifica se o grafo possui vértices ponderados.
 *
 * @return true se ao menos um vértice for ponderado, false caso contrário.
 */
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

/**
 * @brief Verifica se o grafo possui arestas ponderadas.
 *
 * @return true se ao menos uma aresta for ponderada, false caso contrário.
 */
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

/**
 * @brief Obtém o nó pelo seu ID.
 *
 * @param id O ID do nó a ser buscado.
 *
 * @return O ponteiro para o nó com o ID especificado ou nullptr caso o nó não seja encontrado.
 */
No *Grafo::getNoPeloId(int id)
{
    No *no = primeiroNo;
    while (no != nullptr)
    {
        if (no->getIdNo() == id)
        {
            return no;
        }
        no = no->getProxNo();
    }
    return nullptr;
}

/**
 * @brief Obtém o grau de um vértice.
 * @param vertice Índice do vértice.
 * @return Número de arestas conectadas ao vértice especificado.
 */
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
    std::cout << "Vértice não encontrado";
    return -1;
}
void Grafo::novaAresta(int origem, int destino, float peso){    }
/**
 * @brief Verifica se o grafo é bipartido.
 * Um grafo bipartido pode ser dividido em dois subconjuntos, onde não existem arestas entre vértices do mesmo subconjunto.
 * @return true se o grafo é bipartido; caso contrário, false.
 */
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

    auto desenfileirar = [&]() -> No *
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

    return false;
}

/**
 * @brief Determina o número de componentes conexos no grafo.
 * Um componente conexo é um subconjunto de vértices onde existe pelo menos um caminho entre cada par de vértices.
 * @return Número de componentes conexos no grafo.
 */
int Grafo::nConexo()
{
    bool *visitado = new bool[ordem];
    for (int i = 0; i < ordem; i++)
    {
        visitado[i] = false;
    }

    int componentes = 0;

    auto dfs = [&](No *no, auto &dfsRef) -> void
    {
        visitado[no->getIdNo()] = true;
        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            No *noAdjacente = getNoPeloId(aresta->getIdDestino());
            if (!visitado[noAdjacente->getIdNo()])
            {
                dfsRef(noAdjacente, dfsRef);
            }
            aresta = aresta->getProxAresta();
        }
    };

    No *no = primeiroNo;
    while (no != nullptr)
    {
        if (!visitado[no->getIdNo()])
        {
            componentes++;
            dfs(no, dfs);
        }
        no = no->getProxNo();
    }

    delete[] visitado;
    return componentes;

    return 0;
}

/**
 * @brief Verifica se o grafo é completo.
 * Um grafo completo possui todas as combinações possíveis de arestas entre seus vértices.
 * @return true se o grafo é completo; caso contrário, false.
 */
bool Grafo::ehCompleto()
{
    No *no = primeiroNo;
    while (no != nullptr)
    {
        No *noAdjacente = primeiroNo;
        while (noAdjacente != nullptr)
        {
            if (no != noAdjacente)
            {
                Aresta *aresta = no->getPrimeiraAresta();
                bool conectado = false;
                while (aresta != nullptr)
                {
                    if (aresta->getIdDestino() == noAdjacente->getIdNo())
                    {
                        conectado = true;
                        break;
                    }
                    aresta = aresta->getProxAresta();
                }
                if (!conectado)
                {
                    return false;
                }
            }
            noAdjacente = noAdjacente->getProxNo();
        }
        no = no->getProxNo();
    }
    return true;

    return false;
}

/**
 * @brief Verifica se o grafo é uma árvore.
 * Uma árvore é um grafo conexo sem ciclos.
 * @return true se o grafo é uma árvore; caso contrário, false.
 */
bool Grafo::ehArvore()
{
    return (nConexo() == 1 && (ordem - 1) == getNumNos());

    return false;
}

/**
 * @brief Verifica se o grafo possui pontes.
 * Uma ponte é uma aresta cuja remoção aumenta o número de componentes conexos do grafo.
 * @return true se existe pelo menos uma ponte; caso contrário, false.
 */
bool Grafo::possuiPonte()
{
    No *no = primeiroNo;
    while (no != nullptr)
    {
        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            int origem = no->getIdNo();
            int destino = aresta->getIdDestino();

            bool *visitado = new bool[ordem];
            for (int i = 0; i < ordem; i++)
            {
                visitado[i] = false;
            }

            auto dfs = [&](No *noAtual, auto &dfsRef) -> void
            {
                visitado[noAtual->getIdNo()] = true;
                Aresta *arestaAtual = noAtual->getPrimeiraAresta();
                while (arestaAtual != nullptr)
                {
                    int adj = arestaAtual->getIdDestino();
                    if ((noAtual->getIdNo() == origem && adj == destino) || (noAtual->getIdNo() == destino && adj == origem))
                    {
                        arestaAtual = arestaAtual->getProxAresta();
                        continue;
                    }
                    No *noAdjacente = getNoPeloId(adj);
                    if (!visitado[noAdjacente->getIdNo()])
                    {
                        dfsRef(noAdjacente, dfsRef);
                    }
                    arestaAtual = arestaAtual->getProxAresta();
                }
            };

            dfs(no, dfs);

            if (!visitado[destino])
            {
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

/**
 * @brief Verifica se o grafo possui vértices de articulação.
 * Um vértice de articulação é aquele cuja remoção aumenta o número de componentes conexos do grafo.
 * @return true se existe pelo menos um vértice de articulação; caso contrário, false.
 */
bool Grafo::possuiArticulacao()
{
    int componentesOriginais = nConexo();

    No *no = primeiroNo;
    while (no != nullptr)
    {
        int idNo = no->getIdNo();

        bool *visitado = new bool[ordem];
        for (int i = 0; i < ordem; i++)
        {
            visitado[i] = false;
        }

        No *noInicial = (no == primeiroNo) ? no->getProxNo() : primeiroNo;
        auto dfs = [&](No *noAtual, auto &dfsRef) -> void
        {
            visitado[noAtual->getIdNo()] = true;
            Aresta *aresta = noAtual->getPrimeiraAresta();
            while (aresta != nullptr)
            {
                No *noAdjacente = getNoPeloId(aresta->getIdDestino());
                if (noAdjacente->getIdNo() != idNo && !visitado[noAdjacente->getIdNo()])
                {
                    dfsRef(noAdjacente, dfsRef);
                }
                aresta = aresta->getProxAresta();
            }
        };

        dfs(noInicial, dfs);

        int componentes = 0;
        for (int i = 0; i < ordem; i++)
        {
            if (!visitado[i] && getNoPeloId(i) != nullptr)
            {
                componentes++;
                dfs(getNoPeloId(i), dfs);
            }
        }

        delete[] visitado;

        if (componentes > componentesOriginais)
        {
            return true;
        }

        no = no->getProxNo();
    }
    return false;
}

/**
 * @brief Calcula a menor distância entre dois vértices no grafo.
 *
 * Esta função implementa o algoritmo de Dijkstra para encontrar a menor distância entre
 * um vértice de origem e um vértice de destino considerando os pesos das arestas e dos vértices.
 *
 * @param origem O ID do vértice de origem.
 * @param destino O ID do vértice de destino.
 * @return A menor distância entre os vértices de origem e destino, ou -1 se não houver caminho.
 */
int Grafo::menorDistancia(int origem, int destino)
{
    int *distancia = new int[ordem];
    bool *visitado = new bool[ordem];

    for (int i = 0; i < ordem; i++)
    {
        distancia[i] = INT_MAX;
        visitado[i] = false;
    }

    No *noOrigem = getNoPeloId(origem);
    distancia[origem] = noOrigem->getPesoNo();

    for (int count = 0; count < ordem - 1; count++)
    {
        int min = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < ordem; v++)
        {
            if (!visitado[v] && distancia[v] <= min)
            {
                min = distancia[v];
                minIndex = v;
            }
        }

        if (minIndex == -1)
            break;
        visitado[minIndex] = true;

        No *noAtual = getNoPeloId(minIndex);
        Aresta *aresta = noAtual->getPrimeiraAresta();

        while (aresta)
        {
            int v = aresta->getIdDestino();
            No *noDestino = getNoPeloId(v);

            if (!visitado[v] &&
                distancia[minIndex] != INT_MAX &&
                distancia[minIndex] + aresta->getPeso() + noDestino->getPesoNo() < distancia[v])
            {

                distancia[v] = distancia[minIndex] + aresta->getPeso() + noDestino->getPesoNo();
            }
            aresta = aresta->getProxAresta();
        }
    }

    int resultado = distancia[destino];
    delete[] distancia;
    delete[] visitado;

    return resultado == INT_MAX ? -1 : resultado;
}

/**
 * @brief Obtém o peso de uma aresta entre dois vértices.
 *
 * Esta função busca a aresta entre os vértices especificados e retorna seu peso.
 * Caso a aresta não exista, retorna -1.
 *
 * @param origem O ID do vértice de origem.
 * @param destino O ID do vértice de destino.
 * @return O peso da aresta entre os vértices ou -1 se a aresta não existir.
 */
float Grafo::getPesoAresta(int origem, int destino)
{
    No *noOrigem = getNoPeloId(origem);
    if (!noOrigem)
        return -1;

    Aresta *aresta = noOrigem->getPrimeiraAresta();
    while (aresta)
    {
        if (aresta->getIdDestino() == destino)
            return aresta->getPeso();
        aresta = aresta->getProxAresta();
    }
    return -1;
}
