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

#  	if ($run == 122418  ||
#  	    $run == 122147  ||
#  	    $run == 122133  ||
#  	    $run == 122080  ||
#  	    $run == 123817  ||
#  	    $run == 123853  ||
#  	    $run == 124684  ||
#  	    $run == 125176  ||
#  	    $run == 129572  ||
#  	    $run == 129564  ||
#  	    $run == 126870  ||
#  	    $run == 126488     ) {
	if ($run == 123817  ||
	    $run == 125176  ||
	    $run == 126473  ||
	    $run == 126488  ||
	    $run == 126831  ||
	    $run == 126835  ||
	    $run == 129071  ||
	    $run == 129845  ||
	    $run == 129848  ||
	    $run == 130427  ||
	    $run == 121899  ||
	    $run == 121904  ||
	    $run == 121906  ||
	    $run == 122080  ||
	    $run == 122081  ||
	    $run == 122083  ||
	    $run == 122418  ||
	    $run == 122429  ||
	    $run == 122586  ||
	    $run == 122587  ||
	    $run == 122594  ||
	    $run == 122800  ||
	    $run == 122802    ) {
	    open(RUN, "> runs/L$run.run");
	    print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/lumint_$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/luminosity/run/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_DIR=$dir
export USER_RUN=$run
export USER_HASB=$hasb

suez -f ntuple_data.tcl
rm -f core

exit
";
        close(RUN);
        }

    } # end foreach run
    @runs = ();
} # end foreach dir


