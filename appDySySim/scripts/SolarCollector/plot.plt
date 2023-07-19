set grid

sim_name = "SolarCollector"
txt_file__name = "sim".sim_name.".txt"

set terminal png size 1000,500 enhanced font "Helvetica 8"
set output sim_name.".png"

set title sim_name.' simulation'
set xrange [0:178000]
set yrange [-10:45]
set xlabel "Day time [sec]"
set ylabel "Temperature [^oC]"
plot txt_file__name u 1:2 w l t 'T_{outside} [^oC]', txt_file__name u 1:3 w l t 'T_{tank    } [^oC]', txt_file__name u 1:4 w l t 'T_{house  } [^oC]'
 