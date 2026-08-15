# Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
# E-mail: avp70ru@mail.ru 
# Данная программа является свободным программным обеспечением: вы можете 
# распространять ее и/или изменять согласно условиям Стандартной общественной 
# лицензии GNU (GPLv3).

TARGET = math
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)
BASE_CFLAGS = -std=c11 -Os -DNDEBUG -Wall -Wextra -flto
LDFLAGS =

ifeq ($(UNAME_S),Windows)
    EXT = .exe
    RM = del /q
    GET_SIZE = wc -c < $(TARGET)$(EXT) 2>nul || echo 0
    RUN_CMD = ./$(TARGET)$(EXT)
else
    EXT =
    RM = rm -f
    GET_SIZE = wc -c < $(TARGET)$(EXT) 2>/dev/null || echo 0
    RUN_CMD = ./$(TARGET)
endif

SOURCES = main.c math.c $(SYS_SRC)

.PHONY: all musl run clean size

all: clean
	@$(CC) $(BASE_CFLAGS) -o $(TARGET)$(EXT) $(SOURCES) $(LDFLAGS)
	@$(MAKE) --no-print-directory size

musl: clean
	@$(CC) $(BASE_CFLAGS) -o $(TARGET)$(EXT) $(SOURCES) $(LDFLAGS)
	@$(MAKE) --no-print-directory size

size:
	@SIZE=$$($(GET_SIZE)); echo "$(TARGET)$(EXT) $$SIZE byte"

run: clean
	@$(CC) $(BASE_CFLAGS) -o $(TARGET)$(EXT) $(SOURCES) $(LDFLAGS)
	@$(MAKE) --no-print-directory size
	@$(RUN_CMD) || echo "(exit $$?)"

clean:
	@$(RM) $(TARGET)$(EXT) 2>/dev/null || true
