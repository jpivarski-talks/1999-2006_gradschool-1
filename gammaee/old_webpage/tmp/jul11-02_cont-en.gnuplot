set nokey
set size 0.6,0.5
set term pbm small monochrome
set output "jul11-02_cont-en.pbm"
set title "July 11 Continuum Point Energy Stability"
set xlabel "Runs"
set xtics (127619, 127671, 127723)
set ylabel "Energy in GeV"
plot [127614:127728][4.99853:4.99933] "jul11-02_cont-en.dat", 4.99873 with lines 2, 4.99893 with lines 1, 4.99913 with lines 2
exit
