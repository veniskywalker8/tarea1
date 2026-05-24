CANTIDAD=${1:-1}
N=${CANTIDAD#-}   # quita el signo negativo
TIPO="--hard"
if [ "$2" = "-s" ]; then
  TIPO="--soft"
fi
if [ "$2" = "-m" ]; then
  TIPO="--mixed"
fi

git reset $TIPO HEAD~$N

if [ $CANTIDAD -lt 0 ]; then
  # Si es negativo, solo local
  echo "Retrocediendo $N commit(s) SOLO en local..."
else
  # Si es positivo, local + remoto
  echo "Retrocediendo $CANTIDAD commit(s) en local y remoto..."
  git push origin HEAD --force
fi

echo "Listo."