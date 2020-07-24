set nokey
set size 0.75,0.5
set term pbm small monochrome
set output "oct22-02_scan.pbm"
set title ""
set xlabel "Beam Energy in GeV"
set ylabel "Hadronic Cross-Section in nb"
plot [-0.002:0.002][0:2] "oct22-02_scan.dat" with errorbars
exit
