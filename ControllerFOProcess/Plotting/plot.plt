set grid
set title 'ControllerFOProcess'
set xrange [0:1]
set yrange [0:4000]
plot 'simdata.txt' u 1:2 w l t 'setpoint', 'simdata.txt' u 1:3 w l t 'control', 'simdata.txt' u 1:4 w l t 'out'
 

