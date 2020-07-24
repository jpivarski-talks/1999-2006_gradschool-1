#!/usr/local/bin/perl

require("grand_list.pl");
require("gglumi.pl");
require("energy.pl");

# $i = 0;
# $j = 0;
$lum = 0;
$en = 0;
$n = 0;
foreach $r (sort numly keys %run) {
    next if ($run{$r}->[0] != 1);
    next if ($run{$r}->[2] ne "peak");
    next if ($r > 124020);

    $lum += $lumi{$r};
    $en += $energy{$r};
    $n++;
    
#     print "\nhmerge dafedir/early".(++$j).".rzn" if ($i == 0);
#     print " dafedir/plots$r.rzn";
#     $i = 0 if (++$i > 15);
}
# print "\nhmerge dafedir/early.rzn";
# foreach $i (1..$j) {
#     print " dafedir/early$i.rzn";
# }
# print "\n\n";
print "early $lum\n";

# $i = 0;
# $j = 0;
$lum = 0;
foreach $r (sort numly keys %run) {
    next if ($run{$r}->[0] != 1);
    next if ($run{$r}->[2] ne "peak");
    next if ($r <= 124020);
    
    $lum += $lumi{$r};
    $en += $energy{$r};
    $n++;
    
#     print "\nhmerge dafedir/late".(++$j).".rzn" if ($i == 0);
#     print " dafedir/plots$r.rzn";
#     $i = 0 if (++$i > 15);
}
# print "\nhmerge dafedir/late.rzn";
# foreach $i (1..$j) {
#     print " dafedir/late$i.rzn";
# }
# print "\n\n";
print "late $lum\n";

$peake = $en / $n;
print "peake = $peake\n";

# $i = 0;
# $j = 0;
$lum = 0;
$en = 0;
$n = 0;
foreach $r (sort numly keys %run) {
    next if ($run{$r}->[0] != 1);
    next if ($run{$r}->[2] ne "cont");
    
    $lum += $lumi{$r};
    $en += $energy{$r};
    $n++;
    
#     print "\nhmerge dafedir/cont".(++$j).".rzn" if ($i == 0);
#     print " dafedir/plots$r.rzn";
#     $i = 0 if (++$i > 15);
}
# print "\nhmerge dafedir/cont.rzn";
# foreach $i (1..$j) {
#     print " dafedir/cont$i.rzn";
# }
# print "\n\n";
$conte = $en / $n;
print "conte = $conte\n";
print "cont $lum --> ".($lum * $conte * $conte / $peake / $peake)."\n";

# print "h/file 1 dafedir/early.rzn\n";
# print "h/file 2 dafedir/late.rzn\n";
# print "h/file 3 dafedir/cont.rzn\n";
