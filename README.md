# Trabalho 02: Análise Empírica de Algoritmos de Ordenação

# Apresentação

Nesse trabalho você terá a oportunidade de desenvolver algoritmos clássicos de ordenação e realizar um experimento empírico com esses algoritmos.

Para a realização do experimento, é recomendado o desenvolvimento de um sistema computacional que permita a execução e coleta de dados de acordo com os cenários experimentais apresentados no documento descritivo do projeto, o qual pode ser encontrado [**aqui**](docs/sorting_algorithms.pdf).

Por fim, você precisará elaborar um relatório técnico completo, no qual você apresenta o projeto que foi desenvolvido e tenta responder as perguntas de pesquisa presentes no PDF do projeto.

Você precisa fornecer algumas informações no arquivo [author.md](author.md), indicando a autoria do trabalho e quais itens da tarefa foram realizados com sucesso. 


# Compilando e Executando

## Manualmente com g++

Para compilar e executar o programa manualmente basta digitar os seguintes comandos em seu terminal:

```
$ mkdir bin (caso não tenha uma pasta para os executáveis, você deve criá-la com esse comando)
$ g++ -Wall -std=c++11 -g source/main.cpp -I source/lib -o bin/sortsuite (compilar)
$ ./bin/sortsuite (executar)
```

## Cmake

Para compilar e executar o programa com o Cmake você precisa ter instalado pelo menos a versão 3.15. Em seguida, abra seu terminal e execute os seguintes comandos:

```
$ cmake -S source -B build (pede ao cmake para criar o diretório de compilação)
$ cmake --build build (compilar)
$ ./build/sortsuite (executar)
```

--------
&copy; DIMAp/UFRN 2021.
