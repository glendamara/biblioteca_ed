#ifndef LISTA_H
#define LISTA_H

/* Lista Encadeada de Histórico de Empréstimos - Definições*/

typedef struct {
    char nomeUsuario[100];
    int  codigoLivro;
    char tituloLivro[100];
} Emprestimo;

typedef struct NoLista {
    Emprestimo      emprestimo;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *inicio;
} Lista;

/* Cria e retorna uma lista vazia */
Lista *criarLista(void);

/* Insere um empréstimo no início da lista */
void inserirEmprestimo(Lista *lista, Emprestimo emprestimo);

/* Exibe todos os registros de empréstimo */
void listarEmprestimos(Lista *lista);

/* Retorna 1 se a lista estiver vazia, 0 caso contrário */
int listaVazia(Lista *lista);

#endif /* LISTA_H */
