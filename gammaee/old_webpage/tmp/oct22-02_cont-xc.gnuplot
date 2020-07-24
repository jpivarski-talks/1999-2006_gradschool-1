set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "oct22-02_cont-xc.pbm"
set title "Oct 22 Continuum Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (129519, 129525, 129531)
set ylabel "Hadronic XC in nb"
plot [129514:129536][0:4.14] "oct22-02_cont-xc.dat" with errorbars
exit
