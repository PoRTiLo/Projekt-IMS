#makefile
  # IMS- Simulator cernobilych stochasticky Petriho siti
  # 29.11.2010
  # Autor: Jaroslav Sendler, FIT, xsendl00(at)stud.fit.vutbr.cz
  #        Dusan Kovacic, FIT, xkovac21(at)stud.fit.vutbr.cz
  # Prelozeno gcc ...
  #

# jmeno prekladaneho programu
PROGRAM=sim

# jmeno knihovny
LIB=ptnet

# nazev projektu
PROJECT=xkovac21_xsendl00

# seznam souboru
OBJM=base.o coreFunc.o directedArc.o main.o place.o transition.o gen.o calendar.o calendarUnit.o petriSim.o stats.o transPrioData.o
OBJ=base.o coreFunc.o directedArc.o place.o transition.o gen.o calendar.o calendarUnit.o petriSim.o stats.o transPrioData.o
SBASE=base.cpp base.h
SCOREFUNC=coreFunc.cpp coreFunc.h
SDIRECTEDARC=directedArc.cpp directedArc.h
SPLACE=place.cpp place.h
STRANSITION=transition.cpp transition.h
SGEN=gen.cpp gen.h
SCALENDAR=calendar.cpp calendar.h
SCALENDARUNIT=calendarUnit.cpp calendarUnit.h
SPETRISIM=PetriSim.h
SSTATS=stats.cpp stats.h
STRANSPRIODATA=transPrioData.h
SOOBJ=soBase.o soCoreFunc.o soDirectedArc.o soPlace.o soTransition.o soGen.o soCalendar.o soCalendarUnit.o soStats.o 
SRC=base.cpp coreFunc.cpp directedArc.cpp main.cpp place.cpp transition.cpp gen.cpp calendar.cpp calendarUnit.cpp stats.cpp
HEAD=base.h baseData.h directedArc.h coreFunc.h place.h statusList.h transition.h transPrioData.h gen.h calendar.h calendarUnit.h PetriSim.h stats.h

# kompilator
CCM=g++

# parametry
CCMFLAGS=-std=c++98 -Wall -pedantic -Wextra
COBJ=-std=c++98 -Wall -pedantic -Wextra -c

# cilum all, run, sim, clean, delete neodpovida primo zadny soubor
.PHONY: build
.PHONY: dynamic
.PHONY: all
.PHONY: run
.PHONY: clean
.PHONY: clean-all
.PHONY: delete
.PHONY: run-dynamic
.PHONY: help
.PHONY: run-nostat
.PHONY: run-allstat
.PHONY: run-stat

#--------------------------------------------------------------------#

# default - prvni cil je defaultni
build:	${PROGRAM}

# dynamic
dynamic: ${PROGRAM}-dynamic

# vsechno
all:  ${PROGRAM} ${PROGRAM}-dynamic

#............................................. model1 ...............#
run:
	./${PROGRAM}

# spusti priklad s vypisem
run-model1:
	./${PROGRAM} model1

# spusti priklad bez vypisu
run-nostat-model1:
	./${PROGRAM} -nostat model1

# statistika jednotlivych kroku
run-stat-model1:
	./${PROGRAM} -stat model1

# konecna souhrna statistika
run-allstat-model1:
	./${PROGRAM} -allstat model1

# spusteni s dynamickou knihovnou s vypisem
run-dynamic-model1:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic model1

# spusteni s dynamickou knihovnou bez vypisu
run-dynamic-nonstat-model1:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic -nonstat model1

# spusteni s dynamickou knihovnous jednotlivyma krokama 
run-dynamic-stat-model1:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic -stat model1

# spusteni s dynamickou knihovnou se souhrnou statistikou 
run-dynamic-allstat-model1:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic -allstat model1

#............................................. model2 ...............#
# spusti priklad s vypisem
run-model2:
	./${PROGRAM} model2

# spusti priklad bez vypisu
run-nostat-model2:
	./${PROGRAM} -nostat model2

# statistika jednotlivych kroku
run-stat-model2:
	./${PROGRAM} -stat model2

# konecna souhrna statistika
run-allstat-model2:
	./${PROGRAM} -allstat model2

# spusteni s dynamickou knihovnou s vypisem
run-dynamic-model2:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic model2

# spusteni s dynamickou knihovnou bez vypisu
run-dynamic-nonstat-model2:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic -nonstat model2

# spusteni s dynamickou knihovnous jednotlivyma krokama 
run-dynamic-stat-model2:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic -stat model2

# spusteni s dynamickou knihovnou se souhrnou statistikou 
run-dynamic-allstat-model2:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic -allstat model2

#............................................. model3 ...............#
# spusti priklad s vypisem
run-model3:
	./${PROGRAM} model3

# spusti priklad bez vypisu
run-nostat-model3:
	./${PROGRAM} -nostat model3

# statistika jednotlivych kroku
run-stat-model3:
	./${PROGRAM} -stat model3

# konecna souhrna statistika
run-allstat-model3:
	./${PROGRAM} -allstat model3

# spusteni s dynamickou knihovnou s vypisem
run-dynamic-model3:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic model3

# spusteni s dynamickou knihovnou bez vypisu
run-dynamic-nonstat-model3:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic -nonstat model3

