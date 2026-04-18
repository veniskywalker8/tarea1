
# --------------------------------------------------------------------
#  Makefile de tarea 2.

#  Laboratorio de Programación 2.
#  InCo-FIng-UDELAR

# Define un conjunto de reglas.
# Cada regla tiene un objetivo, dependencias y comandos.
#objetivo: dependencia1 dependencia2...
#	comando1
#	comando2
#	comando3
# (antes de cada comando hay un tabulador, no espacios en blanco).
# Se invoca con
#make objetivo
# para que se ejecuten los comandos.
#
# Si `objetivo' es un archivo los comandos se ejecutan solo si no está
# actualizado (esto es, si su fecha de actualización es anterior a la de alguna
# de sus dependencias.
# Previamente se aplica la regla de cada dependencia.


# --------------------------------------------------------------------

# Objetivo predeterminado (no se necesita especificarlo al invocar `make').
all: principal

# Objetivos que no son archivos.
.PHONY: all clean_bin clean_test clean testing entrega claves

ARCHIVO_ENTREGA=EntregaTarea2.tar.gz

ENTREGAR = fecha evento agendaLS persona personasLDE personasABB #debug

MODULOS = $(ENTREGAR) utils

# directorios
HDIR    = include
CPPDIR  = src
ODIR    = obj

INDIR     = test
OUTDIR    = test
SALIDADIR = test/salidas

# extensión de los archivos
EXT = cpp
# compilador
CC = g++ # gcc -x c 
LD = g++ # gcc

# opciones de compilación
# para que los assert tengan efecto 
#CCFLAGS = -Wall -Werror -I$(HDIR) -g

# para que los assert NO tengan efecto y no impacten en el tiempo de ejecución
CCFLAGS = -Wall -Werror -I$(HDIR) -g

# cadena de archivos, con directorio y extensión
HS   = $(MODULOS:%=$(HDIR)/%.h)
CPPS = $(MODULOS:%=$(CPPDIR)/%.$(EXT))
OS   = $(MODULOS:%=$(ODIR)/%.o)

PRINCIPAL=principal
EJECUTABLE=principal

ARCHIVO_CLAVES=claves.txt
COMANDO_CLAVES=shasum

# $@ se expande para tranformarse en el objetivo
# $< se expande para tranformarse en la primera dependencia
$(ODIR)/$(PRINCIPAL).o:$(PRINCIPAL).$(EXT)
	@printf 'Compilando $(<) \n'; \
	$(CC) $(CCFLAGS) -c $< -o $@

$(ODIR)/%.o: $(CPPDIR)/%.$(EXT)  $(HDIR)/%.h
	@printf 'Compilando $(<) \n'; \
	$(CC) $(CCFLAGS) -c $< -o $@ ;

# $^ se expande para tranformarse en todas las dependencias
$(EJECUTABLE):$(ODIR)/$(PRINCIPAL).o $(OS)
	@printf 'Compilando y enlazando $(@) \n'; \
	$(LD) $(CCFLAGS) $^ -o $@

# casos de prueba
IDS_PUBLICOS = fechaEvento1-combinado \
		fechaEvento2-copia \
		agenda1-crear-agregar-imprimir-liberar \
		agenda2-crear-agregar-esVacia-copiar-imprimir-liberar \
		agenda3-esta \
		agenda4-obtener-posponer \
		agenda5-obtener-posponer \
		agenda6-hayEventosFecha-imprimirEventosFecha \
		agenda7-remover \
		agenda8-combinado \
		persona1-crear-imprimir-liberar \
		persona2-id-edad-nombre-agenda \
		persona3-agregar-posponer-remover \
		persona4-esta-obtener-copia \
		personasLDE1-crear-insertar-liberar \
		personasLDE2-crear-liberar-imprimir-cantidad \
		personasLDE3-eliminarInicio-eliminarFinal \
		personasLDE4-esta-obtener \
		personasLDE5-concatenar \
		personasLDE6-concatenar-tiempo \
		personasLDE7-combinado \
		personasABB1-crear-esVacio-insertar-liberar \
		personasABB2-crear-liberar-insertar-imprimir-cantidad \
		personasABB3-maxId-remover \
		personasABB4-esta-obtener \
		personasABB5-altura-esPerfecto \
		personasABB6-mayoresEdad \
		personasABB7-aPersonasLDE \
		personasABB8-combinado

IDS_PRIVADOS = 

CASOS = $(IDS_PUBLICOS) $(IDS_PRIVADOS)

