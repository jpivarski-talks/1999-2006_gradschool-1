#!/usr/local/bin/perl

$statsret = "/nfs/cleo3/Common/rel/current/bin/sparc-sun-solaris2.6/DBRunStatisticsRetrieve";

$run = $ARGV[0];
if ( defined( $ARGV[1] ) )
{ $endtime = $ARGV[1]; }
else
{ $endtime = 0; }

$atime = 0;
$firsttime = 0;
$firstEcur = 0;
$firstPcur = 0;
open( STARTRUN, "$statsret $run 4 |" );
while( <STARTRUN> ) {
    if ( $_ =~ /^Created on[^0-9]*[0-9]+\/[0-9]+\/[0-9]+ +([0-9]+):([0-9]+):([0-9]+)/ ) {
	$atime = $1 * 60 * 60 + $2 * 60 + $3;
	# print "STARTRUN $_";
	# print "$atime = $1 * 60 * 60 + $2 * 60 + $3\n";
    }
    if ( $firstEcur == 0  &&
	 $_ =~ /^CESR\/electron_cur_tot: *([0-9\.\-\+eE]+)/ ) {
	$firstEcur = $1;
	$firsttime = $atime;
	# print "STARTRUN $_";
	# print "$firstEcur = $1; $firsttime = $atime;\n";
	
    }
    if ( $firstPcur == 0  &&
	 $_ =~ /^CESR\/positron_cur_tot: *([0-9\.\-\+eE]+)/ ) {
	$firstPcur = $1;
	$firsttime = $atime;
	# print "STARTRUN $_";
	# print "$firstPcur = $1; $firsttime = $atime;\n";
    }
}

$atime = 0;
$lasttime = 0;
$lastEcur = 0;
$lastPcur = 0;
open( UPDATE, "$statsret $run 64 |" );
while( <UPDATE> ) {
    if ( $_ =~ /^Created on[^0-9]*[0-9]+\/[0-9]+\/[0-9]+ +([0-9]+):([0-9]+):([0-9]+)/ ) {
	$atime = $1 * 60 * 60 + $2 * 60 + $3;
	# print "UPDATE $_";
	# print "$atime = $1 * 60 * 60 + $2 * 60 + $3\n";
    }
    if ( $_ =~ /^CESR\/electron_cur_tot: *([0-9\.\-\+eE]+)/ ) {
	$lastEcur = $1;
	$lasttime = $atime;
	# print "UPDATE $_";
	# print "$lastEcur = $1; $lasttime = $atime;\n";
    }
    if ( $_ =~ /^CESR\/positron_cur_tot: *([0-9\.\-\+eE]+)/ ) {
	$lastPcur = $1;
	$lasttime = $atime;
	# print "UPDATE $_";
	# print "$lastPcur = $1; $lasttime = $atime;\n";
    }
}

if ( $endtime == 0 )
{
    open( ENDRUN, "$statsret $run 16 |" );
    while( <ENDRUN> ) {
	if ( $endtime == 0  &&
	     $_ =~ /^Created on[^0-9]*[0-9]+\/[0-9]+\/[0-9]+ +([0-9]+):([0-9]+):([0-9]+)/ ) {
	    $endtime = $1 * 60 * 60 + $2 * 60 + $3;
	    # print "ENDRUN $_";
	    # print "$endtime = $1 * 60 * 60 + $2 * 60 + $3\n";
	}
    }
    close( ENDRUN );
    
    if ( $endtime < $firsttime )
    { $endtime += 24 * 60 * 60; }

    $endtime = $endtime - $firsttime;
}

if ( $lasttime < $firsttime )
{ $lasttime += 24 * 60 * 60; }

$lasttime = $lasttime - $firsttime;
$firsttime = 0;

$firstcur = $firstEcur + $firstPcur;
$lastcur = $lastEcur + $lastPcur;

$curslope = (($lastcur - $firstcur) / $lasttime);
$curPslope = (($lastPcur - $firstPcur) / $lasttime);
$curEslope = (($lastEcur - $firstEcur) / $lasttime);

$electron_integral = $firstEcur * $firstEcur * $endtime
    + $firstEcur * $curEslope * $endtime * $endtime
    + $curEslope * $curEslope * $endtime * $endtime * $endtime / 3.

    + $firstEcur * $firstPcur * $endtime
    + $firstPcur * $curEslope * $endtime * $endtime / 2.
    + $firstEcur * $curPslope * $endtime * $endtime / 2.
    + $curEslope * $curPslope * $endtime * $endtime * $endtime / 3.;

$positron_integral = $firstPcur * $firstPcur * $endtime
    + $firstPcur * $curPslope * $endtime * $endtime
    + $curPslope * $curPslope * $endtime * $endtime * $endtime / 3.

    + $firstEcur * $firstPcur * $endtime
    + $firstPcur * $curEslope * $endtime * $endtime / 2.
    + $firstEcur * $curPslope * $endtime * $endtime / 2.
    + $curEslope * $curPslope * $endtime * $endtime * $endtime / 3.;

print "$endtime\t$electron_integral\t$positron_integral";
