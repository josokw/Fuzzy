set grid

sim_name = "Delay"
txt_file__name = "sim".sim_name.".txt"

set terminal png size 1000,1000 enhanced font "Helvetica 8"
set output sim_name.".png"

set multiplot layout 4,1 columns

set title sim_name.' simulation'
set xrange [0:10]
set yrange [-4:4]
set xlabel "t [sec] -->"

plot txt_file__name  u 1:2 w l t 'PLS'
plot txt_file__name u 1:3 w l t 'Y1'
plot txt_file__name  u 1:4 w l t 'FRQ'
plot txt_file__name u 1:5 w l t 'Y2'

unset multiplot