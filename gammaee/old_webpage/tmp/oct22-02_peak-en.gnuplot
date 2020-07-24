set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "oct22-02_peak-en.pbm"
set title "Oct 22 Peak Point Energy Stability"
set xlabel "Runs"
set xtics (129535, 129632, 129730)
set ylabel "Energy in GeV"
plot [129530:129735][4.998107:5.014223] "oct22-02_peak-en.dat", 5.005965 with lines 2, 5.006165 with lines 1, 5.006365 with lines 2
exit
