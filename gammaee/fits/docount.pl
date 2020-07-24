#!/usr/local/bin/perl

# $run{$r}->[0] is the resonance number (1, 2, 3)
# $run{$r}->[1] is the scan name ("nov29-01"...)
# $run{$r}->[2] is the run type ("peak", "cont", "scan", "high")
# $run{$r}->[3] is the database number (16..27)

require("grand_list.pl");
require("allenergy.pl");
require("allgglumi.pl");
require("alldb.pl");
require("stability/newGoodEvents.pl");
require("stability/bge.pl");
require("stability/bgp.pl");
require("stability/cos.pl");

$which = 1;

sub takepeak {
#     if ($which == 1)    { (4.727 <= $energy{$r} && $energy{$r} <= 4.734  &&  $db{$r} >= 18  &&  $db{$r} <= 19); }
    if ($which == 1)    { (4.7275 < $energy{$r} && $energy{$r} < 4.7325  &&  $db{$r} >= 18  &&  $db{$r} <= 19); }
    elsif ($which == 2) { (5.010 <= $energy{$r} && $energy{$r} <= 5.015  &&  $db{$r} >= 21  &&  $db{$r} <= 23); }
    else                { (5.175 <= $energy{$r} && $energy{$r} <= 5.183  &&  ($db{$r} >= 16  &&  $db{$r} <= 17)); }
}

sub takecont {
    if ($which == 1)    { ($run{$r}->[0] == 1  &&  $run{$r}->[2] eq "cont"  &&  $db{$r} >= 18  &&  $db{$r} <= 19); }
    elsif ($which == 2) { ($run{$r}->[0] == 2  &&  $run{$r}->[2] eq "cont"  &&  $db{$r} >= 21  &&  $db{$r} <= 23); }
    else                { ($run{$r}->[0] == 3  &&  $run{$r}->[2] eq "cont"  &&  ($db{$r} >= 16  &&  $db{$r} <= 17)); }
}

if ($which == 1)    { $eff = 0.9788; $efferr = 0.01214; }
elsif ($which == 2) { $eff = 0.9497; $efferr = 0.01604; }
else                { $eff = 0.9637; $efferr = 0.01556; }

if ($which == 1)    { $bmm = 0.0249; $bmmerr = 0.00073; }
elsif ($which == 2) { $bmm = 0.0203; $bmmerr = 0.00085; }
else                { $bmm = 0.0239; $bmmerr = 0.00122; }

if ($which == 1)    { $pll = 0.2123; $pllerr = 0.00374; }
elsif ($which == 2) { $pll = 0.2146; $pllerr = 0.00453; }
else                { $pll = 0.1778; $pllerr = 0.00530; }

$allfac = 1./(3. * $bmm * $pll + (1. - 3. * $bmm) * $eff);

$allfacerr2 = (&sqr($bmmerr) * &sqr(3. * $eff - 3. * $pll) +
	       &sqr($pllerr) * &sqr(3. * $bmm) +
	       &sqr($efferr) * &sqr(3. * $bmm - 1.))
    / &sqr(&sqr(3. * $bmm * $pll + (1. - 3. * $bmm) * $eff));

$hadfac = (1. - 3. * $bmm)/(3. * $bmm * $pll + (1. - 3. * $bmm) * $eff);

$hadfacerr2 = (&sqr($bmmerr) * &sqr(3. * $pll) + 
	       &sqr($pllerr) * &sqr(3. * $bmm * (1. - 3. * $bmm)) +
	       &sqr($efferr) * &sqr(&sqr(1. - 3. * $bmm)))
    / &sqr(&sqr(3. * $bmm * $pll + (1. - 3. * $bmm) * $eff));

