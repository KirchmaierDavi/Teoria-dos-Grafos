#include "Grafo.h"
#include "GrafoMatriz.h"
#include "GrafoLista.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

void imprimeDescricao(Grafo* grafo) {
    cout << "========== Descrição do Grafo ==========" << endl;
    cout << "Ordem: " << grafo->getOrdem() << endl;
    cout << "Direcionado: " << (grafo->ehDirecionado() ? "Sim" : "Não") << endl;
    cout << "Vertices ponderados: " << (grafo->verticePonderado() ? "Sim" : "Não") << endl;
    cout << "Arestas ponderadas: " << (grafo->arestaPonderada() ? "Sim" : "Não") << endl;

    // Grau do vértice 0
    try {
        cout << "Grau do vértice 0: " << grafo->getGrau(0) << endl;
    } catch (...) {
        cout << "Erro ao calcular grau do vértice 0." << endl;
    }

    // Componentes conexas
    try {
        cout << "Componentes conexas: " << grafo->nConexo() << endl;
    } catch (...) {
        cout << "Erro ao calcular componentes conexas." << endl;
    }

    // Verifica se o grafo é completo
    try {
        cout << "Completo: " << (grafo->ehCompleto() ? "Sim" : "Não") << endl;
    } catch (...) {
        cout << "Erro ao verificar se o grafo é completo." << endl;
    }

    // Verifica se o grafo é bipartido
    try {
        cout << "Bipartido: " << (grafo->ehBipartido() ? "Sim" : "Não") << endl;
    } catch (...) {
        cout << "Erro ao verificar se o grafo é bipartido." << endl;
    }

    // Verifica se o grafo é uma árvore
    try {
        cout << "Árvore: " << (grafo->ehArvore() ? "Sim" : "Não") << endl;
    } catch (...) {
        cout << "Erro ao verificar se o grafo é uma árvore." << endl;
    }

    // Verifica se o grafo possui aresta ponte
    try {
        cout << "Aresta Ponte: " << (grafo->possuiPonte() ? "Sim" : "Não") << endl;
    } catch (...) {
        cout << "Erro ao verificar se o grafo possui aresta ponte." << endl;
    }

    // Verifica se o grafo possui vértice de articulação
    try {
        cout << "Vértice de Articulação: " << (grafo->possuiArticulacao() ? "Sim" : "Não") << endl;
    } catch (...) {
        cout << "Erro ao verificar se o grafo possui vértice de articulação." << endl;
    }

    cout << "========================================" << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " -[m|l|c] <arquivo>" << endl;
        return 1;
    }

    string tipoGrafo = argv[1];
    string arquivo = argv[2];

    Grafo* grafo = nullptr;

    if (tipoGrafo == "-m") {
        cout << "Carregando grafo como matriz..." << endl;
        grafo = new GrafoMatriz(0, true, true, true);
        grafo->carregaGrafo(arquivo);
        imprimeDescricao(grafo);
    } else if (tipoGrafo == "-l") {
        cout << "Carregando grafo como lista..." << endl;
        grafo = new GrafoLista(0, true, true, true);
        grafo->carregaGrafo(arquivo);
        imprimeDescricao(grafo);
    } else if (tipoGrafo == "-c") {
        ifstream descFile(arquivo);
        if (!descFile.is_open()) {
            cerr << "Erro ao abrir arquivo de configuração: " << arquivo << endl;
            return 1;
        }

        string tipoEstrutura;
        descFile >> tipoEstrutura;

        if (tipoEstrutura == "matriz") {
            grafo = new GrafoMatriz(0, true, true, true);
        } else if (tipoEstrutura == "lista") {
            grafo = new GrafoLista(0, true, true, true);
        } else {
            cerr << "Estrutura desconhecida no arquivo." << endl;
            return 1;
        }

        grafo->novoGrafo(arquivo);
        imprimeDescricao(grafo);
    } else {
        cerr << "Tipo de execução inválido." << endl;
        return 1;
    }

    delete grafo;
    return 0;
}