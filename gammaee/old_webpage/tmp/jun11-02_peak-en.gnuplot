set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jun11-02_peak-en.pbm"
set title "Jun 11 Peak Point Energy Stability"
set xlabel "Runs"
set xtics (126831, 126873, 126915)
set ylabel "Energy in GeV"
plot [126826:126920][5.01239:5.01319] "jun11-02_peak-en.dat", 5.01259 with lines 2, 5.01279 with lines 1, 5.01299 with lines 2
exit
