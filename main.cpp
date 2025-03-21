#include "include/Grafo.h"
#include "include/GrafoMatriz.h"
#include "include/GrafoLista.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

/**
 * @brief Imprime a descrição do grafo fornecido.
 * 
 * Esta função exibe várias informações sobre o grafo, incluindo:
 * - Ordem do grafo (número de vértices).
 * - Se o grafo é direcionado ou não.
 * - Se o grafo contém vértices ponderados.
 * - Se o grafo contém arestas ponderadas.
 * - Grau do vértice 0, ou seja, o número de arestas que incidem sobre o vértice 0.
 * - Número de componentes conexas no grafo.
 * - Se o grafo é completo (ou seja, se há uma aresta entre todos os pares de vértices distintos).
 * - Se o grafo é bipartido.
 * - Se o grafo é uma árvore (ou seja, se é conexo e acíclico).
 * - Se o grafo possui aresta ponte (aresta cuja remoção aumenta o número de componentes conexas).
 * - Se o grafo possui vértice de articulação (vértice cuja remoção aumenta o número de componentes conexas).
 * 
 * Caso algum cálculo ou verificação não seja possível, um erro será capturado e uma mensagem de erro será exibida.
 * 
 * @param grafo Ponteiro para o grafo que será descrito.
 * 
 * @note A função faz uso de blocos `try-catch` para capturar e lidar com erros ao calcular e verificar propriedades do grafo.
 */
void imprimeDescricao(Grafo *grafo)
{
    cout << "========== Descrição do Grafo ==========" << endl;
    cout << "Ordem: " << grafo->getOrdem() << endl;
    cout << "Direcionado: " << (grafo->ehDirecionado() ? "Sim" : "Não") << endl;
    cout << "Vertices ponderados: " << (grafo->verticePonderado() ? "Sim" : "Não") << endl;
    cout << "Arestas ponderadas: " << (grafo->arestaPonderada() ? "Sim" : "Não") << endl;

    // Grau do vértice 0
    try
    {
        cout << "Grau do vértice 0: " << grafo->getGrau(0) << endl;
    }
    catch (...)
    {
        cout << "Erro ao calcular grau do vértice 0." << endl;
    }

    // Componentes conexas
    try
    {
        cout << "Componentes conexas: " << grafo->nConexo() << endl;
    }
    catch (...)
    {
        cout << "Erro ao calcular componentes conexas." << endl;
    }

    // Verifica se o grafo é completo
    try
    {
        cout << "Completo: " << (grafo->ehCompleto() ? "Sim" : "Não") << endl;
    }
    catch (...)
    {
        cout << "Erro ao verificar se o grafo é completo." << endl;
    }

    // Verifica se o grafo é bipartido
    try
    {
        cout << "Bipartido: " << (grafo->ehBipartido() ? "Sim" : "Não") << endl;
    }
    catch (...)
    {
        cout << "Erro ao verificar se o grafo é bipartido." << endl;
    }

    // Verifica se o grafo é uma árvore
    try
    {
        cout << "Árvore: " << (grafo->ehArvore() ? "Sim" : "Não") << endl;
    }
    catch (...)
    {
        cout << "Erro ao verificar se o grafo é uma árvore." << endl;
    }

    // Verifica se o grafo possui aresta ponte
    try
    {
        cout << "Aresta Ponte: " << (grafo->possuiPonte() ? "Sim" : "Não") << endl;
    }
    catch (...)
    {
        cout << "Erro ao verificar se o grafo possui aresta ponte." << endl;
    }

    // Verifica se o grafo possui vértice de articulação
    try
    {
        cout << "Vértice de Articulação: " << (grafo->possuiArticulacao() ? "Sim" : "Não") << endl;
    }
    catch (...)
    {
        cout << "Erro ao verificar se o grafo possui vértice de articulação." << endl;
    }

    cout << "========================================" << endl;
}

