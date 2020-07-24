#!/usr/local/bin/perl

foreach $tag (`ls`) {
    chop($tag);
    if ( -d $tag  &&  -e "$tag/normal.dat" ) {
	open(RUN, "> $tag/normal.run");
	$pwd = `pwd`;
	chop $pwd;
	print RUN "cd $pwd/$tag
/home/mccann/public_html/private/my_gammaee/tools/lineshape_fitter/dafdir/fit < normal.dat > normal.log
";
	close(RUN);
    }
}
