#######################################################

#                                                     #

#                                                     #

#                 20170285 Jihyeon Park               #

#                  20170337 Sojung Son                #

#                                                     #

#                                                     #

#######################################################

 

CC = gcc209

CCFLAGS = -D_DEFAULT_SOURCE -D_GNU_SOURCE

 

.c.o:

$(CC) $(CCFLAGS) -c $<

 

all: ish

 

clean:

rm -f $(OBJECTS)

rm -f $(TARGET)

 

ish: ish.o cmdproc.o dynarray.o fork.o pipe.o validity_test.o

$(CC) $^ -o $@

ish.o : ish.h

cmdproc.o : ish.h

dynarray.o : ish.h

fork.o : ish.h

pipe.o : ish.h

validity_test.o : ish.h
