set grid

sim_name = "Logic"
txt_file__name = "sim".sim_name.".txt"

set terminal png size 750,1200 enhanced font "Helvetica 8"
set output sim_name.".png"

set multiplot layout 5,1 columns

set title sim_name.' simulation'
set xrange [0:1.0]
set yrange [-0.2:1.2]
set xlabel "t [sec] -->"

plot txt_file__name u 1:2 w l t 'in PULS' 
plot txt_file__name u 1:3 w l t 'in PULS'
plot txt_file__name u 1:4 w l t 'out AND'
plot txt_file__name u 1:5 w l t 'out OR' 
plot txt_file__name u 1:6 w l t 'out NOT' 


unset multiplot
 