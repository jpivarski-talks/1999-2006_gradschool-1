set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jul11-02_cont-xc.pbm"
set title "July 11 Continuum Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (127619, 127671, 127723)
set ylabel "Hadronic XC in nb"
plot [127614:127728][0:4.272] "jul11-02_cont-xc.dat" with errorbars
exit
