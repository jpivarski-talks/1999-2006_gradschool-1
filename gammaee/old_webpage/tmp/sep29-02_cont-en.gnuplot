set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "sep29-02_cont-en.pbm"
set title "Sep 29 Continuum Point Energy Stability"
set xlabel "Runs"
set xtics (129064, 129072, 129080)
set ylabel "Energy in GeV"
plot [129059:129085][4.999365:5.000165] "sep29-02_cont-en.dat", 4.999565 with lines 2, 4.999765 with lines 1, 4.999965 with lines 2
exit
