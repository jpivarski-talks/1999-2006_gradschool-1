#!/usr/local/bin/perl

foreach $run (

	    "nt_db16.run",
	    "nt_121899.run",
	    "nt_121904.run",
	    "nt_121906.run",
	    "nt_121969.run",
	    "nt_121972.run",
	    "nt_122080.run",
	    "nt_122081.run",
	    "nt_122083.run",
	    "nt_db17.run",
	    "nt_122091.run",
	    "nt_122132.run",
	    "nt_122133.run",
	    "nt_122136.run",
	    "nt_122137.run",
	    "nt_122143.run",
	    "nt_122147.run",
	    "nt_122418.run",
	    "nt_db18.run",
	    "nt_122429.run",
	    "nt_122430.run",
	    "nt_122576.run",
	    "nt_122586.run",
	    "nt_122587.run",
	    "nt_122594.run",
	    "nt_122647.run",
	    "nt_122800.run",
	    "nt_db19.run",
	    "nt_122802.run",
	    "nt_122816.run",
	    "nt_122829.run",
	    "nt_122831.run",
	    "nt_122832.run",
	    "nt_123043.run",
	    "nt_123044.run",
	    "nt_db21.run",
	    "nt_123817.run",
	    "nt_123853.run",
	    "nt_124684.run",
	    "nt_125176.run",
	    "nt_126473.run",
	    "nt_126488.run",
	    "nt_126563.run",
	    "nt_126831.run",
	    "nt_126835.run",
	    "nt_db23.run",
	    "nt_126870.run",
	    "nt_127317.run",
	    "nt_129071.run",
	    "nt_129572.run",
	    "nt_129630.run",
	    "nt_129845.run",
	    "nt_129848.run",
	    "nt_130427.run",
	    "nt_130473.run",
	    "nt_127319.run",
	    "nt_129564.run",

	    ) {
    do {
        $qstat = `qstat -u mccann | wc -l`;
        chop($qstat);

	if ($qstat >= 5) {
	    print "Waiting five minutes...\n";
	    sleep 300;
	}
    } while ($qstat >= 5);

    system("qsub $run");
}
