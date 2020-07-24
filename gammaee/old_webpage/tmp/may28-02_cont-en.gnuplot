set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "may28-02_cont-en.pbm"
set title "May 28 Continuum Point Energy Stability"
set xlabel "Runs"
set xtics (126252, 126462, 126673)
set ylabel "Energy in GeV"
plot [126247:126678][4.998031:5.004019] "may28-02_cont-en.dat", 5.000825 with lines 2, 5.001025 with lines 1, 5.001225 with lines 2
exit
