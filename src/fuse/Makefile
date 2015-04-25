CFLAGS=-Wall -DFUSE_USE_VERSION=29 `pkg-config fuse --cflags`
LINKFLAGS=-Wall `pkg-config fuse --libs`

all: bin/qosfs

clean:
	rm -rf bin obj

bin:
	mkdir -p bin

bin/qosfs: bin obj/qosfs.o obj/wrap.o obj/main.o obj/xattrs.o
	g++ -g -o bin/qosfs obj/* $(LINKFLAGS)

obj:
	mkdir -p obj

obj/qosfs.o: obj qosfs.cc qosfs.hh
	g++ -g $(CFLAGS) -c qosfs.cc -o obj/qosfs.o

obj/main.o: obj main.c wrap.hh
	gcc -g $(CFLAGS) -c main.c -o obj/main.o

obj/wrap.o: obj wrap.cc wrap.hh qosfs.hh
	g++ -g $(CFLAGS) -c wrap.cc -o obj/wrap.o

obj/xattrs.o: obj xattrs/xattrs.cc xattrs/xattrs.hh
	g++ -g $(CFLAGS) -c xattrs/xattrs.cc -o obj/xattrs.o
