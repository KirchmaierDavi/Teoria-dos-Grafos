/**
 * @file GrafoMatriz.cpp
 * @brief Implementação das funções da classe GrafoMatriz.
 */

#include "../include/GrafoMatriz.h"
#include <fstream>
#include <iostream>

using namespace std;

/**
 * @brief Construtor da classe GrafoMatriz.
 * @param ordem Número de vértices do grafo.
 * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
 * @param ponderadoVertices Indica se os vértices possuem pesos (true) ou não (false).
 * @param ponderadoArestas Indica se as arestas possuem pesos (true) ou não (false).
 */
GrafoMatriz::GrafoMatriz(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas)
    : Grafo(ordem, direcionado, ponderadoVertices, ponderadoArestas)
{
    matrizAdj = new int *[ordem];
    for (int i = 0; i < ordem; ++i)
    {
        matrizAdj[i] = new int[ordem];
        for (int j = 0; j < ordem; ++j)
        {
            matrizAdj[i][j] = 0;
        }
    }
}

/**
 * @brief Destrutor da classe GrafoMatriz.
 * Libera a memória alocada para o grafo de matriz de adjacência.
 */
GrafoMatriz::~GrafoMatriz() {}

/**
 * @brief Calcula o grau de um vértice no grafo.
 * O grau de um vértice é a soma dos pesos das arestas conectadas a ele.
 *
 * @param vertice O índice do vértice cujo grau será calculado.
 * @return O grau do vértice especificado.
 *
 * @warning Certifique-se de que o índice do vértice está dentro do intervalo [0, ordem-1].
 */
int GrafoMatriz::getGrau(int vertice)
{
    int grau = 0;
    for (int i = 0; i < ordem; i++)
    {
        grau += matrizAdj[vertice][i];
    }
    return grau;
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
 * @brief Verifica se o grafo é bipartido.
 * Um grafo bipartido pode ser dividido em dois subconjuntos, onde não existem arestas entre vértices do mesmo subconjunto.
 * @return true se o grafo é bipartido; caso contrário, false.
 */
bool GrafoMatriz::ehBipartido()
{
    int *cores = new int[numVertices];
    for (int i = 0; i < numVertices; ++i)
    {
        cores[i] = -1;
    }

    int *fila = new int[numVertices];
    int inicio = 0, fim = 0;

    cores[0] = 1;
    fila[fim++] = 0;

    while (inicio != fim)
    {
        int u = fila[inicio++];
        for (int v = 0; v < numVertices; v++)
        {
            if (matrizAdj[u][v] && cores[v] == -1)
            {
                cores[v] = 1 - cores[u];
                fila[fim++] = v;
            }
            else if (matrizAdj[u][v] && cores[v] == cores[u])
            {
                delete[] cores;
                delete[] fila;
                return false;
            }
        }
    }

    delete[] cores;
    delete[] fila;
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
