BEGIN{ 
gdir=".."; 
ldir="."; 
}
   // {akt=$2}
   /^G/{ printf "***  [[%s/%s][%s]]\n",gdir,akt,akt; }
   /^L/{ printf "***  [[%s/%s][%s]]\n",ldir,akt,akt; }
   /^P/{ 
      printf "* %s\n",akt;
      printf "**  [[%s/app.cc][app.cc]]\n",ldir;
   }
END{}
