ARCHIVO = thesis

main:
	pdflatex $(ARCHIVO).tex
	makeglossaries $(ARCHIVO).glo
	bibtex $(ARCHIVO).aux
	pdflatex $(ARCHIVO).tex
	pdflatex $(ARCHIVO).tex

clean:
	rm *.txt *.log *.aux *.make *.bak *.d *.fls *.toc $(ARCHIVO).acn $(ARCHIVO).glo $(ARCHIVO).ist $(ARCHIVO).out $(ARCHIVO).toc $(ARCHIVO).idx  $(ARCHIVO).lof  $(ARCHIVO).lot $(ARCHIVO).blg $(ARCHIVO).bbl $(ARCHIVO).glg $(ARCHIVO).gls
	rm -rf *~
