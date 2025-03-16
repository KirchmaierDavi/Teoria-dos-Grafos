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
    nos = new No*[ordem];
    for (int i = 0; i < ordem; i++) {
        nos[i] = new No(i);
    }
    numArestas = 0;
}

/**
 * @brief Destrutor da classe GrafoLista.
 * Libera a memória alocada para a lista de adjacência.
 */
GrafoLista::~GrafoLista()
{
    // Se necessário, a limpeza é feita automaticamente em ~Lista()
}
int* GrafoLista::construcaoGulosa(int* tamanhoCobertura) {

    return nullptr;
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
bool GrafoLista::ehArvore()
{
    return (nConexo() == 1 && (ordem - 1) == numArestas);
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
    if (idNo <= 0 || idNo > ordem)
    {
        cout << "Erro: ID do nó inválido." << endl;
        return;
    }

    idNo--; // Ajustar para zero-based

    cout << "Removendo nó " << idNo + 1 << " da lista de adjacência..." << endl;

    // Remover todas as conexões do nó que será deletado
    for (int i = 0; i < ordem; i++)
    {
        if (i != idNo)
        {
            listaAdj[i].remover(idNo);

            // Atualizar os IDs das conexões maiores que idNo
            for (int j = 0; j < listaAdj[i].getTamanho(); j++)
            {
                No *no = listaAdj[i].getElemento(j);
                if (no->getIdNo() > idNo)
                {
                    no->setIDNo(no->getIdNo() - 1);
                }
            }
        }
    }

    // Criar nova lista de adjacência sem o nó removido
    Lista *novaListaAdj = new Lista[ordem - 1];

    // Copiar e ajustar os IDs
    int novoIndice = 0;
    for (int i = 0; i < ordem; i++)
    {
        if (i == idNo)
        {
            continue;
        }

        // Copiar as conexões ajustando os IDs
        for (int j = 0; j < listaAdj[i].getTamanho(); j++)
        {
            int adj = listaAdj[i].getElemento(j)->getIdNo();
            if (adj > idNo)
            {
                adj--; // Decrementar IDs maiores que o nó removido
            }
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
    Lista *novaListaAdj = new Lista[ordem + 1];

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

/**
 * @brief Remove uma aresta do grafo.
 * @param idNoOrigem ID do nó de origem da aresta.
 * @param idNoDestino ID do nó de destino da aresta.
 * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
 *
 * Se o grafo for não direcionado, a remoção da aresta ocorre nos dois sentidos.
 */
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

/**
 * @brief Adiciona uma nova aresta ao grafo.
 * @param origem ID do nó de origem da aresta.
 * @param destino ID do nó de destino da aresta.
 * @param peso Peso da aresta (caso o grafo seja ponderado por arestas).
 *
 * Se o grafo for não direcionado, a aresta é adicionada nos dois sentidos.
 */
void GrafoLista::novaAresta(int origem, int destino, float peso)
{
    if (origem < 0 || origem >= ordem || destino < 0 || destino >= ordem)
    {
        std::cerr << "Erro: Índices de vértices inválidos." << std::endl;
        return;
    }

    listaAdj[origem].adicionar(destino, peso);

    if (!direcionado)
    {
        listaAdj[destino].adicionar(origem, peso);
    }

    std::cout << "Aresta adicionada: " << origem << " -> " << destino;
    if (ponderadoArestas)
    {
        std::cout << " com peso: " << peso;
    }
    std::cout << std::endl;
}

bool GrafoLista::verificarCobertura(int *cobertura, int tamanhoCobertura)
{
    // Marca os vértices que fazem parte da cobertura
    bool *verticesNaCobertura = new bool[ordem];
    for (int i = 0; i < ordem; i++)
    {
        verticesNaCobertura[i] = false;
    }

    for (int i = 0; i < tamanhoCobertura; i++)
    {
        verticesNaCobertura[cobertura[i]] = true;
    }

    // Verifica se todas as arestas têm pelo menos uma extremidade na cobertura
    for (int i = 0; i < ordem; i++)
    {
        Aresta *aresta = nos[i]->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            int destino = aresta->getIdDestino();
            if (!verticesNaCobertura[i] && !verticesNaCobertura[destino])
            {
                delete[] verticesNaCobertura;
                return false; // Encontrou uma aresta não coberta
            }
            aresta = aresta->getProxAresta();
        }
    }

    delete[] verticesNaCobertura;
    return true;
}

int *GrafoLista::coberturaArestas(float alpha, int maxIteracoes, int *tamanhoCobertura)
{
    int *melhorSolucao = nullptr;
    int melhorTamanho = ordem + 1;

    for (int i = 0; i < maxIteracoes; i++)
    {
        // Fase de Construção
        int tamanhoAtual;
        int *solucaoAtual = construcaoGulosaRandomizada(alpha, &tamanhoAtual);

        // Fase de Busca Local
        int tamanhoMelhorada;
        int *solucaoMelhorada = buscaLocal(solucaoAtual, tamanhoAtual, &tamanhoMelhorada);

        // Atualiza melhor solução encontrada
        if (tamanhoMelhorada < melhorTamanho)
        {
            delete[] melhorSolucao;
            melhorSolucao = solucaoMelhorada;
            melhorTamanho = tamanhoMelhorada;
            solucaoMelhorada = nullptr;
        }
        else
        {
            delete[] solucaoMelhorada;
        }

        delete[] solucaoAtual;
    }

    *tamanhoCobertura = melhorTamanho;
    return melhorSolucao;
}

int *GrafoLista::construcaoGulosaRandomizada(float alpha, int *tamanhoCobertura)
{
    bool *verticesCobertos = new bool[ordem];
    int *graus = new int[ordem];
    int *cobertura = new int[ordem];
    *tamanhoCobertura = 0;

    // Inicialização
    for (int i = 0; i < ordem; i++)
    {
        verticesCobertos[i] = false;
        graus[i] = listaAdj[i].getTamanho();
    }

    while (true)
    {
        // Encontra maior e menor grau
        int maxGrau = -1;
        int minGrau = ordem + 1;

        for (int i = 0; i < ordem; i++)
        {
            if (!verticesCobertos[i] && graus[i] > 0)
            {
                if (graus[i] > maxGrau)
                    maxGrau = graus[i];
                if (graus[i] < minGrau)
                    minGrau = graus[i];
            }
        }

        if (maxGrau == -1)
            break;

        // Define o limiar para a LRC
        int limiar = minGrau + (int)(alpha * (maxGrau - minGrau));

        // Conta candidatos
        int numCandidatos = 0;
        for (int i = 0; i < ordem; i++)
        {
            if (!verticesCobertos[i] && graus[i] >= limiar)
            {
                numCandidatos++;
            }
        }

        if (numCandidatos == 0)
            break;

        // Cria lista de candidatos
        int *candidatos = new int[numCandidatos];
        int idx = 0;
        for (int i = 0; i < ordem; i++)
        {
            if (!verticesCobertos[i] && graus[i] >= limiar)
            {
                candidatos[idx++] = i;
            }
        }

        // Escolhe candidato aleatoriamente
        int escolhido = candidatos[rand() % numCandidatos];
        cobertura[(*tamanhoCobertura)++] = escolhido;
        verticesCobertos[escolhido] = true;

        // Atualiza graus
        No *no = getNoPeloId(escolhido);
        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            int adj = aresta->getIdDestino();
            if (!verticesCobertos[adj])
            {
                graus[adj]--;
            }
            aresta = aresta->getProxAresta();
        }
        graus[escolhido] = 0;

        delete[] candidatos;
    }

    delete[] verticesCobertos;
    delete[] graus;
    return cobertura;
}

/**
 * @brief Implementa um algoritmo guloso para encontrar uma cobertura de vértices.
 * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
 * @return Um array contendo os vértices que fazem parte da cobertura.
 */
 int *GrafoLista::algoritmoGuloso(int *tamanhoCobertura)
 {
     bool *verticesCobertos = new bool[ordem];
     int *cobertura = new int[ordem];
     *tamanhoCobertura = 0;
 
     // Inicialização
     for (int i = 0; i < ordem; i++)
     {
         verticesCobertos[i] = false;
     }
 
     while (true)
     {
         // Encontra o vértice com o maior grau não coberto
         int maxGrau = -1;
         int verticeEscolhido = -1;
 
         for (int i = 0; i < ordem; i++)
         {
             if (!verticesCobertos[i])
             {
                 int grau = listaAdj[i].getTamanho();
                 if (grau > maxGrau)
                 {
                     maxGrau = grau;
                     verticeEscolhido = i;
                 }
             }
         }
 
         if (verticeEscolhido == -1)
             break;
 
         // Adiciona o vértice escolhido à cobertura
         cobertura[(*tamanhoCobertura)++] = verticeEscolhido;
         verticesCobertos[verticeEscolhido] = true;
 
         // Marca todos os vértices adjacentes como cobertos
         for (int i = 0; i < listaAdj[verticeEscolhido].getTamanho(); i++)
         {
             int adj = listaAdj[verticeEscolhido].getElemento(i)->getIdNo();
             verticesCobertos[adj] = true;
         }
     }
 
     delete[] verticesCobertos;
     return cobertura;
 }
 

int *GrafoLista::buscaLocal(int *solucao, int tamanhoSolucao, int *tamanhoMelhorSolucao)
{
    int *melhorVizinho = new int[tamanhoSolucao];
    for (int i = 0; i < tamanhoSolucao; i++)
    {
        melhorVizinho[i] = solucao[i];
    }
    *tamanhoMelhorSolucao = tamanhoSolucao;

    bool melhorou;
    do
    {
        melhorou = false;

        // Tenta remover cada vértice da solução
        for (int i = 0; i < *tamanhoMelhorSolucao; i++)
        {
            int removido = melhorVizinho[i];

            // Remove temporariamente o vértice
            for (int j = i; j < *tamanhoMelhorSolucao - 1; j++)
            {
                melhorVizinho[j] = melhorVizinho[j + 1];
            }

            // Verifica se ainda é uma cobertura válida
            if (verificarCobertura(melhorVizinho, *tamanhoMelhorSolucao - 1))
            {
                (*tamanhoMelhorSolucao)--;
                melhorou = true;
                break;
            }
            else
            {
                // Desfaz a remoção
                for (int j = *tamanhoMelhorSolucao - 1; j > i; j--)
                {
                    melhorVizinho[j] = melhorVizinho[j - 1];
                }
                melhorVizinho[i] = removido;
            }
        }
    } while (melhorou);

    return melhorVizinho;
}