PROJ = calc
PROFILE = stddev
GUI = gui
ZIP = xtobol06_xtesar43_xsteti05_xhalen00.zip
CC = gcc
CFLAGS = -Wall -std=c++20 -MMD
QMFLAGS = -spec linux-g++ CONFIG+=qtquickcompiler
LDLIBS = -lstdc++

PROJ_SRCS = $(wildcard $(PROJ)*.cpp)
PROFILE_SRCS = $(wildcard $(PROFILE)*.cpp)

PROJ_OBJS = $(patsubst %.cpp,%.o,$(PROJ_SRCS))
PROFILE_OBJS = $(patsubst %.cpp,%.o,$(PROFILE_SRCS))

DEPS = $(SRCS:.cpp=.d)

EXECS = $(PROJ) $(PROFILE)
OBJS = $(PROJ_OBJS) $(PROFILE_OBJS)

PROF_DIR = ../profiling

QMAKE_PATH = qmake

PACKAGE_NAME = calculator-1.0
INSTALLER_DEPS = qt6-base-dev qtbase5-dev

PROFILER_NAME = stddev-1.0

.PHONY: clean all gui

gui:
	mkdir -p build
	cd build && \
	$(QMAKE_PATH) ../calculator.pro $(QMFLAGS) && \
	make

installer: clean user_doc
	sudo apt install -y $(INSTALLER_DEPS)
	mkdir -p installer/$(PACKAGE_NAME)
	mkdir -p ../install/
	cp ../doc/dokumentace.pdf installer-dep/install
	cp *.cpp *.hpp *.h *.ui calculator.pro installer/$(PACKAGE_NAME)/ && \
	cd installer && \
	tar -zcvf $(PACKAGE_NAME).tar.gz $(PACKAGE_NAME) && \
	cd $(PACKAGE_NAME) && \
	cp ../../installer-dep/install -r . && \
	dh_make -n -s -c gpl3 -f ../$(PACKAGE_NAME).tar.gz -y && \
	cp ../../installer-dep/debian/* ./debian/ && \
	dpkg-buildpackage -rfakeroot -uc -b && \
	cd .. && cp calculator_1.0_amd64.deb ../../install/

installer-prof: clean profile
	mkdir -p installer/$(PROFILER_NAME)
	mkdir -p ../install/
	mkdir -p installer-$(PROFILE)-dep/install && \
	cp $(PROFILE) installer-$(PROFILE)-dep/install && \
	cd installer && \
	tar -zcvf $(PROFILER_NAME).tar.gz $(PROFILER_NAME) && \
	cd $(PROFILER_NAME) && \
	cp -r ../../installer-$(PROFILE)-dep/install . && \
	dh_make -n -s -c gpl3 -f ../$(PROFILER_NAME).tar.gz -y && \
	cp ../../installer-$(PROFILE)-dep/debian/* ./debian/ && \
	dpkg-buildpackage -rfakeroot -uc -b && \
	cd .. && cp *.deb ../../install/

run-gui: gui
	./build/calculator

all: $(PROJ) $(PROFILE) $(GUI)

$(PROJ): $(OBJS)

profile:
	g++ -pg stddev.cpp calc-lib.cpp -o stddev;

run: $(PROJ)
	./$(PROJ)

pack: purge doc user_doc installer installer-prof clean
	mkdir -p ../odevzdani/repo
	cd ../doc && make purge
	mv -r ../install ../odevzdani
	cd .. && rsync -a --exclude="odevzdani/" * odevzdani/repo
	mv repo/src/html ../odevzdani/doc
	cd ../odevzdani && zip -r $(ZIP) * && mv $(ZIP) ..

# pack minimal version for VUT IS
pack_is:
	cd .. && zip -r $(ZIP) hodnoceni.txt src dokumentace.pdf odevzdani.txt

test:
	mkdir -p build-tests
	cd build-tests && cmake .. && cmake --build . && ./tests-all

prof: stddev.cpp calc-lib.cpp
	g++ $(CFLAGS)  stddev.cpp calc-lib.cpp -o stddev;

prof_generate: profile
# Generate input
	seq 10 		| shuf > $(PROF_DIR)/prof_values10;
	seq 1000 	| shuf > $(PROF_DIR)/prof_values1000;
	seq 1000000	| shuf > $(PROF_DIR)/prof_values1000000;
# Generate .gmon files
	./stddev < $(PROF_DIR)/prof_values10 		> /dev/null	&& mv gmon.out $(PROF_DIR)/gmon10.out;
	./stddev < $(PROF_DIR)/prof_values1000		> /dev/null && mv gmon.out $(PROF_DIR)/gmon1000.out;
	./stddev < $(PROF_DIR)/prof_values1000000 	> /dev/null	&& mv gmon.out $(PROF_DIR)/gmon1000000.out;
# Generate profiling results
	gprof stddev $(PROF_DIR)/gmon10.out			> $(PROF_DIR)/prof_result10.txt;
	gprof stddev $(PROF_DIR)/gmon1000.out		> $(PROF_DIR)/prof_result1000.txt;
	gprof stddev $(PROF_DIR)/gmon1000000.out	> $(PROF_DIR)/prof_result1000000.txt;
# Remove temp files (generated input files, gmon files)
	rm -f $(PROF_DIR)/gmon10*;
	rm -f $(PROF_DIR)/prof_values10*;
# Generate callgraph (if gprah2dot is installed)
	-cat $(PROF_DIR)/prof_result1000000.txt | python -m gprof2dot -n0 -e0 | dot -Tpng -o $(PROF_DIR)/callgraph.png
# Render prokol.pdf
	-pdflatex protokol.tex
# Clean profiling/*

prof_clean:
	rm -rf $(PROF_DIR)/*

doc:
	doxygen

user_doc:
	cd ../doc && make && cp dokumentace.pdf ../

-include $(DEPS)

clean: clean_user_doc
	rm -f $(EXECS) $(OBJS) $(DEPS)
	rm -rf build-tests build html latex installer ../odevzdani ../*.zip

purge: clean
	rm -rf ../install $(PROF_DIR)


clean_user_doc:
	cd ../doc && make purge

