#!/usr/local/bin/perl

@file = ();
%name = ();

foreach $dir ("y1s/feb20-02", "y2s/may28-02", "y3s/dec25-01",
	      "y1s/feb06-02", "y2s/jun11-02", "y3s/dec06-01",
	      "y1s/feb28-02", "y3s/dec13-01", "y1s/jan16-02",
	      "y3s/dec20-01", "y1s/jan30-02", "y3s/jan03-02",
	      "y1s/mar06-02", "y3s/jan10-02", "y3s/nov29-01") {
    opendir(DIR, $dir);
    @files = readdir(DIR);
    closedir(DIR);

    $dirname = substr($dir, 4, 5);

    foreach $file (@files) {
	next if $file !~ /scanyint_([0-9\.]+)\.run/;
	$yint = $1 * 100.;

	push(@file, "$dir/$file");
	$name{"$dir/$file"} = "$dirname\_$yint";
    }
}

foreach $f (@file) {
    print("qsub -l nodlt -N $name{$f} $f\n");
    system("qsub -l nodlt -N $name{$f} $f\n");
    while (`qstat -u mccann | wc -l` > 40) { sleep 300; }
}

