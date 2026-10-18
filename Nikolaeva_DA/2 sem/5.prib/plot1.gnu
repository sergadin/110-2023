set terminal pngcairo enhanced font "arial,10" fontscale 1.0 size 800, 600
set output "pic1.png"
set title "Сравнение функции f=x^2-x-6 и базовых точек"
set xlabel "X"
set ylabel "Y"
plot "out1.txt" using 1:2 with points pointsize 1 pointtype 5 linecolor "purple" title "Данные точки функции", \
     "out1.txt" using 1:2 with lines linecolor "purple" linewidth 3 notitle, \
     "out2.txt" using 1:2 with points pointsize 3 pointtype 30 linecolor "black" title "Полученные базовые точки"