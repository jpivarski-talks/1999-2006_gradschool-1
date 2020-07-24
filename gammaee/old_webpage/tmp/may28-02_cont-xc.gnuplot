set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "may28-02_cont-xc.pbm"
set title "May 28 Continuum Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (126252, 126462, 126673)
set ylabel "Hadronic XC in nb"
plot [126247:126678][0:4.932] "may28-02_cont-xc.dat" with errorbars
exit
