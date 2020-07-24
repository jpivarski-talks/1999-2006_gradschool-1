set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jun11-02_cont-en.pbm"
set title "Jun 11 Continuum Point Energy Stability"
set xlabel "Runs"
set xtics (126832, 126844, 126856)
set ylabel "Energy in GeV"
plot [126827:126861][4.998425:4.999225] "jun11-02_cont-en.dat", 4.998625 with lines 2, 4.998825 with lines 1, 4.999025 with lines 2
exit
