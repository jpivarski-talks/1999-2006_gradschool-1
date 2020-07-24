#!/usr/local/bin/perl

foreach $run (123610, 123611, 123612,                   121916, 121917, 121918,
	      123615, 123616, 123617,			121920, 121924, 121925,
	      123618, 123619, 123620,			121927, 121928, 121929,
	      123621, 123623, 123624,			121930, 121932, 121933,
	      123631, 123632, 123633,			121936, 121939, 121940,
	      123635, 123636, 123637,			121943, 121944, 121946,
	      123638, 123639, 123640,			121948, 121949, 121950,
	      123641, 123643, 123644,			121951, 121952, 121953,
	      123645, 123646, 123647,			121962, 121963, 121965,
	      123648, 123650, 123651,			121966, 121968, 121969,
	      123652, 123653, 123654,			121970, 121972, 121973,
	      123656, 123658, 123659,			121974, 121975, 121976,
	      123665, 123670, 123673,			121985, 121986, 121987,
	      123674, 123675, 123678,			121989, 121992, 121993,
	      123679, 123683, 123685,			121995, 121996, 121999,
	      123686, 123691, 123692,			122001, 122003, 122006,
	      123693, 123695, 123697,
	      123698, 123699, 123700,
	      123705, 123706                                                      ) {

# foreach $run (129535, 129536, 129538, 129539, 129540, 129541, 129545,
# 	      129549, 129550, 129551, 129552, 129553, 129564, 129566,
# 	      129567, 129568, 129572, 129573, 129574, 129575, 129576,
# 	      129579, 129580, 129582, 129591, 129607, 129611, 129617,
# 	      129618, 129619, 129620, 129623, 129626, 129629, 129630,
# 	      129631, 129632, 129633, 129635, 129637, 129638, 129641,
# 	      129643, 129644, 129645, 129646, 129648, 129649, 129651,
# 	      129652, 129653, 129655, 129656, 129659, 129660, 129731,
# 	      129732, 129733, 129734, 129737, 129738, 129739, 129740,
# 	      129741, 129742, 129743, 129752, 129753, 129754, 129756,
# 	      129757, 129758, 129760, 129761, 129762, 129763, 129764,
# 	      129768, 129769, 129771, 129772, 129773, 129774, 129775,
# 	      129778, 129780, 129781, 129783, 129784, 129786, 129787,
# 	      129788, 129789, 129790, 129791, 129792, 129795, 129796,
# 	      129797, 129798, 129799, 129800, 129803, 129804, 129805,
# 	      129806, 129808, 129809, 129811, 129812, 129813, 129814,
# 	      129817, 129818, 129819, 129820, 129824, 129831, 129833,
# 	      129834, 129835, 129836, 129837, 129841) {

    do {
        print "Waiting one minute...\n";
        sleep 60;

        $qstat = `qstat -u mccann | wc -l`;
        chop($qstat);
        $qstat -= 2;

    } while ($qstat >= 22);

    if ($run > 123000) {$dir = "y1s";}
    else {$dir = "y3s";}

    system("qsub $dir/mc$run.run");
}



