#!/bin/bash
# Script para hacer merge desde otra rama hacia la rama actual
# Uso: ./hacer_merge.sh <rama_origen> [mensaje_commit]

# Verifica argumento obligatorio
if [ -z "$1" ]; then
  echo "Uso: $0 <rama_origen> [mensaje_commit]"
  exit 1
fi

ORIGEN=$1
DESTINO=$(git rev-parse --abbrev-ref HEAD)

# Si hay segundo argumento, úsalo como mensaje; si no, usa uno por defecto
if [ -n "$2" ]; then
  MENSAJE=$2
else
  MENSAJE="Merge branch '$ORIGEN' into $DESTINO"
fi

echo "Haciendo merge de $ORIGEN en la rama actual ($DESTINO)..."

# Actualiza la rama destino
git pull origin $DESTINO

# Hace el merge con commit explícito
git merge --no-ff $ORIGEN -m "$MENSAJE"

# Sube los cambios al remoto
git push origin $DESTINO

echo "Merge completado y registrado en el historial."