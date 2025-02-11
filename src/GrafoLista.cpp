/**
 * @file GrafoLista.cpp
 * @brief Implementação das funções da classe GrafoLista.
 */

#include "../include/GrafoLista.h"
#include "../include/Lista.h"
#include <fstream>
#include <iostream>

using namespace std;

/**
 * @brief Construtor da classe GrafoLista.
 * @param ordem Número de vértices do grafo.
 * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
 * @param ponderadoVertices Indica se os vértices possuem pesos (true) ou não (false).
 * @param ponderadoArestas Indica se as arestas possuem pesos (true) ou não (false).
 */
GrafoLista::GrafoLista(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas)
    : Grafo(ordem, direcionado, ponderadoVertices, ponderadoArestas)
{
    listaAdj = new Lista[ordem];
}

/**
 * @brief Destrutor da classe GrafoLista.
 * Libera a memória alocada para a lista de adjacência.
 */
GrafoLista::~GrafoLista()
{
    delete[] listaAdj;
}

/**
 * @brief Obtém o grau de um vértice.
 * @param vertice Índice do vértice.
 * @return Número de arestas conectadas ao vértice especificado.
 */
int GrafoLista::getGrau(int vertice)
{
    return listaAdj[vertice].getTamanho();
}

/**
 * @brief Verifica se o grafo é completo.
 * Um grafo completo possui todas as combinações possíveis de arestas entre seus vértices.
 * @return true se o grafo é completo; caso contrário, false.
 */
