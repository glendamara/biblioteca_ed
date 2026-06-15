# Sistema de Gerenciamento de Biblioteca

## Equipe
- Integrante 1: Glenda Mara da Silva Pereira
- Integrante 2: Olga Pedrosa de Sousa
- Integrante 3: Marília Milfont Rangel Lima

## Disciplina
Estrutura de Dados — UECE  
Professor: Bonfim Amaro Junior

---

## Descrição do Sistema

Sistema desenvolvido em linguagem C para gerenciamento de acervo de biblioteca.
O projeto foi inicialmente montado e testado no C Online, mas também pode ser
compilado localmente no Windows ou diretamente no terminal integrado do VS Code.

Utilizando:

- **TAD Livro** — encapsula os dados e operações de cada obra.
- **Árvore Binária de Busca (ABB)** — armazena e organiza os livros pelo código identificador.
- **Fila (FIFO)** — gerencia as reservas de livros indisponíveis.
- **Lista Encadeada** — mantém o histórico de empréstimos realizados.

---

## Estrutura de Arquivos

```
trabalho_biblioteca/
├── main.c      → Menu principal e integração das estruturas
├── livro.h     → Definição do TAD Livro
├── livro.c     → Implementação do TAD Livro
├── arvore.h    → Definição da Árvore Binária de Busca
├── arvore.c    → Implementação da ABB
├── fila.h      → Definição da Fila de Reservas
├── fila.c      → Implementação da Fila
├── lista.h     → Definição da Lista de Histórico
├── lista.c     → Implementação da Lista
└── README.md
```

---

## Como compilar e executar

O projeto pode ser compilado localmente com o `gcc` ou diretamente no terminal integrado do VS Code.

### No Windows / terminal local

Na pasta do projeto, execute:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c livro.c arvore.c fila.c lista.c -o biblioteca_ed.exe
```

Depois, rode o programa com:

```bash
./biblioteca_ed.exe
```

Se estiver usando PowerShell, o executável também pode ser aberto com:

```powershell
.\biblioteca_ed.exe
```

### No VS Code

1. Abra a pasta `biblioteca_ed` no VS Code.
2. Abra o terminal integrado em `Terminal > New Terminal`.
3. Execute o mesmo comando de compilação mostrado acima.
4. Depois, inicie o programa pelo terminal.

Se o `gcc` não estiver instalado, será necessário instalar uma distribuição como MinGW-w64, GCC via WSL, ou outra toolchain C compatível com o seu ambiente.

---

## Exemplos de Uso

### Cadastrar livro
```
Opcao: 1
Código      : 10
Título      : Introdução a Algoritmos
Autor       : Cormen
Ano         : 2009
Qtd. total  : 3
→ Livro 'Introdução a Algoritmos' cadastrado com sucesso!
```

### Buscar livro
```
Opcao: 2
Código: 10
→ exibe os dados do livro
```

### Realizar empréstimo
```
Opcao: 6
Nome do usuário : João Silva
Código do livro : 10
→ Empréstimo realizado com sucesso!
```

### Reservar livro indisponível
```
Opcao: 6
Nome do usuário : Maria Costa
Código do livro : 10   ← sem exemplares
→ Deseja entrar na fila de reservas? (s/n): s
→ Reserva adicionada à fila.
```

### Devolver livro
```
Opcao: 7
Código do livro: 10
→ Livro devolvido com sucesso!
→ Atenção: há usuários na fila de reserva para este livro.
```

---

## Funcionalidades Implementadas

| # | Funcionalidade                         | Status |
|---|----------------------------------------|--------|
| 1 | Cadastrar novo livro                   | ✓      |
| 2 | Buscar livro por código                | ✓      |
| 3 | Listar em ordem crescente              | ✓      |
| 4 | Listar em pré-ordem                    | ✓      |
| 5 | Listar em pós-ordem                    | ✓      |
| 6 | Realizar empréstimo                    | ✓      |
| 7 | Devolver livro                         | ✓      |
| 8 | Exibir fila de reservas                | ✓      |
| 9 | Exibir histórico de empréstimos        | ✓      |
|10 | Exibir quantidade de livros cadastrados| ✓      |
|11 | Exibir altura da árvore                | ✓      |
|   | Atendimento automático da fila na devolução | ✓ (extra) |

---