# spusteni s dynamickou knihovnous jednotlivyma krokama 
run-dynamic-stat-model3:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic -stat model3

# spusteni s dynamickou knihovnou se souhrnou statistikou 
run-dynamic-allstat-model3:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic -allstat model3

#----------------- KOMPILACE ----------------------------------------#
${PROGRAM}: main.o ${LIB}.a
	$(CCM) ${CCMFLAGS} $^ -o $@

${PROGRAM}-dynamic: main.o ${LIB}.so
	${CCM} ${CCMFLAGS} $^ -o $@

main.o: main.cpp
	${CCM} ${COBJ} $< -o $@

#sim:  ${OBJ}
#	$(CCM) ${CCMFLAGS} ${OBJ} -o ${PROGRAM}

#${OBJ}:${HEAD}

#------------------ DYNAMICKE ---------------------------------------#
${LIB}.so: ${SOOBJ}
	${CCM} ${CCMFLAGS} -shared -fPIC $^ -o $@

# moduly
soBase.o: ${SBASE}
	${CCM} ${COBJ} -fPIC $< -o $@

soCoreFunc.o: ${SCOREFUNC}
	${CCM} ${COBJ} -fPIC $< -o $@

soDirectedArc.o: ${SDIRECTEDARC}
	${CCM} ${COBJ} -fPIC $< -o $@

soPlace.o: ${SPLACE}
	${CCM} ${COBJ} -fPIC $< -o $@

soTransition.o: ${STRANSITION}
	${CCM} ${COBJ} -fPIC $< -o $@

soGen.o: ${SGEN}
	${CCM} ${COBJ} -fPIC $< -o $@

soCalendar.o: ${SCALENDAR}
	${CCM} ${COBJ} -fPIC $< -o $@

soCalendarUnit.o: ${SCALENDARUNIT}
	${CCM} ${COBJ} -fPIC $< -o $@

soPetriSim.o: ${SPETRISIM}
	${CCM} ${COBJ} -fpic $< -o $@

soStats.o: ${SSTATS}
	${CCM} ${COBJ} -fpic $< -o $@

soTransPrioData.o: ${STRANSPRIODATA}
	${CCM} ${COBJ} -fpic $< -o $@

#----------------- STATICKE ----------------------------------------#
${LIB}.a: ${OBJ}
	ar crs $@ $^

# moduly
base.o: ${SBASE}
	${CCM} ${COBJ} $< -o $@

coreFunc.o: ${SCOREFUNC}
	${CCM} ${COBJ} $< -o $@

directedArc.o: ${SDIRECTEDARC}
	${CCM} ${COBJ} $< -o $@

place.o: ${SPLACE}
	${CCM} ${COBJ} $< -o $@

transition.o: ${STRANSITION}
	${CCM} ${COBJ} $< -o $@

gen.o: ${SGEN}
	${CCM} ${COBJ} $< -o $@

calendar.o: ${SCALENDAR}
	${CCM} ${COBJ} $< -o $@

calendarUnit.o: ${SCALENDARUNIT}
	${CCM} ${COBJ} $< -o $@

petriSim.o: ${SPETRISIM}
	${CCM} ${COBJ} $< -o $@

stats.o: ${SSTATS}
	${CCM} ${COBJ} $< -o $@

transPrioData.o: ${STRANSPRIODATA}
	${CCM} ${COBJ} $< -o $@

#------------------ SMAZANI souboru ---------------------------------#

# odstrani zkompilovane soubory
clean: 
	rm -f *.o ${PROGRAM} ${PROGRAM}-dynamic

# odstrani zkompilovane soubory a vytvorene knihovny
clean-all: clean
	rm -f *.so *.a

# smaze vsenchno krome zdrojovych souboru a makefile
delete: 
	rm -f *.o  *.so *.a ${PROGRAM} ${PROGRAM}-dynamic ${PROGRAM}.tar.gz *.gz *.zip

#------------------ SBALENI projektu na odevzdani -------------------#

tar:
	tar -c ${SRC} ${HEAD} makefile dokumentace.pdf > ${PROJECT}.tar; \
	gzip ${PROJECT}.tar

zip:
	zip ${PROJECT}  ${SRC} ${HEAD} makefile dokumentace.pdf

#------------------ NAPOVEDA ----------------------------------------#
help:
		@echo ""
		@echo "----------MAKEFILE--------"
		@echo "make(build)	- Staticke sestaveni knihovny"
		@echo "make dynamic	- Kompilace s dynamickou knihovnou"
		@echo "make all   	- Kompletni kompilace souboru"
		@echo "run        	- Spusteni staticke verze s vypisy"
		@echo "run-nostat 	- Spusteni staticke verze bez vypisu"
		@echo "run-allstat	- Spusteni staticke verze se souhrnyma vypisema na konci"
		@echo "run-stat   	- Spsuteni staticke verze s vypisema po kroku"
		@echo "run-dynamic	- Spusteni dynamicke verze"
		@echo "clean      	- Smazani zkompilovanych souboru"
		@echo "delete     	- Smazani vsech souboru, krome zdrojovych"
		@echo "tar        	- Sbaleni potrebnych souboru pomoci tar"
		@echo "zip        	- Sbaleni potrebnych souboru pomoci zip"
		@echo "help       	- Vypis teto napovedy"
		@echo ""

#-------------------------------------------------------------------#
