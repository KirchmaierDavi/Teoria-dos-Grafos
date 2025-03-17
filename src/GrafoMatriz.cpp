/**
 * @file GrafoMatriz.cpp
 * @brief Implementação das funções da classe GrafoMatriz.
 */

#include "../include/GrafoMatriz.h"
#include <fstream>
#include <iostream>
#include "../include/No.h"

using namespace std;

GrafoMatriz::GrafoMatriz(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas) : Grafo(ordem, direcionado, ponderadoVertices, ponderadoArestas), matrizAdj(nullptr), nos(nullptr)
{
    this->capacidade = 10;
    matrizAdj = new int *[capacidade];
    for (int i = 0; i < capacidade; ++i)
    {
        matrizAdj[i] = new int[capacidade]();
    }
}

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

bool GrafoMatriz::ehArvore()
{
    return (nConexo() == 1 && (numNos - 1) == getOrdem());
}

bool GrafoMatriz::possuiPonte()
{
    for (int u = 0; u < numNos; u++)
    {
        for (int v = 0; v < numNos; v++)
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

bool GrafoMatriz::possuiArticulacao()
{
    bool *visitado = new bool[numNos];
    int componentesOriginais = nConexo();

    for (int v = 0; v < numNos; v++)
    {
        for (int i = 0; i < numNos; ++i)
        {
            visitado[i] = false;
        }
        visitado[v] = true;

        int componentes = 0;
        for (int u = 0; u < numNos; u++)
        {
            if (!visitado[u])
            {
                componentes++;
                auto dfs = [&](int x, auto &dfsRef) -> void
                {
                    visitado[x] = true;
                    for (int i = 0; i < numNos; i++)
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

void GrafoMatriz::deleta_no(int idNo)
{
    if (idNo < 0 || idNo >= ordem)
    {
        cout << "Erro: ID do nó inválido. Ordem atual: " << ordem << endl;
        return;
    }

    cout << "Removendo nó " << idNo << " da matriz de adjacência...\n";

    // Atualizar IDs dos nós e suas arestas
    for (int i = idNo; i < ordem - 1; i++)
    {
        No *no = getNoPeloId(i + 1);
        no->setIDNo(i);

        // Atualizar IDs das arestas que apontam para nós com índices maiores que idNo
        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            int destino = aresta->getIdDestino();
            if (destino > idNo)
            {
                // Atualiza o ID de destino da aresta
                No *novoDestino = getNoPeloId(destino - 1);
                aresta->setNoDestino(novoDestino);
            }
            aresta = aresta->getProxAresta();
        }
    }

    // Remover todas as arestas que apontam para o nó a ser removido
    for (int i = 0; i < ordem; i++)
    {
        if (i != idNo)
        {
            No *no = getNoPeloId(i);
            no->removeAresta(idNo, direcionado);
        }
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

void GrafoMatriz::novaAresta(int origem, int destino, float peso)
{
    if (origem < 0 || origem >= numNos || destino < 0 || destino >= numNos)
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

int *GrafoMatriz::coberturaArestas(float alpha, int maxIteracoes, int *tamanhoCobertura)
{
    int *melhorSolucao = nullptr;
    int melhorTamanho = ordem + 1; // Inicializa com valor maior que possível

    for (int i = 0; i < maxIteracoes; i++)
    {
        // Fase de Construção
        int tamanhoAtual;
        int *solucaoAtual = construcaoGulosaRandomizada(alpha, &tamanhoAtual);

        // Fase de Busca Local
        int tamanhoMelhorada;
        int *solucaoMelhorada = buscaLocal(solucaoAtual, tamanhoAtual, &tamanhoMelhorada);

        // Atualiza melhor solução
        if (tamanhoMelhorada < melhorTamanho)
        {
            delete[] melhorSolucao;
            melhorSolucao = solucaoMelhorada;
            melhorTamanho = tamanhoMelhorada;
            solucaoMelhorada = nullptr; // Evita delete duplo
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

int *GrafoMatriz::construcaoGulosa(int *tamanhoCobertura)
{
    bool *coberto = new bool[ordem];
    for (int i = 0; i < ordem; i++)
    {
        coberto[i] = false;
    }

    int *cobertura = new int[ordem];
    int tamanhoAtual = 0;

    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
        {
            if (matrizAdj[i][j] && !coberto[i] && !coberto[j])
            {
                cobertura[tamanhoAtual++] = i;
                cobertura[tamanhoAtual++] = j;
                coberto[i] = true;
                coberto[j] = true;
            }
        }
    }

    *tamanhoCobertura = tamanhoAtual;
    return cobertura;
}

bool GrafoMatriz::verificarCobertura(int *cobertura, int tamanhoCobertura)
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

int* GrafoMatriz::construcaoGulosaRandomizada(float alpha, int* tamanhoCobertura) {
    // Inicialização
    bool* verticesCobertos = new bool[ordem];
    int* cobertura = new int[ordem];
    *tamanhoCobertura = 0;

    // Inicializa array de vértices cobertos
    for(int i = 0; i < ordem; i++) {
        verticesCobertos[i] = false;
    }

    bool todasArestasCoberta = false;
    while(!todasArestasCoberta) {
        // Conta graus dos vértices não cobertos
        int maxGrau = -1;
        int minGrau = ordem + 1;
        
        // Calcula graus máximo e mínimo
        for(int i = 0; i < ordem; i++) {
            if(verticesCobertos[i]) continue;
            
            int grau = 0;
            for(int j = 0; j < ordem; j++) {
                if(matrizAdj[i][j] && !verticesCobertos[j]) {
                    grau++;
                }
            }
            
            if(grau > maxGrau) maxGrau = grau;
            if(grau < minGrau && grau > 0) minGrau = grau;
        }

        if(maxGrau == -1) {
            break;  // Não há mais arestas para cobrir
        }

        // Calcula limiar para LRC
        int limiar = minGrau + (int)(alpha * (maxGrau - minGrau));

        // Conta candidatos
        int numCandidatos = 0;
        for(int i = 0; i < ordem; i++) {
            if(verticesCobertos[i]) continue;
            
            int grau = 0;
            for(int j = 0; j < ordem; j++) {
                if(matrizAdj[i][j] && !verticesCobertos[j]) {
                    grau++;
                }
            }
            
            if(grau >= limiar) numCandidatos++;
        }

        if(numCandidatos == 0) {
            break;  // Não há mais candidatos válidos
        }

        // Cria e preenche array de candidatos
        int* candidatos = new int[numCandidatos];
        int idx = 0;
        for(int i = 0; i < ordem; i++) {
            if(verticesCobertos[i]) continue;
            
            int grau = 0;
            for(int j = 0; j < ordem; j++) {
                if(matrizAdj[i][j] && !verticesCobertos[j]) {
                    grau++;
                }
            }
            
            if(grau >= limiar) {
                candidatos[idx++] = i;
            }
        }

        // Seleciona candidato aleatoriamente
        int escolhido = candidatos[rand() % numCandidatos];
        cobertura[(*tamanhoCobertura)++] = escolhido;
        verticesCobertos[escolhido] = true;

        // Verifica se todas as arestas estão cobertas
        todasArestasCoberta = true;
        for(int i = 0; i < ordem && todasArestasCoberta; i++) {
            for(int j = 0; j < ordem && todasArestasCoberta; j++) {
                if(matrizAdj[i][j] && !verticesCobertos[i] && !verticesCobertos[j]) {
                    todasArestasCoberta = false;
                }
            }
        }

        delete[] candidatos;
    }

    // Imprime resultado para debug
    std::cout << "Cobertura encontrada: ";
    for(int i = 0; i < *tamanhoCobertura; i++) {
        std::cout << cobertura[i] + 1 << " ";
    }
    std::cout << "\nTamanho da cobertura: " << *tamanhoCobertura << std::endl;

    delete[] verticesCobertos;
    return cobertura;
}

int *GrafoMatriz::buscaLocal(int *solucao, int tamanhoSolucao, int *tamanhoMelhorSolucao)
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

int *GrafoMatriz::coberturaArestasReativa(int maxIteracoes, int tamanhoListaAlpha, int *tamanhoCobertura)
{
    float *alphas = new float[tamanhoListaAlpha];
    float *probabilidades = new float[tamanhoListaAlpha];
    float *valores = new float[tamanhoListaAlpha];
    int *contadores = new int[tamanhoListaAlpha];

    // Inicialização
    for (int i = 0; i < tamanhoListaAlpha; i++)
    {
        alphas[i] = (i + 1.0f) / tamanhoListaAlpha;
        probabilidades[i] = 1.0f / tamanhoListaAlpha;
        valores[i] = 0;
        contadores[i] = 0;
    }

    int *melhorSolucao = nullptr;
    int melhorTamanho = ordem + 1;

    for (int iter = 0; iter < maxIteracoes; iter++)
    {
        // Escolhe alpha baseado nas probabilidades
        float r = (float)rand() / RAND_MAX;
        float soma = 0;
        int indexAlpha = 0;

        for (int i = 0; i < tamanhoListaAlpha; i++)
        {
            soma += probabilidades[i];
            if (r <= soma)
            {
                indexAlpha = i;
                break;
            }
        }

        // Constrói solução
        int tamanhoAtual;
        int *solucaoAtual = construcaoGulosaRandomizada(alphas[indexAlpha], &tamanhoAtual);

        // Busca local
        int tamanhoMelhorada;
        int *solucaoMelhorada = buscaLocal(solucaoAtual, tamanhoAtual, &tamanhoMelhorada);

        // Atualiza estatísticas
        contadores[indexAlpha]++;
        valores[indexAlpha] += tamanhoMelhorada;

        // Atualiza melhor solução
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

        // Atualiza probabilidades a cada 100 iterações
        if ((iter + 1) % 100 == 0)
        {
            float melhorValor = valores[0];
            for (int i = 1; i < tamanhoListaAlpha; i++)
            {
                if (valores[i] < melhorValor && valores[i] > 0)
                {
                    melhorValor = valores[i];
                }
            }
            atualizaProbabilidades(alphas, probabilidades, valores, contadores,
                                   tamanhoListaAlpha, melhorValor);
        }
    }

    delete[] alphas;
    delete[] probabilidades;
    delete[] valores;
    delete[] contadores;

    *tamanhoCobertura = melhorTamanho;
    return melhorSolucao;
}

void GrafoMatriz::atualizaProbabilidades(float *alphas, float *probabilidades,
                                         float *valores, int *contadores,
                                         int tamanhoLista, float melhorValor)
{
    float somaQ = 0;
    float *q = new float[tamanhoLista];

    // Calcula q_i para cada alpha usando multiplicação
    for (int i = 0; i < tamanhoLista; i++)
    {
        if (valores[i] > 0 && contadores[i] > 0)
        {
            float ratio = melhorValor / (valores[i] / contadores[i]);
            // Simula pow(ratio, 10) com multiplicações
            float result = ratio;
            for (int j = 1; j < 10; j++)
            {
                result *= ratio;
            }
            q[i] = result;
            somaQ += q[i];
        }
        else
        {
            q[i] = 0;
        }
    }

    // Atualiza probabilidades
    for (int i = 0; i < tamanhoLista; i++)
    {
        if (somaQ > 0)
        {
            probabilidades[i] = q[i] / somaQ;
        }
        else
        {
            probabilidades[i] = 1.0f / tamanhoLista;
        }
    }

    delete[] q;
}