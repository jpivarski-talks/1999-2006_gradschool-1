#!/usr/local/bin/perl

foreach $run (

	      "y2pho3_129535.run",
	      "y2pho3_129536.run",
	      "y2pho3_129538.run",
	      "y2pho3_129539.run",
	      "y2pho3_129540.run",
	      "y2pho3_129541.run",
	      "y2pho3_129545.run",

	      "y3pho3_121916.run",
	      "y3pho3_121917.run",
	      "y3pho3_121918.run",
	      "y3pho3_121920.run",
	      "y3pho3_121924.run",
	      "y3pho3_121925.run",
	      "y3pho3_121927.run",

	      ) {

    do {
        $qstat = `qstat -u mccann | wc -l`;
        chop($qstat);

        if ($qstat >= 37) {
            print "Waiting five minutes...\n";
            sleep 300;
        }
    } while ($qstat >= 37);

    print "Submitting $run.\n";
    system("qsub $run");
}
