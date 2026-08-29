# Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
# E-mail: avp70ru@mail.ru 
# Данная программа является свободным программным обеспечением: вы можете 
# распространять ее и/или изменять согласно условиям Стандартной общественной 
# лицензии GNU (GPLv3).

TARGET = math
SOURCES = main.c math.c
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)
GLANG_CFLAGS = -std=c11 -Os -DNDEBUG -Wall -Wextra
CLANG_CFLAGS = -std=c11 -Oz -DNDEBUG -Wall -Wextra -Wno-stringop-overflow -Wno-unknown-warning-option
LDFLAGS = -s
ifeq ($(UNAME_S),Windows)
    EXT = .exe
    RM = del /q
    GET_SIZE = wc -c < $(TARGET)$(EXT) 2>nul || echo 0
    RUN_CMD = $(TARGET)$(EXT)
else
    EXT =
    RM = rm -f
    GET_SIZE = wc -c < $(TARGET)$(EXT) 2>/dev/null || echo 0
    RUN_CMD = ./$(TARGET)
endif

.PHONY: all c musl run clean size
all: clean
	@gcc $(GLANG_CFLAGS) -o $(TARGET)$(EXT) $(SOURCES) $(LDFLAGS)
	@$(MAKE) --no-print-directory size
c: clean
	@clang $(CLANG_CFLAGS) -o $(TARGET)$(EXT) $(SOURCES) $(LDFLAGS)
	@$(MAKE) --no-print-directory size
musl:
	@gcc $(BASE_CFLAGS) -static -o $(TARGET)-static $(SOURCES) $(LDFLAGS)
size:
	@SIZE=$$($(GET_SIZE)); echo "$(TARGET)$(EXT) $$SIZE byte"
run: clean
	@gcc $(GLANG_CFLAGS) -o $(TARGET)$(EXT) $(SOURCES) $(LDFLAGS)
	@$(MAKE) --no-print-directory size
	@$(RUN_CMD) || echo "(exit $$?)"
clean:
	@$(RM) $(TARGET)$(EXT) 2>/dev/null || true
