set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "nov04-02_cont-en.pbm"
set title "November 4 Continuum Point Energy Stability"
set xlabel "Runs"
set xtics (129842, 129853, 129864)
set ylabel "Energy in GeV"
plot [129837:129869][4.999355:5.000155] "nov04-02_cont-en.dat", 4.999555 with lines 2, 4.999755 with lines 1, 4.999955 with lines 2
exit
