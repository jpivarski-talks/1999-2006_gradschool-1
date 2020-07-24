#!/usr/local/bin/perl

%numberOfEvents = ();
%numberOfEventsStat = ();
%numberOfEventsSyst = ();
%luminosity = ();
%luminosityStat = ();
%luminositySyst = ();
%energy = ();

@y1s = ();
@y2s = ();
@y3s = ();
%skip = ();
&fill_runnumbers();

sub sqr { $_[0] * $_[0]; }

open(COLLECTION, "/home/mccann/super_hadrons/allcleo3/dafedir/collection.dat");
while (my $line = <COLLECTION>) {
    chop($line);
    my ($run,
	$passed,
	$beamgas, $bgstat, $bgsyst,
	$cosmics, $cstat, $csyst)
	= split("\t", $line);
    $numberOfEvents{$run} = $passed - $beamgas - $cosmics;
    $numberOfEventsStat{$run} = sqrt($passed + &sqr($bgstat) + &sqr($cstat));
    $numberOfEventsSyst{$run} = $bgsyst + $csyst;
}
close(COLLECTION);

open(RUNINFO, "/nfs/cleo3/Offline/InfoFiles/data/runinfo.runinfo");
while (my $line = <RUNINFO>) {
    chop($line);
    my ($run,
	$evts, $had, $last,
	$bhalum, $bbstat, $bbsyst,
	$e_cor, $e_uncor,
	$b_cor, $b_uncor,
	$gglum, $ggstat, $ggsyst,
	$db)
	= split(/\s+/, substr($line, 2));
    $luminosity{$run} = $gglum;
    $luminosityStat{$run} = $ggstat;
    $luminositySyst{$run} = $ggsyst;
    $energy{$run} = $e_cor;
}
close(RUNINFO);

# $lumi = 0;
# foreach my $run ( @y3s ) {
#     if ( defined($numberOfEvents{$run})  &&
#  	 defined($luminosity{$run})      &&
#  	 ! defined($skip{$run})             ) {
# 	$lumi += $luminosity{$run};
#     }
# }
# $lumi /= 1000.;
# $lumi /= 1000.;
# print "$lumi\n";

# while (my $run = <STDIN>) {
#     chop($run);
#     if ( defined($numberOfEvents{$run})  &&
# 	 defined($luminosity{$run})      &&
# 	 ! defined($skip{$run})             ) {

# 	my $en = 2000. * $energy{$run};
# 	my $hxs = ($numberOfEvents{$run} + 0.*$numberOfEventsSyst{$run}) / $luminosity{$run};
# 	my $hxs_err = $hxs * sqrt(&sqr($numberOfEventsStat{$run}/$numberOfEvents{$run}) +
# 				  &sqr($luminosityStat{$run}/$luminosity{$run})           );

# 	print "$en\t$hxs\t$hxs_err\n";
#     }
# }

