#!/usr/local/bin/perl

require("tt.pl");
require("../gglumi.pl");
require("../grand_list.pl");

$which = 3;
   if ($which == 1) { $clum = 183343 }
elsif ($which == 2) { $clum = 358181 }
elsif ($which == 3) { $clum = 94739 }

   if ($which == 1) { $cnumer = 50416 }
elsif ($which == 2) { $cnumer = 92637 }
elsif ($which == 3) { $cnumer = 23100 }

   if ($which == 1) { $cdenom = 54952 }
elsif ($which == 2) { $cdenom = 100703 }
elsif ($which == 3) { $cdenom = 25252 }

foreach $r (sort numly %run) {
    next if ($run{$r}->[0] != $which);
    next if $run{$r}->[2] eq "cont";

    $ptoc = $lumi{$r}/$clum;
#     $e_ptoc = $lumistat{$r}/$clum;
    $numer = $ttnumer{$r} - $ptoc * $cnumer;
    $denom = $ttdenom{$r} - $ptoc * $cdenom;
#     $e2_ttnumer = $ttdenom{$r} - $ttnumer{$r};

    $frac = $numer / $denom;
#     $e_frac = sqrt(&sqr($e_ptoc) * &sqr(($cnumer * $ttdenom{$r} - $ttnumer{$r} * $cdenom) / &sqr($denom)) +
# 		   $e2_ttnumer / $denom);

    print "$r $frac\n" if ($ttdenom{$r} > 1000);
}

sub sqr { $_[0] * $_[0] };
