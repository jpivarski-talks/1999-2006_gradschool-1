#!/usr/local/bin/perl

# y1s

foreach $run (123610, 123611, 123612, 123615, 123616, 123617, 123618,
	      123619, 123620, 123621, 123623, 123624, 123631, 123632,
	      123633, 123635, 123636, 123637, 123638, 123639, 123640,
	      123641, 123643, 123644, 123645, 123646, 123647, 123648,
	      123650, 123651, 123652, 123653, 123654, 123656, 123658,
	      123659, 123665, 123670, 123673, 123674, 123675, 123678,
	      123679, 123683, 123685, 123686, 123691, 123692, 123693,
	      123695, 123697, 123698, 123699, 123700, 123705, 123706) {

    open(RUN, "> y1s/mc$run.run");
    print RUN "#\$ -l sigmc=1
#\$ -o /cdat/tem/mccann/mc$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/neweff/data_method/evtgen/y1s
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_RUN=$run
# rm -f /home/mccann/neweff/data_method_rzn/evtgen/y1s/cleog_\$USER_RUN.pds
rm -f /home/mccann/neweff/data_method_rzn/evtgen/y1s/mcpass2_\$USER_RUN.pds

export USER_EBEAM=4.73015
export USER_RES=9.46030
export USER_WIDE=0.0000525
export USER_DIR=y1s
export USER_DEC=ups1s.dec

# suez -f /home/mccann/neweff/data_method/evtgen/cleog.tcl
suez -f /home/mccann/neweff/data_method/evtgen/mcpass2_y1s.tcl
";
    }

# y2s

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
#     open(RUN, "> y2s/mc$run.run");
#     print RUN "#\$ -l sigmc=1
# #\$ -o /cdat/tem/mccann/mc$run.log
# #\$ -S /bin/bash
# #\$ -j y

# cd /home/mccann/neweff/data_method/evtgen/y2s
# . /nfs/cleo3/scripts/cleo3defs
# c3rel Dec10_03

# export USER_RUN=$run
# rm -f ../../../data_method_rzn/evtgen/y2s/cleog_\$USER_RUN.pds
# rm -f ../../../data_method_rzn/evtgen/y2s/mcpass2_\$USER_RUN.pds

# export USER_EBEAM=5.01163
# export USER_RES=10.02326
# export USER_WIDE=0.000044
# export USER_DIR=y2s
# export USER_DEC=ups2s.dec

# # export C3_SHLIB=../../build_legacy/shlib:/nfs/cleo3/Offline/rel/Dec10_03/shlib/SunOS/CC
# suez -f ../cleog.tcl
# suez -f ../mcpass2.tcl
# ";
#     }



# y3s

foreach $run (121916, 121917, 121918, 121920, 121924, 121925, 121927,
	      121928, 121929, 121930, 121932, 121933, 121936, 121939,
	      121940, 121943, 121944, 121946, 121948, 121949, 121950,
	      121951, 121952, 121953, 121962, 121963, 121965, 121966,
	      121968, 121969, 121970, 121972, 121973, 121974, 121975,
	      121976, 121985, 121986, 121987, 121989, 121992, 121993,
	      121995, 121996, 121999, 122001, 122003, 122006) {

    open(RUN, "> y3s/mc$run.run");
    print RUN "#\$ -l sigmc=1
#\$ -o /cdat/tem/mccann/mc$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/neweff/data_method/evtgen/y3s
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_RUN=$run
# rm -f /home/mccann/neweff/data_method_rzn/evtgen/y3s/cleog_\$USER_RUN.pds
rm -f /home/mccann/neweff/data_method_rzn/evtgen/y3s/mcpass2_\$USER_RUN.pds

export USER_EBEAM=5.1776
export USER_RES=10.3552
export USER_WIDE=0.0000263
export USER_DIR=y3s
export USER_DEC=ups3s.dec

# suez -f /home/mccann/neweff/data_method/evtgen/cleog.tcl
suez -f /home/mccann/neweff/data_method/evtgen/mcpass2_y3s.tcl
";
    }
