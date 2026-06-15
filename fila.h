#ifndef FILA_H
#define FILA_H

/* Fila de Reservas - Definições (política FIFO)*/

typedef struct {
    char nomeUsuario[100];
    int  codigoLivro;
} Reserva;

typedef struct NoFila {
    Reserva         reserva;
    struct NoFila  *proximo;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;

/* Cria e retorna uma fila vazia */
Fila *criarFila(void);

/* Insere uma reserva no fim da fila */
void enfileirarReserva(Fila *fila, Reserva reserva);

/* Remove e retorna a reserva do início da fila */
Reserva desenfileirarReserva(Fila *fila);

/* Retorna 1 se a fila estiver vazia, 0 caso contrário */
int filaVazia(Fila *fila);

/* Exibe todas as reservas da fila sem removê-las */
void exibirReservas(Fila *fila);

/* Verifica se há reserva para um código de livro específico */
int existeReservaParaLivro(Fila *fila, int codigoLivro);

#endif /* FILA_H */
