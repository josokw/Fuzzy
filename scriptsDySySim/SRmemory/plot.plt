set grid

sim_name = "SRmemory"
txt_file__name = "sim".sim_name.".txt"

set terminal png size 750,1200 enhanced font "Helvetica 8"
set output sim_name.".png"

set multiplot layout 5,1 columns

set title sim_name.' simulation'
set xrange [0:10.0]
set yrange [-0.2:1.3]
set xlabel "t [sec] -->"

plot txt_file__name u 1:2 w l t 'in PULS set 0->1' 
plot txt_file__name u 1:3 w l t 'in CLK'
plot txt_file__name u 1:4 w l t 'in PULS reset 0->1'
plot txt_file__name u 1:9 w l t 'out Q'
plot txt_file__name u 1:10 w l t 'out -Q'

unset multiplot
 