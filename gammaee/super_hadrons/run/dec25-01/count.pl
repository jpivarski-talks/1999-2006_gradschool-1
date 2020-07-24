#!/usr/local/bin/perl

foreach $run ( 122536, 122537, 122538, 122539, 122540, 122541, 122542,
	       122545, 122548, 122549, 122550, 122551, 122555, 122556,
	       122557, 122559, 122560, 122562, 122563, 122564, 
	       122568, 122569, 122570, 122571, 122572, 122573, 122574,
	       122575, 122576, 122577, 122579, 122585, 122586,
	       122587, 122590, 122593, 122594, 122596, 122599,
	       122602, 122603, 122604, 122605, 122606, 122608,
	       122610, 122613, 122614, 122615, 122616, 122618,
	       122619, 122620, 122623, 122625, 122626, 122628, 122629,
	       122631, 122632, 122634, 122640, 122641, 122642, 122643,
	       122646, 122647, 122648, 122649, 122650, 122653, 122654,
	       122657, 122658, 122661, 122665, 122667, 
	       122672, 122673 ) {
    open(RUN, "> r$run.run");
    
    print RUN "#\$ -l calibration
#\$ -o /cdat/tem/mccann/r$run.out
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/super_hadrons/run/dec25-01
. /nfs/cleo3/scripts/cleo3defs
c3rel Jan24_03_P2

USER_RUN=$run
export USER_RUN

suez -f count.tcl > /cdat/tem/mccann/r$run.log

perl final_count.pl $run /cdat/tem/mccann/r$run.log > r$run.txt
";

}