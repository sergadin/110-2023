set terminal pngcairo enhanced font "arial,10" fontscale 1.0 size 800, 600
set output "pic3.png"
set title "Сравнение двух функций"
set xlabel "X"
set ylabel "Y"
plot "out5.txt" using 1:2 with points pointsize 1 pointtype 5 linecolor "red" title "Данные точки", \
     "out5.txt" using 1:2 with lines linecolor "red" linewidth 3 notitle, \
     "out6.txt" using 1:2 with points pointsize 3 pointtype 3 linecolor "black" title "Полученные точки"