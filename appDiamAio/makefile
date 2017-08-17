CC=g++-6 -std=c++14

WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

aD=diamaio.hpp
aDEPS=$(addprefix ../,$(aD))

bD=common.hpp inc.hpp mrand.hpp utils.hpp destat.hpp
bDEPS=$(addprefix ../,$(bD))

cD=graph.hpp tartaly.hpp treap.hpp
cDEPS=$(addprefix ../,$(cD))

default:_app

_app: app.cc $(aDEPS) $(bDEPS) $(cDEPS)
	$(CC) $(LF) app.cc -o _app

pgapp: 
	$(CC) $(LF) -pg app.cc -o _app; ./_app ; gprof ./_app > _gp.out


clean:
	rm -f _app
