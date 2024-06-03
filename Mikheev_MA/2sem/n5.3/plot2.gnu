set terminal pngcairo enhanced font "Lucida Console, 13" fontscale 1.0 size 1280, 960
set output "pic2.png"
set title "График функции"
set xlabel "X"
set ylabel "Y"

plot sin(x) with lines linecolor "blue" title "y = sin(x)", \
     "out3.txt" using 1:2 with points pointsize 1 pointtype 7 linecolor "blue" title "Данные точки", \
     "out4.txt" using 1:2 with points pointsize 6 pointtype 1 linecolor "black" title "Полученные точки"