# cadena de archivos, con directorio y extensión
INS=$(CASOS:%=$(INDIR)/%.in)
OUTS=$(CASOS:%=$(OUTDIR)/%.out)
SALS=$(CASOS:%=$(SALIDADIR)/%.sal)
DIFFS=$(CASOS:%=$(SALIDADIR)/%.diff)

$(SALS):$(EJECUTABLE)
# el guión antes del comando es para que si hay error no se detenga la
# ejecución de los otros casos
$(SALIDADIR)/%.sal:$(INDIR)/%.in
	-timeout 4 valgrind -q --leak-check=full ./$(EJECUTABLE) < $< > $@ 2>&1
	@if [ $$(stat -L -c %s $@) -ge 20000 ]; then \
		echo "tamaño excedido" > $@;\
	fi

# test de tiempo
$(SALIDADIR)/%-tiempo.sal:$(INDIR)/%-tiempo.in
	-timeout 10 ./$(EJECUTABLE) < $< > $@ 2>&1

%.diff:Makefile
# cada .diff depende de su .out y de su .sal
$(SALIDADIR)%.diff: $(OUTDIR)%.out $(SALIDADIR)%.sal
	@diff $^ > $@;                                            \
	if [ $$? -ne 0 ];                                         \
	then                                                      \
		echo ---- ERROR en caso $@ ----;                  \
	fi
# Con $$? se obtiene el estado de salida del comando anterior.
# En el caso de `diff', si los dos archivos comparados no son iguales,
# el estado de la salida no es 0 y en ese caso se imprime el mensaje.

# crea las reglas t-caso, y cada una depende del ejecutable
tS=$(CASOS:%=t-%)
$(tS):$(EJECUTABLE)

ttS=$(CASOS:%=tt-%)
$(ttS):$(EJECUTABLE)

# corre el ejecutable con el .in (el primer prerequisito $<) y lo guarda en un archivo temporal
# hace el diff entre el -out (el segundo prerequisito, echo $(word 2,$^)) y el archivo temporal
# borra el archivo temporal
t-%:$(INDIR)/%.in $(OUTDIR)/%.out
	@timeout 4 valgrind -q --leak-check=full ./$(EJECUTABLE) < $< > $@tmp 2>&1;  \
	diff `echo $(word 2,$^)` $@tmp ; \
	if [ $$? -eq 0 ];                                         \
	then                                                      \
		echo ---- Bien ----;                              \
	fi;                                                       \
	rm -f $@tmp

tt-%:$(INDIR)/%.in $(OUTDIR)/%.out
	@timeout 10 ./$(EJECUTABLE) < $< > $@tmp 2>&1;  \
	diff `echo $(word 2,$^)` $@tmp ; \
	if [ $$? -eq 0 ];                                         \
	then                                                      \
		echo ---- Bien ----;                              \
	fi;                                                       \
	rm -f $@tmp

# Test general. Las dependencias son los .diff.
# Con `find` se encuentran los .diff de tamaño > 0 que están en el directorio
# $(SALIDADIR) y lo asigna a $(LST_ERR).
# Si el tamaño de $(LST_ERR) no es cero imprime los casos con error.
# Con `sed` se elimina el nombre de directorio y la extensión.
testing:all $(DIFFS)
	@LST_ERR=$$(find $(SALIDADIR) -name *.diff* -size +0c -print);          \
	if [ -n "$${LST_ERR}" ];                                                \
	then                                                                    \
		echo -- CASOS CON ERRORES --;                                   \
		echo "$${LST_ERR}" | sed -e 's/.*\///' -e 's/\..*//';           \
	fi;                                                                     \
	echo -- RESULTADO DE CADA CASO --;                                      \
	RES=;                                                                   \
	for id in $(IDS_PUBLICOS); do                                                    \
		if [ 0 -eq $$(stat -c %s "$(SALIDADIR)/$${id}.diff") ];         \
		then                                                            \
			RES=$${RES}1 ;                                          \
		else                                                            \
			RES=$${RES}0 ;                                          \
		fi;                                                             \
	done;                                                            \
	RES=$${RES}-;  													\
	for id in $(IDS_PRIVADOS); do                                                    \
		if [ 0 -eq $$(stat -c %s "$(SALIDADIR)/$${id}.diff") ];         \
		then                                                            \
			RES=$${RES}1 ;                                          \
		else                                                            \
			RES=$${RES}0 ;                                          \
		fi;                                                             \
	done;                                                                  \
	echo $${RES}                                                            \


# inlcuye la clave de cada archivo en $(ARCHIVO_CLAVES)
$(ARCHIVO_CLAVES):
	rm -f $@
	$(COMANDO_CLAVES) $(ENTREGAR:%=$(CPPDIR)/%.$(EXT)) > $@

