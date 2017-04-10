#TODO : compilation sur Windows

#CC = gcc
CFLAGS = -Wall -g -std=c99
LDFLAGS = 

#MODIFIER JDKPATH SELON VOTRE INSTALLATION
#une façon simple pour avoir une idée du chemin d'installation sous linux : readlink -f $(which java)
JDKPATH = /usr/lib/jvm/java-7-openjdk-amd64/
JINCLUDE = -I$(JDKPATH)include -I$(JDKPATH)include/linux

JC = javac
JFLAGS = -g
JAVAFILES = Hex.java

#BINDIR = bin
OBJDIR = obj

#pour clean
#EXEC = 



.PHONY: all clean create_dir

all: libHex classes

#for_future_use:  
#	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)


$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	
#Java
classes:
	$(JC) $(JFLAGS) $(JAVAFILES)
	mv *.class $(OBJDIR)

#compile la bibliothèque utilisée par la partie java
libHex:
	$(CC) -fPIC $(JINCLUDE) -o $(OBJDIR)/hex.o -c hex.c
	$(CC) -shared -o libhex.so $(OBJDIR)/hex.o
	

create_dir:
	mkdir obj
#	mkdir bin

clean:
	rm -f $(OBJDIR)/*.o
#	rm -f $(BINDIR)/$(EXEC)
	rm -f *.class
