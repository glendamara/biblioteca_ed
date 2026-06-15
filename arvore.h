#ifndef ARVORE_H
#define ARVORE_H

#include "livro.h"

/* Árvore Binária de Busca (ABB) de Livros - Definições */

typedef struct NoArvore {
    Livro           *livro;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct {
    NoArvore *raiz;
} Arvore;

/* Cria e retorna uma árvore vazia */
Arvore *criarArvore(void);

/* Insere um livro na árvore pelo campo codigo.
   Não aceita códigos duplicados. */
void inserirLivroArvore(Arvore *arvore, Livro *livro);

/* Busca um livro pelo código; retorna NULL se não encontrado */
Livro *buscarLivroArvore(Arvore *arvore, int codigo);

/* Percurso em ordem (esq - raiz - dir) — ordem crescente de código */
void listarLivrosEmOrdem(Arvore *arvore);

/* Percurso em pré-ordem (raiz - esq - dir) */
void listarLivrosPreOrdem(Arvore *arvore);

/* Percurso em pós-ordem (esq - dir - raiz) */
void listarLivrosPosOrdem(Arvore *arvore);

/* Retorna o número total de livros cadastrados */
int contarLivros(Arvore *arvore);

/* Retorna a altura da árvore (-1 se vazia) */
int calcularAlturaArvore(Arvore *arvore);

#endif /* ARVORE_H */
