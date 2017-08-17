CC=g++ -std=c++14

WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

pDEPS=csillagos.hpp graph.hpp wgraph.hpp tartaly.hpp treap.hpp mrand.hpp inc.hpp pagerank.hpp artipt.hpp
DEPS=$(addprefix ../,$(pDEPS))


default:_app

_app: app.cc $(DEPS)
	$(CC) $(LF) app.cc -o _app


pgapp: 
	$(CC) $(LF) -pg app.cc -o _app; ./_app ; gprof ./_app > gp.out

clean:
	rm -f _app
