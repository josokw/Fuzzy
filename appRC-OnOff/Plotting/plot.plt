set grid

sim_name = "RC-OnOff"
txt_file_name = "sim".sim_name.".txt"

set terminal png size 1000,500 enhanced font "Helvetica 8"
set output sim_name.".png"

set xrange [0:1]
set yrange [-100:4000]
plot 'simdata.txt' u 1:2 w l t 'setpoint', 'simdata.txt' u 1:3 w l t 'control', 'simdata.txt' u 1:4 w l t 'out'
 

