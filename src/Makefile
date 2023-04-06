PROJ = calc
PROFILE = prof
ZIP = xtobol06_xtesar43_xsteti05_xhalen00.zip
CC = gcc
CFLAGS = -Wall -std=c++20 -MMD
LDLIBS = -lstdc++

PROJ_SRCS = $(wildcard $(PROJ)*.cpp)
PROFILE_SRCS = $(wildcard $(PROFILE)*.cpp)

PROJ_OBJS = $(patsubst %.cpp,%.o,$(PROJ_SRCS))
PROFILE_OBJS = $(patsubst %.cpp,%.o,$(PROFILE_SRCS))

DEPS = $(SRCS:.cpp=.d)

EXECS = $(PROJ) $(PROFILE)
OBJS = $(PROJ_OBJS) $(PROFILE_OBJS)

PROF_DIR = ../profiling

.PHONY: clean all

all: $(PROJ) $(PROFILE)

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
	mkdir -p build
	cd build && cmake .. && cmake --build . && ./tests-all

profiling: stddev.cpp
	g++ -Wall -Wextra -pg stddev.cpp -o stddev;
	mkdir -p $(PROF_DIR)/res
	seq 10 		| sort -R > $(PROF_DIR)/prof_values10;
	seq 1000 	| sort -R > $(PROF_DIR)/prof_values1000;
	seq 1000000	| sort -R > $(PROF_DIR)/prof_values1000000;
	./stddev < $(PROF_DIR)/prof_values10 		> /dev/null	&& mv gmon.out $(PROF_DIR)/gmon10.out;
	./stddev < $(PROF_DIR)/prof_values1000		> /dev/null && mv gmon.out $(PROF_DIR)/gmon1000.out;
	./stddev < $(PROF_DIR)/prof_values1000000 	> /dev/null	&& mv gmon.out $(PROF_DIR)/gmon1000000.out;
	gprof stddev $(PROF_DIR)/gmon10.out			> $(PROF_DIR)/res/prof_result10.txt;
	gprof stddev $(PROF_DIR)/gmon1000.out		> $(PROF_DIR)/res/prof_result1000.txt;
	gprof stddev $(PROF_DIR)/gmon1000000.out	> $(PROF_DIR)/res/prof_result1000000.txt;
	rm stddev;

doc:
	doxygen

user_doc:
	cd ../doc && make && mv dokumentace.pdf ../

-include $(DEPS)

clean: clean_user_doc
	rm -f $(EXECS) $(OBJS) $(DEPS)
	rm -rf build html latex ../odevzdani ../*.zip $(PROF_DIR)

clean_user_doc:
	cd ../doc && make purge
