PROJ = calc
PROFILE = prof
GUI = gui
GUI = gui
ZIP = xtobol06_xtesar43_xsteti05_xhalen00.zip
CC = gcc
CFLAGS = -Wall -std=c++20 -MMD
QMFLAGS = -spec linux-g++ CONFIG+=qtquickcompiler
QMFLAGS = -spec linux-g++ CONFIG+=qtquickcompiler
LDLIBS = -lstdc++

PROJ_SRCS = $(wildcard $(PROJ)*.cpp)
PROFILE_SRCS = $(wildcard $(PROFILE)*.cpp)

PROJ_OBJS = $(patsubst %.cpp,%.o,$(PROJ_SRCS))
PROFILE_OBJS = $(patsubst %.cpp,%.o,$(PROFILE_SRCS))

DEPS = $(SRCS:.cpp=.d)

EXECS = $(PROJ) $(PROFILE)
OBJS = $(PROJ_OBJS) $(PROFILE_OBJS)

QMAKE_PATH = qmake

PACKAGE_NAME = calculator-1.0


.PHONY: clean all gui

gui:
	mkdir -p build
	cd build && \
	$(QMAKE_PATH) ../calculator.pro $(QMFLAGS) && \
	make

installer:
	sudo apt install -y $(INSTALLER_DEPS)
	mkdir -p installer/$(PACKAGE_NAME)
	mkdir -p ../install/
	cp *.cpp *.hpp *.h *.ui calculator.pro installer/$(PACKAGE_NAME)/ && \
	cd installer && \
	tar -zcvf $(PACKAGE_NAME).tar.gz $(PACKAGE_NAME) && \
	cd $(PACKAGE_NAME) && \
	cp ../../installer-dep/install -r . && \
	dh_make -n -s -c gpl3 -f ../$(PACKAGE_NAME).tar.gz -y && \
	cp ../../installer-dep/debian/* ./debian/ && \
	dpkg-buildpackage -rfakeroot -uc -b && \
	cd .. && cp calculator_1.0_amd64.deb ../../install/

run-gui: gui
	./build/Calculator

all: $(PROJ) $(PROFILE) $(GUI)

$(PROJ): $(OBJS)
$(PROFILE): $(PROFILE_OBJS)

profile: $(PROFILE)

run: $(PROJ)
	./$(PROJ)

pack: clean doc user_doc
	mkdir -p ../odevzdani/repo
	cd ../doc && make purge
	cd .. && rsync -a --exclude="odevzdani/" * odevzdani/repo
	ln -s repo/src/html ../odevzdani/doc
	ln -s repo/install ../odevzdani/install
	cd ../odevzdani && zip -r --symlinks $(ZIP) * && mv $(ZIP) ..

# pack minimal version for VUT IS
pack_is:
	cd .. && zip -r $(ZIP) hodnoceni.txt src dokumentace.pdf odevzdani.txt

test:
	mkdir -p build-tests
	cd build-tests && cmake .. && cmake --build . && ./tests-all
	mkdir -p build-tests
	cd build-tests && cmake .. && cmake --build . && ./tests-all

doc:
	doxygen

user_doc:
	cd ../doc && make && mv dokumentace.pdf ../

-include $(DEPS)

clean: clean_user_doc
	rm -f $(EXECS) $(OBJS) $(DEPS)
	rm -rf build-test build html latex installer ../install ../odevzdani ../*.zip

clean_user_doc:
	cd ../doc && make purge
