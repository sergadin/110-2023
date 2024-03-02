#Set linestyle 1 to blue (#0060ad)
set style line 1 \
	linecolor rgb '#0060ad' \
	linetype 1 linewidth 2 \
	pointtype 7 pointsize 1.5 \
	
#set terminal dumb

set terminal png size 1920,1080 enhanced font "Helveticf,20"
set output 'output.png'

plot 'data1.txt' with linespoints linestyle 1, \
	'data2.txt'
