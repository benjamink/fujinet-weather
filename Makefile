# Generic CC65 TARGETS makefile++
#
# Set the TARGETS and PROGRAM values as required.
# Put any custom settings into 'custom.mk' in root folder, e.g. additional LDFLAGS, AUTOSTART etc.

# see makefiles/build.mk for details on directory structure for src files

TARGETS = atari apple2
PROGRAM := weather

SUB_TASKS := build clean disk test get_fujinet_lib get_apple_tools 
.PHONY: all $(SUB_TASKS) 

all:
	@for target in $(TARGETS); do \
		echo "-------------------------------------"; \
		echo "Building $$target"; \
		echo "-------------------------------------"; \
		$(MAKE) --no-print-directory -f makefiles/build.mk CURRENT_TARGET=$$target PROGRAM=$(PROGRAM) $(MAKECMDGOALS); \
	done

$(SUB_TASKS): _do_all
$(SUB_TASKS):
	@:

_do_all: all