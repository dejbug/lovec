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
all : $(NAME).exe
	strip $<
	upx -9 $<
else
all : $(NAME).exe
endif

$(NAME).exe : main.o crc32.o
main.o : main.cpp error_id.h error_t.h file_t.h dll_t.h args_t.h lua_dll_t.h lua_handle_t.h crc32.h strutil.h path_t.h zstr_t.h cmp.h
crc32.o : crc32.cpp crc32.h

%.exe : ; $(CXX) -o $@ $(filter %.o %.a %.dll,$^) $(CXXFLAGS) $(LDFLAGS)
%.o : ; $(CXX) -o $@ -c $(filter %.c %.cpp,$^) $(CXXFLAGS)

.PHONY : run clean reset

run : $(NAME).exe ; @.\$<

clean : ; DEL *.o 2> NUL
reset : | clean ; DEL $(NAME).exe 2> NUL
