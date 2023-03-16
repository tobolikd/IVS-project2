PROJ = calc
PROFILE = prof
DOCUMENTATION = calculator.html # TODO add documentation name
ZIP = xtobol06_xtesar43_xsteti05_xhalen00.zip
CC = gcc
CFLAGS = -Wall -std=c11 -MMD
LDLIBS = -lm

PROJ_SRCS = $(wildcard $(PROJ)*.cpp)
PROFILE_SRCS = $(wildcard $(PROFILE)*.cpp)

PROJ_OBJS = $(patsubst %.c,%.o,$(PROJ_SRCS))
PROFILE_OBJS = $(patsubst %.c,%.o,$(PROFILE_SRCS))



DEPS = $(SRCS:.c=.d)

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
	cd build && cmake .. && cmake --build .

doc:
	doxygen

user_doc:
	cd ../doc && make && mv dokumentace.pdf ../

-include $(DEPS)

clean: clean_user_doc
	rm -f $(EXECS) $(OBJS) $(DEPS)
	rm -rf build html latex ../odevzdani ../*.zip

clean_user_doc:
	cd ../doc && make purge
