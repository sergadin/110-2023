set terminal png
set output 'intersection.png'
set title 'Initial and Transformed Triangles with Intersection'
set xrange [-0.2:2.2]
set yrange [-0.2:3.2]
plot '-' with lines lw 2 lc rgb 'blue' title 'Triangle 1 (Initial)', '-' with lines lw 2 lc rgb 'green' title 'Triangle 2', '-' with lines lw 2 lc rgb 'red' title 'Intersection', '-' with lines lw 2 lc rgb 'cyan' title 'Triangle 1 (Transformed)'
0 0
1 0
0 1
0 0
e
0.5 0.5
1.5 3
2 1.5
0.5 0.5
e
0.80595 1.06285
1.71525 1.47899
1.2991 2.38829
0.80595 1.06285
e
1.71525 1.47899
1.2991 2.38829
0.80595 1.06285
1.71525 1.47899
e
