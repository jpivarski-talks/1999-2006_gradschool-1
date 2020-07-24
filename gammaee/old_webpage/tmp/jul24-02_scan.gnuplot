set nokey
set size 0.75,0.5
set term pbm small monochrome
set output "jul24-02_scan.pbm"
set title "July 24 Scan"
set xlabel "Beam Energy in GeV"
set ylabel "Hadronic Cross-Section in nb"
plot [5.00444:5.02256][0:10.19] "jul24-02_scan.dat" with errorbars
exit
