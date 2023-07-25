set grid

sim_name = "FluPandemic"
txt_file__name = "sim".sim_name.".txt"

set terminal png size 750,1200 enhanced font "Helvetica 8"
set output sim_name.".png"

set multiplot layout 4,1 columns

set title sim_name.' simulation'
set xrange [0:10.0]
set yrange [0:300]
set xlabel "t [sec] -->"

plot txt_file__name u 1:2 w l t 'N' 
plot txt_file__name u 1:3 w l t 'I'
plot txt_file__name u 1:4 w l t 'B'
plot txt_file__name u 1:5 w l t 'P'

unset multiplot
 