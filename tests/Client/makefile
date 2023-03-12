# makefile uteset client

CXX = g++
CC = $(CXX)

CPPFLAGS = -I $(INC_DIR) -I $(INL_DIR)
CPPFLAGS += -MMD -MP
# c language
CFLAGS = -g3

# c++ language
CXXFLAGS = -std=c++14
CXXFLAGS+= -Wall -pedantic 
CXXFLAGS+=#-Werror
CXXFLAGS+= -g3

LDFLAGS =
LDLIBS = -lpthread

SRC_DIR= ../../src/
INC_DIR= ../../inc/
INL_DIR= ../../inc/inl/

TARGET = utestClient
OBJS = utestClient.o $(SRC_DIR)client.o 
		

all: $(TARGET)

$(TARGET): $(OBJS)

check: $(TARGET)
	./$(TARGET) -v

vala: all
	valgrind --leak-check=yes --track-origins=yes -s ./$(TARGET)

DEPENDS= $(OBJS:%.o=%.d)

clean:
	@$(RM) $(TARGET) $(OBJS) $(DEPENDS)

.PHONY: all check clean DEPENDS

-include $(DEPENDS) 