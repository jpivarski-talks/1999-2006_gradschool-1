set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "may28-02_peak-en.pbm"
set title "May 28 Peak Point Energy Stability"
set xlabel "Runs"
set xtics (126496, 126530, 126564)
set ylabel "Energy in GeV"
plot [126491:126569][5.01233:5.01313] "may28-02_peak-en.dat", 5.01253 with lines 2, 5.01273 with lines 1, 5.01293 with lines 2
exit