claves:$(ARCHIVO_CLAVES)

# Genera el entregable.
CPPS_ENTREGA = $(ENTREGAR:%=%.$(EXT))
entrega:claves
	@rm -f $(ARCHIVO_ENTREGA)
	tar zcf $(ARCHIVO_ENTREGA) $(ARCHIVO_CLAVES) -C src $(CPPS_ENTREGA)
	@echo --        El directorio y archivo a entregar es:
	@echo $$(pwd)/$(ARCHIVO_ENTREGA)

# borra binarios
clean_bin:
	@rm -f $(EJECUTABLE) $(ODIR)/$(PRINCIPAL).o $(OS)

# borra resultados de ejecución y comparación
clean_test:
	@rm -f $(SALIDADIR)/*.sal $(SALIDADIR)/*.diff

# borra binarios, resultados de ejecución y comparación, y copias de respaldo
clean:clean_test clean_bin
	@rm -f $(ARCHIVO_ENTREGA) $(ARCHIVO_CLAVES) *~ $(HDIR)/*~ $(CPPDIR)/*~ $(INDIR)/*~ $(OUTDIR)/*~

check-syntax:
	gcc -o nul -S ${CHK_SOURCES}

LIB = tarea.a
$(LIB):	$(ODIR)/utils.o $(ODIR)/$(PRINCIPAL).o
	ar -qc $@ $^	


#! Regla propia
#? VARIABLES
#* Colores ANSI
ROJO=\033[31m
VERDE=\033[32m
AMARILLO=\033[33m
AZUL=\033[34m
MAGENTA=\033[35m
CIAN=\033[36m
NC=\033[0m   # Reset (No Color)
#* borra binarios, resultados de ejecución y comparación, y copias de respaldo
cc:clean_test clean_bin
	@rm -f $(ARCHIVO_ENTREGA) $(ARCHIVO_CLAVES) *~ $(HDIR)/*~ $(CPPDIR)/*~ $(INDIR)/*~ $(OUTDIR)/*~
#* Esta regla ejecuta el binario 
pp: principal
	@echo "$(VERDE)COMPILADO$(NC)"
#*TESTING
#? Esta regla se invoca con `make test-` y el nombre del modulo.
#TODO: Llama todos los casos de prueba de un módulo.
#? Por ejemplo, `make test-fecha` ejecuta los de fecha.
#? Con `--no-print-directory` se evita que se imprima el nombre del directorio
test-%:
	@# Filtra los casos que pertenecen al módulo invocado
	@# Si el patrón es "test-*", usar todos los casos
	@if [ "$*" = "*" ]; then \
		casos="$(tS)"; \
	else \
		casos="$(filter t-$*%,$(tS))"; \
	fi; \
	ok=0; fail=0; RES=""; PRUEBAS="";\
	for c in $$casos; do \
		# Quita el prefijo t- para obtener el ID real \
		id="$${c#t-}"; \
		# Define rutas de entrada, salida, esperado y diff \
		in="$(INDIR)/$$id.in"; \
		sal="$(SALIDADIR)/$$id.sal"; \
		exp="$(OUTDIR)/$$id.out"; \
		diff="$(SALIDADIR)/$$id.diff"; \
		tmp=".tmp-salida"; \
		# Ejecuta el programa con valgrind y timeout, redirige salida \
		timeout 4 valgrind -q --leak-check=full ./$(EJECUTABLE) < "$$in" > "$$tmp" 2>&1; \
		cp "$$tmp" "$$sal"; \
		# Compara salida esperada vs generada \
		if diff -u "$$exp" "$$sal" > "$$diff"; then \
			ok=$$((ok + 1)); \
			RES=$${RES}1; \
			rm -f "$$diff"; \
			printf "$(VERDE)✓ OK: %s$(NC)\n" "$$id"; \
			PRUEBAS=$${PRUEBAS}"$(VERDE)✓ OK: $$id$(NC)\n"; \
		else \
			fail=$$((fail + 1)); \
			RES=$${RES}0; \
			cat "$$diff"; \
			printf "$(ROJO)✗ FAIL: %s$(NC)\n" "$$id"; \
			PRUEBAS=$${PRUEBAS}"$(ROJO)✗ FAIL: $$id$(NC)\n"; \
		fi; \
		rm -f "$$tmp"; \
	done; \
	echo -- RESULTADO DE CADA CASO --; \
	total=$$((ok + fail)); \
	echo "Resumen módulo '$*': $$ok bien, $$fail mal, $$total total"; \
	echo "$$RES";\
	echo "$$PRUEBAS"
