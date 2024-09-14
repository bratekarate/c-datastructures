CC=gcc
CFLAGS=-I. -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
FLAGS=-g -pedantic -Wall -Wextra
CLIBS=-lglib-2.0
NAME=data_structures
SRCDIR=src
TESTDIR=test
DEPS=$(SRCDIR)/dastruct.h
OUTDIR=out
OBJ_LIB=arraylist.o linkedlist.o
OBJ_MAIN=$(addprefix $(OUTDIR)/, $(OBJ_LIB) main.o)
OBJ_TEST=$(addprefix $(OUTDIR)/, $(OBJ_LIB) tests.o)

$(OUTDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@[ -d "$(@D)" ] || mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $(FLAGS) -c -o $@ $<

main: $(OUTDIR)/$(NAME)
$(OUTDIR)/$(NAME): $(OBJ_MAIN)
	$(CC) $(FLAGS) $(CFLAGS) -o $@ $^ $(CLIBS)

$(OUTDIR)/%.o: $(TESTDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) $(FLAGS) -c -o $@ $<

test: $(OUTDIR)/$(NAME)_tests
$(OUTDIR)/$(NAME)_tests: $(OBJ_TEST) $(OUTDIR)/tests.o
	$(CC) $(FLAGS) $(CFLAGS) -o $@ $^ $(CLIBS)

watch:
	@command -v inotifywait > /dev/null || \
		{ \
			echo "Please install inotifywait"; exit 2; \
		}
	@while true ; do \
		NAME=$$(inotifywait \
			-e create,modify \
			--include '.*\.(c|h)' \
			--format '%w%f' \
			"$(SRCDIR)" "$(TESTDIR)"); \
		($(MAKE)); \
		($(MAKE) test); \
	done
