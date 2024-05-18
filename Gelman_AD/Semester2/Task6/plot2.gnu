set terminal pngcairo enhanced font "arial,10" fontscale 1.0 size 800, 600
set output "pic2.png"
set title "Comparing two functions"
set xlabel "X"
set ylabel "Y"
plot "out3.txt" using 1:2 with points pointsize 1 pointtype 5 linecolor "red" title "Given points", \
     "out3.txt" using 1:2 with lines linecolor "red" linewidth 3 notitle, \
     "out4.txt" using 1:2 with points pointsize 3 pointtype 3 linecolor "black" title "Obtained points"