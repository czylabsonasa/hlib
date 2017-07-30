c=['k';'r';'g';'b';'m';'c'];
v=['f00';'f0';'f1';'f2';'f4';'f16'];
for i=1:2
figure(i)
X=dlmread(deblank(v(i,:)),' ');
s=sum(X(:,2));
X(:,2)/=s;
plot(log10(X(:,1)),log10(X(:,2)),'marker','x','markersize',1,'color',c(i,:));
end