#!/usr/local/bin/perl

# Location of things
$base = "/home/mccann/public_html/private/my_gammaee";
$fitY1s = "$base/tools/real_fit/fitY1s";
$fitY2s = "$base/tools/real_fit/fitY2s";
$fitY3s = "$base/tools/real_fit/fitY3s";

# These are the scans that have enough data to form a peak, and
# therefore can be fit individually
@singleY1s = ( "jan16-02", "jan30-02", "feb06-02", "feb20-02",
	       "feb28-02", "mar06-02", "mar14-02", "apr02-02",
	       "apr08-02" );
@singleY2s = ( "may28-02", "jun11-02", "jul11-02", "jul24-02" );
@singleY3s = ( "nov29-01", "dec06-01", "dec13-01", "dec20-01",
	       "dec25-01", "jan03-02", "jan10-02" );

# These are all the scan tags that belong to a given resonance. 
@allY1s = ( "jan16-02", "jan30-02", "feb06-02", "feb14-02",
	    "feb20-02", "feb28-02", "mar06-02", "mar14-02",
	    "mar21-02", "apr02-02", "apr08-02" );
@allY2s = ( "may28-02", "jun11-02", "jun28-02", "jul11-02", "jul24-02" );
@allY3s = ( "nov29-01", "dec06-01", "dec13-01", "dec20-01",
	    "dec25-01", "jan03-02", "jan10-02" );

&fitsingles( $fitY3s, "run_infoY3s.html", ( "dec25-01" ) );

sub fitsingles {
    my ($fitter, $run_info, @tags) = @_;

    foreach my $tag ( @tags ) {
	print "* * * $tag * * *\n";

	chdir( "$base/fits/$tag/pass1" );
	system( "awk '{print 2*\$3, \$4, \$5}' data.dat | $fitter | tee fit.log" );

	my $low = 20000;
	my $high = 0;
	my $peak = 0;
	my $n = 0;
	open( EXPT, "expt.dat" );
	while ( <EXPT> ) {
	    $_ =~ s/^\s+//;
	    my ($en, $hxs, $err) = split( /\s+/, $_ );
	    if ( $en < $low ) { $low = $en }
	    if ( $en > $high ) { $high = $en }
	    if ( $hxs > $peak ) { $peak = $hxs }
	    $n++;
	}
	close( EXPT );

	open( GNUPLOT, "| gnuplot" );
	print GNUPLOT "set nokey\n";
	print GNUPLOT "set xlabel \"COM Energy in MeV\"\n";
	print GNUPLOT "set ylabel \"Pass1 Hadronic Cross-Section in nb\"\n";
	print GNUPLOT "set title \"Kuraev-Fadin Fit to $tag\"\n";
	print GNUPLOT "set term gif transparent interlace medium size 640,480\n";
	print GNUPLOT "set output \"fit.gif\"\n";
	print GNUPLOT "plot [".($low-3).":".($high+3)."][0:".($peak+4)."] \"expt.dat\" with errorbars, \"theo.dat\" with lines\n";
	print GNUPLOT "set term postscript eps color solid\n";
	print GNUPLOT "set output \"fit.eps\"\n";
	print GNUPLOT "plot [".($low-3).":".($high+3)."][0:".($peak+4)."] \"expt.dat\" with errorbars, \"theo.dat\" with lines\n";
	print GNUPLOT "exit\n";

	open( FIT, "> fit.html" );
	print FIT "<html><title>$tag Kuraev-Fadin Fit</title><body>

<center><h1>Kuraev-Fadin Fit to $tag</h1></center>

<h2>Plot of Fit</h2>

<center><img src=\"fit.gif\"></center>

<p>Click <a href=\"fit.eps\">here</a> for EPS!

<h2>Data Used</h2>
<pre>
 RUN    TYPE   ENERGY (single-beam, GeV)   PASS1 HADRONIC CROSS-SECTION (nb)
============================================================================
";
	open( DATA, "data.dat" );
	while( <DATA> ) {
	    my ($run, $type, $energy, $hxs, $err) = split(/\s+/);
	    printf( FIT "%06d   %s             %7.5f                      %5.2f +/- %4.2f\n",
		    $run, $type, $energy, $hxs, $err );
	} # end data
	
	print FIT "</pre>

<p>Types: \"S\" = Scan point, \"C\" = Continuum (off-resonance), \"P\" = Peak (on-resonance)
and \"H\" = High-energy tail point (a scan point very high above the peak).

<p>Tab-delimited in <a href=\"data.dat\">data.dat</a>

<p>Click <a href=\"../../../$run_info#$tag\">here</a> to see this data in the original run list.

<h2>Fit function is</h2>

<p>Given an energy in MeV,
<pre>
      real*8 rm, wspread, hc
      rm = <b>mass</b> * 1000.d0
      wspread = <b>wide</b>
      hc = enMeV(i) - rm
      backgr = <b>back</b> * 9430.d0**2 / enMeV(i)**2

      fit = <b>area</b> * <a href=\"../../gbwkf2.F\">gbwkf</a>( rm, gam, wspread, hc ) + backgr
</pre>

<h2>Fit Parameters are</h2>
<pre>
";
	my $fcn, $status;
	open( LOG, "fit.log" );
	while( <LOG> ) {
	    if ( $_ =~ /param\s+([a-z]+)\s+=\s+(.*)/ ) { print FIT "<b>$1</b> = $2\n" }
	    if ( $_ =~ /FCN\s*=\s*([0-9\-\.\+eE]+)/ ) { $fcn = $1 }
	    if ( $_ =~ /STATUS\s*=\s*([a-zA-Z]+)/ ) { $status = $1 }
	} # end log

	print FIT "</pre>

<table width=600><tr><td>Chi^2 / ndf = $fcn / $n = ".sprintf("%5.2f", (0.+$fcn)/$n)."</td>
                     <td align=right>STATUS = $status</td></tr></table>

<h2>Fitter Log</h2>
<pre>
";

	open( LOG, "fit.log" );
	while( <LOG> ) {
	    print FIT $_;
	} # end log

	print FIT "</pre>

</body></html>
";



    }
}

