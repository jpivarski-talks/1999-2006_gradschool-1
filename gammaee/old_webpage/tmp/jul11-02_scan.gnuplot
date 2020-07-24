set nokey
set size 0.75,0.5
set term pbm small monochrome
set output "jul11-02_scan.pbm"
set title "July 11 Scan"
set xlabel "Beam Energy in GeV"
set ylabel "Hadronic Cross-Section in nb"
plot [5.00671:5.02858][0:11.29] "jul11-02_scan.dat" with errorbars
exit
