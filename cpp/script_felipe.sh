#!/bin/bash

mkdir ../statistic_actives

liglist=$(ls *.top | cut -d. -f1)

for lig in $liglist
do
	/scratch/dockvs/softwares/dtstatistic -l $lig -c 2.0 -n 10 -o dts_$lig
done

mv dts_* ../statistic_actives
#cd ../
