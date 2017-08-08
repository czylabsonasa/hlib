CC=g++ -std=c++14


WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

pDEPS=csillagos.hpp graph.hpp wgraph.hpp tartaly.hpp treap.hpp mrand.hpp inc.hpp pagerank.hpp artipt.hpp
DEPS=$(addprefix ../,$(pDEPS))


default:all

app: app.cc $(DEPS)
	$(CC) $(LF) app.cc -o app


pgapp: 
	$(CC) $(LF) -pg app.cc -o app; ./app ; gprof ./app > gp.out

openall: 
	kate *.hpp *.cc makefile model.conf run&

all: app

clean:
	rm -f app
