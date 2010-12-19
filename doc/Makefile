#makefile
	# IMS - Modelovani a simulac
	# 22.9.2010
	# Author: Jaroslav Sendler, FIT, xsendl00 AT stud.fit.vutbr.cz


FILE=dokumentace
NAME=ims

all:	$(FILE)

$(FILE): $(FILE).tex
#	latex $(FILE).tex
	pdflatex $(FILE).tex
	pdflatex $(FILE).tex
	pdflatex $(FILE).tex
	cp $(FILE).pdf ../

clean:
	rm -f *.dvi *.ps *.aux *.log 

clean-all: clean
	rm -f $(FILE).pdf

remove: clean-all
	rm -f ${NAME}.tar.gz

zip:
	tar -c ${FILE}.tex Makefile > ${NAME}.tar; \
	gzip ${NAME}.tar
