# This is meant to be run from the vcv/ dir
# make -f tests/Makefile

TEST_DIR ?= tests
DOCTESTHEADER_DIR ?= $(TEST_DIR)
BUILDDIR = $(TEST_DIR)/build/obj
RYMLDIR = lib/patch-serial/ryml/rapidyaml
JANSSON_CONF_DIR = tests/jansson
JANSSON_DIR = tests/jansson/jansson/src

TEST_SOURCES = $(TEST_DIR)/doctest.cc
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_SOURCES += lib/patch-serial/patch_to_yaml.cc
TEST_SOURCES += lib/patch-serial/ryml/ryml_serial.cc
TEST_SOURCES += lib/patch-serial/ryml/ryml_init.cc
TEST_SOURCES += src/mapping/patch_writer.cc
TEST_SOURCES += $(wildcard $(RYMLDIR)/src/c4/yml/*.cpp)
TEST_SOURCES += $(wildcard $(RYMLDIR)/ext/c4core/src/c4/*.cpp)
TEST_SOURCES += $(wildcard $(JANSSON_DIR)/*.c)


INCLUDES = -I. \
			-Isrc \
			-Isrc/hub \
			-Isrc/mapping\
			-Ilib\
			-Ilib/cpputil \
			-Ilib/patch-serial \
			-Ilib/patch-serial/ryml \
			-I$(TEST_DIR) \
			-I$(RYMLDIR)/src \
			-I$(RYMLDIR)/ext/c4core/src \
			-Ilib/metamodule-core-interface \
			-I$(JANSSON_DIR) \
			-I$(JANSSON_CONF_DIR) \

CFLAGS = -DHAVE_CONFIG_H \
		 -DTESTPROJECT \

CXXFLAGS = 	-Wall \
		 	-std=gnu++2a \
			-DTESTPROJECT \
			-Wno-missing-braces \

### Boilerplate below here:

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(TEST_SOURCES))))
DEPDIR := $(BUILDDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(basename $<).d

.PHONY: all tests clean

TMPFILE = $(BUILDDIR)/runtests.out

all: $(DOCTESTHEADER_DIR)/doctest.h tests

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CC) -c $(DEPFLAGS) $(INCLUDES) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) -c $(DEPFLAGS) $(INCLUDES) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) -c $(DEPFLAGS) $(INCLUDES) $(CXXFLAGS) $< -o $@

tests: $(BUILDDIR)/runtests
	@$(BUILDDIR)/runtests --out=$(TMPFILE) && echo "[√] Unit tests passed: $(notdir $(PWD))" || cat $(TMPFILE)

$(BUILDDIR)/runtests: $(OBJECTS)
	@$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

$(DOCTESTHEADER_DIR)/doctest.h:
	wget https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h -P $(DOCTESTHEADER_DIR)/

clean:
	rm -rf $(BUILDDIR)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(addprefix $(DEPDIR)/, $(addsuffix .d, $(basename $(TEST_SOURCES))))
$(DEPFILES):

include $(wildcard $(DEPFILES))

