set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jul24-02_cont-xc.pbm"
set title "July 24 Continuum Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (127950, 127952, 127955)
set ylabel "Hadronic XC in nb"
plot [127945:127960][0:4.152] "jul24-02_cont-xc.dat" with errorbars
exit
