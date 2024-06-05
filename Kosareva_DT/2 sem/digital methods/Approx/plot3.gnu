set terminal pngcairo enhanced font "arial,12" fontscale 1.0 size 1000, 1000
set output "graph3.png"
set title "Функция и интерполяция"
set xlabel "x"
set ylabel "y"
set grid
plot "function3.txt" using 1:2 with lines linecolor "blue" linewidth 2 notitle, \
	"given3.txt" using 1:2 with points pointsize 3 pointtype 5 linecolor "green" title "Given", \
	"output3.txt" using 1:2 with points pointsize 3 pointtype 6 linecolor "red" title "Found"
