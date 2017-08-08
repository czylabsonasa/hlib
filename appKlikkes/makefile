STD=-std=c++11
CC=g++ $(STD) -O2
PCC=g++-4.9 $(STD) 
WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

aD=klikkes.hpp 
aDEPS=$(addprefix ../,$(aD))

bD=common.hpp inc.hpp mrand.hpp utils.hpp destat.hpp
bDEPS=$(addprefix ../,$(bD))

cD=graph.hpp tartaly.hpp treap.hpp
cDEPS=$(addprefix ../,$(cD))

default:all
all: app


app: app.cc $(aDEPS) $(bDEPS) $(cDEPS)
	$(CC) $(LF) app.cc -o _app

pgapp: 
	$(PCC) $(LF) -pg app.cc -o _app; ./_app ; gprof ./_app > gp.out


clean:
	rm -f _app