sub fill_runnumbers {
    @y1s = (123164, 123165, 123166, 123167, 123168, 123169, 123170,
	    123175, 123176, 123178, 123193, 123196, 123197, 123198,
	    123200, 123201, 123202, 123369, 123370, 123378, 123379,
	    123380, 123382, 123565, 123566, 123567, 123568, 123569,
	    123570, 123591, 123592, 123596, 123597, 123598, 123599,
	    123600, 123601, 123602, 123603, 123604, 123606, 123607,
	    123608, 123610, 123611, 123612, 123615, 123616, 123617,
	    123618, 123619, 123620, 123621, 123623, 123624, 123631,
	    123632, 123633, 123635, 123636, 123637, 123638, 123639,
	    123640, 123641, 123643, 123644, 123645, 123646, 123647,
	    123648, 123650, 123651, 123652, 123653, 123654, 123655,
	    123656, 123658, 123659, 123767, 123768, 123771, 123772,
	    123773, 123774, 123775, 123781, 123782, 123783, 123784,
	    123786, 123787, 123789, 123790, 123792, 123793, 123794,
	    123796, 123799, 123800, 123803, 123804, 123805, 123809,
	    123810, 123811, 123812, 123813, 123814, 123815, 123816,
	    123817, 123818, 123820, 123821, 123822, 123823, 123826,
	    123829, 123830, 123831, 123833, 123836, 123837, 123839,
	    123840, 123841, 123842, 123843, 123844, 123845, 123847,
	    123848, 123849, 123850, 123851, 123852, 123853, 123858,
	    123859, 123860, 123862, 123863, 123864, 123865, 123866,
	    123867, 123868, 123869, 123871, 123872, 123873, 124080,
	    124081, 124084, 124085, 124086, 124087, 124089, 124091,
	    124092, 124102, 124103, 124106, 124107, 124109, 124110,
	    124111, 124112, 124113, 124114, 124115, 124117, 124118,
	    124119, 124121, 124122, 124123, 124125, 124126, 124127,
	    124128, 124129, 124132, 124134, 124137, 124138, 124139,
	    124140, 124141, 124142, 124144, 124146, 124149, 124150,
	    124152, 124153, 124154, 124155, 124156, 124158, 124159,
	    124162, 124164, 124165, 124166, 124167, 124170, 124171,
	    124172, 124173, 124174, 124175, 124176, 124177, 124178,
	    124179, 124181, 124185, 124186, 124188, 124190, 124192,
	    124193, 124194, 124281, 124282, 124286, 124289, 124290,
	    124291, 124293, 124294, 124296, 124299, 124300, 124301,
	    124302, 124305, 124309, 124311, 124312, 124313, 124314,
	    124315, 124318, 124319, 124321, 124322, 124323, 124324,
	    124326, 124327, 124328, 124329, 124333, 124334, 124335,
	    124336, 124337, 124338, 124339, 124341, 124343, 124344,
	    124346, 124347, 124348, 124349, 124350, 124351, 124352,
	    124353, 124354, 124357, 124359, 124360, 124361, 124363,
	    124364, 124365, 124368, 124369, 124372, 124373, 124374,
	    124375, 124376, 124436, 124437, 124440, 124444, 124445,
	    124448, 124449, 124450, 124452, 124454, 124456, 124458,
	    124459, 124462, 124464, 124465, 124466, 124467, 124469,
	    124472, 124473, 124474, 124475, 124477, 124479, 124480,
	    124481, 124484, 124486, 124487, 124490, 124491, 124492,
	    124493, 124495, 124496, 124497, 124498, 124499, 124500,
	    124502, 124505, 124506, 124507, 124508, 124509, 124510,
	    124513, 124515, 124516, 124517, 124518, 124519, 124522,
	    124523, 124524, 124525, 124526, 124527, 124625, 124626,
	    124629, 124630, 124632, 124633, 124639, 124640, 124641,
	    124644, 124645, 124647, 124648, 124650, 124651, 124652,
	    124653, 124655, 124657, 124658, 124659, 124660, 124663,
	    124665, 124666, 124667, 124668, 124671, 124672, 124673,
	    124674, 124675, 124676, 124677, 124678, 124679, 124680,
	    124681, 124683, 124684, 124685, 124687, 124688, 124690,
	    124691, 124695, 124699, 124701, 124702, 124704, 124705,
	    124706, 124707, 124708, 124709, 124712, 124713, 124714,
	    124716, 124718, 124719, 125119, 125120, 125121, 125122,
	    125124, 125125, 125126, 125127, 125149, 125151, 125153,
	    125154, 125155, 125158, 125159, 125161, 125162, 125163,
	    125166, 125167, 125168, 125169, 125170, 125171, 125175,
	    125176, 125177, 125178, 125179, 125183, 125184, 125187,
	    125188, 125189, 125190, 125191, 125192, 125193, 125194,
	    125197, 125198, 125199, 125200, 125202, 125205, 125206,
	    125207, 125208, 125209, 125212, 125213, 125214, 125215,
	    125217, 125219, 125220, 125222, 125223, 125224, 125225,
	    125226, 125227, 125254, 125255, 125256, 125257, 125259,
	    125260, 125261, 125262, 125264, 125285, 125286, 125287,
	    125288, 125290, 125291, 125292, 125293, 125294, 125295,
	    125297, 125303, 125305, 125307, 125309, 125310, 125311,
	    125312, 125315, 125316, 125317, 125318, 125323, 125325,
	    125326, 125327, 125329, 125331, 125335, 125337, 125338,
	    125339, 125340, 125343, 125344, 125345, 125346, 125347,
	    125348, 125351, 125352, 125353, 125354, 125357, 125358,
	    125360, 125361, 125362, 125363, 125364, 125366, 125367,
	    125368, 125369, 125370);
    @y2s = (126252, 126253, 126254, 126255, 126256, 126257, 126258,
	    126259, 126260, 126262, 126263, 126265, 126266, 126267,
	    126268, 126273, 126274, 126422, 126424, 126428, 126429,
	    126431, 126432, 126433, 126434, 126435, 126436, 126449,
	    126451, 126453, 126454, 126457, 126458, 126460, 126461,
	    126462, 126464, 126465, 126467, 126469, 126496, 126499,
	    126500, 126503, 126505, 126506, 126507, 126508, 126509,
	    126510, 126511, 126513, 126514, 126520, 126521, 126525,
	    126527, 126528, 126531, 126532, 126535, 126536, 126540,
	    126541, 126542, 126546, 126552, 126554, 126555, 126556,
	    126557, 126559, 126562, 126563, 126564, 126649, 126650,
	    126651, 126652, 126653, 126656, 126657, 126658, 126662,
	    126664, 126665, 126666, 126667, 126668, 126669, 126670,
	    126673, 126776, 126777, 126778, 126779, 126780, 126782,
	    126783, 126814, 126815, 126817, 126821, 126823, 126824,
	    126825, 126831, 126832, 126834, 126835, 126836, 126837,
	    126838, 126839, 126842, 126845, 126846, 126847, 126851,
	    126853, 126854, 126855, 126856, 126858, 126859, 126862,
	    126866, 126868, 126869, 126870, 126871, 126874, 126875,
	    126877, 126878, 126879, 126880, 126881, 126882, 126883,
	    126890, 126892, 126893, 126894, 126895, 126906, 126907,
	    126909, 126911, 126912, 126914, 126915, 127588, 127589,
	    127592, 127594, 127598, 127600, 127601, 127602, 127606,
	    127610, 127611, 127612, 127613, 127615, 127619, 127620,
	    127621, 127622, 127623, 127625, 127626, 127627, 127628,
	    127630, 127631, 127632, 127635, 127637, 127638, 127641,
	    127642, 127643, 127644, 127645, 127646, 127647, 127650,
	    127651, 127652, 127654, 127656, 127657, 127659, 127661,
	    127662, 127663, 127667, 127668, 127670, 127672, 127673,
	    127677, 127678, 127680, 127681, 127682, 127683, 127684,
	    127685, 127688, 127690, 127692, 127693, 127694, 127695,
	    127698, 127700, 127701, 127702, 127703, 127710, 127712,
	    127715, 127719, 127720, 127721, 127722, 127723, 127924,
	    127925, 127927, 127928, 127930, 127931, 127932, 127933,
	    127950, 127951, 127955, 127956, 127957, 127958, 127959,
	    127961, 127962, 12796);
    @y3s = (121887, 121889, 121890, 121891, 121892, 121895, 121897,
	    121898, 121899, 121901, 121902, 121903, 121904, 121905,
	    121906, 121909, 121911, 121912, 121914, 121915, 121916,
	    121917, 121918, 121920, 121924, 121925, 121927, 121928,
	    121929, 121930, 121932, 121933, 121935, 121936, 121939,
	    121940, 121943, 121944, 121946, 121948, 121949, 121950,
	    121951, 121952, 121953, 121956, 121961, 121962, 121963,
	    121965, 121966, 121968, 121969, 121970, 121972, 121973,
	    121974, 122063, 122064, 122066, 122069, 122070, 122071,
	    122072, 122073, 122074, 122076, 122077, 122079, 122080,
	    122081, 122083, 122085, 122090, 122091, 122092, 122093,
	    122094, 122097, 122098, 122099, 122100, 122101, 122102,
	    122104, 122105, 122108, 122109, 122117, 122123, 122124,
	    122125, 122126, 122127, 122128, 122129, 122132, 122133,
	    122134, 122136, 122137, 122138, 122139, 122141, 122142,
	    122143, 122145, 122146, 122147, 122245, 122246, 122247,
	    122249, 122251, 122252, 122253, 122256, 122263, 122264,
	    122268, 122269, 122272, 122273, 122274, 122275, 122276,
	    122277, 122278, 122279, 122280, 122281, 122283, 122285,
	    122286, 122287, 122288, 122289, 122291, 122292, 122293,
	    122296, 122297, 122298, 122300, 122301, 122305, 122306,
	    122307, 122309, 122310, 122312, 122313, 122314, 122315,
	    122316, 122317, 122319, 122321, 122322, 122323, 122409,
	    122410, 122411, 122412, 122413, 122414, 122415, 122416,
	    122418, 122420, 122422, 122423, 122424, 122425, 122426,
	    122427, 122428, 122429, 122430, 122432, 122433, 122434,
	    122437, 122439, 122440, 122442, 122443, 122445, 122447,
	    122448, 122450, 122452, 122453, 122454, 122455, 122461,
	    122462, 122464, 122465, 122466, 122467, 122468, 122469,
	    122470, 122471, 122472, 122473, 122476, 122480, 122536,
	    122537, 122538, 122539, 122540, 122541, 122542, 122545,
	    122546, 122548, 122549, 122550, 122551, 122555, 122556,
	    122557, 122559, 122560, 122562, 122563, 122564, 122567,
	    122568, 122569, 122570, 122571, 122572, 122573, 122574,
	    122575, 122576, 122577, 122578, 122579, 122585, 122586,
	    122587, 122590, 122593, 122594, 122595, 122596, 122599,
	    122600, 122602, 122603, 122604, 122605, 122606, 122608,
	    122610, 122613, 122614, 122615, 122616, 122617, 122618,
	    122619, 122620, 122622, 122623, 122625, 122626, 122627,
	    122628, 122629, 122630, 122631, 122632, 122634, 122640,
	    122641, 122642, 122643, 122646, 122647, 122648, 122649,
	    122650, 122653, 122654, 122657, 122658, 122661, 122665,
	    122667, 122668, 122669, 122672, 122673, 122766, 122767,
	    122768, 122769, 122770, 122771, 122772, 122773, 122776,
	    122777, 122778, 122779, 122780, 122781, 122783, 122786,
	    122787, 122789, 122796, 122797, 122798, 122799, 122800,
	    122801, 122802, 122803, 122804, 122805, 122808, 122809,
	    122810, 122812, 122813, 122815, 122816, 122819, 122820,
	    122821, 122823, 122824, 122825, 122826, 122827, 122829,
	    122830, 122831, 122832, 122833, 122835, 122838, 122841,
	    122842, 122843, 122844, 122845, 122846, 122847, 122853,
	    122855, 122856, 122858, 122859, 122860, 122993, 122994,
	    122995, 122996, 122998, 122999, 123001, 123002, 123003,
	    123004, 123010, 123011, 123012, 123013, 123014, 123015,
	    123016, 123018, 123019, 123020, 123021, 123022, 123023,
	    123024, 123025, 123026, 123027, 123028, 123029, 123034,
	    123035, 123036, 123038, 123039, 123040, 123041, 123042,
	    123043, 123044, 123048, 123049, 123050, 123051, 123052,
	    123054, 123055, 123056, 123058, 123059, 123060, 123062,
	    123063, 123065);
    %skip = (109013 => 1, 109032 => 1, 109033 => 1, 109035 => 1,
	     109037 => 1, 109061 => 1, 109065 => 1, 109066 => 1,
	     109166 => 1, 109197 => 1, 109198 => 1, 109199 => 1,
	     109223 => 1, 109248 => 1, 109258 => 1, 109368 => 1,
	     109370 => 1, 109371 => 1, 109372 => 1, 109391 => 1,
	     109421 => 1, 109422 => 1, 109464 => 1, 109590 => 1,
	     109592 => 1, 109598 => 1, 109620 => 1, 109779 => 1,
	     109788 => 1, 109789 => 1, 109961 => 1, 109967 => 1,
	     110038 => 1, 110055 => 1, 110061 => 1, 110092 => 1,
	     110095 => 1, 110097 => 1, 110129 => 1, 110187 => 1,
	     110188 => 1, 110190 => 1, 110197 => 1, 110198 => 1,
	     110202 => 1, 110934 => 1, 110958 => 1, 110977 => 1,
	     111079 => 1, 111189 => 1, 111324 => 1, 111354 => 1,
	     111385 => 1, 111397 => 1, 111411 => 1, 111580 => 1,
	     111655 => 1, 111736 => 1, 111740 => 1, 111741 => 1,
	     111742 => 1, 111744 => 1, 111745 => 1, 111746 => 1,
	     111747 => 1, 111751 => 1, 111771 => 1, 111772 => 1,
	     111779 => 1, 111802 => 1, 111820 => 1, 111825 => 1,
	     111839 => 1, 111841 => 1, 111844 => 1, 111862 => 1,
	     111865 => 1, 111866 => 1, 111879 => 1, 111880 => 1,
	     111894 => 1, 111909 => 1, 111971 => 1, 111999 => 1,
	     112038 => 1, 112044 => 1, 112046 => 1, 112057 => 1,
	     112062 => 1, 112066 => 1, 112071 => 1, 112081 => 1,
	     112110 => 1, 112127 => 1, 112133 => 1, 112134 => 1,
	     112135 => 1, 112137 => 1, 112141 => 1, 112142 => 1,
	     112148 => 1, 112156 => 1, 112214 => 1, 112251 => 1,
	     112280 => 1, 112291 => 1, 112320 => 1, 112324 => 1,
	     112331 => 1, 112346 => 1, 112347 => 1, 112349 => 1,
	     112368 => 1, 112376 => 1, 112386 => 1, 112388 => 1,
	     112401 => 1, 112411 => 1, 112419 => 1, 112430 => 1,
	     112447 => 1, 112451 => 1, 112460 => 1, 112465 => 1,
	     112471 => 1, 112503 => 1, 112505 => 1, 112507 => 1,
	     112508 => 1, 112537 => 1, 112651 => 1, 112692 => 1,
	     112694 => 1, 112770 => 1, 112771 => 1, 112793 => 1,
	     112798 => 1, 112818 => 1, 112832 => 1, 112839 => 1,
	     112847 => 1, 112848 => 1, 112874 => 1, 112976 => 1,
	     113001 => 1, 113003 => 1, 113026 => 1, 113027 => 1,
	     113030 => 1, 113050 => 1, 113064 => 1, 113080 => 1,
	     113112 => 1, 113122 => 1, 113133 => 1, 113146 => 1,
	     113158 => 1, 113193 => 1, 113201 => 1, 113206 => 1,
	     113216 => 1, 113239 => 1, 113240 => 1, 113246 => 1,
	     113249 => 1, 113250 => 1, 113257 => 1, 113266 => 1,
	     113301 => 1, 113308 => 1, 113328 => 1, 113332 => 1,
	     113334 => 1, 113336 => 1, 113342 => 1, 113352 => 1,
	     113354 => 1, 113422 => 1, 113431 => 1, 113434 => 1,
	     113435 => 1, 113436 => 1, 113503 => 1, 113529 => 1,
	     113556 => 1, 113563 => 1, 113642 => 1, 113680 => 1,
	     113684 => 1, 113767 => 1, 113782 => 1, 113824 => 1,
	     113840 => 1, 113982 => 1, 113995 => 1, 114017 => 1,
	     114092 => 1, 114098 => 1, 114136 => 1, 114146 => 1,
	     114147 => 1, 114148 => 1, 114149 => 1, 114150 => 1,
	     114160 => 1, 114208 => 1, 114265 => 1, 114273 => 1,
	     114320 => 1, 114323 => 1, 114331 => 1, 114385 => 1,
	     114413 => 1, 114425 => 1, 114429 => 1, 114475 => 1,
	     114493 => 1, 114520 => 1, 114563 => 1, 114572 => 1,
	     114573 => 1, 114574 => 1, 114575 => 1, 114577 => 1,
	     114581 => 1, 114591 => 1, 114602 => 1, 114604 => 1,
	     114608 => 1, 114612 => 1, 114631 => 1, 114673 => 1,
	     114709 => 1, 114740 => 1, 114742 => 1, 114841 => 1,
	     114843 => 1, 114849 => 1, 114861 => 1, 114862 => 1,
	     114867 => 1, 114889 => 1, 114906 => 1, 114922 => 1,
	     114933 => 1, 115096 => 1, 115097 => 1, 115108 => 1,
	     115110 => 1, 115167 => 1, 115311 => 1, 115323 => 1,
	     115325 => 1, 115330 => 1, 115432 => 1, 115441 => 1,
	     115479 => 1, 115490 => 1, 115496 => 1, 115523 => 1,
	     115546 => 1, 115552 => 1, 115566 => 1, 115598 => 1,
	     115606 => 1, 115612 => 1, 115633 => 1, 115635 => 1,
	     115643 => 1, 115710 => 1, 115725 => 1, 115740 => 1,
	     115801 => 1, 115816 => 1, 115818 => 1, 115854 => 1,
	     115867 => 1, 115892 => 1, 115914 => 1, 115932 => 1,
	     115952 => 1, 115953 => 1, 115975 => 1, 115976 => 1,
	     115982 => 1, 116010 => 1, 116032 => 1, 116038 => 1,
	     116071 => 1, 116079 => 1, 116083 => 1, 116143 => 1,
	     116155 => 1, 116157 => 1, 116165 => 1, 116213 => 1,
	     116220 => 1, 116226 => 1, 116228 => 1, 116245 => 1,
	     116260 => 1, 116288 => 1, 116357 => 1, 116384 => 1,
	     116407 => 1, 116454 => 1, 116467 => 1, 116480 => 1,
	     116512 => 1, 116584 => 1, 116611 => 1, 116662 => 1,
	     116668 => 1, 116675 => 1, 116678 => 1, 116713 => 1,
	     116718 => 1, 116729 => 1, 116743 => 1, 116756 => 1,
	     116759 => 1, 116760 => 1, 116813 => 1, 116862 => 1,
	     116890 => 1, 116911 => 1, 116918 => 1, 116928 => 1,
	     116932 => 1, 116943 => 1, 116961 => 1, 116962 => 1,
	     116963 => 1, 116981 => 1, 116984 => 1, 117013 => 1,
	     117021 => 1, 117028 => 1, 117037 => 1, 117038 => 1,
	     117044 => 1, 117048 => 1, 117061 => 1, 117067 => 1,
	     117071 => 1, 117089 => 1, 117092 => 1, 117093 => 1,
	     117101 => 1, 117102 => 1, 117161 => 1, 117172 => 1,
	     117249 => 1, 117253 => 1, 117300 => 1, 117359 => 1,
	     117410 => 1, 117411 => 1, 117413 => 1, 117414 => 1,
	     117498 => 1, 117524 => 1, 117533 => 1, 117545 => 1,
	     117582 => 1, 117583 => 1, 117611 => 1, 117623 => 1,
	     117624 => 1, 117625 => 1, 117649 => 1, 117723 => 1,
	     117730 => 1, 117733 => 1, 117775 => 1, 117821 => 1,
	     117850 => 1, 117876 => 1, 117877 => 1, 117885 => 1,
	     117953 => 1, 117958 => 1, 117979 => 1, 118020 => 1,
	     118022 => 1, 118030 => 1, 118031 => 1, 118033 => 1,
	     118034 => 1, 118035 => 1, 118036 => 1, 118060 => 1,
	     118086 => 1, 118111 => 1, 118130 => 1, 118131 => 1,
	     118134 => 1, 118150 => 1, 118195 => 1, 118201 => 1,
	     118223 => 1, 118256 => 1, 118259 => 1, 118276 => 1,
	     118294 => 1, 118310 => 1, 118313 => 1, 118319 => 1,
	     118321 => 1, 118325 => 1, 118333 => 1, 118334 => 1,
	     118335 => 1, 118359 => 1, 118364 => 1, 118366 => 1,
	     118387 => 1, 118388 => 1, 118438 => 1, 118445 => 1,
	     118467 => 1, 118525 => 1, 118531 => 1, 118549 => 1,
	     118561 => 1, 118589 => 1, 118652 => 1, 118671 => 1,
	     118676 => 1, 118681 => 1, 118750 => 1, 118794 => 1,
	     118858 => 1, 118867 => 1, 118875 => 1, 118895 => 1,
	     118897 => 1, 118899 => 1, 118915 => 1, 118928 => 1,
	     118971 => 1, 119090 => 1, 119096 => 1, 119100 => 1,
	     119190 => 1, 119231 => 1, 119242 => 1, 119271 => 1,
	     119272 => 1, 119308 => 1, 119310 => 1, 119314 => 1,
	     119388 => 1, 119398 => 1, 119418 => 1, 119428 => 1,
	     119438 => 1, 119446 => 1, 119457 => 1, 119459 => 1,
	     119461 => 1, 119482 => 1, 119483 => 1, 119503 => 1,
	     119544 => 1, 119550 => 1, 119594 => 1, 119598 => 1,
	     119599 => 1, 119620 => 1, 119628 => 1, 119648 => 1,
	     119652 => 1, 119675 => 1, 119677 => 1, 119690 => 1,
	     119695 => 1, 119735 => 1, 119764 => 1, 119797 => 1,
	     119813 => 1, 119826 => 1, 119828 => 1, 119844 => 1,
	     119846 => 1, 119847 => 1, 119868 => 1, 119885 => 1,
	     119905 => 1, 121338 => 1, 121342 => 1, 121355 => 1,
	     121386 => 1, 121388 => 1, 121403 => 1, 121404 => 1,
	     121431 => 1, 121444 => 1, 121447 => 1, 121478 => 1,
	     121518 => 1, 121546 => 1, 121599 => 1, 121605 => 1,
	     121620 => 1, 121632 => 1, 121635 => 1, 121685 => 1,
	     121690 => 1, 121691 => 1, 121695 => 1, 121697 => 1,
	     121740 => 1, 121743 => 1, 121762 => 1, 121777 => 1,
	     121791 => 1, 121797 => 1, 121807 => 1, 121828 => 1,
	     121883 => 1, 121891 => 1, 121909 => 1, 121935 => 1,
	     121956 => 1, 121961 => 1, 121964 => 1, 121981 => 1,
	     121988 => 1, 121991 => 1, 122005 => 1, 122054 => 1,
	     122140 => 1, 122161 => 1, 122227 => 1, 122228 => 1,
	     122231 => 1, 122232 => 1, 122234 => 1, 122235 => 1,
	     122261 => 1, 122316 => 1, 122333 => 1, 122355 => 1,
	     122362 => 1, 122367 => 1, 122441 => 1, 122442 => 1,
	     122451 => 1, 122470 => 1, 122476 => 1, 122481 => 1,
	     122522 => 1, 122523 => 1, 122530 => 1, 122532 => 1,
	     122533 => 1, 122534 => 1, 122546 => 1, 122567 => 1,
	     122578 => 1, 122580 => 1, 122584 => 1, 122595 => 1,
	     122600 => 1, 122622 => 1, 122627 => 1, 122668 => 1,
	     122669 => 1, 122680 => 1, 122709 => 1, 122771 => 1,
	     122836 => 1, 122875 => 1, 122994 => 1, 123010 => 1,
	     123045 => 1, 123064 => 1, 123069 => 1, 123080 => 1,
	     123216 => 1, 123220 => 1, 123221 => 1, 123235 => 1,
	     123254 => 1, 123257 => 1, 123287 => 1, 123291 => 1,
	     123298 => 1);
}