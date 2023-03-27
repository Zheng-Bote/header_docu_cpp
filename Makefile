CXX := clang++
CXXFLAGS := -std=c++20 -I/opt/homebrew/opt/openssl@3.1/include/openssl -L/opt/homebrew/opt/openssl@3.1/lib -lcrypto
#-stdlib=libc++

DEBUG_FLAGS = -g3 -O0
RELEASE_FLAGS = -DNDEBUG -O3
WARNING_FLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wconversion

FLAGS := $(CXXFLAGS) $(DEBUG_FLAGS) $(WARNING_FLAGS)

# dirs
SRCDIR := src
OBJDIR := obj
BINDIR := bin

EXEFILE := start

objs := $(OBJDIR)/start.o $(OBJDIR)/rz_files.o $(OBJDIR)/rz_datetime.o $(OBJDIR)/rz_filesystem.o $(OBJDIR)/rz_crypt.o

# make
$(BINDIR)/$(EXEFILE): $(objs)
	mkdir -p $(BINDIR)
	$(CXX) $(FLAGS) -o $@ $^

# link
$(OBJDIR)/start.o: $(SRCDIR)/start.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(FLAGS) -c $(SRCDIR)/start.cpp -o $(OBJDIR)/start.o

# files
$(OBJDIR)/rz_files.o: $(SRCDIR)/rz_files.cpp $(SRCDIR)/rz_files.h
	mkdir -p $(OBJDIR)
	$(CXX) $(FLAGS) -c $(SRCDIR)/rz_files.cpp -o $(OBJDIR)/rz_files.o

# rz_datetime
$(OBJDIR)/rz_datetime.o: $(SRCDIR)/rz_datetime.cpp $(SRCDIR)/rz_datetime.h
	mkdir -p $(OBJDIR)
	$(CXX) $(FLAGS) -c $(SRCDIR)/rz_datetime.cpp -o $(OBJDIR)/rz_datetime.o

# rz_filesystem
$(OBJDIR)/rz_filesystem.o: $(SRCDIR)/rz_filesystem.cpp $(SRCDIR)/rz_filesystem.h
	mkdir -p $(OBJDIR)
	$(CXX) $(FLAGS) -c $(SRCDIR)/rz_filesystem.cpp -o $(OBJDIR)/rz_filesystem.o

# rz_crypt
$(OBJDIR)/rz_crypt.o: $(SRCDIR)/rz_crypt.cpp $(SRCDIR)/rz_crypt.h
	mkdir -p $(OBJDIR)
	$(CXX) $(FLAGS) -c $(SRCDIR)/rz_crypt.cpp -o $(OBJDIR)/rz_crypt.o

# clean
clean:
	rm -f $(BINDIR)/start $(OBJDIR)/*

