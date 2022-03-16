include make/all.mk
include make/flags.mk
include make/variables.mk
include make/functions.mk
include make/objects.mk
include make/special_rules.mk

# TODO: split up into per-directory Makefiles
NESTY_SRC := src/main.cc

$(eval $(call binary,nesty,$(NESTY_SRC)))