bool GrafoLista::ehCompleto()
{
    for (int i = 0; i < ordem; i++)
    {
        if (listaAdj[i].getTamanho() != ordem - 1)
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Verifica se o grafo é bipartido.
 * Um grafo bipartido pode ser dividido em dois subconjuntos, onde não existem arestas entre vértices do mesmo subconjunto.
 * @return true se o grafo é bipartido; caso contrário, false.
 */
bool GrafoLista::ehBipartido()
{
    int *cores = new int[ordem];
    for (int i = 0; i < ordem; ++i)
    {
        cores[i] = -1; // -1 significa não colorido
    }

    int *fila = new int[ordem];
    int inicio = 0, fim = 0;

    cores[0] = 1; // Começa colorindo o primeiro vértice
    fila[fim++] = 0;

    while (inicio != fim)
    {
        int u = fila[inicio++];
        for (int i = 0; i < listaAdj[u].getTamanho(); ++i)
        {
            int v = listaAdj[u].getElemento(i)->getIdNo();
            if (cores[v] == -1)
            {
                cores[v] = 1 - cores[u];
                fila[fim++] = v;
            }
            else if (cores[v] == cores[u])
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
int GrafoLista::nConexo()
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
        for (int i = 0; i < listaAdj[v].getTamanho(); ++i)
        {
            int adj = listaAdj[v].getElemento(i)->getIdNo();
            if (!visitado[adj])
            {
                dfsRef(adj, dfsRef);
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
bool GrafoLista::ehArvore()
{
    return (nConexo() == 1 && (ordem - 1) == numVertices);
}

/**
 * @brief Verifica se o grafo possui pontes.
 * Uma ponte é uma aresta cuja remoção aumenta o número de componentes conexos do grafo.
 * @return true se existe pelo menos uma ponte; caso contrário, false.
 */
bool GrafoLista::possuiPonte()
{
    for (int u = 0; u < ordem; u++)
    {
        for (int i = 0; i < listaAdj[u].getTamanho(); ++i)
        {
            int v = listaAdj[u].getElemento(i)->getIdNo();

            listaAdj[u].remover(v);
            if (!direcionado)
            {
                listaAdj[v].remover(u);
            }
            bool *visitado = new bool[ordem];
            for (int j = 0; j < ordem; ++j)
            {
                visitado[j] = false;
            }

            auto dfs = [&](int vertice, auto &dfsRef) -> void
            {
                visitado[vertice] = true;
                for (int k = 0; k < listaAdj[vertice].getTamanho(); ++k)
                {
                    int adj = listaAdj[vertice].getElemento(k)->getIdNo();
                    if (!visitado[adj])
                    {
                        dfsRef(adj, dfsRef);
                    }
                }
            };

            int componentes = 0;
            for (int j = 0; j < ordem; j++)
            {
                if (!visitado[j])
                {
                    componentes++;
                    dfs(j, dfs);
                }
            }

            delete[] visitado;
            listaAdj[u].adicionar(v);
            if (!direcionado)
            {
                listaAdj[v].adicionar(u);
            }

            if (componentes > 1)
            {
                return true;
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
bool GrafoLista::possuiArticulacao()
{
    bool *visitado = new bool[ordem];
    int componentesOriginais = nConexo();

    for (int v = 0; v < ordem; v++)
    {
        for (int i = 0; i < ordem; ++i)
        {
            visitado[i] = false;
        }
        visitado[v] = true;

        int componentes = 0;
        for (int u = 0; u < ordem; u++)
        {
            if (!visitado[u])
            {
                componentes++;
                auto dfs = [&](int x, auto &dfsRef) -> void
                {
                    visitado[x] = true;
                    for (int i = 0; i < listaAdj[x].getTamanho(); ++i)
                    {
                        int adj = listaAdj[x].getElemento(i)->getIdNo();
                        if (!visitado[adj])
                        {
                            dfsRef(adj, dfsRef);
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
void GrafoLista::carregaGrafo(const std::string &arquivo)
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

    delete[] listaAdj;
    listaAdj = new Lista[numNos];

    int origem, destino, peso;
    while (file >> origem >> destino >> peso)
    {
        origem--;
        destino--;
        listaAdj[origem].adicionar(destino);
        if (!direcionado)
        {
            listaAdj[destino].adicionar(origem);
        }
        std::cout << "Aresta adicionada: " << origem + 1 << " -> " << destino + 1 << " com peso " << peso << std::endl;
    }

    file.close();
    std::cout << "Lista de Adjacência carregada com sucesso." << std::endl;
}

/**
 * @brief Cria um novo grafo a partir de um arquivo de configuração.
 * O arquivo deve conter as informações do grafo, como tipo de estrutura, número de nós e arestas.
 * @param arquivoConfig Caminho para o arquivo de configuração.
 */
void GrafoLista::novoGrafo(const std::string &arquivoConfig)
{
    std::ifstream file(arquivoConfig);
    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo de configuração!" << std::endl;
        return;
    }

    std::string tipo;
    file >> tipo; // Ignora "matriz" ou "lista"
    file >> ordem >> direcionado >> ponderadoVertices >> ponderadoArestas;
    delete[] listaAdj;
    listaAdj = new Lista[ordem];

    int origem, destino, peso;
    while (file >> origem >> destino >> peso)
    {
        listaAdj[origem].adicionar(destino);
        if (!direcionado)
        {
            listaAdj[destino].adicionar(origem);
        }
    }

    file.close();
    std::cout << "Novo grafo configurado como " << tipo << "." << std::endl;
}

/**
 * @brief Remove um nó do grafo representado por lista de adjacência.
 * @param idNo ID do nó a ser removido (ajustado para índice zero-based).
 */
void GrafoLista::deleta_no(int idNo)
{
    if (idNo <= 0 || idNo > ordem)  // Ajustando a verificação de índice
    {
        cout << "Erro: ID do nó inválido." << endl;
        return;
    }

    idNo--;  // Ajustar o ID para zero-based (o ID do arquivo começa em 1, mas a lista começa em 0)

    cout << "Removendo nó " << idNo + 1 << " da lista de adjacência..." << endl;

    // Remover todas as conexões do nó que será deletado
    for (int i = 0; i < ordem; i++)
    {
        listaAdj[i].remover(idNo);
    }

    // Criar nova lista de adjacência sem o nó removido
    Lista* novaListaAdj = new Lista[ordem - 1];

    int novoIndice = 0;
    for (int i = 0; i < ordem; i++)
    {
        if (i == idNo) continue; // Ignorar o nó que será removido

        for (int j = 0; j < listaAdj[i].getTamanho(); j++)
        {
            int adj = listaAdj[i].getElemento(j)->getIdNo();
            if (adj != idNo)
            {
                novaListaAdj[novoIndice].adicionar(adj);
            }
        }
        novoIndice++;
    }

    // Liberar a memória da antiga lista de adjacência
    delete[] listaAdj;

    // Atualizar a estrutura do grafo
    listaAdj = novaListaAdj;
    ordem--;

    cout << "Nó " << idNo + 1 << " removido com sucesso! Nova ordem: " << ordem << endl;
}

/**
 * @brief Adiciona um nó ao grafo representado por lista de adjacência.
 * @param idNo ID do nó a ser adicionado.
 */
void GrafoLista::adicionaNo(int idNo)
{
    if (idNo < 0 || idNo >= ordem)
    {
        cout << "Erro: ID do nó inválido. " << endl;
        return;
    }

    cout << "Adicionando nó " << idNo << " à lista de adjacência..." << endl;

    // Criar nova lista de adjacência com o novo nó
    Lista* novaListaAdj = new Lista[ordem + 1];

    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < listaAdj[i].getTamanho(); j++)
        {
            novaListaAdj[i].adicionar(listaAdj[i].getElemento(j)->getIdNo());
        }
    }

    // Adicionar o novo nó
    novaListaAdj[ordem].adicionar(idNo);

    // Liberar a memória da antiga lista de adjacência
    delete[] listaAdj;

    // Atualizar a estrutura do grafo
    listaAdj = novaListaAdj;
    ordem++;

    cout << "Nó " << idNo << " adicionado com sucesso! Nova ordem: " << ordem << endl;
}

void GrafoLista::removeAresta(int idNoOrigem, int idNoDestino, bool direcionado)
{
    if (!listaAdj[idNoOrigem].contem(idNoDestino))
    {
        std::cout << "Aresta inexistente" << std::endl;
        return;
    }

    listaAdj[idNoOrigem].remover(idNoDestino);
    listaAdj[idNoOrigem].getElemento(idNoOrigem)->removeAresta(idNoDestino, direcionado);

    if (!direcionado)
    {
        listaAdj[idNoDestino].remover(idNoOrigem);
        listaAdj[idNoOrigem].getElemento(idNoOrigem)->removeAresta(idNoOrigem, direcionado);
    }
}
