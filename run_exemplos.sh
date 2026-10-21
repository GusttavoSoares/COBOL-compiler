#!/bin/bash
# Roda o lexer em cada exemplo e salva a saida em um .txt com o mesmo nome:
#   exemplos/      -> resultados/
#   testes_erros/  -> resultados_erros/

gcc -Wall -o lexer lexer.c || exit 1

rodar() {
    entrada="$1"
    saida="$2"
    mkdir -p "$saida"

    for arquivo in "$entrada"/*.cob "$entrada"/*.cbl; do
        [ -f "$arquivo" ] || continue
        nome=$(basename "$arquivo")
        nome="${nome%.*}"
        ./lexer "$arquivo" > "$saida/$nome.txt" 2>&1
        echo "$saida/$nome.txt"
    done
}

rodar exemplos resultados
rodar testes_erros resultados_erros
