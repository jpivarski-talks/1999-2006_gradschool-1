set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jul24_cont-en.pbm"
set title "July 24 Continuum Point Energy Stability"
set xlabel "Runs"
set xtics (127955, 127955, 127955)
set ylabel "Energy in GeV"
plot [127950:127960][4.99818:4.99898] "jul24_cont-en.dat", 4.99838 with lines 2, 4.99858 with lines 1, 4.99878 with lines 2
exit
