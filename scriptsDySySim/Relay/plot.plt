set grid

sim_name = "Relay"
txt_file__name = "sim".sim_name.".txt"

set terminal png size 1000,500 enhanced font "Helvetica 8"
set output sim_name.".png"

set title sim_name.' simulation'
set xrange [0:1.3]
set yrange [-2:3]
plot txt_file__name u 1:2 w l t 'in(t)', txt_file__name u 1:3 w l t 'out(t)'
 