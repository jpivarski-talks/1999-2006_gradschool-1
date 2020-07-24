set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jul24-02_cont-en.pbm"
set title "July 24 Continuum Point Energy Stability"
set xlabel "Runs"
set xtics (127950, 127952, 127955)
set ylabel "Energy in GeV"
plot [127945:127960][4.99814:4.99894] "jul24-02_cont-en.dat", 4.99834 with lines 2, 4.99854 with lines 1, 4.99874 with lines 2
exit
