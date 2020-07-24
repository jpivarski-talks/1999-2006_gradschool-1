set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "sep29-02_cont-xc.pbm"
set title "Sep 29 Continuum Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (129064, 129072, 129080)
set ylabel "Hadronic XC in nb"
plot [129059:129085][0:4.092] "sep29-02_cont-xc.dat" with errorbars
exit
