#makefile
  # IMS- Implementace diskr. simulatoru zalozeneho na rizeni UDALOSTMI(opak procesne orientovaneho pristupu)
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
OBJM=base.o coreFunc.o directedArc.o main.o place.o transition.o gen.o calendar.o calendarUnit.o
OBJ=base.o coreFunc.o directedArc.o place.o transition.o gen.o calendar.o calendarUnit.o
SBASE=base.cpp base.h
SCOREFUNC=coreFunc.cpp coreFunc.h
SDIRECTEDARC=directedArc.cpp directedArc.h
SPLACE=place.cpp place.h
STRANSITION=transition.cpp transition.h
SGEN=gen.cc gen.h
SCALENDAR=calendar.cc calendar.h
SCALENDARUNIT=calendarUnit.cc calendarUnit.h
SOOBJ=soBase.o soCoreFunc.o soDirectedArc.o soPlace.o soTransition.o soGen.o soCalendar.o soCalendarUnit.o
SRC=base.cpp coreFunc.cpp directedArc.cpp main.cpp place.cpp transition.cpp gen.cc calendar.cc calendarUnit.cc
HEAD=base.h baseData.h directedArc.h coreFunc.h place.h statusList.h transition.h transPrioData.h gen.h calendar.h calendarUnit.h

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
.PHONY: delete
.PHONY: run-dynamic
.PHONY: help

#--------------------------------------------------------------------#

# default - prvni cil je defaultni
build:	${PROGRAM}

# dynamic
dynamic: ${PROGRAM}-dynamic

# vsechno
all:  ${PROGRAM} ${PROGRAM}-dynamic

# spusti priklad
run:
	./${PROGRAM}

# spusteni s dynamickou knihovnou
run-dynamic:
	LD_LIBRARY_PATH="." ./${PROGRAM}-dynamic

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


#------------------ SMAZANI souboru ---------------------------------#

# odstrani zkompilovane soubory
clean: 
	rm -f *.o ${PROGRAM} ${PROGRAM}-dynamic

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
		@echo "----------MAKEFILE--------"
		@echo "make(build)	- Staticke sestaveni knihovny"
		@echo "make dynamic	- Kompilace s dynamickou knihovnou"
		@echo "make all   	- Kompletni kompilace souboru"
		@echo "run        	- Spusteni staticke verze"
		@echo "run-dynamic	- Spusteni dynamicke verze"
		@echo "clean      	- Smazani zkompilovanych souboru"
		@echo "delete     	- Smazani vsech souboru, krome zdrojovych"
		@echo "tar        	- Sbaleni potrebnych souboru pomoci tar"
		@echo "zip        	- Sbaleni potrebnych souboru pomoci zip"
		@echo "help       	- Vypis teto napovedy"

#-------------------------------------------------------------------#
