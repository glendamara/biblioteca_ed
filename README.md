# biblioteca_ed
Sistema de Gerenciamento de Biblioteca com TADs, Lista, Fila e Árvore  Binária de Busca

# Sistema de Gerenciamento de Biblioteca 📚

Trabalho prático desenvolvido para a disciplina de **Estrutura de Dados** do curso de Ciência da Computação da **Universidade Estadual do Ceará (UECE)**.

## 👥 Equipe
* **Integrante 1**: [Seu Nome Completo] - Matrícula: [XXXXXXX]
* **Integrante 2**: [Nome do Integrante 2] - Matrícula: [XXXXXXX]
* **Integrante 3**: [Nome do Integrante 3] - Matrícula: [XXXXXXX]

## 📝 Descrição do Sistema
Este sistema consiste em uma aplicação em modo texto (terminal) voltada para o controle e gerenciamento do acervo de uma biblioteca. O grande diferencial do projeto é a implementação manual e integrada de estruturas de dados lineares e não lineares para garantir eficiência nas operações, sem a utilização de bibliotecas prontas de armazenamento dinâmico.

As principais estruturas utilizadas são:
* **Árvore Binária de Busca (ABB)**: Estrutura principal, responsável por armazenar, organizar e buscar os livros de forma rápida utilizando o `codigo` único como chave.
* **Fila Encadeada (FIFO)**: Utilizada para gerenciar a lista de espera e reservas de usuários quando um livro solicitado não possui exemplares disponíveis para empréstimo imediato.
* **Lista Encadeada Simples**: Destinada a registrar e manter de forma sequencial o histórico de todos os empréstimos bem-sucedidos realizados no sistema.

---

## 🛠️ Estrutura de Arquivos do Projeto
O projeto está organizado de forma modular nos seguintes arquivos:
* `main.c`: Contém o menu interativo e a integração lógica entre as estruturas.
* `livro.h` / `livro.c`: Definição do TAD Livro e suas operações de manipulação.
* `arvore.h` / `arvore.c`: Implementação da Árvore Binária de Busca e percursos.
* `fila.h` / `fila.c`: Implementação da fila dinâmica para controle de reservas.
* `lista.h` / `lista.c`: Implementação da lista encadeada para histórico de empréstimos.

---

## 🚀 Como Compilar e Executar

Para compilar o projeto de forma correta, garantindo a ligação de todos os módulos, utilize o compilador `gcc` através do terminal com o comando abaixo:

```bash
gcc main.c livro.c arvore.c fila.c lista.c -o biblioteca