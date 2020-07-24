set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jul24_cont-xc.pbm"
set title "July 24 Continuum Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (127955, 127955, 127955)
set ylabel "Hadronic XC in nb"
plot [127950:127960][0:3.804] "jul24_cont-xc.dat" with errorbars
exit
