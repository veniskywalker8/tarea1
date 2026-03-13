#!/bin/bash
# Script para retroceder commits en local y remoto
# Uso: ./retroceder.sh [cantidad]
# Si no se indica cantidad, se retrocede 1 commit por defecto.

# Si no se pasa argumento, asigna 1
CANTIDAD=${1:-1}

echo "Retrocediendo $CANTIDAD commit(s)..."

# Retrocede en local
git reset --hard HEAD~$CANTIDAD

# Fuerza el push al remoto
git push origin HEAD --force

echo "Listo: se eliminaron $CANTIDAD commit(s) en local y remoto."
