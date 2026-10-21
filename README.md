# Analisador Léxico para COBOL

Analisador léxico (lexer) escrito em C para programas COBOL de formato fixo, seguindo o COBOL padrão (COBOL-85).

O lexer lê um arquivo `.cob`/`.cbl` e gera a lista de tokens na ordem em que aparecem, com a categoria, o lexema, a linha e a coluna de cada um. Lexemas que não seguem as regras do COBOL são classificados como `TOK_ERROR`.

## O que o lexer reconhece

- **Formato fixo:** ignora as colunas 1 a 6 (área de sequência) e as colunas 73 em diante, e valida o indicador da coluna 7. Linhas com `*` ou `/` na coluna 7 são comentários.
- **Palavras reservadas:** `IDENTIFICATION`, `DIVISION`, `DISPLAY`, `PERFORM` etc., sem diferenciar maiúsculas de minúsculas.
- **Identificadores:** até 30 caracteres, apenas letras, dígitos e hífen, sem começar nem terminar com hífen e com pelo menos uma letra.
- **Literais:**
  - números (`30`, `-5`, `3.14`);
  - strings entre aspas (`"MARIA"`);
  - máscaras de `PIC` (`9(05)V99`, `X(20)`).
- **Símbolos:** `.`, `(`, `)`, `=`, `<`, `>`, `<=`, `>=`, `-`.
- **Parágrafos de documentação:** `AUTHOR`, `DATE-WRITTEN`, `REMARKS` etc. são ignorados, como comentários.

Exemplo de saída:

```
LINHA  COLUNA  CATEGORIA        LEXEMA
   15       8  IDENTIFICATION   IDENTIFICATION
   15      23  DIVISION         DIVISION
   15      31  DOT              .
   16       8  PROGRAM-ID       PROGRAM-ID
```

## Estrutura

| Arquivo / pasta | Conteúdo |
|---|---|
| `lexer.c` | código do analisador léxico |
| `run_exemplos.sh` | script que compila o lexer e roda todos os testes |
| `exemplos/` | programas COBOL usados como teste |
| `resultados/` | saída do lexer para cada programa de `exemplos/` |
| `testes_erros/` | cópias do `prog001_divisoes.cob` com erros léxicos inseridos de propósito |
| `resultados_erros/` | saída do lexer para cada programa de `testes_erros/` |

## Como rodar

É preciso ter o `gcc` instalado.

Para compilar e rodar todos os testes, gerando um `.txt` com o mesmo nome de cada programa em `resultados/` e `resultados_erros/`:

```bash
./run_exemplos.sh
```

Para compilar e rodar o lexer em um único arquivo:

```bash
gcc -Wall -o lexer lexer.c
./lexer exemplos/prog001_divisoes.cob
```

Sem argumento, o lexer lê o arquivo `cobol_code.cbl`.

## Origem dos exemplos

Os programas da pasta `exemplos/` foram retirados do repositório [ebasso/cobol-exemplos](https://github.com/ebasso/cobol-exemplos), de Enio Basso, distribuído sob a licença MIT.

Esses exemplos foram escritos para o GnuCOBOL, que aceita o sublinhado (`_`) em nomes como extensão. Como este lexer segue o COBOL padrão, nomes como `PROG006_FILES` são classificados como `TOK_ERROR`, e esse é o comportamento esperado.
