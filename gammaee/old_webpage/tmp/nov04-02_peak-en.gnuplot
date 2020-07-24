set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "nov04-02_peak-en.pbm"
set title " Energy Stability"
set xlabel "Runs"
set xtics (start, 0, start)
set ylabel "Energy in GeV"
plot [-5:5][-0.0004:0.0004] "nov04-02_peak-en.dat", -0.0002 with lines 2, 0 with lines 1, 0.0002 with lines 2
exit
