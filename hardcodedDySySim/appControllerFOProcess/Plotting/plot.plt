set grid

sim_name = "ControllerFOProcess"
txt_file_name = "sim".sim_name.".txt"

set terminal png size 1000,500 enhanced font "Helvetica 8"
set output sim_name.".png"

set title sim_name
set xrange [0:10]
set yrange [0:1.5]
plot txt_file_name u 1:3 w l t 'control', txt_file_name u 1:4 w l t 'out'
 