$cn = 0;
$cl = 0;
$clerr2 = 0;
$cenergy = 0;
$cpoints = 0;
$cbge = 0;
$cbgp = 0;
$ccos = 0;
foreach $r (keys %energy) {
    next if !&takecont();

    $cn += $newGoodEvents{$r};
    $cl += $lumi{$r};
    $clerr2 += $lumistat{$r}*$lumistat{$r};

    $cenergy += $energy{$r};
    $cpoints++;

    $cbge += $bge{$r};
    $cbgp += $bgp{$r};
    $ccos += $cos{$r};
}
$realcn = $cn - 52./14.*$cbge - 21./9.*$cbgp - 253./1933.*$ccos;
$realcnerr2 = $cn + &sqr( 52./  14.*$cbge)*(1./$cbge + 0.6245)
                  + &sqr( 21./   9.*$cbgp)*(1./$cbgp + 0.3930);
                  + &sqr(253./1933.*$ccos)*(1./$ccos + 0.004470);
$cenergy = $cenergy / $cpoints;

print "raw cont count: $cn with ".($cl/1000./1000.)." +- ".(sqrt($clerr2)/1000./1000.)." fb^-1 at $cenergy GeV\n";
print "backgrounds: $cbge, $cbgp, $ccos\n";
print "&sqr( 52./  14.*$cbge)*(1./$cbge + 0.6245) = ".&sqr( 52./  14.*$cbge)*(1./$cbge + 0.6245)."\n";
print "&sqr( 21./   9.*$cbgp)*(1./$cbgp + 0.3930) = ".&sqr( 21./   9.*$cbgp)*(1./$cbgp + 0.3930)."\n";
print "&sqr(253./1933.*$ccos)*(1./$ccos + 0.004470) = ".&sqr(253./1933.*$ccos)*(1./$ccos + 0.004470)."\n";
print "cont background errors are ".sqrt($realcnerr2 - $cn)."\n";

$pn = 0;
$pl = 0;
$plerr2 = 0;
$penergy = 0;
$ppoints = 0;
$pbge = 0;
$pbgp = 0;
$pcos = 0;
foreach $r (keys %energy) {
    next if !&takepeak();

    $pn += $newGoodEvents{$r};
    $pl += $lumi{$r};
    $plerr2 += $lumistat{$r}*$lumistat{$r};

    $penergy += $energy{$r};
    $ppoints++;

    $pbge += $bge{$r};
    $pbgp += $bgp{$r};
    $pcos += $cos{$r};
}
$realpn = $pn - 52./14.*$pbge - 21./9.*$pbgp - 253./1933.*$pcos;
$realpnerr2 = $pn + &sqr( 52./  14.*$pbge)*(1./$pbge + 0.6245)
                  + &sqr( 21./   9.*$pbgp)*(1./$pbgp + 0.3930);
                  + &sqr(253./1933.*$pcos)*(1./$pcos + 0.004470);
$penergy = $penergy / $ppoints;

print "raw peak count: $pn with ".($pl/1000./1000.)." +- ".(sqrt($plerr2)/1000./1000.)." fb^-1 at $penergy GeV\n";
print "backgrounds: $pbge, $pbgp, $pcos\n";
print "peak background errors are ".sqrt($realpnerr2 - $pn)."\n";

$excess = $realpn - (($pl * &sqr($cenergy) / $cl / &sqr($penergy)) * $realcn);

$eerr2 = $realpnerr2 + (&sqr(($pl * &sqr($cenergy) / $cl / &sqr($penergy)) * $realcn) *
			($plerr2/&sqr($pl) + $clerr2/&sqr($cl) + $realcnerr2/&sqr($realcn)));

print "Excess is $excess +/- ".sqrt($eerr2)."\n";

$hads = $excess * $hadfac;
$hadserr2 = &sqr($hads) * ($eerr2/&sqr($excess) + $hadfacerr2 / &sqr($hadfac));
print "hadfac is $hadfac +/- ".sqrt($hadfacerr2)."\n";
print "number of ups($which\S) -> hadrons is ".($hads/1000000.)." +/- ".(sqrt($hadserr2)/1000000.)." million\n";

$alls = $excess * $allfac;
$allserr2 = &sqr($alls) * ($eerr2/&sqr($excess) + $allfacerr2 / &sqr($allfac));
print "allfac is $allfac +/- ".sqrt($allfacerr2)."\n";
print "number of ups($which\S) -> anything is ".($alls/1000000.)." +/- ".(sqrt($allserr2)/1000000.)." million\n";








sub sqr {$_[0] * $_[0]}
