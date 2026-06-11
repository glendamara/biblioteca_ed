#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* =========================================================
 * Lista Encadeada de Histórico de Empréstimos - Implementação
 * ========================================================= */

Lista *criarLista(void)
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    if (lista == NULL) {
        printf("Erro: falha ao alocar lista.\n");
        return NULL;
    }
    lista->inicio = NULL;
    return lista;
}

void inserirEmprestimo(Lista *lista, Emprestimo emprestimo)
{
    if (lista == NULL) return;

    NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
    if (novo == NULL) {
        printf("Erro: falha ao alocar nó da lista.\n");
        return;
    }

    novo->emprestimo = emprestimo;
    /* Insere no início da lista */
    novo->proximo  = lista->inicio;
    lista->inicio  = novo;
}

void listarEmprestimos(Lista *lista)
{
    if (listaVazia(lista)) {
        printf("Nenhum empréstimo registrado no histórico.\n");
        return;
    }

    printf("\n=== Histórico de Empréstimos ===\n");
    NoLista *atual  = lista->inicio;
    int      numero = 1;

    while (atual != NULL) {
        printf("[%d] Usuário : %s\n",    numero, atual->emprestimo.nomeUsuario);
        printf("     Livro   : %s (código %d)\n",
               atual->emprestimo.tituloLivro,
               atual->emprestimo.codigoLivro);
        printf("     --------------------------------\n");
        atual = atual->proximo;
        numero++;
    }
}

int listaVazia(Lista *lista)
{
    return (lista == NULL || lista->inicio == NULL);
}
