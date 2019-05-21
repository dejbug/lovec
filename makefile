NAME ?= lovec

DEPLOY ?= 0
STATIC ?= 0

PEDANTIC ?= 1


CXX := g++
CXXFLAGS :=
LDFLAGS :=

ifeq ($(DEPLOY), 1)
CXXFLAGS += \
	-O3 \
	-flto \
	-faggressive-loop-optimizations
endif

ifeq ($(STATIC), 1)
CXXFLAGS += -static
endif

ifneq ($(PEDANTIC), 0)
CXXFLAGS += -pedantic-errors
CXXFLAGS += -Wall -Wextra -Wpedantic
else
CXXFLAGS += -Wno-unused-parameter
endif

INCLUDE_PREREQS = 1
NON_BUILD_GOALS := clean reset


ifeq ($(findstring clean,$(MAKECMDGOALS)), clean)
INCLUDE_PREREQS = 0
else ifeq ($(findstring reset,$(MAKECMDGOALS)), reset)
INCLUDE_PREREQS = 0
endif


SOURCES := $(subst /,\,$(wildcard src/*.cpp))
PREREQS := $(SOURCES:src\\%.cpp=build\\%.d)
OBJECTS := $(SOURCES:src\\%.cpp=build\\%.o)


.PHONY : all

ifeq ($(DEPLOY), 1)
all : deploy\$(NAME).exe | deploy
	strip $<
	upx -9 $<
else
all : deploy\$(NAME).exe | deploy
endif

ifeq ($(INCLUDE_PREREQS),1)
include $(PREREQS)
endif

deploy\$(NAME).exe : $(OBJECTS)

build deploy : ; $(call MKDIR,$@)

deploy\\%.exe : | deploy ; $(call LINK,$@,$^)
build\\%.o : src\%.cpp | build ; $(call COMPILE,$@,$^)
build\\%.d : src\%.cpp | build ; $(call GEN_PREREQ,$@,$<)


.PHONY : run clean reset

run : deploy\$(NAME).exe ; $(call RUN,$<)
clean : ; $(call DELTREE,build)
reset : | clean ; $(call DELTREE,deploy)


.DELETE_ON_ERROR :


define MKDIR
@echo --- creating dir "$1"
@IF NOT EXIST $1 mkdir $1
endef

define DELTREE
@echo --- removing dir "$1"
@IF EXIST $1 ( RMDIR /S /Q $1 )
endef

define RUN
@echo --- running "$1"
@echo.
@.\$1
endef

define COMPILE
@echo --- compiling "$1"
@echo.
$(CXX) -c $(filter %.c %.cpp,$2) -o $1 $(CXXFLAGS)
@echo.
endef

define LINK
@echo --- linking "$1"
@echo.
$(CXX) $(filter %.o %.a %.dll,$2) -o $1 $(CXXFLAGS) $(LDFLAGS)
@echo.
endef

define GEN_PREREQ
@echo --- generating prerequisites "$1" for "$2"
@echo.
$(CXX) -MF $1 -MM -MG $2 -MT "$1 $(notdir $(1:.d=.o))" $(CXXFLAGS)
@echo.
endef

define HAS_GOAL
$(findstring $1,$(MAKECMDGOALS))
endef

define HAS_NON_BUILD_GOAL
$(or $(call HAS_GOAL,clean),$(call HAS_GOAL,reset))
endef
