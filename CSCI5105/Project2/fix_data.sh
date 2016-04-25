#!/bin/bash
for i in `ls data`
do
  grep -e '^Write\|^Read' data/$i | sort >> data/file.csv
done

sort data/file.csv > data/filedone.csv
