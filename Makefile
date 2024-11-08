ifeq ($(origin CC),default)
	СС = g++
endif

OBLIGATORE= -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ \
	  	-Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations \
	  	-Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported \
		-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral \
		-Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
		-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith \
		-Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
		-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn \
		-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default \
		-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast \
		-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing \
		-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation \
		-fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
		-Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -D DOUBLE_STACK -D NDEBUG
target = test
override CFLAGS += $(OBLIGATORE)
CSRC = test.cpp list_dump.cpp
COBJ = $(CSRC:%.cpp=%.o)

.PHONY: all clean

all: $(target)

$(target) : $(COBJ)
	@($(СС) $(CFLAGS) $^  -o $(target))

%.o : %.cpp
	@($(CC) $(CFLAGS)  -c -o $@ $^)


clean:
	rm -rf $(target) *.o