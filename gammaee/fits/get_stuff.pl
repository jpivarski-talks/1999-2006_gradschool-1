#!/usr/local/bin/perl

require("grand_list.pl");

open(RUNINFO, "/nfs/cleo3/Offline/InfoFiles/data/runinfo.runinfo");
open(ENERGY, "> energy.pl");  print ENERGY "\%energy = ();\n";
open(BBLUMI, "> bblumi.pl");  print BBLUMI "\%lumi = ();  \%lumistat = ();  \%lumisyst = ();\n";
open(GGLUMI, "> gglumi.pl");  print GGLUMI "\%lumi = ();  \%lumistat = ();  \%lumisyst = ();\n";
while (my $ri = <RUNINFO>) {
    chop $ri;
    my ($dummy,
	$r, $events, $hadrons, $last,
	$bblumi, $bbstat, $bbsyst,
	$ebeam, $ebeam_unc, $bfield, $bfield_unc,
	$gglumi, $ggstat, $ggsyst,
	$db) = split(/\s+/, $ri);
    if (defined($run{$r})) {
	print ENERGY "\$energy{$r} = $ebeam;\n";
	print BBLUMI "\$lumi{$r} = $bblumi;  \$lumistat{$r} = $bbstat;  \$lumisyst{$r} = $bbsyst;\n";
	print GGLUMI "\$lumi{$r} = $gglumi;  \$lumistat{$r} = $ggstat;  \$lumisyst{$r} = $ggsyst;\n";
    }
}    
print ENERGY "1\n";
print BBLUMI "1\n";
print GGLUMI "1\n";
close(RUNINFO);
close(ENERGY);
close(BBLUMI);
close(GGLUMI);

open(BEAMSPOT, "/nfs/cleo3/Offline/InfoFiles/data/beamspot.beamspot");
open(BS, "> beamspot.pl");  print BS "\%bsx = ();  \%bsy = ();  \%bsz = ();\n";
while (my $bs = <BEAMSPOT>) {
    chop $bs;
    my ($r, $label, $tried, $used, $bsx, $bsy, $bsz, @other) = split(/\s+/, $bs);
    if (defined($run{$r})) {
	print BS "\$bsx{$r} = $bsx;  \$bsy{$r} = $bsy;  \$bsz{$r} = $bsz;\n";
    }
}
print BS "1\n";
close(BEAMSPOT);
close(BS);
