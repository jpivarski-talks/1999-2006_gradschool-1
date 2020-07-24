#!/usr/local/bin/perl

require("grand_list.pl");
require("stability/newGoodEvents.pl");
require("allgglumi.pl");
require("allenergy.pl");

# perl -e 'require("grand_list.pl"); require("stability/newGoodEvents.pl"); $c = 0; foreach $r (keys %run) {next if $run{$r}->[2] ne "cont"; next if $run{$r}->[0] ne 1; $c += $newGoodEvents{$r}; } print "$c\n";'
# 1218202
# perl -e 'require("grand_list.pl"); require("stability/newGoodEvents.pl"); $c = 0; foreach $r (keys %run) {next if $run{$r}->[2] ne "cont"; next if $run{$r}->[0] ne 2; $c += $newGoodEvents{$r}; } print "$c\n";'
# 2128003
# perl -e 'require("grand_list.pl"); require("stability/newGoodEvents.pl"); $c = 0; foreach $r (keys %run) {next if $run{$r}->[2] ne "cont"; next if $run{$r}->[0] ne 3; $c += $newGoodEvents{$r}; } print "$c\n";'
# 533166

# perl -e 'require("grand_list.pl"); require("allgglumi.pl"); $c = 0; $e = 0; foreach $r (keys %run) {next if $run{$r}->[2] ne "cont"; next if $run{$r}->[0] ne 1; $c += $lumi{$r}; $e += $lumistat{$r}*$lumistat{$r}; } $e = sqrt($e); print "$c +/- $e\n";'
# 183342.5 +/- 325.187745771577
# perl -e 'require("grand_list.pl"); require("allgglumi.pl"); $c = 0; $e = 0; foreach $r (keys %run) {next if $run{$r}->[2] ne "cont"; next if $run{$r}->[0] ne 2; $c += $lumi{$r}; $e += $lumistat{$r}*$lumistat{$r}; } $e = sqrt($e); print "$c +/- $e\n";'
# 358181 +/- 481.796066816656
# perl -e 'require("grand_list.pl"); require("allgglumi.pl"); $c = 0; $e = 0; foreach $r (keys %run) {next if $run{$r}->[2] ne "cont"; next if $run{$r}->[0] ne 3; $c += $lumi{$r}; $e += $lumistat{$r}*$lumistat{$r}; } $e = sqrt($e); print "$c +/- $e\n";'
# 94739.1 +/- 257.258838526493

sub sqr { @_[0]*@_[0]; }

foreach $r (keys %newGoodEvents) {
    next if ($energy{$r} < 4.71 || $energy{$r} > 5.205);
    if ($run{$r}->[2] eq "cont") {
	print "$r $res $energy{$r} -1e+20 -1\n";
	next;
    }

    if ($energy{$r} < 4.86591) { # 1S
	$res = 1;

	$contevents = 1218202;
	$contlumi   =  183342;
	$contenergy =  4.7167;

	$taufrac = 0.0149;
	$eff = 0.9905;
	$bmumu = 0.0249;

# 	if ($energy{$r} < 4.72625  ||  $energy{$r} > 4.735) {
# 	    print "$r $res $energy{$r} 0 0\n";
# 	    next;
# 	}
    }
    elsif ($energy{$r} < 5.088855) { # 2S
	$res = 2;

	$contevents = 2128003;
	$contlumi   =  358181;
	$contenergy =  5.00163;

	$taufrac = 0.0132;
	$eff = 0.9695;
	$bmumu = 0.0203;

# 	if ($energy{$r} < 5.009  ||  $energy{$r} > 5.0165) {
# 	    print "$r $res $energy{$r} 0 0\n";
# 	    next;
# 	}
    }
    else { # 3S
	$res = 3;

	$contevents = 533166;
	$contlumi   =  94739;
	$contenergy =  5.16486;

	$taufrac = 0.0151;
	$eff = 0.9680;
	$bmumu = 0.0239;

# 	if ($energy{$r} < 5.175  ||  $energy{$r} > 5.184) {
# 	    print "$r $res $energy{$r} 0 0\n";
# 	    next;
# 	}
    }

# number of events - (lumi / contlumi) * contevents * (ec / energy)^2
    $upsilons = $newGoodEvents{$r} - ($lumi{$r} / $contlumi) * $contevents * &sqr($contenergy / $energy{$r});
    $staterrr = sqrt($newGoodEvents{$r} + &sqr(($lumistat{$r} / $contlumi) * $contevents * &sqr($contenergy / $energy{$r})));

# drop the taus before efficiency correcting (no error--- it's all Bmumu, which will be put in at the end)
    $upsilons = $upsilons - $taufrac * $subtracted;
    $staterrr = $staterrr - $taufrac * $staterrr;

# eff = 99.05% +/- 0.58%,  96.95 +/- 0.77%,  96.80% +/- 0.81%
    $upsilons = $upsilons / $eff;
    $staterrr = $staterrr / $eff;

# bmumu = 2.49 +/- 0.07%,  2.03 +/- 0.09%,  2.39 +/- 0.12%
# correrr =   0.25%,           0.31%,            0.42%
    $upsilons = $upsilons / (1.0 - 3.0 * $bmumu);
    $staterrr = $staterrr / (1.0 - 3.0 * $bmumu);

# non-beam-beam backgrounds error: 0.5%

# all systematic errors: 0.80%,  0.97%,  1.04%
    print "$r $res $energy{$r} $upsilons $staterrr\n";

}
