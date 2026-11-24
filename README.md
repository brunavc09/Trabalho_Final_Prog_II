#  Sistema de Gestão de Estoque e Custos para Marcenaria
Projeto final da disciplina Programação II do curso de Engenharia de Telecomunicações.

Sistema escrito em linguagem C, desenvolvido no CLion, que organiza o estoque de materiais de uma marcenaria e calcula o custo dos materiais usados em um serviço.

## 1. Descrição do projeto

O programa mantém um cadastro de materiais (parafusos, madeiras, ferramentas etc.) e permite cadastrar, buscar, remover e salvar esses materiais em arquivo. Um módulo de gastos calcula o custo de um serviço a partir dos materiais e das quantidades utilizadas, conferindo o estoque disponível.

## 2. A instituição escolhida

- Nome: RJ Móveis.
- O que é e o que faz: É uma marcenaria, com foco na produção de móveis sob medida.
- Quem atende: Clientes.
- Real ou idealizada: Instituição real de fácil acesso para as alunas, o que permitiu trocas com a equipe da empresa durante todo o processo garantindo que o resultado suprisse de fato suas necessidades.
- Contato com a instituição: O contato foi com Juciane, sócia da empresa responsável pela criação dos projetos realizados e contato com fornecedores, devido a isso tem ligação direta com o estoque e os gastos permitindo que entendêssemos a fundo suas necessidades.

## 3. Justificativa

Como mencionado anteriormente, a marcenaria é de fácil contato permitindo feedbacks constantes e, além disso, as necessidades apresentadas se enquadravam dentro dos parâmetros estabelecidos da atividade.

Problemas relatados: dificuldade de saber o que há em estoque e onde está guardado; compra de material sem necessidade ou falta de material no meio de um serviço; perda de informação quando o controle é feito de memória ou em papel.

## 4. Funcionalidades

Implementadas

- Cadastro de materiais, com ID automático;
- Busca de material por nome (parcial, por trecho do nome) e por ID;
- Remoção de material;
- Persistência em arquivo de texto: o estoque é salvo e carregado, e a numeração dos códigos continua de onde parou;
- Cálculo de custos de um serviço (módulo de gastos), com validação da quantidade disponível em estoque;
- Edição de material;
- Listagem ordenada do estoque (relatório);
- Menu de uso no terminal.

 Outros comportamentos:

- Validação das entradas numéricas (aceita vírgula ou ponto como separador decimal; rejeita texto, nan e inf).
- No cálculo de gastos, a palavra Sair encerra a operação e devolve o total parcial.
- Se a busca por nome encontrar vários materiais, eles são listados e o usuário refina com marca e/ou especificações.

- ## 5. Estruturas de dados utilizadas

 Estrutura | Onde é usada | Arquivo | Por que esta e não outra |
|---|---|---|---|
| Árvore AVL (chave: id) | Armazena todo o estoque | estoque.c, arquivo.c, main.c | Os IDs são gerados em ordem crescente. Em uma ABP sem balanceamento, inserir IDs sequenciais degeneraria a árvore em uma lista (busca O(n)). A AVL mantém a altura em O(log n) na busca, inserção e remoção. Um vetor exigiria deslocar elementos na remoção. |
| Pilha (LIFO) | Desfazer a última edição | main.c (no_pilha_t) | A última edição feita deve ser a primeira desfeita, o que é exatamente o comportamento LIFO. Fila ou lista comum não modelam isso naturalmente. |
| Lista encadeada simples (com ponteiro para o fim) | Monta o relatório de materiais com estoque baixo | main.c (no_lista_t) | O número de itens do relatório não é conhecido de antemão. A lista cresce sob demanda, com inserção no fim em O(1), sem realocar vetor. |

Decisões de projeto

- Nó genérico (void). A AVL fica em uma biblioteca separada (libprg) e guarda um ponteiro genérico para o dado. Assim ela não depende da estrutura material, e o estoque faz a conversão de volta para material.
- Dono da memória. A árvore nunca libera o material. Quem cadastra aloca, e quem remove libera, depois de retirar o nó da árvore.
- Busca por nome. Como a árvore é organizada por código, a busca por nome percorre a árvore inteira em ordem (custo O(n)). Para o tamanho de um estoque de marcenaria, o custo é aceitável, e evita manter duas árvores sincronizadas.
- Código sequencial. Garante código único sem precisar verificar duplicidade, e o contador é salvo no arquivo.

## 6. Como compilar e executar

Requisitos

- CMake 3.21 ou superior
- Compilador C (GCC, Clang ou MinGW)
- Conexão com a internet na primeira compilação, pois a libprg é baixada do GitHub (github.com/brunavc09/libprg, versão v1.2) pelo FetchContent


bash
cmake -S . -B build
cmake --build build
./build/Trabalho_Final_Prog_II          # Linux/macOS/Git Bash
.\build\Trabalho_Final_Prog_II.exe      # Windows (CMD/PowerShell)

Há um segundo executável, teste_estoque, que testa o cadastro, a busca e a persistência sem menu.

Observação para Windows: o programa configura o console para UTF-8 automaticamente. Se os acentos aparecerem trocados, confira se os arquivos estão salvos em UTF-8.

Observações

- O programa lê e grava o arquivo estoque.txt na pasta em que é executado. Se o arquivo não existir, o estoque começa vazio.

## 7. Organização do repositório

```
├── CMakeLists.txt        configuração da compilação
├── README.md
├── include/
│   ├── estoque.h         materiais e operações do estoque
│   ├── arquivo.h         salvar e carregar o estoque
│   └── gastos.h          cálculo de custos
│   └── entrada.h         funções utilizadas para teste
├── src/
│   ├── main.c
│   ├── estoque.c
│   ├── arquivo.c
│   └── gastos.c
│   └── entrada.c
└── tests/
    └── teste_arquivo.c   programa de teste (executável teste_estoque)
    └── teste_entrada.c   
```

A biblioteca libprg (estruturas de dados) fica em um repositório separado e é baixada na compilação.

Formato do arquivo estoque.txt:

<próximo id>
<id>;<insumo>;<marca>;<especificações>;<quantidade>;<valor unitário>;<local>

O caractere ";" digitado pelo usuário é trocado por "," na leitura, para não quebrar o formato.

## 8. Dificuldades encontradas e o que foi aprendido

- Aprender como tornar o código compatível com Windows e Linux devido ao uso de funções como strcasecmp e o uso de palavras acentuadas;
- Como tratar possíveis entradas inválidas;
- A criação de uma AVL genérica que pudesse ser utilizada de diversas formas, por exemplo, permitindo a conversão de void * para material *;
- Como implementar uma busca por nome na AVL, tendo ID como critério de ordenação.

## 9. Declaração de uso de IA

| Ferramenta | Finalidade | Trecho / arquivo afetado |
|---|---|---|
|Claude| Revisão de erros sem reescrever o código | gastos.c e estoque.c|
|CLaude| Revisão da descrição do projeto para erros de ortografia | README |
|Claude| Criação de dados fictícios para teste | teste_arquivo.c e teste_entrada.c |


## 10. Autoria

| Nome completo | Matrícula |
|---|---|
| Bárbara Boeng | 202610406143 |
| Bruna Vieira da Cunha | 202610403743 |
