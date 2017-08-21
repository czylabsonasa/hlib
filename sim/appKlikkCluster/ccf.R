elist<-as.matrix(read.table(fname,skip=1));
g<-graph_from_edgelist(elist, directed = FALSE);
ccf<-transitivity(g,type='local',isolates = "zero");
