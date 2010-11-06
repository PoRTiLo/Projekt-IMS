#makefile
  # IMS- Implementace diskr. simulatoru zalozeneho na rizeni UDALOSTMI(opak procesne orientovaneho pristupu)
  # 12.12.2009
  # Autor: Jaroslav Sendler, FIT, xsendl00@stud.fit.vutbr.cz
  #        Dusan Kovacic, FIT, xkovac21@stud.fit.vutbr.cz
  # Prelozeno gcc 4.2
  #

PROGRAM=sim
PROJECT=xkovac21_xsendl00

OBJ=base.o coreFunc.o directedArc.o main.o place.o transition.o
SRC=base.cpp coreFunc.cpp directedArc.cpp main.cpp place.cpp transition.cpp
HEAD=base.h baseData.h directedArc.h coreFunc.h place.h statusList.h transition.h transPrioData.h

CCM=g++
CCMFLAGS=-std=c++98 -Wall -pedantic 
	
all:  ${PROGRAM} 

run:
	./sim

sim:  ${OBJ}
	$(CCM) ${CCMFLAGS} ${OBJ} -o ${PROGRAM}

${OBJ}:${HEAD}

clean: 
	rm -f *.o

delete: 
	rm -f *.o ${PROGRAM} ${PROGRAM}.tar.gz *.gz *.zip


tar:
	tar -c ${SRC} ${HEAD} makefile dokumentace.pdf > ${PROJECT}.tar; \
	gzip ${PROJECT}.tar

#zip:
#	gzip -c ${SRC} ${HEAD} makefile README > ${PROJECT};
