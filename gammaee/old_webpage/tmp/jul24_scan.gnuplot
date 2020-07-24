set nokey
set size 0.75,0.5
set term pbm small monochrome
set output "jul24_scan.pbm"
set title "July 24 Scan"
set xlabel "Beam Energy in GeV"
set ylabel "Hadronic Cross-Section in nb"
plot [4.9965:5.1813][0:10.19] "jul24_scan.dat" with errorbars
exit
