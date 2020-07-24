#!/usr/local/bin/perl

foreach $res (1, 2, 3) {
    foreach $type ("scan", "peak", "cont") {
	if ($type eq "scan") {
	    if ($res == 1) {
		@runs = (124102, 123167, 123606, 123601, 124969,
			 124450, 124971, 123598, 125261, 125294,
			 124296, 125293, 124281, 124963, 123786,
			 124327, 125311, 124091, 124289, 125309,
			 124081, 124291, 124107, 123790, 124110,
			 124633, 123166, 123600, 123607, 125120,
			 124294, 125291, 125121, 125290, 124629,
			 124973, 125310, 123172, 124112, 125255,
			 123175, 125256, 125260, 123169, 124449,
			 125307, 124445, 123178, 124282, 123596,
			 123782, 123603, 125119, 123170, 125295,
			 124106, 124084, 124641, 125127, 125254,
			 124961, 123608, 124970, 125125, 125126,
			 123787, 124960, 124087, 123164, 124086,
			 123168, 124640, 124967, 125259, 123792,
			 125122, 124089, 124639, 123602, 124109,
			 124972, 124448, 123176, 124444, 125285,
			 125287, 124625, 125286, 124632, 124085,
			 123783, 124452, 124968, 123784, 123604,
			 124630, 124962, 123165, 125257, 123781,
			 124626, 123597, 124103, 124290, 124293,
			 124080, 123599, 124111, 125262, 124440,
			 124966, 123789, 124437, 125305, 124436, );
	    }
	    elsif ($res == 2) {
		@runs = (126465, 127613, 127600, 126454, 126434,
			 127598, 127606, 126451, 126467, 126783,
			 127925, 128314, 127924, 127615, 127602,
			 126429, 127214, 126777, 127958, 126824,
			 126461, 126436, 128303, 126778, 126449,
			 126821, 127928, 126435, 128312, 128313,
			 126780, 127932, 127962, 127959, 128307,
			 127215, 126431, 126460, 127612, 126453,
			 128315, 126782, 127601, 128306, 126817,
			 127594, 126433, 126776, 127206, 126815,
			 127963, 127219, 128316, 127218, 126779,
			 127927, 128309, 126814, 126823, 126432,
			 127213, 126825, 128310, 127611, 128305,
			 127217, 126464, 127961, 127588, 127931,
			 127589, 126462, 127610, 127592, 127933,
			 126469, );
	    }
	    elsif ($res == 3) {
		@runs = (122572, 122412, 122557, 122781, 122563,
			 122568, 122993, 122999, 122252, 122575,
			 123004, 122253, 122562, 122249, 122069,
			 122768, 122773, 122780, 122256, 122571,
			 122415, 121897, 122556, 122555, 122073,
			 122560, 122066, 121889, 122070, 122573,
			 122410, 122559, 122564, 122574, 121892,
			 122998, 122772, 122416, 122409, 122996,
			 122537, 122246, 123003, 122770, 122247,
			 122251, 122245, 122071, 122545, 122538,
			 122551, 122767, 123001, 122769, 122766,
			 122570, 122995, 122064, 121898, 123002,
			 122072, 122411, 122548, 122074, 122536,
			 122569, 122413, 122542, 122077, 122777,
			 122076, 122541, 121890, 122414, 122550,
			 122779, 121887, 122776, 122549, 122778,
			 122539, 122540, );
	    }
	}
	elsif ($type eq "peak") {
	    if ($res == 1) {
		@runs = (125327, 124363, 123872, 124150, 123993,
			 123852, 124706, 123656, 123823, 124016,
			 125226, 125153, 125198, 123826, 125357,
			 124690, 123198, 124377, 123829, 124674,
			 124142, 123997, 124505, 124711, 124194,
			 124484, 123984, 124516, 125362, 123617,
			 125183, 124515, 124517, 125214, 123994,
			 124349, 125348, 124346, 124527, 123963,
			 124360, 125366, 125343, 124171, 124486,
			 124852, 123969, 123618, 124510, 125337, );
	    }
	    elsif ($res == 2) {
		@runs = (129551, 129580, 127268, 126556, 126893,
			 126541, 127320, 127264, 127279, 127262,
			 129649, 127273, 129591, 126579, 129651,
			 126871, 126566, 129637, 127315, 126831,
			 126907, 129552, 127285, 127261, 126868,
			 127321, 129541, 126559, 126858, 126513,
			 129572, 126879, 126540, 126532, 126877,
			 129611, 127280, 129644, 129574, 129638,
			 127269, 127319, 127307, 129566, 126557,
			 126859, 127330, 127322, 129630, 129619, );
	    }
	    elsif ($res == 3) {
		@runs = (123040, 122300, 122631, 123065, 122307,
			 122462, 121953, 122610, 121952, 122649,
			 122323, 122461, 122855, 122844, 122312,
			 122305, 122136, 122812, 122619, 121916,
			 122653, 123063, 122464, 122133, 122825,
			 121950, 123035, 122277, 122313, 122274,
			 123038, 122141, 122830, 123056, 123059,
			 122628, 121973, 122661, 122615, 121925,
			 123039, 122647, 122650, 122291, 122667,
			 122648, 122292, 122276, 122652, 122860, );
	    }
	}
	elsif ($type eq "cont") {
	    if ($res == 1) {
		@runs = (123813, 123956, 123380, 123774, 124302,
			 124820, 124644, 123815, 124667, 124456,
			 123812, 123960, 124322, 123820, 124121,
			 125178, 123794, 123959, 124658, 125176,
			 124140, 125315, 123814, 124128, 124113,
			 124314, 124809, 123955, 124139, 124464,
			 124123, 124126, 123811, 124324, 124650,
			 123566, 124115, 123944, 123369, 125169,
			 123939, 123941, 123958, 124475, 124814,
			 123569, 123816, 124117, 124665, 124309, );
	    }
	    elsif ($res == 2) {
		@runs = (129071, 129857, 127663, 127631, 127673,
			 127712, 127626, 126483, 127625, 129522,
			 129692, 126853, 126477, 127692, 126260,
			 129845, 127442, 126255, 127659, 129529,
			 127645, 127643, 127646, 129712, 126855,
			 126480, 126666, 126839, 129673, 129524,
			 127723, 129681, 126856, 126476, 126263,
			 129728, 126490, 127703, 129685, 126494,
			 126653, 129711, 129724, 127701, 127684,
			 127417, 127677, 127651, 129519, 126479, );
	    }
	    elsif ($res == 3) {
		@runs = (122787, 121901, 122603, 122803, 122269,
			 122800, 122091, 121914, 122272, 122587,
			 122430, 121899, 122432, 121904, 122605,
			 122083, 122418, 122804, 122424, 122429,
			 122596, 122797, 122798, 122789, 123016,
			 122080, 122606, 121905, 122427, 123014,
			 122422, 122585, 122586, 123019, 121915,
			 122594, 122423, 122805, 122433, 122426,
			 122081, 122085, 122796, 121906, 122599,
			 122434, 122810, 122602, 123013, 122799, );
	    }
	}

	foreach $run (@runs) {
	    if ($run >= 121339  &&  $run <= 122179) {$db = 16;}
	    if ($run >= 122245  &&  $run <= 123304) {$db = 17;}
	    if ($run >= 123314  &&  $run <= 124575) {$db = 18;}
	    if ($run >= 124624  &&  $run <= 125416) {$db = 19;}
	    if ($run >= 125428  &&  $run <= 126206) {$db = 20;}
	    if ($run >= 126252  &&  $run <= 127545) {$db = 21;}
	    if ($run >= 127550  &&  $run <= 128401) {$db = 22;}
	    if ($run >= 128684  &&  $run <= 129223) {$db = 23;}
	    if ($run >= 129257  &&  $run <= 129488) {$db = 24;}
	    if ($run >= 129519  &&  $run <= 129865) {$db = 25;}
	    if ($run >= 129897  &&  $run <= 130187) {$db = 26;}
	    if ($run >= 130198  &&  $run <= 130630) {$db = 27;}
	    if ($run >= 130676  &&  $run <= 131640) {$db = 28;}
	    if ($run >= 131679  &&  $run <= 132285) {$db = 29;}
	    if ($run >= 200520  &&  $run <= 200854) {$db = 30;}
	    if ($run >= 200978  &&  $run <= 202101) {$db = 31;}
	    if ($run >= 202126  &&  $run <= 203089) {$db = 32;}
	    if ($run >= 203104  &&  $run <= 203634) {$db = 33;}
	    if ($run >= 203912  &&  $run <= 204348) {$db = 34;}

	    open(RUN, "> $type$res/r$run.run");
	    print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/$type$res\_$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/acceptance/run2/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_DB=$db
export USER_RUN=$run
export USER_DIR=$type$res

suez -f make_index.tcl
rm -f core
";
            close(RUN);
} # run
} # type
} # res
