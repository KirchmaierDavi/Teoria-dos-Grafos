#include "GrafoLista.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

GrafoLista::GrafoLista(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas)
    : Grafo(ordem, direcionado, ponderadoVertices, ponderadoArestas) {
    listaAdj.resize(ordem);
}

GrafoLista::~GrafoLista() {}

int GrafoLista::getGrau(int vertice) {
    return listaAdj[vertice].size();
}

bool GrafoLista::ehCompleto() {
    for (int i = 0; i < ordem; i++) {
        if (listaAdj[i].size() != static_cast<size_t>(ordem - 1)) {
            return false;
        }
    }
    return true;
}

bool GrafoLista::ehBipartido() {
    vector<int> cores(ordem, -1); // -1 significa não colorido
    queue<int> fila;

    cores[0] = 1; // Começa colorindo o primeiro vértice
    fila.push(0);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (const auto& adj : listaAdj[u]) {
            int v = adj.first;
            if (cores[v] == -1) {
                cores[v] = 1 - cores[u];
                fila.push(v);
            } else if (cores[v] == cores[u]) {
                return false;
            }
        }
    }
    return true;
}

int GrafoLista::nConexo() {
    vector<bool> visitado(ordem, false);
    int componentes = 0;

    auto dfs = [&](int v, auto& dfsRef) -> void {
        visitado[v] = true;
        for (const auto& adj : listaAdj[v]) {
            if (!visitado[adj.first]) {
                dfsRef(adj.first, dfsRef);
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

bool GrafoLista::ehArvore() {
    return (nConexo() == 1 && listaAdj.size() == static_cast<size_t>(ordem - 1));
}

bool GrafoLista::possuiPonte() {
    vector<vector<bool>> matrizAdj(ordem, vector<bool>(ordem, false));

    for (int u = 0; u < ordem; u++) {
        for (const auto& adj : listaAdj[u]) {
            matrizAdj[u][adj.first] = true;
            if (!direcionado) {
                matrizAdj[adj.first][u] = true;
            }
        }
    }

    for (int u = 0; u < ordem; u++) {
        for (const auto& adj : listaAdj[u]) {
            int v = adj.first;

            // Remove a aresta
            matrizAdj[u][v] = matrizAdj[v][u] = false;

            // Verifica componentes
            vector<bool> visitado(ordem, false);
            auto dfs = [&](int v, auto& dfsRef) -> void {
                visitado[v] = true;
                for (int w = 0; w < ordem; w++) {
                    if (matrizAdj[v][w] && !visitado[w]) {
                        dfsRef(w, dfsRef);
                    }
                }
            };

            int componentes = 0;
            for (int i = 0; i < ordem; i++) {
                if (!visitado[i]) {
                    componentes++;
                    dfs(i, dfs);
                }
            }

            if (componentes > 1) {
                return true;
            }

            // Reinsere a aresta
            matrizAdj[u][v] = matrizAdj[v][u] = true;
        }
    }

    return false;
}

bool GrafoLista::possuiArticulacao() {
    vector<bool> visitado(ordem);
    int componentesOriginais = nConexo();

    for (int v = 0; v < ordem; v++) {
        fill(visitado.begin(), visitado.end(), false);
        visitado[v] = true;

        int componentes = 0;
        for (int u = 0; u < ordem; u++) {
            if (!visitado[u]) {
                componentes++;
                auto dfs = [&](int x, auto& dfsRef) -> void {
                    visitado[x] = true;
                    for (const auto& adj : listaAdj[x]) {
                        if (!visitado[adj.first]) {
                            dfsRef(adj.first, dfsRef);
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

void GrafoLista::carregaGrafo(const std::string& arquivo) {
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

    listaAdj.resize(numNos);

    int origem, destino, peso;
    while (file >> origem >> destino >> peso) {
        origem--; // Ajusta para índices baseados em 0
        destino--;
        listaAdj[origem].emplace_back(destino, peso);
        if (!direcionado) {
            listaAdj[destino].emplace_back(origem, peso);
        }
        std::cout << "Aresta adicionada: " << origem + 1 << " -> " << destino + 1 << " com peso " << peso << std::endl;
    }

    file.close();
    std::cout << "Lista de Adjacência carregada com sucesso." << std::endl;
}

void GrafoLista::novoGrafo(const std::string& arquivoConfig) {
    std::ifstream file(arquivoConfig);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de configuração!" << std::endl;
        return;
    }

    std::string tipo;
    file >> tipo;  // Ignora "matriz" ou "lista"
    file >> ordem >> direcionado >> ponderadoVertices >> ponderadoArestas;
    listaAdj.clear();
    listaAdj.resize(ordem);

    int origem, destino, peso;
    while (file >> origem >> destino >> peso) {
        listaAdj[origem].emplace_back(destino, peso);
        if (!direcionado) {
            listaAdj[destino].emplace_back(origem, peso);
        }
    }

    file.close();
}
