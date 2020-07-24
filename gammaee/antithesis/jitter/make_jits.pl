#!/usr/local/bin/perl

foreach $res ("1s", "2s", "3s") {
    foreach $letter ("a", "b", "c", "d", "e", "f", "g") {

	open(FILE, "> j$res\_$letter.run");
	print FILE "#\$ -l arch=lx24-x86
#\$ -o /home/mccann/antithesis/jitter/j$res\_$letter.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/antithesis/
/nfs/cleo3/Offline/rel/20050721_P2/other_sources/python/bin/python2.4 jitter/jitter$res.py
";
	close(FILE);
    }
}
