#!/bin/bash
for file in /auto_home/tcastanie/tp7/bibliR2/*.pgm
do
echo $(./moyBibli $file) $file >> tabMoy.txt
done