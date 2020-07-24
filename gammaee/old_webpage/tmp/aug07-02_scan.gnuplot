set nokey
set size 0.75,0.5
set term pbm small monochrome
set output "aug07-02_scan.pbm"
set title "August 7 Scan"
set xlabel "Beam Energy in GeV"
set ylabel "Hadronic Cross-Section in nb"
plot [4.9965:5.01723][0:11.42] "aug07-02_scan.dat" with errorbars
exit
