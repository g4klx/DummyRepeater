export BINDIR  := /usr/bin

export CXX     := $(shell wx-config --cxx)
export CFLAGS  := -O2 -Wall $(shell wx-config --cxxflags)
export LIBS    := $(shell wx-config --libs adv,core) -lasound -lusb-1.0
export LDFLAGS := 

all:	DummyRepeater/dummyrepeater

DummyRepeater/dummyrepeater:	Common/Common.a
	make -C DummyRepeater

Common/Common.a:
	make -C Common

install:	all
	make -C DummyRepeater install

clean:
	make -C Common clean
	make -C DummyRepeater clean

