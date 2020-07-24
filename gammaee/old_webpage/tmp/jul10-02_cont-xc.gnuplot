set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jul10-02_cont-xc.pbm"
set title " Hadronic XC Stability"
set xlabel "Runs"
set xtics (start, 0, start)
set ylabel "Hadronic XC in nb"
plot [-5:5][0:0] "jul10-02_cont-xc.dat" with errorbars
exit
