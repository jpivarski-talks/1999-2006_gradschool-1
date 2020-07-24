set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jun11-02_cont-xc.pbm"
set title "Jun 11 Continuum Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (126832, 126844, 126856)
set ylabel "Hadronic XC in nb"
plot [126827:126861][0:4.08] "jun11-02_cont-xc.dat" with errorbars
exit
