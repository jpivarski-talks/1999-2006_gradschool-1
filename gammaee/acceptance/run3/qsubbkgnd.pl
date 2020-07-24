#!/usr/local/bin/perl

foreach $run (

# positron beamgas
126785,
# electron beamgas
126828, 126920, 126922, 127014,
# cosmic rays
128706, 128736, 128741, 128746, 128748, 128750, 128751,

	      ) {

    do {
        $qstat = `qstat -u mccann | grep id1 | wc -l`;
        chop($qstat);

	if ($qstat >= 8) {
	    print "Waiting $ARGV[0] seconds...\n";
	    sleep $ARGV[0];
	}
    } while ($qstat >= 8);

    print "Submitting $run.\n";
    system("qsub id$run.run");
}
