#!/usr/local/bin/perl

# died in trigger_only! 122091
# died! 122133
# # 122430
# died in trigger_only! 122832
# # 123817
# died! 123853
# died! 124684
# died in trigger_only! 125176
# # 126488
# # 126870
# 129572 STILL RUNNING
# # 130427
# # 121969 error messages!
# # 122634
# # 122808
# # 123013
# # 123592
# # 123638
# 124708 STILL RUNNING
# constants loading problem! 126521
# constants loading problem! 126531
# constants loading problem! 126906
# constants loading problem! 127318
# constants loading problem! 127418
# constants loading problem! 127955
# constants loading problem! 129674
# constants loading problem! 129850
# constants loading problem! 130268
# constants loading problem! 130316

foreach $run (

 	      122091,
 	      122133,
# 	      122430,
 	      122832,
# 	      123817,
 	      123853,
 	      124684,
 	      125176,
# 	      126488,
# 	      126870,
# 	      129572,
# 	      130427,

# 	      121969,
# 	      122634,
# 	      122808,
# 	      123013,
# 	      123592,
# 	      123638,
# 	      124708,
 	      126521,
 	      126531,
 	      126906,
 	      127318,
 	      127418,
 	      127955,
 	      129674,

 	      129850,
 	      130268,
 	      130316,

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
