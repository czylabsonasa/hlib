cres<-data.table(read.table("cres"))
tbl<-as.matrix(read.table("pelda5",skip=1))
g<-graph_from_edgelist(tbl, directed = FALSE)
res<-page.rank(g)$vector
x<-cor(res,cres)