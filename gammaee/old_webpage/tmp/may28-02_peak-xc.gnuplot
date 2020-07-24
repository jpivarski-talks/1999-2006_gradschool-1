set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "may28-02_peak-xc.pbm"
set title "May 28 Peak Point Hadronic XC Stability"
set xlabel "Runs"
set xtics (126496, 126530, 126564)
set ylabel "Hadronic XC in nb"
plot [126491:126569][0:12.048] "may28-02_peak-xc.dat" with errorbars
exit
