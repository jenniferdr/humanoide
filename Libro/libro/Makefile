ARCHIVO = thesis

main:
	pdflatex $(ARCHIVO).tex
	makeglossaries $(ARCHIVO)  
	bibtex $(ARCHIVO).aux
	pdflatex $(ARCHIVO).tex
	pdflatex $(ARCHIVO).tex

clean:
	rm *.txt *.log *.aux *.make *.bak *.d *.fls *.toc $(ARCHIVO).acn $(ARCHIVO).nlo $(ARCHIVO).acl $(ARCHIVO).acr $(ARCHIVO).alg $(ARCHIVO).glo $(ARCHIVO).ist $(ARCHIVO).out $(ARCHIVO).toc $(ARCHIVO).idx  $(ARCHIVO).lof  $(ARCHIVO).lot $(ARCHIVO).blg $(ARCHIVO).bbl $(ARCHIVO).glg $(ARCHIVO).gls
	rm -rf *~
