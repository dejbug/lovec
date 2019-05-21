NAME ?= lovec

DEPLOY ?= 0
STATIC ?= 0

PEDANTIC ?= 1


CXX := g++
CXXFLAGS :=
LDFLAGS :=

ifneq ($(DEPLOY), 0)
CXXFLAGS += \
	-O3 \
	-flto \
	-faggressive-loop-optimizations
endif

ifneq ($(STATIC), 0)
CXXFLAGS += -static
endif

ifneq ($(PEDANTIC), 0)
CXXFLAGS += -pedantic-errors
CXXFLAGS += -Wall -Wextra -Wpedantic
else
CXXFLAGS += -Wno-unused-parameter
endif


.PHONY : all

ifneq ($(DEPLOY), 0)
all : deploy\$(NAME).exe | build deploy
	strip $<
	upx -9 $<
else
all : deploy\$(NAME).exe
endif


deploy\$(NAME).exe : build\main.o build\crc32.o

build\main.o : $(addprefix src\,main.cpp error_id.h error_t.h file_t.h dll_t.h args_t.h lua_dll_t.h lua_handle_t.h crc32.h strutil.h path_t.h zstr_t.h cmp.h)

build\crc32.o : $(addprefix src\,crc32.cpp crc32.h)

build : ; IF NOT EXIST $@ MKDIR $@

deploy : ; IF NOT EXIST $@ MKDIR $@


%.exe : | deploy ; $(CXX) -o $@ $(filter %.o %.a %.dll,$^) $(CXXFLAGS) $(LDFLAGS)
%.o : | build ; $(CXX) -o $@ -c $(filter %.c %.cpp,$^) $(CXXFLAGS)


.PHONY : run clean reset

run : deploy\$(NAME).exe ; @.\$<
clean : ; IF EXIST build RMDIR /S /Q build
reset : | clean ; IF EXIST deploy RMDIR /S /Q deploy
