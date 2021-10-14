# ----------------------------
# Makefile Options
# ----------------------------

NAME = CONNECT4
DESCRIPTION = "Connect 4 game for TI-84 pluc CE"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
