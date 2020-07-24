#!/usr/local/bin/perl

$limit = 15;

foreach $run (

#	      "y2s_Jun13_03_MC/mc129623.run",
#	      "y2s_Jun13_03_MC/mc129618.run",
#	      "y3s_Jun27_02_MC/mc121932.run",
#	      "y3s_Jun27_02_MC/mc121939.run",
#	      "y2s_Apr16_03_MC/mc129552.run",
#	      "y2s_Apr16_03_MC/mc129545.run",
#	      "y1s_Jun13_03_MC/mc123639.run",
#	      "y2s_Apr16_03_MC/mc129549.run",
#	      "y3s_Jun27_02_MC/mc121916.run",
#	      "y3s_Jun27_02_MC/mc121917.run",
#	      "y3s_Jun27_02_MC/mc121927.run",
#	      "y2s_Jun13_03_MC/mc129620.run",
#	      "y1s_Jun13_03_MC/mc123640.run",
#	      "y2s_Apr16_03_MC/mc129551.run",
#	      "y3s_Jun27_02_MC/mc121928.run",
#	      "y1s_May12_03_MC/mc123653.run",
# 	      "y1s_Jun13_03_MC/mc123633.run",
#	      "y1s_May12_03_MC/mc123651.run",
#	      "y2s_Jun13_03_MC/mc129629.run",
#	      "y1s_May12_03_MC/mc123670.run",
#	      "y2s_Apr16_03_MC/mc129566.run",
#	      "y3s_Jun27_02_MC/mc121924.run",
#	      "y2s_Jun13_03_MC/mc129631.run",
#	      "y1s_Jun13_03_MC/mc123645.run",
#	      "y2s_Apr16_03_MC/mc129539.run",
#	      "y3s_Jun27_02_MC/mc121918.run",
#	      "y3s_Jun27_02_MC/mc121930.run",
#	      "y1s_May12_03_MC/mc123654.run",
#	      "y2s_Jun13_03_MC/mc129626.run",
	      "y1s_Jun13_03_MC/mc123647.run",
#	      "y1s_May12_03_MC/mc123665.run",
	      "y1s_May12_03_MC/mc123650.run",
#  	      "y2s_Jun13_03_MC/mc129635.run",
#	      "y1s_Jun13_03_MC/mc123646.run",
#	      "y2s_Jun13_03_MC/mc129637.run",
#	      "y2s_Jun13_03_MC/mc129638.run",
#	      "y1s_May12_03_MC/mc123658.run",
#	      "y1s_May12_03_MC/mc123652.run",
#	      "y1s_Jun13_03_MC/mc123648.run",
	      "y2s_Apr16_03_MC/mc129564.run",
#	      "y2s_Apr16_03_MC/mc129536.run",
#	      "y2s_Jun13_03_MC/mc129632.run",
#	      "y1s_Jun13_03_MC/mc123641.run",
#	      "y3s_Jun27_02_MC/mc121920.run",
#	      "y1s_Jun13_03_MC/mc123635.run",
#	      "y1s_May12_03_MC/mc123678.run",
#	      "y2s_Jun13_03_MC/mc129619.run",
#	      "y1s_May12_03_MC/mc123674.run",
#	      "y3s_Jun27_02_MC/mc121936.run",
#	      "y1s_May12_03_MC/mc123659.run",
#	      "y2s_Apr16_03_MC/mc129535.run",
#	      "y2s_Apr16_03_MC/mc129550.run",
#	      "y1s_May12_03_MC/mc123675.run",
#	      "y2s_Jun13_03_MC/mc129630.run",
#	      "y1s_Jun13_03_MC/mc123643.run",
#	      "y3s_Jun27_02_MC/mc121929.run",
#	      "y1s_Jun13_03_MC/mc123636.run",
#	      "y2s_Apr16_03_MC/mc129538.run",
#	      "y1s_Jun13_03_MC/mc123638.run",
#	      "y2s_Apr16_03_MC/mc129553.run",
#	      "y2s_Jun13_03_MC/mc129633.run",
#	      "y1s_May12_03_MC/mc123673.run",
#	      "y2s_Jun13_03_MC/mc129641.run",
#	      "y2s_Apr16_03_MC/mc129541.run",
#	      "y1s_May12_03_MC/mc123656.run",
#	      "y1s_Jun13_03_MC/mc123637.run",
#	      "y3s_Jun27_02_MC/mc121933.run",
#	      "y1s_Jun13_03_MC/mc123644.run",
#	      "y2s_Apr16_03_MC/mc129540.run",
#	      "y3s_Jun27_02_MC/mc121925.run",

# None of these: the only 1S peak in db17 has its continuum in db18!!!
#	      "y1s_Jun27_02_MC/mc123610.run",
#	      "y1s_Jun27_02_MC/mc123615.run",
#	      "y1s_Jun27_02_MC/mc123617.run",
#	      "y1s_Jun27_02_MC/mc123632.run",
#	      "y1s_Jun27_02_MC/mc123619.run",
#	      "y1s_Jun27_02_MC/mc123631.run",
#	      "y1s_Jun27_02_MC/mc123612.run",
#	      "y1s_Jun27_02_MC/mc123620.run",
#	      "y1s_Jun27_02_MC/mc123618.run",
#	      "y1s_Jun27_02_MC/mc123616.run",
#	      "y1s_Jun27_02_MC/mc123624.run",
#	      "y1s_Jun27_02_MC/mc123623.run",
#	      "y1s_Jun27_02_MC/mc123611.run",
#	      "y1s_Jun27_02_MC/mc123621.run",

# None of these: the only peak in db22 is a miniscan, and it's redundant anyway
# #	      "y2s_May12_03_MC/mc129572.run",
# #	      "y2s_May12_03_MC/mc129591.run",
# #	      "y2s_May12_03_MC/mc129611.run",
# 	      "y2s_May12_03_MC/mc129575.run",
# 	      "y2s_May12_03_MC/mc129582.run",
# 	      "y2s_May12_03_MC/mc129579.run",
# 	      "y2s_May12_03_MC/mc129617.run",
# 	      "y2s_May12_03_MC/mc129580.run",
# 	      "y2s_May12_03_MC/mc129567.run",
# 	      "y2s_May12_03_MC/mc129576.run",
# 	      "y2s_May12_03_MC/mc129568.run",
# 	      "y2s_May12_03_MC/mc129607.run",
# 	      "y2s_May12_03_MC/mc129574.run",
# 	      "y2s_May12_03_MC/mc129573.run",

	      ) {

    do {
        $qstat = `qstat -u mccann | grep mc1 | wc -l`;
        chop($qstat);

	if ($qstat >= $limit) {
	    print "Waiting $ARGV[0] seconds...\n";
	    sleep $ARGV[0];
	}
    } while ($qstat >= $limit);

    print "Submitting $run.\n";
    system("qsub $run");
}
