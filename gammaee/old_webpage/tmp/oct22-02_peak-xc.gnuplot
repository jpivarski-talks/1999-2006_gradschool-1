set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "oct22-02_peak-xc.pbm"
set title "Oct 22 Peak Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (129535, 129632, 129730)
set ylabel "Hadronic XC in nb"
plot [129530:129735][0:13.284] "oct22-02_peak-xc.dat" with errorbars
exit
