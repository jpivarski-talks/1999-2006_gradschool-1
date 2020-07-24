set nokey
set size 0.75,0.5
set term pbm small monochrome
set output "jun28-02_scan.pbm"
set title "June 28 High-Energy Tail Point"
set xlabel "Beam Energy in GeV"
set ylabel "Hadronic Cross-Section in nb"
plot [5.0096:5.04473][0:11.81] "jun28-02_scan.dat" with errorbars
exit
