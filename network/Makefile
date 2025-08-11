#gcc:
CD = gcc
CP = g++
AC = arm-linux-gnueabihf-gcc
AP = arm-linux-gnueabihf-g++
#gcc flags:
CFLAGS = -pedantic-errors -Wall -Wextra -g -fPIC
INCLUDE = -I ./inc/
#compiler:
GD := $(CD) $(CFLAGS) $(DEBUG) $(INCLUDE)
GP := $(CP) $(CFLAGS) $(DEBUG) $(INCLUDE)
GAC := $(AC) $(CFLAGS) $(DEBUG) $(INCLUDE)
GAP := $(AP) $(CFLAGS) $(DEBUG) $(INCLUDE)
#library flags:
LDFLAGS = -shared
LDLIBS_C = -lnetwork_c -L . -Wl,-rpath,.
LDLIBS_CPP = -lnetwork_cpp -L . -Wl,-rpath,.
LDLIBS_ARM = -lnetwork_arm_c -L . -Wl,-rpath,.
#dirs:
SRC_DIR = ./src/
TEST_DIR = ./test/
#files:
NET_SRC = $(SRC_DIR)network_utils.c
TCP_S = $(TEST_DIR)tcp_server.c
TCP_C = $(TEST_DIR)tcp_client.c
UDP_S = $(TEST_DIR)udp_server.c
UDP_C = $(TEST_DIR)udp_client.c
UDP_BS = $(TEST_DIR)udp_broadcast_sender.c
UDP_BR = $(TEST_DIR)udp_broadcast_receiver.c
SERVER = $(TEST_DIR)server_test.cpp $(SRC_DIR)server.cpp $(NET_SRC)
OBJS_C = network_utils_c.o
OBJS_CPP = network_utils_cpp.o
OBJS_ARM_C = network_utils_arm_c.o
OBJS_ARM_CPP = network_utils_arm_cpp.o
OBJS = $(OBJS_C) $(OBJS_CPP) $(OBJS_ARM)
#targets:
LIB_C = libnetwork_c.so
LIB_CPP = libnetwork_cpp.so
LIB_ARM = libnetwork_arm_c.so
LIBS = $(LIB_C) $(LIB_CPP) $(LIB_ARM)
TARGETS = network_arm_static server tcp_s tcp_c udp_s udp_s_pi udp_c udp_bs udp_br
#clean:
RM = rm -f

all : $(TARGETS)

#obj:
network_utils_c.o: $(NET_SRC)
	$(GD) $(NET_SRC) -c -o $@

network_utils_cpp.o: $(NET_SRC)
	$(GP) $(NET_SRC) -c -o $@

network_utils_arm_c.o: $(NET_SRC)
	$(GAC) $(NET_SRC) -c -o $@

network_utils_arm_cpp.o: $(NET_SRC)
	$(GAP) $(NET_SRC) -c -o $@

#so:	
libnetwork_c.so : $(OBJS_C)
	$(GD) $(LDFLAGS) $(OBJS_C) -o $@

libnetwork_cpp.so : $(OBJS_CPP)
	$(GP) $(LDFLAGS) $(OBJS_CPP) -o $@

libnetwork_arm_c.so : $(OBJS_ARM_C)
	$(GAC) $(LDFLAGS) $(OBJS_ARM_C) -o $@

network_arm_static: $(OBJS_ARM_CPP)
	ar rcs -o /home/lior/git/projects/final_project/concrete/libnetwork_arm.a $?

#exe:
server : $(SERVER) $(LIB_CPP)
	$(GP) $(SERVER) $(LDLIBS_CPP) -o $@

tcp_s : $(TCP_S) $(LIB_C)
	$(GD) $(TCP_S) $(LDLIBS_C) -o $@
	
tcp_c : $(TCP_C) $(LIB_C)
	$(GD) $(TCP_C) $(LDLIBS_C) -o $@
	
udp_s : $(UDP_S) $(LIB_C)
	$(GD) $(UDP_S) $(LDLIBS_C) -o $@

udp_s_pi : $(UDP_S) $(LIB_ARM)
	$(GAC) $(UDP_S) $(LDLIBS_ARM) -o $@
	
udp_c : $(UDP_C) $(LIB_C)
	$(GD) $(UDP_C) $(LDLIBS_C) -o $@

udp_bs : $(UDP_BS) $(LIB_C)
	$(GD) $(UDP_BS) $(LDLIBS_C) -o $@
	
udp_br : $(UDP_BR) $(LIB_C)
	$(GD) $(UDP_BR) $(LDLIBS_C) -o $@
	
.PHONY: clean

clean: 
	$(RM) $(OBJS) $(LIBS) $(TARGETS)

