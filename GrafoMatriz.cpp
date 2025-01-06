#include "GrafoMatriz.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

GrafoMatriz::GrafoMatriz(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas)
    : Grafo(ordem, direcionado, ponderadoVertices, ponderadoArestas) {
    matrizAdj.resize(ordem, vector<int>(ordem, 0));
}

GrafoMatriz::~GrafoMatriz() {}

int GrafoMatriz::getGrau(int vertice) {
    int grau = 0;
    for (int i = 0; i < ordem; i++) {
        grau += matrizAdj[vertice][i];
    }
    return grau;
}

bool GrafoMatriz::ehCompleto() {
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            if (i != j && matrizAdj[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool GrafoMatriz::ehBipartido() {
    vector<int> cores(numVertices, -1); // -1 significa não colorido
    queue<int> fila;

    cores[0] = 1; // Começa colorindo o primeiro vértice
    fila.push(0);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int v = 0; v < numVertices; v++) {
            if (matrizAdj[u][v] && cores[v] == -1) {
                cores[v] = 1 - cores[u];
                fila.push(v);
            } else if (matrizAdj[u][v] && cores[v] == cores[u]) {
                return false;
            }
        }
    }
    return true;
}

int GrafoMatriz::nConexo() {
    vector<bool> visitado(ordem, false);
    int componentes = 0;

    auto dfs = [&](int v, auto& dfsRef) -> void {
        visitado[v] = true;
        for (int i = 0; i < ordem; i++) {
            if (matrizAdj[v][i] && !visitado[i]) {
                dfsRef(i, dfsRef);
            }
        }
    };

    for (int i = 0; i < ordem; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs(i, dfs);
        }
    }
    return componentes;
}

bool GrafoMatriz::ehArvore() {
    return (nConexo() == 1 && (numVertices - 1) == getOrdem());
}

bool GrafoMatriz::possuiPonte() {
    for (int u = 0; u < numVertices; u++) {
        for (int v = 0; v < numVertices; v++) {
            if (matrizAdj[u][v]) {
                matrizAdj[u][v] = 0;
                if (nConexo() > 1) {
                    matrizAdj[u][v] = 1;
                    return true;
                }
                matrizAdj[u][v] = 1;
            }
        }
    }
    return false;
}

bool GrafoMatriz::possuiArticulacao() {
    vector<bool> visitado(numVertices);
    int componentesOriginais = nConexo();

    for (int v = 0; v < numVertices; v++) {
        fill(visitado.begin(), visitado.end(), false);
        visitado[v] = true;

        int componentes = 0;
        for (int u = 0; u < numVertices; u++) {
            if (!visitado[u]) {
                componentes++;
                auto dfs = [&](int x, auto& dfsRef) -> void {
                    visitado[x] = true;
                    for (int i = 0; i < numVertices; i++) {
                        if (matrizAdj[x][i] && !visitado[i]) {
                            dfsRef(i, dfsRef);
                        }
                    }
                };
                dfs(u, dfs);
            }
        }

        if (componentes > componentesOriginais) {
            return true;
        }
    }
    return false;
}

void GrafoMatriz::carregaGrafo(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << arquivo << std::endl;
        return;
    }

    int numNos, direcionado, ponderadoVertices, ponderadoArestas;
    file >> numNos >> direcionado >> ponderadoVertices >> ponderadoArestas;

    this->ordem = numNos;
    this->direcionado = direcionado;
    this->ponderadoVertices = ponderadoVertices;
    this->ponderadoArestas = ponderadoArestas;

    if (ponderadoVertices) {
        std::cout << "Pesos dos vértices:" << std::endl;
        for (int i = 0; i < numNos; i++) {
            int pesoVertice;
            file >> pesoVertice;
            std::cout << "Vértice " << i + 1 << ": Peso " << pesoVertice << std::endl;
        }
    }

    matrizAdj.resize(numNos, std::vector<int>(numNos, 0));

    int origem, destino, peso;
    while (file >> origem >> destino >> peso) {
        origem--; // Ajusta para índices baseados em 0
        destino--;
        matrizAdj[origem][destino] = peso;
        if (!direcionado) {
            matrizAdj[destino][origem] = peso;
        }
        std::cout << "Aresta adicionada: " << origem + 1 << " -> " << destino + 1 << " com peso " << peso << std::endl;
    }

    file.close();
    std::cout << "Matriz de Adjacência carregada com sucesso." << std::endl;
}

void GrafoMatriz::novoGrafo(const std::string& arquivoConfig) {
    std::ifstream file(arquivoConfig);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de configuração: " << arquivoConfig << std::endl;
        return;
    }

    std::string estrutura;
    file >> estrutura; // Lê a estrutura (matriz ou lista)

    file >> ordem >> direcionado >> ponderadoVertices >> ponderadoArestas;
    matrizAdj.resize(ordem, std::vector<int>(ordem, 0));

    int origem, destino, peso;
    while (file >> origem >> destino >> peso) {
        origem--;
        destino--;
        matrizAdj[origem][destino] = peso;
        if (!direcionado) {
            matrizAdj[destino][origem] = peso;
        }
    }

    file.close();
    std::cout << "Novo grafo configurado como " << estrutura << "." << std::endl;
}