CC=g++ -std=c++11
PCC=g++-4.9 -std=c++11

WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

aD=csillagos.hpp pagerank.hpp cluster.hpp
aDEPS=$(addprefix ../,$(aD))

bD=common.hpp inc.hpp mrand.hpp utils.hpp destat.hpp
bDEPS=$(addprefix ../,$(bD))

cD=graph.hpp tartaly.hpp treap.hpp
cDEPS=$(addprefix ../,$(cD))

default:_app


_app: app.cc $(aDEPS) $(bDEPS) $(cDEPS)
	$(CC) $(LF) app.cc -o _app

pgapp: 
	$(PCC) $(LF) -pg app.cc -o _app; ./_app ; gprof ./_app > gp.out


clean:
	rm -f _app
