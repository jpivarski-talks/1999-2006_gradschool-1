set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "oct22-02_cont-en.pbm"
set title "Oct 22 Continuum Point Energy Stability"
set xlabel "Runs"
set xtics (129519, 129525, 129531)
set ylabel "Energy in GeV"
plot [129514:129536][4.99913:4.99993] "oct22-02_cont-en.dat", 4.99933 with lines 2, 4.99953 with lines 1, 4.99973 with lines 2
exit
