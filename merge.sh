#!/bin/bash
# Script para hacer merge entre ramas
# Uso:
#   ./hacer_merge.sh -o <origen> <destino> [mensaje_commit]
#   ./hacer_merge.sh <destino> [mensaje_commit]

if [ "$1" == "-o" ]; then
  # Caso con -o: origen, destino y mensaje
  if [ $# -lt 3 ]; then
    echo "Uso: $0 -o <origen> <destino> [mensaje_commit]"
    exit 1
  fi
  ORIGEN=$2
  DESTINO=$3
  MENSAJE=${4:-"Merge branch '$ORIGEN' into $DESTINO"}
else
  # Caso sin -o: solo destino y mensaje, origen = main
  if [ $# -lt 1 ]; then
    echo "Uso: $0 <destino> [mensaje_commit]"
    exit 1
  fi
  DESTINO=$(git rev-parse --abbrev-ref HEAD)
  ORIGEN=$1
  MENSAJE=${2:-"Merge branch '$ORIGEN' into $DESTINO"}
fi

echo "Haciendo merge de $ORIGEN en $DESTINO..."

# Cambia a la rama destino
git checkout $DESTINO || exit 1

# Actualiza la rama destino
git pull origin $DESTINO

# Hace el merge con commit explícito
git merge --no-ff $ORIGEN -m "$MENSAJE"

# Sube los cambios al remoto
git push origin $DESTINO

echo "Merge completado y registrado en el historial."
