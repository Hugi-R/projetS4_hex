#TODO : compilation sur Windows

#CC = gcc
CFLAGS = -Wall -g -std=c99
LDFLAGS = 

JINCLUDE = -I/usr/lib/jvm/java-7-openjdk-amd64/include \
-I/usr/lib/jvm/java-7-openjdk-amd64/include/linux

#Java
JC = javac
JFLAGS = -g
CLASS = Test.java

BINDIR = bin
OBJDIR = obj

#pour clean
EXEC = 



.PHONY: all clean create_dir

all: libHex classes

#for_future_use:  
#	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)


$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	
#Java
classes:
	$(JC) $(JFLAGS) $(CLASS)

#compile la bibliothèque utilisée par la partie java
libHex:
	$(CC) -fPIC $(JINCLUDE) -o $(OBJDIR)/libHex.o -c libHex.c
	$(CC) -shared -o libHex.so $(OBJDIR)/libHex.o
	

create_dir:
	mkdir obj
	mkdir bin

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/$(EXEC)
	rm -f *.class