/**
 * @brief Função principal para carregar e exibir informações sobre um grafo.
 *
 * Esta função principal permite ao usuário carregar um grafo a partir de um arquivo,
 * escolher entre diferentes representações (matriz ou lista) e exibir uma série de informações
 * sobre o grafo, como grau dos vértices, componentes conexas, se é completo, bipartido, árvore,
 * se possui arestas pontes ou vértices de articulação.
 *
 * O tipo de grafo a ser carregado é determinado pelo primeiro argumento da linha de comando:
 * - "-m" para carregar como uma matriz de adjacência.
 * - "-l" para carregar como uma lista de adjacência.
 * - "-c" para carregar a partir de um arquivo de configuração.
 *
 * Dependendo da opção escolhida, o grafo será carregado, processado e diversas propriedades
 * serão verificadas e impressas.
 *
 * @param argc Número de argumentos passados na linha de comando.
 * @param argv Lista de argumentos passados na linha de comando.
 *
 * @return Retorna 0 se a execução for bem-sucedida, ou 1 se ocorrer um erro de sintaxe ou leitura de arquivo.
 *
 * @note A função utiliza exceções para capturar e lidar com erros durante o processamento.
 */
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Uso: " << argv[0] << " -[m|l|c] <arquivo> [-r <idNoRemover>]" << endl;
        return 1;
    }

    string tipoGrafo = argv[1];
    string arquivo = argv[2];
    bool removerNo = false;
    bool adicionarNo = false;
    bool executarGuloso = false;
    bool executarRandomizado = false;
    bool executarReativo = false;
    int idNoRemover = -1;
    int idNoAdicionar = -1;

    // Verificar se há a opção de executar algoritmos gulosos (-g)
    if (argc == 4 && string(argv[3]) == "-g")
    {
        executarGuloso = true;
    }

    // Verificar se há a opção de executar algoritmo reativo (-r)
    if (argc == 4 && string(argv[3]) == "-r")
    {
        executarReativo = true;
    }

    // Verificar se há a opção de remover nó (-r <idNo>)
    if (argc == 5 && string(argv[3]) == "-r")
    {
        removerNo = true;
        idNoRemover = stoi(argv[4]);  // Pegando corretamente o ID do nó para remoção
    }

    //Verificar se há a opção de adicionar nó (-a <idNo>)
    if (argc == 5 && string(argv[3]) == "-a")
    {
        adicionarNo = true;
        idNoAdicionar = stoi(argv[4]);  // Pegando corretamente o ID do nó para adição
    }

    // Verificar flags para cada algoritmo
    if (argc == 4) {
        if (string(argv[3]) == "-g") {
            executarGuloso = true;
        }
        else if (string(argv[3]) == "-gr") {
            executarRandomizado = true;
        }
        else if (string(argv[3]) == "-r") {
            executarReativo = true;
        }
    }

    Grafo *grafo = nullptr;

    // Se for matriz de adjacência
    if (tipoGrafo == "-m")
    {
        cout << "Carregando grafo como matriz..." << endl;
        grafo = new GrafoMatriz(0, true, true, true);
        grafo->carregaGrafo(arquivo);

        if (executarRandomizado)
        {
            cout << "\n========== Algoritmo Guloso Randomizado ==========\n";
            int tamanhoCobertura;
            
            cout << "Executando construção gulosa randomizada...\n";
            float alpha = 0.5; // valor entre 0 e 1
            int maxIteracoes = 100;
            int* coberturaRandomizada = grafo->coberturaArestas(alpha, maxIteracoes, &tamanhoCobertura);
            
            if (coberturaRandomizada != nullptr) {
                cout << "Tamanho da cobertura (randomizada): " << tamanhoCobertura << "\nVértices na cobertura: ";
                for(int i = 0; i < tamanhoCobertura; i++) {
                    cout << coberturaRandomizada[i] + 1 << " ";
                }
                cout << "\n";
                delete[] coberturaRandomizada;
            } else {
                cout << "Não foi possível encontrar uma cobertura randomizada.\n";
            }
            
            cout << "=============================================\n\n";
        }
        else if (executarGuloso)
        {
            cout << "\n========== Algoritmo Guloso ==========\n";
            int tamanhoCobertura;
            
            cout << "Executando algoritmo guloso...\n";
            int* coberturaGulosa = grafo->construcaoGulosa(&tamanhoCobertura);
            
            if (coberturaGulosa != nullptr) {
                cout << "Tamanho da cobertura (gulosa): " << tamanhoCobertura << "\nVértices na cobertura: ";
                for(int i = 0; i < tamanhoCobertura; i++) {
                    cout << coberturaGulosa[i] + 1 << " ";
                }
                cout << "\n";
                delete[] coberturaGulosa;
            } else {
                cout << "Não foi possível encontrar uma cobertura gulosa.\n";
            }
            
            cout << "===================================\n\n";
        }

        if (executarReativo)
        {
            cout << "\n========== Algoritmo Reativo ==========\n";
            int tamanhoCobertura;
            int maxIteracoes = 100;
            int tamanhoListaAlpha = 5;
            
            cout << "Executando construção gulosa reativa...\n";
            int* coberturaReativa = grafo->coberturaArestasReativa(maxIteracoes, tamanhoListaAlpha, &tamanhoCobertura);
            
            if (coberturaReativa != nullptr) {
                cout << "Tamanho da cobertura (reativa): " << tamanhoCobertura << "\nVértices na cobertura: ";
                for(int i = 0; i < tamanhoCobertura; i++) {
                    cout << coberturaReativa[i] + 1 << " "; // +1 para ajustar índice baseado em 0
                }
                cout << "\n";
                delete[] coberturaReativa;
            } else {
                cout << "Não foi possível encontrar uma cobertura reativa.\n";
            }
            
            cout << "====================================\n\n";
        }

        if (removerNo)
        {
            cout << "Removendo nó " << idNoRemover << "...\n";
            grafo->deleta_no(idNoRemover);
        }
        if(adicionarNo)
        {
            cout << "Adicionando nó " << idNoAdicionar << "...\n";
            grafo->adicionaNo(idNoAdicionar);
        }

        imprimeDescricao(grafo);
    }
    // Se for lista de adjacência
    else if (tipoGrafo == "-l")
    {
        cout << "Carregando grafo como lista..." << endl;
        grafo = new GrafoLista(0, true, true, true);
        grafo->carregaGrafo(arquivo);

        if (executarRandomizado)
        {
            cout << "\n========== Algoritmo Guloso Randomizado ==========\n";
            int tamanhoCobertura;
            
            cout << "Executando construção gulosa randomizada...\n";
            float alpha = 0.5; // valor entre 0 e 1
            int maxIteracoes = 100;
            int* coberturaRandomizada = grafo->coberturaArestas(alpha, maxIteracoes, &tamanhoCobertura);
            
            if (coberturaRandomizada != nullptr) {
                cout << "Tamanho da cobertura (randomizada): " << tamanhoCobertura << "\nVértices na cobertura: ";
                for(int i = 0; i < tamanhoCobertura; i++) {
                    cout << coberturaRandomizada[i] + 1 << " ";
                }
                cout << "\n";
                delete[] coberturaRandomizada;
            } else {
                cout << "Não foi possível encontrar uma cobertura randomizada.\n";
            }
            
            cout << "=============================================\n\n";
        }
        else if (executarGuloso)
        {
            cout << "\n========== Algoritmo Guloso ==========\n";
            int tamanhoCobertura;
            
            cout << "Executando algoritmo guloso...\n";
            int* coberturaGulosa = grafo->construcaoGulosa(&tamanhoCobertura);
            
            if (coberturaGulosa != nullptr) {
                cout << "Tamanho da cobertura (gulosa): " << tamanhoCobertura << "\nVértices na cobertura: ";
                for(int i = 0; i < tamanhoCobertura; i++) {
                    cout << coberturaGulosa[i] + 1 << " ";
                }
                cout << "\n";
                delete[] coberturaGulosa;
            } else {
                cout << "Não foi possível encontrar uma cobertura gulosa.\n";
            }
            
            cout << "===================================\n\n";
        }

        if (executarReativo)
        {
            cout << "\n========== Algoritmo Reativo ==========\n";
            int tamanhoCobertura;
            int maxIteracoes = 100;
            int tamanhoListaAlpha = 5;
            
            cout << "Executando construção gulosa reativa...\n";
            int* coberturaReativa = grafo->coberturaArestasReativa(maxIteracoes, tamanhoListaAlpha, &tamanhoCobertura);
            
            if (coberturaReativa != nullptr) {
                cout << "Tamanho da cobertura (reativa): " << tamanhoCobertura << "\nVértices na cobertura: ";
                for(int i = 0; i < tamanhoCobertura; i++) {
                    cout << coberturaReativa[i] + 1 << " "; // +1 para ajustar índice baseado em 0
                }
                cout << "\n";
                delete[] coberturaReativa;
            } else {
                cout << "Não foi possível encontrar uma cobertura reativa.\n";
            }
            
            cout << "====================================\n\n";
        }

        if (removerNo)
        {
            cout << "Removendo nó " << idNoRemover << "...\n";
            grafo->deleta_no(idNoRemover);
        }

        if(adicionarNo)
        {
            cout << "Adicionando nó " << idNoAdicionar << "...\n";
            grafo->adicionaNo(idNoAdicionar);
        }

        imprimeDescricao(grafo);
    }
    // Se for carregar a partir de um arquivo de configuração
    else if (tipoGrafo == "-c")
    {
        ifstream descFile(arquivo);
        if (!descFile.is_open())
        {
            cerr << "Erro ao abrir arquivo de configuração: " << arquivo << endl;
            return 1;
        }

        string tipoEstrutura;
        descFile >> tipoEstrutura;

        if (tipoEstrutura == "matriz")
        {
            grafo = new GrafoMatriz(0, true, true, true);
        }
        else if (tipoEstrutura == "lista")
        {
            grafo = new GrafoLista(0, true, true, true);
        }
        else
        {
            cerr << "Estrutura desconhecida no arquivo." << endl;
            return 1;
        }

        grafo->novoGrafo(arquivo);

        if (removerNo)
        {
            cout << "Removendo nó " << idNoRemover << "...\n";
            grafo->deleta_no(idNoRemover);
        }

        if(adicionarNo)
        {
            cout << "Adicionando nó " << idNoAdicionar << "...\n";
            grafo->adicionaNo(idNoAdicionar);
        }

        imprimeDescricao(grafo);
    }
    // Caso a opção passada seja inválida
    else
    {
        cerr << "Tipo de execução inválido." << endl;
        return 1;
    }

    delete grafo;
    return 0;
}
