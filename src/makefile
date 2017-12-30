CXX = g++
CXXFLAGS = -g
CXXFLAGS += -std=c++0x

OBJS =  main.o Island.o Space.o Player.o utilities.o 

SRCS =  main.cpp Island.cpp Space.cpp Player.cpp utilities.cpp

main: ${OBJS}
	${CXX} ${OBJS} -o main
	
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c   $(@:.o=.cpp)
	
clean:
	rm main *.o