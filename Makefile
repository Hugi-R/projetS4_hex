# Visiblement la console windows accepte / comme délimiteur entre dossier (ainsi que \)

#----Windows ou Linux----
ifeq ($(OS),Windows_NT)
	LIBCMD = -shared -o hex.dll $(OBJDIR)/hex.o hex.def
	RM = del /Q
	OSDIR = win32
else
	LIBCMD = -shared -o libhex.so $(OBJDIR)/hex.o
	RM = rm -f
	OSDIR = linux
endif
#------------------------

#--Variables modifiables-
# A MODIFIER SELON VOTRE INSTALLATION
CC = gcc
JDKPATH = C:/Program\ Files/Java/jdk1.8.0_111/
#une façon simple pour avoir une idée du chemin d'installation sous linux : readlink -f $(which java)
#ne pas oublier d'ignorer les espaces avec un \

JC = $(JDKPATH)bin/javac
JINCLUDE = -I$(JDKPATH)include -I$(JDKPATH)include/$(OSDIR)

CFLAGS = -Wall -g -std=c99
LDFLAGS = 

JFLAGS = -g

OBJDIR = obj
#------------------------

JAVAFILES = Hex.java

.PHONY: all clean create_dir

all: libHex classes

#for_future_use:  
#	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)


$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	
#Java
classes:
	$(JC) $(JFLAGS) $(JAVAFILES)


#compile la bibliothèque utilisée par la partie java
libHex:
	$(CC) -fPIC $(JINCLUDE) -o $(OBJDIR)/hex.o -c hex.c
	$(CC) $(LIBCMD)
	

create_dir:
	mkdir obj

clean:
	$(RM) $(OBJDIR)/*.o
	$(RM) *.class
