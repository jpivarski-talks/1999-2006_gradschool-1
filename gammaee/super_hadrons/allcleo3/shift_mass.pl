#!/usr/local/bin/perl

$ave = 0;
$n = 0;

foreach $tag (`ls`) {
    chop($tag);
    $logfile = "$tag/normal.log";
    $logfile = "$tag/nopeak.log" if ( $tag eq "feb06-02" );
    $logfile = "$tag/nooutlier.log" if ( $tag eq "feb28-02" );

    if ( -d $tag  &&  -e $logfile ) {
	$massline = `grep \"FITTED PARAMETER\" $logfile | grep \"mass =\"`;
	if ( $massline =~ /mass =\s+([0-9\.\-\+eE]+)/ ) {
	    $mass = $1;

	    $ave += $mass;
	    $n++;
	}
    }
}
$ave /= $n;

open(SHIFTED, "> combined.dat");
foreach $tag (`ls`) {
    chop($tag);
    $logfile = "$tag/normal.log";
    $logfile = "$tag/nopeak.log" if ( $tag eq "feb06-02" );
    $logfile = "$tag/nooutlier.log" if ( $tag eq "feb28-02" );

    if ( -d $tag  &&  -e $logfile ) {
	$massline = `grep \"FITTED PARAMETER\" $logfile | grep \"mass =\"`;
	if ( $massline =~ /mass =\s+([0-9\.\-\+eE]+)/ ) {
	    $mass = $1;

	    $datafile = $logfile;
	    $datafile =~ s/log$/dat/;

	    open(NORMAL, $datafile);
	    while ($line = <NORMAL>) {
		chop $line;
		($energy, $xs, $err) = split(/\s+/, $line);
		$w = $energy - $mass;
		$newenergy = $ave + $w;
		print SHIFTED "$newenergy\t$xs\t$err\n";
	    }
	    close(NORMAL);
	}
    }
}
close(SHIFTED);




