set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "nov04-02_cont-xc.pbm"
set title "November 4 Continuum Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (129842, 129853, 129864)
set ylabel "Hadronic XC in nb"
plot [129837:129869][0:4.5] "nov04-02_cont-xc.dat" with errorbars
exit
