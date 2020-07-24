#!/usr/local/bin/perl

$x = 0.;
$sig = 0.;

foreach $tag ( @ARGV ) {
    open( FIT, "../../fits/$tag/pass1/real.txt" );
    while ( <FIT> ) {
	if ( $_ =~ /^mass/ ) {
	    ( $mass, $equals, $shift{$tag}, $pm, $err{$tag}, @rest ) = split( /\s+/ );
#	    print "$shift{$tag} +/- $err{$tag}\n";
	    $weight = 1. / $err{$tag} / $err{$tag};
	    $x += $shift{$tag} * $weight;
	    $sig += $weight;
	}
    }
}

$mean = $x / $sig;
# $err = 1. / sqrt( $sig );

# print "==================================\n";
# printf "%10.8f +/- %10.8f\n", $mean, $err;

foreach $tag ( @ARGV ) {
    open( DATAUSE, "../../fits/$tag/pass1/datause.dat" );
    while ( <DATAUSE> ) {
	chop;
	( $energy, $hxc, $err ) = split( /\s+/ );
	$energy -= $shift{$tag} - $mean;
	print "$energy\t$hxc\t$err\n";
    }
}
