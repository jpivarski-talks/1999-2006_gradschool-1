set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jun11-02_peak-xc.pbm"
set title "Jun 11 Peak Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (126831, 126873, 126915)
set ylabel "Hadronic XC in nb"
plot [126826:126920][0:11.676] "jun11-02_peak-xc.dat" with errorbars
exit
