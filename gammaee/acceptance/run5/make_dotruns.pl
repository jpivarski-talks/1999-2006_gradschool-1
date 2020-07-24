#!/usr/local/bin/perl

# for y in bblumi gglumi; do for x in all3 all2 all1 big3 small3 db16 db17 db18 db19 db21 db23; do for z in aggrcc coolcc normcc; do (echo "1"; echo "exec classic_plots_and_tables.kumac" $x $y $z) | paw | tee $x\_$y\_$z.log; done; done; done

foreach $y ("bblumi", "gglumi") {
    foreach $x ("all3", "all2", "all1", "big3", "small3", "db16", "db17", "db18", "db19", "db21", "db23") {
	foreach $z ("aggrcc", "coolcc", "normcc") {
	    $name = "$x\_$y\_$z";

	    open(NAME, "> $name.run");
	    print NAME "#/usr/local/bin/bash

cd /home/mccann/acceptance/run5/tables5
export DISPLAY=lnx193:0.0
(echo \"1\"; echo \"exec classic_plots_and_tables.kumac\" $x $y $z) | /nfs/cern/pro/bin/pawX11 | tee $name.log
exit
";
}}}
