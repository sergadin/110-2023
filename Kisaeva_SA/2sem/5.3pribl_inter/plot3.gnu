set terminal pngcairo enhanced font "arial,10" fontscale 1.0 size 800, 600
set output "pic3.png"
set title "Сравнение функции f=cos(x) и базовых точек"
set xlabel "X"
set ylabel "Y"
plot "out5.txt" using 1:2 with points pointsize 1 pointtype 5 linecolor "purple" title "Данные точки функции", \
     "out5.txt" using 1:2 with lines linecolor "purple" linewidth 3 notitle, \
     "out6.txt" using 1:2 with points pointsize 3 pointtype 30 linecolor "black" title "Полученные базовые точки"