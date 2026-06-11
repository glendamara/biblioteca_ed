#ifndef LIVRO_H
#define LIVRO_H

/* =========================================================
 * TAD Livro - Definição da estrutura e declaração das funções
 * ========================================================= */

typedef struct {
    int  codigo;
    char titulo[100];
    char autor[100];
    int  ano;
    int  quantidadeTotal;
    int  quantidadeDisponivel;
} Livro;

/* Cria e retorna um ponteiro para um novo livro */
Livro *criarLivro(int codigo, char titulo[], char autor[],
                  int ano, int quantidadeTotal);

/* Exibe todas as informações do livro */
void exibirLivro(Livro *livro);

/* Retorna o código do livro */
int obterCodigoLivro(Livro *livro);

/* Retorna a quantidade de exemplares disponíveis */
int obterQuantidadeDisponivel(Livro *livro);

/* Decrementa a quantidade disponível (empréstimo) */
void emprestarExemplar(Livro *livro);

/* Incrementa a quantidade disponível (devolução) */
void devolverExemplar(Livro *livro);

#endif /* LIVRO_H */
