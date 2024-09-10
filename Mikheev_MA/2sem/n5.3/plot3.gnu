set terminal pngcairo enhanced font "Lucida Console, 13" fontscale 1.0 size 1280, 960
set output "pic3.png"
set title "График функции"
set xlabel "X"
set ylabel "Y"

plot log(x) with lines linecolor "blue" title "y = ln(x)", \
     "out5.txt" using 1:2 with points pointsize 1 pointtype 7 linecolor "blue" title "Данные точки", \
     "out6.txt" using 1:2 with points pointsize 6 pointtype 1 linecolor "black" title "Полученные точки"
