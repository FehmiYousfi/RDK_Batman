CC = gcc

SRCDIR = src

INCDIR = include
INCDIR_ubus = $(INCDIR)/ubus
INCDIR_ubox = $(INCDIR)/libubox
INCDIR_json = $(INCDIR)/json

OUT_LIB_dir := lib
BUILDDIR = build
BINDIR = bin
combined_out_dir = $(BINDIR)/combined

SOURCES = $(wildcard $(SRCDIR)/*.c $(INCDIR_ubus)/*.c $(INCDIR_ubox)/*.c $(INCDIR_json)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(filter $(SRCDIR)/%.c, $(SOURCES))) \
          $(BUILDDIR)/libubus.o $(BUILDDIR)/libubus-io.o $(BUILDDIR)/libubus-obj.o $(BUILDDIR)/libubus-sub.o $(BUILDDIR)/libubus-req.o \
          $(patsubst $(INCDIR_ubox)/%.c, $(BUILDDIR)/%.o, $(filter $(INCDIR_ubox)/%.c, $(SOURCES))) \
          $(patsubst $(INCDIR_json)/%.c, $(BUILDDIR)/%.o, $(filter $(INCDIR_json)/%.c, $(SOURCES)))

object_ubus := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(filter $(SRCDIR)/%.c, $(SOURCES))) \
          $(BUILDDIR)/libubus.o $(BUILDDIR)/libubus-io.o $(BUILDDIR)/libubus-obj.o $(BUILDDIR)/libubus-sub.o $(BUILDDIR)/libubus-req.o 
object_ubox := $(patsubst $(INCDIR_ubox)/%.c, $(BUILDDIR)/%.o, $(filter $(INCDIR_ubox)/%.c, $(SOURCES)))
object_json := $(patsubst $(INCDIR_json)/%.c, $(BUILDDIR)/%.o, $(filter $(INCDIR_json)/%.c, $(SOURCES)))

EXECUTABLES = $(BINDIR)/client $(BINDIR)/server

define check_and_create_dir
	@if [ ! -d $(1) ]; then \
		mkdir -p $(1); \
		echo "Created directory: $(1)"; \
	else \
		echo "Directory $(1) already exists"; \
	fi
endef

