SHELL := /bin/sh
CXX ?= c++
CXXFLAGS ?= -O3 -march=native
PDFLATEX ?= pdflatex
export SOURCE_DATE_EPOCH := 1795737600
export FORCE_SOURCE_DATE := 1
export TZ := UTC

.PHONY: verify paper
verify: build/construct build/verify
	@sh verify.sh

build:
	@mkdir -p build

build/construct: evidence/build.cpp | build
	$(CXX) $(CXXFLAGS) -std=c++17 $< -o $@

build/verify: evidence/verify.cpp | build
	$(CXX) $(CXXFLAGS) -std=c++17 $< -o $@

paper:
	@mkdir -p build/tex
	@$(PDFLATEX) -halt-on-error -interaction=batchmode -output-directory=build/tex paper/main.tex
	@$(PDFLATEX) -halt-on-error -interaction=batchmode -output-directory=build/tex paper/main.tex
	@! grep -E 'Overfull|undefined references|undefined citations|Warning:' build/tex/main.log
	@cp build/tex/main.pdf paper/main.pdf
