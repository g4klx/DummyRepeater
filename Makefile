export BINDIR  := /usr/bin

export CXX     := $(shell wx-config --cxx)
export CFLAGS  := -O2 -Wall $(shell wx-config --cxxflags)
export LIBS    := $(shell wx-config --libs adv,core) -lasound -lusb-1.0
export LDFLAGS := 

# Uncomment below lines to build with wiringpi GPIO support
export CFLAGS  := $(CFLAGS) -DGPIO
export LIBS    := $(LIBS) -lwiringPi

.PHONY: all
all:	DummyRepeater/dummyrepeater

DummyRepeater/dummyrepeater:	Common/Common.a force
	$(MAKE) -C DummyRepeater

Common/Common.a:	force
	$(MAKE) -C Common

.PHONY: install
install:	all
	$(MAKE) -C DummyRepeater install

.PHONY: clean
clean:
	$(MAKE) -C Common clean
	$(MAKE) -C DummyRepeater clean

.PHONY: force
force :
	@true