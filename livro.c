#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

/* =========================================================
 * TAD Livro - Implementação das funções
 * ========================================================= */

Livro *criarLivro(int codigo, char titulo[], char autor[],
                  int ano, int quantidadeTotal)
{
    Livro *novo = (Livro *)malloc(sizeof(Livro));
    if (novo == NULL) {
        printf("Erro: falha ao alocar memória para livro.\n");
        return NULL;
    }

    novo->codigo             = codigo;
    novo->ano                = ano;
    novo->quantidadeTotal    = quantidadeTotal;
    novo->quantidadeDisponivel = quantidadeTotal;

    strncpy(novo->titulo, titulo, 99);
    novo->titulo[99] = '\0';

    strncpy(novo->autor, autor, 99);
    novo->autor[99] = '\0';

    return novo;
}

void exibirLivro(Livro *livro)
{
    if (livro == NULL) {
        printf("Livro inválido.\n");
        return;
    }
    printf("------------------------------------------\n");
    printf("Código   : %d\n",  livro->codigo);
    printf("Título   : %s\n",  livro->titulo);
    printf("Autor    : %s\n",  livro->autor);
    printf("Ano      : %d\n",  livro->ano);
    printf("Total    : %d exemplar(es)\n", livro->quantidadeTotal);
    printf("Disponível: %d exemplar(es)\n", livro->quantidadeDisponivel);
    printf("------------------------------------------\n");
}

int obterCodigoLivro(Livro *livro)
{
    if (livro == NULL) return -1;
    return livro->codigo;
}

int obterQuantidadeDisponivel(Livro *livro)
{
    if (livro == NULL) return 0;
    return livro->quantidadeDisponivel;
}

void emprestarExemplar(Livro *livro)
{
    if (livro == NULL) return;
    if (livro->quantidadeDisponivel > 0)
        livro->quantidadeDisponivel--;
}

void devolverExemplar(Livro *livro)
{
    if (livro == NULL) return;
    if (livro->quantidadeDisponivel < livro->quantidadeTotal)
        livro->quantidadeDisponivel++;
}
