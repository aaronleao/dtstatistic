#!/bin/bash

mkdir ../statistic_actives

liglist=$(ls *.top | cut -d. -f1)

for lig in $liglist
do
	./dtstatistic -l $lig -c 2.0 -n 20 -o dts_$lig.log
done

mv dts_* ../statistic_actives
#cd ../
