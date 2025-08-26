#!/bin/bash

# Uso: ./rename_all.sh ruta_del_directorio
# Cambia:
#   "Token"      -> "t_token"
#   "TokenType"  -> "t_token_type"
#   "ASTNode"    -> "t_ast"
#   "NodeType"   -> "t_node_type"

find "$1" -type f \( -name "*.c" -o -name "*.h" \) -exec sed -i \
    -e 's/\<TokenType\>/t_token_type/g' \
    -e 's/\<Token\>/t_token/g' \
    -e 's/\<ASTNode\>/t_ast/g' \
    -e 's/\<NodeType\>/t_node_type/g' {} +
