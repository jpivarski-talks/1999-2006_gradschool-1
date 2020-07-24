#!/usr/local/bin/perl

while($line = <>) {
    next if ( substr($line,4,24) != "SYSTEM-Processor.BeamGas" );

    if( $line =~ /SYSTEM\-Processor\.BeamGasFilterProc: RUN_CONCLUSION for ([0-9]{6}) : Saw ([0-9\.]+) \+\/\- ([0-9\.]+) \+\/\- ([0-9\.]+) real/ ) {
	$run = $1;
	$hadrons = $2;
	$statistical = $3;
	$systematic = $4;
	print "$run $hadrons $statistical $systematic\n";
    }
}
