CC = g++
#INCLUDE = -I/usr/include/openbabel-2.0/
INCLUDE =
CFLAGS = -std=c++11 -c -g -Wall
#LDFLAGS = -lopenbabel
LDFLAGS =
TARGET = dtstatistic
PARSING = parsing
DIRECTORY = directory
SORT = sort
MOLECULE = molecule
CLUSTERING = clustering
RMSD = rmsd
LOG = log
SRCS = parsing.cpp directory.cpp sort.cpp molecule.cpp clustering.cpp rmsd.cpp log.cpp dtstatistic.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)
	
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(TARGET).o: $(TARGET).cpp 
	$(CC) $(CFLAGS) $(TARGET).cpp

$(MOLECULE).o: $(MOLECULE).cpp 
	$(CC) $(CFLAGS) $(MOLECULE).cpp

$(SORT).o: $(SORT).cpp
	$(CC) $(CFLAGS) $(SORT).cpp

$(DIRECTORY).o: $(DIRECTORY).cpp
	$(CC) $(CFLAGS) $(DIRECTORY).cpp

$(PARSING).o: $(PARSING).cpp
	$(CC) $(CFLAGS) $(PARSING).cpp

$(CLUSTERING).o: $(CLUSTERING).cpp
	$(CC) $(CFLAGS) $(CLUSTERING).cpp

$(RMSD).o: $(RMSD).cpp
	$(CC) $(CFLAGS) $(RMSD).cpp

$(LOG).o: $(LOG).cpp
	$(CC) $(CFLAGS) $(LOG).cpp

clean:
	$(RM) $(TARGET) $(OBJS)	
