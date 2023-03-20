#Author: xtobol06

PROJ=dokumentace

# for inverse rm expr
SHELL=/bin/bash

all: $(PROJ)
.PHONY: all clean

$(PROJ):
	latexmk -pdf -pdflatex="pdflatex -interaction=nonstopmode" $(PROJ).tex

clean:
	latexmk -c

purge:
	latexmk -C
