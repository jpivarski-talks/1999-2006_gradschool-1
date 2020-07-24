#!/usr/local/bin/perl

foreach $run ( 124080, 124081, 124084, 124085, 124086, 124087, 124089,
	       124091, 124092, 124102, 124103, 124106, 124107, 124109,
	       124110, 124111, 124112, 124113, 124114, 124115, 124117,
	       124121, 124123, 124125, 124126,
	       124127, 124128, 124129, 124132, 124134, 124137, 124138,
	       124139, 124140, 124141, 124142, 124144, 124146, 124149,
	       124150, 124152, 124153, 124154, 124155, 124156, 
	       124159, 124162, 124165, 124166, 124167, 124170,
	       124171, 124172, 124173, 124174, 124175, 124176, 124177,
	       124178, 124179, 124181, 124185, 124186, 124188, 124190,
	       124192, 124193, 124194 ) {
    open(RUN, "> r$run.run");
    
    print RUN "#\$ -l calibration
#\$ -o /cdat/tem/mccann/r$run.out
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/super_hadrons/run/feb20-02
. /nfs/cleo3/scripts/cleo3defs
c3rel Jan24_03_P2

USER_RUN=$run
export USER_RUN

suez -f count.tcl > /cdat/tem/mccann/r$run.log

perl final_count.pl $run /cdat/tem/mccann/r$run.log > r$run.txt
";

}
