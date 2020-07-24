set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jun28-02_cont-xc.pbm"
set title "June 28 Continuum Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (127417, 127430, 127444)
set ylabel "Hadronic XC in nb"
plot [127412:127449][0:4.524] "jun28-02_cont-xc.dat" with errorbars
exit
