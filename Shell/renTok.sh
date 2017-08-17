#!/bin/bash
# small modification, search and replace the entire source tree
# find + -exec slower
# how to tell find to match multiple regex pattern? boolean OR argument



#for fn in $(find .. -name "*.cc" -type f -exec grep -l $1 {} \;)
# for fn in $(find .. -name "*.cc" -type f | xargs grep -l $1 - )
echo "processing..."
echo ""
for fn in $(find .. -type f -name "*.cc" -o -name "*.hpp" | xargs grep -l $1 - )
do
   echo ${fn}
   #make a backup: bfn
   bfn=$(echo ${fn}|tr '/.' '_')
   cp ${fn} ./_backup/${bfn}
   cat ${fn} | sed s/$1/$2/g > _tmp_
   mv _tmp_ ${fn}
done