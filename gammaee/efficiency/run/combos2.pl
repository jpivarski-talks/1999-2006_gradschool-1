#!/usr/local/bin/perl

%w = ();
$n = 0;

while (<>) {
    chop;
    $w{$n} = $_;
    $n++;
}

$mask = 1;
foreach $type ("hadron", "bhagam", "radbha", "mupair", "track3", "barrelbhabha") {
    $this = 0;
    $total = 0;
    foreach $n (0..63) {
	if (($n & $mask) > 0) {
	    $this += $w{$n};
	}
	$total += $w{$n};
    }
    print "$type: $this / $total\n";
    $mask = 2 * $mask;
}

# sol222% perl combos2.pl < datal3combos.dat     |    sol222% perl combos2.pl < mcl3combos.dat 
# hadron: 580770 / 693337			 |    hadron: 3939583 / 4293924		 
# bhagam: 2090 / 693337				 |    bhagam: 85982 / 4293924			 
# radbha: 5535 / 693337				 |    radbha: 4739 / 4293924			 
# mupair: 30197 / 693337			 |    mupair: 111228 / 4293924		 
# track3: 46228 / 693337			 |    track3: 37682 / 4293924			 
# barrelbhabha: 741 / 693337			 |    barrelbhabha: 73735 / 4293924		 
