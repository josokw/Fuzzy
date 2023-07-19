set grid

sim_name = "MassSpringDamper"
txt_file__name = "sim".sim_name.".txt"

set terminal png size 1000,500 enhanced font "Helvetica 8"
set output sim_name.".png"

set title sim_name.' simulation'
set xrange [0:5.2]
set yrange [-0.1:28]
set xlabel "t [sec] -->"
plot txt_file__name  u 1:2 w l t 'in(t)', txt_file__name u 1:3 w l t 'out(t)'
 