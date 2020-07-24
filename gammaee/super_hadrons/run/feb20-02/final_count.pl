#!/usr/local/bin/perl

$run = $ARGV[0];
$log = $ARGV[1];

$hadrons = 0;

open(LOG, $log);
while($line = <LOG>) {
    next if ( substr($line,4,24) != "SYSTEM-Processor.BeamGas" );

    if( $line =~ /SYSTEM\-Processor\.BeamGasFilterProc: So that\'s ([0-9\.]+) \+\/\- ([0-9\.]+) \+\/\- ([0-9\.]+) real hadronic events/ ) {
	$hadrons = $1;
	$statistical = $2;
	$systematic = $3;
    }
}

if ( $hadrons > 0 ) {
    print "$run	$hadrons $statistical $systematic\n";
}
else {
    print "$run	FAILED\n";
}
