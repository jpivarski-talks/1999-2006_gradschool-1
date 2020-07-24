#!/usr/local/bin/perl

$dir = "/home/mrs43/energy_program/tmp/2001_logs";

@files = ("energy_Apr2401_0517.log",
	  "energy_Apr2401_0518.log",
	  "energy_Apr2401_0519.log",
	  "energy_Dec0401_1205.log",
	  "energy_Dec0501_1717.log",
	  "energy_Dec0501_2023.log",
	  "energy_Dec1701_2047.log",
	  "energy_Dec1801_1640.log",
	  "energy_Dec1801_1941.log",
	  "energy_Dec3101_0731.log",
	  "energy_Dec3101_0752.log",
	  "energy_Feb0701_0149.log",
	  "energy_Feb0701_0404.log",
	  "energy_Feb2101_0115.log",
	  "energy_Jan0401_1421.log",
	  "energy_Jan1101_0426.log",
	  "energy_Jun0201_1537.log",
	  "energy_Mar0301_0832.log",
	  "energy_Mar1401_0406.log",
	  "energy_Mar1901_0921.log",
	  "energy_May0101_1524.log",
	  "energy_May0301_0947.log",
	  "energy_May0701_2038.log",
	  "energy_May2401_1834.log",
	  "energy_May2401_1835.log",
	  "energy_May2401_1905.log",
	  "energy_May2401_2309.log",
	  "energy_May2501_2341.log",
	  "energy_Nov0201_1952.log",
	  "energy_Nov1201_1650.log",
	  "energy_Nov1201_1709.log",
	  "energy_Nov1701_0957.log",
	  "energy_Nov1701_1001.log",
	  "energy_Nov1701_1502.log",
	  "energy_Nov1801_0917.log",
	  "energy_Nov1901_0525.log",
	  "energy_Nov1901_0750.log",
	  "energy_Oct1901_1408.log",
	  "energy_Oct1901_1529.log",
	  "energy_Oct2701_0547.log",
	  "energy_Oct3101_0630.log");

foreach $file ( @files ) {
    open(FILE, "$dir/$file");
    print "BEGINNING FILE $file\n";

    while ($outer = <FILE>) {
	if ( $outer =~ /ERROR: SEN/ ) {
	
	    $seen_date = 0;
	    $seen_time = 0;
	    while ($inner = <FILE>) {
		if ( $inner =~ /Date:\s+([0-9]+)/i ) {
		    $seen_date = 1;
		    $date = $1;
		    }
		elsif ( $inner =~ /time:\s+([0-9:]+)/ ) {
		    $seen_time = 1;
		    $time = $1;
		    }
		
		last if ( $seen_date == 1  &&  $seen_time == 1 );
	    }
	    
	    print "Error at $date $time\n";
	}
    }
}
