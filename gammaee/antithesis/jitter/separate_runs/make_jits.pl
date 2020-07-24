#!/usr/local/bin/perl

foreach $res ("1s", "2s", "3s") {
#     foreach $degree ("0.01",
# 		     "0.02",
# 		     "0.03",
# 		     "0.04",
# 		     "0.05",
# 		     "0.06",
# 		     "0.08",
# 		     "0.10",
# 		     "0.12",
# 		     "0.14",
# 		     "0.16",
# 		     "0.18",
# 		     "0.20",
# 		     "0.30",
# 		     "0.40",
# 		     "0.50",
# 		     "1.00") {
    foreach $degree (# "0.00",
		     "0.05",
		     "0.07") {

	open(FILE, "> j$res\_$degree.run");
	print FILE "#\$ -l arch=glinux
#\$ -o /home/mccann/antithesis/jitter/j$res\_$degree.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/antithesis/
/nfs/cleo3/Offline/rel/current/other_sources/python/bin/python2.4 jitter/jitter$res.py $degree
";
	close(FILE);
    }
}
