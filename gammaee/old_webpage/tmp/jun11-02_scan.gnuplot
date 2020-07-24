set nokey
set size 0.75,0.5
set term pbm small monochrome
set output "jun11-02_scan.pbm"
set title "Jun 11 Scan"
set xlabel "Beam Energy in GeV"
set ylabel "Hadronic Cross-Section in nb"
plot [5.00476:5.02862][0:9.85] "jun11-02_scan.dat" with errorbars
exit
