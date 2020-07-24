#!/usr/local/bin/perl

open(COS, "> stability/cos.pl");
open(TT, "> stability/tt.pl");
open(LEFF, "> stability/leff.pl");

print COS "\%cos = ();\n";
print TT "\%ttnumer = ();  \%ttdenom = ();\n";
print LEFF "\%leff1 = ();  \%leff2 = ();  \%leff3 = ();  \%leff4 = ();  \%leff5 = ();  \%leff6 = ();  \%leff7 = ();  \%leff8 = ();  \%leff9 = ();  \%leff10 = ();  \%leff11 = ();  \%leff12 = ();  \%leff13 = ();  \%leff14 = ();  \%leff15 = ();  \%leff16 = ();\n";

foreach $file ("/cdat/tem/mccann/db16_redo.log",
	       "/cdat/tem/mccann/db17_redo.log",
	       "/cdat/tem/mccann/db18a_redo.log",
	       "/cdat/tem/mccann/db18b_redo.log",
	       "/cdat/tem/mccann/db18c_redo.log",
	       "/cdat/tem/mccann/db18f_redo.log",
	       "/cdat/tem/mccann/db19_redo.log",
	       "/cdat/tem/mccann/db19b_redo.log",
	       "/cdat/tem/mccann/db21_redo.log",
	       "/cdat/tem/mccann/db22_redo.log",
	       "/cdat/tem/mccann/db23_redo.log",
	       "/cdat/tem/mccann/db25_redo.log",
	       "/cdat/tem/mccann/db27_redo.log") {

    open(FILE, $file);
    while (my $line = <FILE>) {
	if (substr($line, 0, 5) eq "RUNA ") {
	    next if $line !~ /RUNA ([0-9]+) has/;
	    my $run = $1;
	    next if $line !~ /events, ([0-9]+) \*253/;
	    my $cos = $1;
	    print COS "\$cos{$run} = $cos;\n";
	}
	elsif (substr($line, 0, 5) eq "RUNC ") {
	    next if $line !~ /RUNC ([0-9]+) ttcheck = ([0-9]+) \/ ([0-9]+) = /;
	    my $run = $1;
	    my $ttnumer = $2;
	    my $ttdenom = $3;
	    print TT "\$ttnumer{$run} = $ttnumer;  \$ttdenom{$run} = $ttdenom;\n";
	    next if $line !~ /layers (.*)$/;
	    my @l = split(/\s+/, $1);
	    print LEFF "\$leff1{$run} = $l[0];  \$leff2{$run} = $l[1];  \$leff3{$run} = $l[2];  \$leff4{$run} = $l[3];  \$leff5{$run} = $l[4];  \$leff6{$run} = $l[5];  \$leff7{$run} = $l[6];  \$leff8{$run} = $l[7];  \$leff9{$run} = $l[8];  \$leff10{$run} = $l[9];  \$leff11{$run} = $l[10];  \$leff12{$run} = $l[11];  \$leff13{$run} = $l[12];  \$leff14{$run} = $l[13];  \$leff15{$run} = $l[14];  \$leff16{$run} = $l[15];\n";
	}
    }
}

print COS "1;\n";
print TT "1;\n";
print LEFF "1;\n";
