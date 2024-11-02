set terminal x11
set term x11 window "220001e"
set term x11 enhanced font "arial,15" 
set title '{/=20 Big} Medium {/=5 Small}'
set xlabel "X"
set ylabel "Y"
set pointsize 1.5
plot "triangle1.txt" using 1:2 with lines
close 1
