
# Projeto de Implementação de Grafos

Este projeto é uma implementação de estruturas e funcionalidades relacionadas a grafos em C++. Ele permite carregar grafos a partir de arquivos, realizar análises como conexidade, verificação de árvores, detecção de arestas ponte, entre outras.

## Funcionalidades

- **Representação de grafos**:
  - Matriz de adjacência
  - Lista de adjacência
- **Carregamento de grafos**:
  - A partir de arquivos de entrada (`grafo.txt` e `descricao.txt`)
- **Análises**:
  - Componentes conexas
  - Verificação de completude
  - Detecção de bipartidos
  - Identificação de arestas ponte
  - Identificação de vértices de articulação

## Estrutura de Arquivos

### Exemplo de `grafo.txt`

```
3 1 1 1
2 3 7
1 2 6
2 1 4
2 3 -5
```
- Linha 1: `nós direcionado ponderado_vertices ponderado_arestas`
- Linha 2: Pesos dos vértices (opcional, dependendo do grafo)
- Linhas seguintes: `origem destino peso`

### Exemplo de `descricao.txt`

```
matriz
3
3
1
2
1
1
0
1
0
1
1
```
- Linha 1: Tipo da representação (`matriz` ou `lista`)
- Demais linhas: Informam propriedades do grafo (grau, ordem, conexidade etc.)

## Como Compilar

Certifique-se de que você tenha um compilador C++ instalado, como o **g++**.

1. Compile o projeto:
   ```bash
   g++ -std=c++14 -Wall -Iinclude -o grafo_exec src/*.cpp
   ```

2. Execute o programa:
   - Para carregar um grafo como **matriz**:
     ```bash
     .\grafo_exec.exe -m grafo.txt
     ```
   - Para carregar um grafo como **lista**:
     ```bash
     .\grafo_exec.exe -l grafo.txt
     ```
   - Para carregar um grafo a partir de um arquivo de configuração:
     ```bash
     .\grafo_exec.exe -c descricao.txt
     ```

## Saída Esperada

Exemplo de saída:

```
========== Descrição do Grafo ==========
Ordem: 3
Direcionado: Sim
Vertices ponderados: Sim
Arestas ponderadas: Sim
Grau do vértice 0: 1
Componentes conexas: 1
Completo: Não
Bipartido: Sim
Árvore: Não
Aresta Ponte: Sim
Vértice de Articulação: Sim
========================================
```

## Estrutura do Código

- `main.cpp`: Ponto de entrada do programa.
- `Grafo.h` e `Grafo.cpp`: Classe base para grafos.
- `GrafoMatriz.h` e `GrafoMatriz.cpp`: Implementação da representação por matriz de adjacência.
- `GrafoLista.h` e `GrafoLista.cpp`: Implementação da representação por lista de adjacência.
- `Aresta.h` e `Aresta.cpp`: Classe para representação de arestas.
- `No.h` e `No.cpp`: Classe para representação de nós.

## Requisitos

- **Compilador C++** (suporta padrão C++14 ou superior).
- Sistema operacional Windows, Linux ou macOS.