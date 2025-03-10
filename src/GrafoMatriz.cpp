/**
 * @file GrafoMatriz.cpp
 * @brief Implementação das funções da classe GrafoMatriz.
 */

#include "../include/GrafoMatriz.h"
#include <fstream>
#include <iostream>
#include "../include/No.h"

using namespace std;

/**
 * @brief Construtor da classe GrafoMatriz.
 * @param ordem Número de vértices do grafo.
 * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
 * @param ponderadoVertices Indica se os vértices possuem pesos (true) ou não (false).
 * @param ponderadoArestas Indica se as arestas possuem pesos (true) ou não (false).
 */
GrafoMatriz::GrafoMatriz(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas)
    : Grafo(ordem, direcionado, ponderadoVertices, ponderadoArestas), matrizAdj(nullptr), nos(nullptr)
{
    this->capacidade = 10;
    matrizAdj = new int *[capacidade];
    for (int i = 0; i < capacidade; ++i)
    {
        matrizAdj[i] = new int[capacidade]();
    }
}

/**
 * @brief Destrutor da classe GrafoMatriz.
 * Libera a memória alocada para o grafo de matriz de adjacência.
 */
GrafoMatriz::~GrafoMatriz()
{
    if (matrizAdj != nullptr)
    {
        for (int i = 0; i < capacidade; ++i)
        {
            delete[] matrizAdj[i];
        }
        delete[] matrizAdj;
    }

    if (nos != nullptr)
    {
        for (int i = 0; i < ordem; ++i)
        {
            delete nos[i];
        }
        delete[] nos;
    }
}

/**
 * @brief Verifica se o grafo é completo.
 * Um grafo completo possui todas as combinações possíveis de arestas entre seus vértices.
 * @return true se o grafo é completo; caso contrário, false.
 */
