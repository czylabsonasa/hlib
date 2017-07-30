ccf<-function(fname){
  elist<-as.matrix(read.table(fname,skip=1));
  g<-graph_from_edgelist(elist, directed = FALSE);
  ccf<-mean(transitivity(g,type='local',isolates = "zero"));
}