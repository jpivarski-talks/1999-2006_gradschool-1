set nokey
set size 0.75,0.5
set term pbm small monochrome
set output "may28-02_scan.pbm"
set title "May 28 Scan"
set xlabel "Beam Energy in GeV"
set ylabel "Hadronic Cross-Section in nb"
plot [5.00453:5.02865][0:11.74] "may28-02_scan.dat" with errorbars
exit
