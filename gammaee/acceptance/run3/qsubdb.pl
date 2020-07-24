#!/usr/local/bin/perl

foreach $run (

	      122091, 122133, 122430, 122832, 123817, 123853, 124684,
	      125176, 126488, 126870, 129572, 130427,

	      121969, 122634, 122808, 123013, 123592, 123638, 124708,
	      126521, 126531, 126906, 127318, 127418, 127955, 129674,
	      129850, 130268, 130316

	      ) {

    do {
        $qstat = `qstat -u mccann | grep db1 | wc -l`;
        chop($qstat);

	if ($qstat >= 30) {
	    print "Waiting $ARGV[0] seconds...\n";
	    sleep $ARGV[0];
	}
    } while ($qstat >= 30);

    print "Submitting $run.\n";
    system("qsub db$run.run");
}
