#!/usr/local/bin/perl

# USER_DIR
# USER_RUN
# USER_HASB

foreach $dir ("rzn3", "rzn4", "rzn5") {
    @runs = (122091, 122133, 122430, 122832, 123817, 123853,
	     124684, 125176, 126488, 126870, 129572, 130427) if ($dir eq "rzn3");
    @runs = (121899, 121906, 121969, 122083, 122132, 122137,
	     122147, 122429, 122576, 122586, 122594, 122647,
	     122802, 122829, 123044) if ($dir eq "rzn4");
    @runs = (121904, 121972, 122080, 122081, 122136, 122143,
	     122418, 122587, 122800, 122816, 122831, 123043,
	     126473, 126563, 126831, 126835, 127317, 127319,
	     129071, 129564, 129630, 129845, 129848, 130473) if ($dir eq "rzn5");
    foreach $run (@runs) {
	$hasb = 0;
	$hasb = 1 if ($run == 123853  ||  $run == 124684  ||  $run == 122133  ||  $run == 121899);

	open(RUN, "> bs_$run.run");
	print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/bs_$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/acceptance/run5/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_DIR=$dir
export USER_RUN=$run
export USER_HASB=$hasb

suez -f bigsyst_data.tcl
rm -f core

exit
";
    close(RUN);

    } # end foreach run
    @runs = ();
} # end foreach dir


