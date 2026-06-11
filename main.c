#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"
#include "arvore.h"
#include "fila.h"
#include "lista.h"

/* =========================================================
 * Sistema de Gerenciamento de Biblioteca
 * Disciplina: Estrutura de Dados - UECE
 * ========================================================= */

/* ---------- utilitários ---------- */

/* Lê uma linha do stdin, descartando o '\n', com tamanho máximo max-1 */
static void lerString(char *destino, int max)
{
    if (fgets(destino, max, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n')
            destino[len - 1] = '\0';
    }
}

/* Limpa o buffer de entrada após leitura numérica */
static void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ---------- funções do menu ---------- */

static void cadastrarLivro(Arvore *arvore)
{
    int  codigo, ano, qtd;
    char titulo[100], autor[100];

    printf("\n--- Cadastrar Novo Livro ---\n");

    printf("Código      : ");
    scanf("%d", &codigo);
    limparBuffer();

    /* Verifica duplicata antes de pedir os demais dados */
    if (buscarLivroArvore(arvore, codigo) != NULL) {
        printf("Erro: já existe um livro com o código %d.\n", codigo);
        return;
    }

    printf("Título      : ");
    lerString(titulo, 100);

    printf("Autor       : ");
    lerString(autor, 100);

    printf("Ano         : ");
    scanf("%d", &ano);
    limparBuffer();

    printf("Qtd. total  : ");
    scanf("%d", &qtd);
    limparBuffer();

    if (qtd <= 0) {
        printf("Erro: a quantidade deve ser maior que zero.\n");
        return;
    }

    Livro *livro = criarLivro(codigo, titulo, autor, ano, qtd);
    if (livro == NULL) return;

    inserirLivroArvore(arvore, livro);
    printf("Livro '%s' cadastrado com sucesso!\n", titulo);
}

static void buscarLivro(Arvore *arvore)
{
    int codigo;
    printf("\n--- Buscar Livro por Código ---\n");
    printf("Código: ");
    scanf("%d", &codigo);
    limparBuffer();

    Livro *livro = buscarLivroArvore(arvore, codigo);
    if (livro == NULL)
        printf("Livro com código %d não encontrado.\n", codigo);
    else
        exibirLivro(livro);
}

static void realizarEmprestimo(Arvore *arvore, Fila *fila, Lista *lista)
{
    char nomeUsuario[100];
    int  codigo;

    printf("\n--- Realizar Empréstimo ---\n");
    printf("Nome do usuário : ");
    lerString(nomeUsuario, 100);

    printf("Código do livro : ");
    scanf("%d", &codigo);
    limparBuffer();

    Livro *livro = buscarLivroArvore(arvore, codigo);
    if (livro == NULL) {
        printf("Erro: livro com código %d não encontrado.\n", codigo);
        return;
    }

    if (obterQuantidadeDisponivel(livro) > 0) {
        /* Há exemplar disponível — realiza o empréstimo */
        emprestarExemplar(livro);

        /* Registra no histórico */
        Emprestimo emp;
        strncpy(emp.nomeUsuario, nomeUsuario, 99);
        emp.nomeUsuario[99] = '\0';
        emp.codigoLivro = codigo;
        strncpy(emp.tituloLivro, livro->titulo, 99);
        emp.tituloLivro[99] = '\0';

        inserirEmprestimo(lista, emp);
        printf("Empréstimo realizado com sucesso!\n");
        printf("Usuário '%s' retirou '%s'.\n", nomeUsuario, livro->titulo);
    } else {
        /* Sem exemplares disponíveis */
        printf("Não há exemplares disponíveis de '%s'.\n", livro->titulo);
        printf("Deseja entrar na fila de reservas? (s/n): ");

        char opcao[4];
        lerString(opcao, 4);

        if (opcao[0] == 's' || opcao[0] == 'S') {
            Reserva res;
            strncpy(res.nomeUsuario, nomeUsuario, 99);
            res.nomeUsuario[99] = '\0';
            res.codigoLivro     = codigo;
            enfileirarReserva(fila, res);
        } else {
            printf("Operação cancelada.\n");
        }
    }
}

static void realizarDevolucao(Arvore *arvore, Fila *fila, Lista *lista)
{
    int codigo;
    printf("\n--- Devolver Livro ---\n");
    printf("Código do livro: ");
    scanf("%d", &codigo);
    limparBuffer();

    Livro *livro = buscarLivroArvore(arvore, codigo);
    if (livro == NULL) {
        printf("Erro: livro com código %d não encontrado.\n", codigo);
        return;
    }

    devolverExemplar(livro);
    printf("Livro '%s' devolvido com sucesso!\n", livro->titulo);

    /* Informa se há reservas para esse livro */
    if (existeReservaParaLivro(fila, codigo)) {
        printf("Atenção: há usuários na fila de reserva para este livro.\n");
        printf("Deseja atender o próximo da fila agora? (s/n): ");

        char opcao[4];
        lerString(opcao, 4);

        if (opcao[0] == 's' || opcao[0] == 'S') {
            if (!filaVazia(fila) &&
                fila->inicio->reserva.codigoLivro == codigo)
            {
                Reserva atendida = desenfileirarReserva(fila);

                /* Desconta o exemplar que acabou de ser incrementado */
                emprestarExemplar(livro);

                /* Registra o empréstimo da reserva atendida no histórico */
                Emprestimo emp;
                strncpy(emp.nomeUsuario, atendida.nomeUsuario, 99);
                emp.nomeUsuario[99] = '\0';
                emp.codigoLivro = codigo;
                strncpy(emp.tituloLivro, livro->titulo, 99);
                emp.tituloLivro[99] = '\0';
                inserirEmprestimo(lista, emp);

                printf("Reserva atendida: '%s' retirou '%s'.\n",
                       atendida.nomeUsuario, livro->titulo);
            } else {
                printf("O primeiro da fila geral aguarda outro livro.\n");
                printf("Exibindo a fila completa:\n");
                exibirReservas(fila);
            }
        }
    }
}

static void exibirMenu(void)
{
    printf("\n========================================\n");
    printf("   SISTEMA DE GERENCIAMENTO DE BIBLIOTECA\n");
    printf("========================================\n");
    printf(" 1. Cadastrar novo livro\n");
    printf(" 2. Buscar livro por codigo\n");
    printf(" 3. Listar livros em ordem crescente\n");
    printf(" 4. Listar livros em pre-ordem\n");
    printf(" 5. Listar livros em pos-ordem\n");
    printf(" 6. Realizar emprestimo de livro\n");
    printf(" 7. Devolver livro\n");
    printf(" 8. Exibir fila de reservas\n");
    printf(" 9. Exibir historico de emprestimos\n");
    printf("10. Exibir quantidade de livros cadastrados\n");
    printf("11. Exibir altura da arvore\n");
    printf(" 0. Sair\n");
    printf("========================================\n");
    printf("Opcao: ");
}

/* ---------- main ---------- */

int main(void)
{
    Arvore *arvore = criarArvore();
    Fila   *fila   = criarFila();
    Lista  *lista  = criarLista();

    if (arvore == NULL || fila == NULL || lista == NULL) {
        printf("Erro crítico: falha ao inicializar estruturas.\n");
        return 1;
    }

    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarLivro(arvore);
                break;

            case 2:
                buscarLivro(arvore);
                break;

            case 3:
                listarLivrosEmOrdem(arvore);
                break;

            case 4:
                listarLivrosPreOrdem(arvore);
                break;

            case 5:
                listarLivrosPosOrdem(arvore);
                break;

            case 6:
                realizarEmprestimo(arvore, fila, lista);
                break;

            case 7:
                realizarDevolucao(arvore, fila, lista);
                break;

            case 8:
                exibirReservas(fila);
                break;

            case 9:
                listarEmprestimos(lista);
                break;

            case 10:
                printf("\nTotal de livros cadastrados: %d\n",
                       contarLivros(arvore));
                break;

            case 11:
                printf("\nAltura da arvore: %d\n",
                       calcularAlturaArvore(arvore));
                break;

            case 0:
                printf("Encerrando o sistema. Ate logo!\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    /* Liberação básica das estruturas raiz
       (liberação completa seria funcionalidade extra) */
    free(arvore);
    free(fila);
    free(lista);

    return 0;
}