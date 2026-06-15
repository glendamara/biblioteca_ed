#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

/* Fila de Reservas - Implementação (política FIFO) */

Fila *criarFila(void)
{
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    if (fila == NULL) {
        printf("Erro: falha ao alocar fila.\n");
        return NULL;
    }
    fila->inicio = NULL;
    fila->fim    = NULL;
    return fila;
}

void enfileirarReserva(Fila *fila, Reserva reserva)
{
    if (fila == NULL) return;

    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    if (novo == NULL) {
        printf("Erro: falha ao alocar nó da fila.\n");
        return;
    }

    novo->reserva  = reserva;
    novo->proximo  = NULL;

    if (filaVazia(fila)) {
        fila->inicio = novo;
        fila->fim    = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim          = novo;
    }

    printf("Reserva de '%s' para o livro %d adicionada à fila.\n",
           reserva.nomeUsuario, reserva.codigoLivro);
}

Reserva desenfileirarReserva(Fila *fila)
{
    Reserva vazia;
    memset(&vazia, 0, sizeof(Reserva));

    if (fila == NULL || filaVazia(fila)) {
        printf("Fila de reservas vazia.\n");
        return vazia;
    }

    NoFila  *temp    = fila->inicio;
    Reserva  reserva = temp->reserva;

    fila->inicio = temp->proximo;
    if (fila->inicio == NULL)
        fila->fim = NULL;

    free(temp);
    return reserva;
}

int filaVazia(Fila *fila)
{
    return (fila == NULL || fila->inicio == NULL);
}

void exibirReservas(Fila *fila)
{
    if (filaVazia(fila)) {
        printf("Nenhuma reserva na fila.\n");
        return;
    }

    printf("\n=== Fila de Reservas ===\n");
    NoFila *atual = fila->inicio;
    int posicao   = 1;

    while (atual != NULL) {
        printf("[%d] Usuário: %-30s | Livro código: %d\n",
               posicao, atual->reserva.nomeUsuario,
               atual->reserva.codigoLivro);
        atual = atual->proximo;
        posicao++;
    }
    printf("========================\n");
}

int existeReservaParaLivro(Fila *fila, int codigoLivro)
{
    if (filaVazia(fila)) return 0;

    NoFila *atual = fila->inicio;
    while (atual != NULL) {
        if (atual->reserva.codigoLivro == codigoLivro)
            return 1;
        atual = atual->proximo;
    }
    return 0;
}
