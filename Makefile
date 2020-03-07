export BINDIR  := /usr/bin

export CXX     := $(shell wx-config --cxx)
export CFLAGS  := -O2 -Wall $(shell wx-config --cxxflags)
export LIBS    := $(shell wx-config --libs adv,core) -lasound -lusb-1.0
export LDFLAGS := 

all:	DummyRepeater/dummyrepeater

DummyRepeater/dummyrepeater:	Common/Common.a
	$(MAKE) -C DummyRepeater

Common/Common.a:
	$(MAKE) -C Common

install:	all
	$(MAKE) -C DummyRepeater install

clean:
	$(MAKE) -C Common clean
	$(MAKE) -C DummyRepeater clean

