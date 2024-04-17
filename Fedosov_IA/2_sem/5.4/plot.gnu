#Set linestyle 1 to blue (#0060ad)
set style line 1 \
	linecolor rgb '#0060ad' \
	linetype 1 linewidth 2 \
	pointtype 7 pointsize 4 \

set style line 2 \
	linecolor rgb '#990099' \
	linetype 1 linewidth 2 \
	pointtype 7 pointsize 4 \
	
#set terminal dumb

set terminal png size 1920,1080 enhanced font "Helveticf,20"
set output 'output1.png'

plot 'data2.txt' with linespoints linestyle 1, \
	'data1.txt' with linespoints linestyle 2

set terminal png size 1920,1080 enhanced font "Helveticf,20"
set output 'output2.png'

plot 'data4.txt' with linespoints linestyle 1, \
	'data3.txt' with linespoints linestyle 2