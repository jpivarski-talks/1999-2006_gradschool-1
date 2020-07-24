set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jun28-02_cont-en.pbm"
set title "June 28 Continuum Point Energy Stability"
set xlabel "Runs"
set xtics (127417, 127430, 127444)
set ylabel "Energy in GeV"
plot [127412:127449][4.998395:4.999195] "jun28-02_cont-en.dat", 4.998595 with lines 2, 4.998795 with lines 1, 4.998995 with lines 2
exit