bool GrafoMatriz::ehCompleto()
{
    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
        {
            if (i != j && matrizAdj[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Determina o número de componentes conexos no grafo.
 * Um componente conexo é um subconjunto de vértices onde existe pelo menos um caminho entre cada par de vértices.
 * @return Número de componentes conexos no grafo.
 */
int GrafoMatriz::nConexo()
{
    bool *visitado = new bool[ordem];
    for (int i = 0; i < ordem; ++i)
    {
        visitado[i] = false;
    }

    int componentes = 0;

    auto dfs = [&](int v, auto &dfsRef) -> void
    {
        visitado[v] = true;
        for (int i = 0; i < ordem; ++i)
        {
            if (matrizAdj[v][i] && !visitado[i])
            {
                dfsRef(i, dfsRef);
            }
        }
    };

    for (int i = 0; i < ordem; ++i)
    {
        if (!visitado[i])
        {
            componentes++;
            dfs(i, dfs);
        }
    }

    delete[] visitado;
    return componentes;
}

/**
 * @brief Verifica se o grafo é uma árvore.
 * Uma árvore é um grafo conexo sem ciclos.
 * @return true se o grafo é uma árvore; caso contrário, false.
 */
bool GrafoMatriz::ehArvore()
{
    return (nConexo() == 1 && (numVertices - 1) == getOrdem());
}

/**
 * @brief Verifica se o grafo possui pontes.
 * Uma ponte é uma aresta cuja remoção aumenta o número de componentes conexos do grafo.
 * @return true se existe pelo menos uma ponte; caso contrário, false.
 */
bool GrafoMatriz::possuiPonte()
{
    for (int u = 0; u < numVertices; u++)
    {
        for (int v = 0; v < numVertices; v++)
        {
            if (matrizAdj[u][v])
            {
                matrizAdj[u][v] = 0;
                if (nConexo() > 1)
                {
                    matrizAdj[u][v] = 1;
                    return true;
                }
                matrizAdj[u][v] = 1;
            }
        }
    }
    return false;
}

/**
 * @brief Verifica se o grafo possui vértices de articulação.
 * Um vértice de articulação é aquele cuja remoção aumenta o número de componentes conexos do grafo.
 * @return true se existe pelo menos um vértice de articulação; caso contrário, false.
 */
bool GrafoMatriz::possuiArticulacao()
{
    bool *visitado = new bool[numVertices];
    int componentesOriginais = nConexo();

    for (int v = 0; v < numVertices; v++)
    {
        for (int i = 0; i < numVertices; ++i)
        {
            visitado[i] = false;
        }
        visitado[v] = true;

        int componentes = 0;
        for (int u = 0; u < numVertices; u++)
        {
            if (!visitado[u])
            {
                componentes++;
                auto dfs = [&](int x, auto &dfsRef) -> void
                {
                    visitado[x] = true;
                    for (int i = 0; i < numVertices; i++)
                    {
                        if (matrizAdj[x][i] && !visitado[i])
                        {
                            dfsRef(i, dfsRef);
                        }
                    }
                };
                dfs(u, dfs);
            }
        }

        if (componentes > componentesOriginais)
        {
            delete[] visitado;
            return true;
        }
    }

    delete[] visitado;
    return false;
}

/**
 * @brief Carrega o grafo a partir de um arquivo.
 * O arquivo deve conter os dados do grafo, como número de nós, tipo de grafo e arestas.
 * @param arquivo Caminho para o arquivo de entrada.
 */
void GrafoMatriz::carregaGrafo(const std::string &arquivo)
{
    std::ifstream file(arquivo);
    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo " << arquivo << std::endl;
        return;
    }

    int numNos, direcionado, ponderadoVertices, ponderadoArestas;
    file >> numNos >> direcionado >> ponderadoVertices >> ponderadoArestas;

    this->ordem = numNos;
    this->direcionado = direcionado;
    this->ponderadoVertices = ponderadoVertices;
    this->ponderadoArestas = ponderadoArestas;

    if (ponderadoVertices)
    {
        std::cout << "Pesos dos vértices:" << std::endl;
        for (int i = 0; i < numNos; i++)
        {
            int pesoVertice;
            file >> pesoVertice;
            std::cout << "Vértice " << i + 1 << ": Peso " << pesoVertice << std::endl;
        }
    }

    matrizAdj = new int *[numNos];
    for (int i = 0; i < numNos; ++i)
    {
        matrizAdj[i] = new int[numNos];
        for (int j = 0; j < numNos; ++j)
        {
            matrizAdj[i][j] = 0;
        }
    }

    int origem, destino, peso;
    while (file >> origem >> destino >> peso)
    {
        origem--; // Ajusta para índices baseados em 0
        destino--;
        matrizAdj[origem][destino] = peso;
        if (!direcionado)
        {
            matrizAdj[destino][origem] = peso;
        }
        std::cout << "Aresta adicionada: " << origem + 1 << " -> " << destino + 1 << " com peso " << peso << std::endl;
    }

    file.close();
    std::cout << "Matriz de Adjacência carregada com sucesso." << std::endl;
}

/**
 * @brief Cria um novo grafo a partir de um arquivo de configuração.
 * O arquivo deve conter as informações do grafo, como tipo de estrutura, número de nós e arestas.
 * @param arquivoConfig Caminho para o arquivo de configuração.
 */
void GrafoMatriz::novoGrafo(const std::string &arquivoConfig)
{
    std::ifstream file(arquivoConfig);
    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo de configuração: " << arquivoConfig << std::endl;
        return;
    }

    std::string estrutura;
    file >> estrutura; // Lê a estrutura (matriz ou lista)

    file >> ordem >> direcionado >> ponderadoVertices >> ponderadoArestas;
    matrizAdj = new int *[ordem];
    for (int i = 0; i < ordem; ++i)
    {
        matrizAdj[i] = new int[ordem];
        for (int j = 0; j < ordem; ++j)
        {
            matrizAdj[i][j] = 0;
        }
    }

    nos = new No *[ordem];
    if (ponderadoVertices)
    {
        for (int i = 0; i < ordem; ++i)
        {
            float pesoNo;
            file >> pesoNo;
            nos[i] = new No(i, pesoNo);
        }
    }
    else
    {
        for (int i = 0; i < ordem; ++i)
        {
            nos[i] = new No(i, 0.0f);
        }
    }

    int origem, destino, peso;
    while (file >> origem >> destino >> peso)
    {
        origem--;
        destino--;
        matrizAdj[origem][destino] = peso;
        if (!direcionado)
        {
            matrizAdj[destino][origem] = peso;
        }
    }

    file.close();
    std::cout << "Novo grafo configurado como " << estrutura << "." << std::endl;
}

/**
 * @brief Remove um nó do grafo representado por matriz de adjacência.
 * @param idNo ID do nó a ser removido.
 */
void GrafoMatriz::deleta_no(int idNo)
{
    if (idNo < 0 || idNo >= ordem)
    {
        cout << "Erro: ID do nó inválido. Ordem atual: " << ordem << endl;
        return;
    }

    cout << "Removendo nó " << idNo << " da matriz de adjacência...\n";

    // Atualizar IDs dos nós
    for (int i = idNo; i < ordem - 1; i++)
    {
        No *no = getNoPeloId(i + 1);
        no->setIDNo(i);
    }

    // Criar nova matriz reduzida
    int novaOrdem = ordem - 1;
    int **novaMatriz = new int *[novaOrdem];

    for (int i = 0, ni = 0; i < ordem; i++)
    {
        if (i == idNo)
            continue;

        novaMatriz[ni] = new int[novaOrdem];

        for (int j = 0, nj = 0; j < ordem; j++)
        {
            if (j == idNo)
                continue;
            novaMatriz[ni][nj] = matrizAdj[i][j];
            nj++;
        }
        ni++;
    }

    // Liberar a matriz antiga
    for (int i = 0; i < ordem; i++)
    {
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;

    // Atualizar estrutura
    matrizAdj = novaMatriz;
    ordem = novaOrdem;

    cout << "Nó " << idNo << " removido com sucesso! Nova ordem: " << ordem << endl;
}

/**
 * @brief Adiciona um nó ao grafo representado por matriz de adjacência.
 * @param idNo ID do nó a ser adicionado.
 */
void GrafoMatriz::adicionaNo(int idNo)
{
    if (idNo < 0 || idNo >= ordem)
    {
        cout << "Erro: ID do nó inválido." << endl;
        return;
    }

    cout << "Adicionando nó " << idNo << " à matriz de adjacência...\n";

    // Verifica se precisa aumentar a capacidade
    if (ordem >= capacidade)
    {
        int novaCapacidade = capacidade * 2;
        cout << "Expandindo matriz de " << capacidade << " para " << novaCapacidade << endl;

        // Cria nova matriz com capacidade dobrada
        int **novaMatriz = new int *[novaCapacidade];
        for (int i = 0; i < novaCapacidade; ++i)
        {
            novaMatriz[i] = new int[novaCapacidade]();

            // Copia dados existentes
            if (i < ordem)
            {
                for (int j = 0; j < ordem; ++j)
                {
                    novaMatriz[i][j] = matrizAdj[i][j];
                }
            }
        }

        // Libera matriz antiga
        for (int i = 0; i < capacidade; ++i)
        {
            delete[] matrizAdj[i];
        }
        delete[] matrizAdj;

        // Atualiza para nova matriz
        matrizAdj = novaMatriz;
        capacidade = novaCapacidade;
    }

    // Incrementa a ordem do grafo
    ordem++;
    cout << "Nó " << idNo << " adicionado com sucesso! Nova ordem: " << ordem << endl;
}

/**
 * @brief Remove uma aresta do grafo.
 *
 * Esta função remove a aresta entre dois nós especificados. Se o grafo for não direcionado,
 * a remoção ocorre nos dois sentidos. Além disso, a aresta correspondente é removida da estrutura
 * de nós do grafo.
 *
 * @param idNoOrigem ID do nó de origem da aresta.
 * @param idNoDestino ID do nó de destino da aresta.
 * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
 *
 * @note Se a aresta não existir, a função exibe uma mensagem informativa e não realiza nenhuma alteração.
 */
void GrafoMatriz::removeAresta(int idNoOrigem, int idNoDestino, bool direcionado)
{
    if (matrizAdj[idNoOrigem][idNoDestino] == 0)
    {
        std::cout << "Aresta inexistente" << std::endl;
        return;
    }

    matrizAdj[idNoOrigem][idNoDestino] = 0;
    if (!direcionado)
    {
        matrizAdj[idNoDestino][idNoOrigem] = 0;
        nos[idNoOrigem]->removeAresta(idNoDestino, direcionado);
    }

    nos[idNoOrigem]->removeAresta(idNoDestino, direcionado);
}

/**
 * @brief Adiciona uma nova aresta ao grafo.
 *
 * Esta função adiciona uma aresta entre dois nós, atribuindo um peso caso o grafo seja ponderado.
 * Se o grafo for não direcionado, a aresta é adicionada em ambos os sentidos.
 *
 * @param origem ID do nó de origem.
 * @param destino ID do nó de destino.
 * @param peso Peso da aresta (usado apenas se o grafo for ponderado).
 *
 * @note A função verifica se os índices dos nós são válidos e impede a criação de laços (arestas de um nó para ele mesmo).
 * @warning Se os parâmetros forem inválidos ou se origem e destino forem iguais, uma mensagem de erro será exibida.
 */
void GrafoMatriz::novaAresta(int origem, int destino, float peso)
{
    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices)
    {
        std::cout << "Parâmetros errados!" << std::endl;
        return;
    }

    if (origem == destino)
    {
        std::cout << "Origem e destino iguais, erro!" << std::endl;
        return;
    }

    if (ponderadoArestas)
    {
        matrizAdj[origem][destino] = peso;
        if (!direcionado)
        {
            matrizAdj[destino][origem] = peso;
        }
    }
    else
    {
        matrizAdj[origem][destino] = 1;
        if (!direcionado)
        {
            matrizAdj[destino][origem] = 1;
        }
    }
}
