#!/usr/local/bin/perl

foreach $run ( 122536, 122537, 122538, 122539, 122540, 122541, 122542, 122545,
	       122548, 122549, 122550, 122551, 122555, 122556, 122557,
	       122559, 122560, 122562, 122563, 122564, 122568, 122569,
	       122570, 122571, 122572, 122573, 122574, 122575, 122576, 122577,
	       122579, 122585, 122586, 122587, 122590, 122593, 122594,
	       122596, 122599, 122602, 122603, 122604, 122605,
	       122606, 122608, 122610, 122613, 122614, 122615, 122616,
	       122618, 122619, 122620, 122623, 122625, 122626,
	       122628, 122629, 122631, 122632, 122634, 122640, 122641,
	       122642, 122643, 122646, 122647, 122648, 122649, 122650, 122653,
	       122654, 122657, 122658, 122661, 122665, 122667, 
	       122672, 122673 ) {
    open(LOG, "/home/mccann/hadron_filter/run/dec25-01/log/r$run.log");
    $passed_hbook_terminate = 0;
    $passed_exit = 0;
    $all_cuts = 0;
    $hadron_cut = 0;
    $saw_2 = 0;
    $saw_3 = 0;
    while(<LOG>) {
	if ( $_ =~ /^Suez\.r$run> hbook terminate$/ ) {
	    $passed_hbook_terminate = 1;
	}
	if ( $_ =~ /^Suez\.r$run> exit$/ ) {
	    $passed_exit = 1;
	}
	elsif ( $passed_hbook_terminate == 1 && $passed_exit == 1 ) {
	    if ( $_ =~ /HadronFilterProc: Events which have passed \/ all events = ([0-9]+) \/ ([0-9]+) / ) {
		$all_cuts = $1;
		$hadron_cut = $2;
	    }
	    elsif ( $hadron_cut != 0  &&  $_ =~ /Summary from EventTypeFilterProc/  &&
		    $_ =~ /for\s+([0-9]+) events/ ) {
		$saw_2 = 1;
	    }
	    elsif ( $hadron_cut != 0  &&  $_ =~ /passed EventTypeFilterProc filtering/  &&
		    $_ =~ /=\s+([0-9]+) events/ ) {
		$saw_3 = 1;
	    }
	}
    }
    die if ( $saw_2 == 0 );
    die if ( $saw_3 == 0 );

    print "$run $all_cuts\n";
}

