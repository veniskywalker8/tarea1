#!/bin/bash

# ============================================================
# Instrucciones iniciales:
# Para dar permisos de ejecución a este script (setup.sh):
#   chmod +x setup.sh
# Para corregir terminadores de línea de Windows en este script:
#   sed -i 's/\r$//' setup.sh
# Luego puedes ejecutarlo con:
#   ./setup.sh
# ============================================================

# Actualiza la lista de paquetes
sudo apt-get update

# Instala valgrind y herramientas básicas de compilación
sudo apt-get install -y valgrind build-essential

# build-essential incluye gcc, g++, make y otras utilidades necesarias
# para compilar proyectos en C/C++.

# Da permisos de ejecución a los scripts auxiliares
chmod +x des_comit.sh
chmod +x merge.sh

# Corrige terminadores de línea de Windows (\r) en los scripts
sed -i 's/\r$//' des_comit.sh
sed -i 's/\r$//' merge.sh

# Explicación:
# El comando sed -i 's/\r$//' elimina el carácter de retorno de carro (\r)
# que aparece cuando un archivo fue editado en Windows y luego usado en Linux.
# Esto evita errores como "bad interpreter" al ejecutar scripts.
