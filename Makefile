include make/all.mk
include make/flags.mk
include make/variables.mk
include make/functions.mk
include make/objects.mk
include make/special_rules.mk

# TODO: split up into per-directory Makefiles
STATUS_SRC := src/util/status.cc
STATUSOR_SRC := $(STATUS_SRC)
CPU_SRC := $(shell find src/cpu/ -type f -name "*.cc" -not -name "*_test.cc")
NESTY_SRC := src/main.cc $(CPU_SRC)

$(eval $(call binary,nesty,$(NESTY_SRC)))

$(eval $(call test,status_test,src/util/status_test.cc $(STATUS_SRC)))
$(eval $(call test,statusor_test,src/util/statusor_test.cc $(STATUSOR_SRC)))
