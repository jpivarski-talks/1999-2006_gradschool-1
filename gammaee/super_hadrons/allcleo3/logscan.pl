#!/usr/local/bin/perl

$prevline = "";
while($_ = <>) {
    print $_ if ( substr($_, 0, 44) eq " %% SYSTEM-Processor.BeamGasFilterProc: RUN_" );
    if ( $_ eq " %% ERROR-JobControl.JobControl: -eventLoop: caught a DAException:\n" ) {
	print $prevline;
 	print $_;
 	print $_ if ($_ = <>);
 	print $_ if ($_ = <>);
	print "\n";
    }
    $prevline = $_;
}

