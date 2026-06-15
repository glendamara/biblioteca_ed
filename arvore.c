#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

/* Árvore Binária de Busca (ABB) - Implementação */

/* -- funções auxiliares (estáticas / internas) -- */

static NoArvore *criarNo(Livro *livro)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
        printf("Erro: falha ao alocar nó da árvore.\n");
        return NULL;
    }
    no->livro     = livro;
    no->esquerda  = NULL;
    no->direita   = NULL;
    return no;
}

static NoArvore *inserirRec(NoArvore *no, Livro *livro)
{
    if (no == NULL)
        return criarNo(livro);

    int cod    = obterCodigoLivro(livro);
    int codNo  = obterCodigoLivro(no->livro);

    if (cod < codNo)
        no->esquerda = inserirRec(no->esquerda, livro);
    else if (cod > codNo)
        no->direita  = inserirRec(no->direita,  livro);
    else
        printf("Atenção: livro com código %d já está cadastrado.\n", cod);

    return no;
}

static NoArvore *buscarRec(NoArvore *no, int codigo)
{
    if (no == NULL) return NULL;

    int codNo = obterCodigoLivro(no->livro);

    if (codigo == codNo) return no;
    if (codigo  < codNo) return buscarRec(no->esquerda, codigo);
    return buscarRec(no->direita, codigo);
}

static void emOrdemRec(NoArvore *no)
{
    if (no == NULL) return;
    emOrdemRec(no->esquerda);
    exibirLivro(no->livro);
    emOrdemRec(no->direita);
}

static void preOrdemRec(NoArvore *no)
{
    if (no == NULL) return;
    exibirLivro(no->livro);
    preOrdemRec(no->esquerda);
    preOrdemRec(no->direita);
}

static void posOrdemRec(NoArvore *no)
{
    if (no == NULL) return;
    posOrdemRec(no->esquerda);
    posOrdemRec(no->direita);
    exibirLivro(no->livro);
}

static int contarRec(NoArvore *no)
{
    if (no == NULL) return 0;
    return 1 + contarRec(no->esquerda) + contarRec(no->direita);
}

static int alturaRec(NoArvore *no)
{
    if (no == NULL) return -1;

    int altEsq = alturaRec(no->esquerda);
    int altDir = alturaRec(no->direita);

    return 1 + (altEsq > altDir ? altEsq : altDir);
}

/* ----- funções públicas ---- */

Arvore *criarArvore(void)
{
    Arvore *arvore = (Arvore *)malloc(sizeof(Arvore));
    if (arvore == NULL) {
        printf("Erro: falha ao alocar árvore.\n");
        return NULL;
    }
    arvore->raiz = NULL;
    return arvore;
}

void inserirLivroArvore(Arvore *arvore, Livro *livro)
{
    if (arvore == NULL || livro == NULL) return;
    arvore->raiz = inserirRec(arvore->raiz, livro);
}

Livro *buscarLivroArvore(Arvore *arvore, int codigo)
{
    if (arvore == NULL) return NULL;
    NoArvore *resultado = buscarRec(arvore->raiz, codigo);
    return resultado ? resultado->livro : NULL;
}

void listarLivrosEmOrdem(Arvore *arvore)
{
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    printf("\n=== Listagem em Ordem (crescente por código) ===\n");
    emOrdemRec(arvore->raiz);
}

void listarLivrosPreOrdem(Arvore *arvore)
{
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    printf("\n=== Listagem em Pré-Ordem ===\n");
    preOrdemRec(arvore->raiz);
}

void listarLivrosPosOrdem(Arvore *arvore)
{
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    printf("\n=== Listagem em Pós-Ordem ===\n");
    posOrdemRec(arvore->raiz);
}

int contarLivros(Arvore *arvore)
{
    if (arvore == NULL) return 0;
    return contarRec(arvore->raiz);
}

int calcularAlturaArvore(Arvore *arvore)
{
    if (arvore == NULL) return -1;
    return alturaRec(arvore->raiz);
}
