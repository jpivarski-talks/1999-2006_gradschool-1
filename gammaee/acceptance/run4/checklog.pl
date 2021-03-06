#!/usr/local/bin/perl

%n = ();
%last = ();
open(LOG, $ARGV[0]);
while (my $line = <LOG>) {
    next if (substr($line, 0, 8) ne "RUNEVENT");
    chop($line);
    my ($label, $run, $event) = split(' ', $line);
    $n{$run}{$event}++;
    $last{$run} = 0 if (!defined($last{$run}));
    $last{$run} = $event if ($event > $last{$run});
}
close(LOG);

sub numly {$a <=> $b;}

foreach my $run (keys %n) {
    print "Run $run:\n";
    %m = %{ $n{$run} };
    foreach my $event (1..$last{$run}) {
	print "    event $event has $m{$event}\n" if ($m{$event} != 1);
    }
    print "    last is $last{$run}\n";
    system("awk '(\$1==$run){print \$1, \$4}' /nfs/cleo3/Offline/InfoFiles/data/runinfo.runinfo");
    print "\n";
}

# Run 122133:
#     event 3995 has 
#     event 3996 has 
#     event 110177 has 
#     event 154390 has 2
#     last is 183322
# 122133 183322

# Run 122832:
#     last is 181932
# 122832 181932

# Run 123853:
#     event 160299 has 2
#     last is 235740
# 123853 235740

# Run 124684:
#     event 65758 has 2
#     last is 205630
# 124684 205630

# Run 126870:
#     last is 185771
# 126870 185771

# Run 129572:
#     last is 233487
# 129572 233487

# Run 122091:
#     last is 162025
# 122091 162025

# Run 122430:
#     last is 143582
# 122430 143582

# Run 123817:
#     last is 160461
# 123817 160461

# Run 125176:
#     last is 144231
# 125176 144231

# Run 126488:
#     last is 145729
# 126488 145729

# Run 130427:
#     last is 195430
# 130427 195430

# Run 122634:
#     last is 68526
# 122634 68526

# Run 121969:
#     event 2 has 
#     event 15 has 
#     event 30 has 
#     event 49 has 
#     event 53 has 
#     event 59 has 
#     event 77 has 
#     event 85 has 
#     event 117 has 
#     event 129 has 
#     event 141 has 
#     event 146 has 
#     event 147 has 
#     event 176 has 
#     event 183 has 
#     event 189 has 
#     event 215 has 
#     event 219 has 
#     event 241 has 
#     event 270 has 
#     event 271 has 
#     event 277 has 
#     event 278 has 
#     event 289 has 
#     event 321 has 
#     event 323 has 
#     event 352 has 
#     event 355 has 
#     event 361 has 
#     event 366 has 
#     event 380 has 
#     event 401 has 
#     event 411 has 
#     event 425 has 
#     event 448 has 
#     event 456 has 
#     event 457 has 
#     event 476 has 
#     event 481 has 
#     event 486 has 
#     event 505 has 
#     event 519 has 
#     event 554 has 
#     event 564 has 
#     event 569 has 
#     event 570 has 
#     event 573 has 
#     event 596 has 
#     event 606 has 
#     event 619 has 
#     event 632 has 
#     event 633 has 
#     event 640 has 
#     event 690 has 
#     event 691 has 
#     event 694 has 
#     event 702 has 
#     event 713 has 
#     event 740 has 
#     event 753 has 
#     event 757 has 
#     event 758 has 
#     event 768 has 
#     event 796 has 
#     event 806 has 
#     event 812 has 
#     event 815 has 
#     event 820 has 
#     event 828 has 
#     event 864 has 
#     event 870 has 
#     event 878 has 
#     event 890 has 
#     event 895 has 
#     event 904 has 
#     event 927 has 
#     event 928 has 
#     event 940 has 
#     event 981 has 
#     event 985 has 
#     event 987 has 
#     event 991 has 
#     event 1009 has 
#     event 1013 has 
#     event 1015 has 
#     event 1074 has 
#     event 1075 has 
#     event 1076 has 
#     event 1079 has 
#     event 1084 has 
#     event 1095 has 
#     event 1118 has 
#     event 1140 has 
#     event 1141 has 
#     event 1158 has 
#     event 1160 has 
#     event 1169 has 
#     event 1188 has 
#     event 1195 has 
#     event 1231 has 
#     event 1234 has 
#     event 1266 has 
#     event 1272 has 
#     event 1293 has 
#     event 1328 has 
#     event 1365 has 
#     event 1371 has 
#     event 1414 has 
#     event 1442 has 
#     event 1446 has 
#     event 1450 has 
#     event 1470 has 
#     event 1484 has 
#     event 1488 has 
#     event 1496 has 
#     event 1497 has 
#     event 1524 has 
#     event 1532 has 
#     event 1542 has 
#     event 1547 has 
#     event 1572 has 
#     event 1579 has 
#     event 1586 has 
#     event 1594 has 
#     event 1633 has 
#     event 1681 has 
#     event 1688 has 
#     event 1724 has 
#     event 1751 has 
#     event 1770 has 
#     event 1801 has 
#     event 1806 has 
#     event 1813 has 
#     event 1828 has 
#     event 1831 has 
#     event 1838 has 
#     event 1855 has 
#     event 1869 has 
#     event 1872 has 
#     event 1873 has 
#     event 1881 has 
#     event 1911 has 
#     event 1914 has 
#     event 1919 has 
#     event 1935 has 
#     event 1941 has 
#     event 1993 has 
#     event 1998 has 
#     event 2003 has 
#     event 2011 has 
#     event 2024 has 
#     event 2033 has 
#     event 2074 has 
#     event 2077 has 
#     event 2097 has 
#     event 2106 has 
#     event 2107 has 
#     event 2110 has 
#     event 2128 has 
#     event 2153 has 
#     event 2158 has 
#     event 2159 has 
#     event 2163 has 
#     event 2168 has 
#     event 2192 has 
#     event 2203 has 
#     event 2208 has 
#     event 2241 has 
#     event 2260 has 
#     event 2264 has 
#     event 2280 has 
#     event 2288 has 
#     event 2291 has 
#     event 2307 has 
#     event 2321 has 
#     event 2335 has 
#     event 2338 has 
#     event 2339 has 
#     event 2340 has 
#     event 2343 has 
#     event 2347 has 
#     event 2357 has 
#     event 2358 has 
#     event 2371 has 
#     event 2384 has 
#     event 2409 has 
#     event 2412 has 
#     event 2424 has 
#     event 2433 has 
#     event 2439 has 
#     event 2447 has 
#     event 2455 has 
#     event 2473 has 
#     event 2488 has 
#     event 2510 has 
#     event 2544 has 
#     event 2554 has 
#     event 2588 has 
#     event 2589 has 
#     event 2591 has 
#     event 2596 has 
#     event 2603 has 
#     event 2648 has 
#     event 2680 has 
#     event 2683 has 
#     event 2702 has 
#     event 2709 has 
#     event 2744 has 
#     event 2747 has 
#     event 2759 has 
#     event 2761 has 
#     event 2787 has 
#     event 2788 has 
#     event 2792 has 
#     event 2800 has 
#     event 2801 has 
#     event 2817 has 
#     event 2840 has 
#     event 2850 has 
#     event 2860 has 
#     event 2868 has 
#     event 2878 has 
#     event 2884 has 
#     event 2886 has 
#     event 2889 has 
#     event 2896 has 
#     event 2909 has 
#     event 2911 has 
#     event 2913 has 
#     event 2927 has 
#     event 2945 has 
#     event 2953 has 
#     event 2962 has 
#     event 2973 has 
#     event 2996 has 
#     event 3010 has 
#     event 3032 has 
#     event 3042 has 
#     event 3045 has 
#     event 3052 has 
#     event 3062 has 
#     event 3085 has 
#     event 3103 has 
#     event 3112 has 
#     event 3128 has 
#     event 3135 has 
#     event 3146 has 
#     event 3170 has 
#     event 3185 has 
#     event 3187 has 
#     event 3198 has 
#     event 3217 has 
#     event 3262 has 
#     event 3265 has 
#     event 3266 has 
#     event 3288 has 
#     event 3326 has 
#     event 3336 has 
#     event 3346 has 
#     event 3365 has 
#     event 3379 has 
#     event 3388 has 
#     event 3390 has 
#     event 3399 has 
#     event 3406 has 
#     event 3421 has 
#     event 3459 has 
#     event 3468 has 
#     event 3473 has 
#     event 3484 has 
#     event 3486 has 
#     event 3490 has 
#     event 3497 has 
#     event 3617 has 
#     event 3624 has 
#     event 3646 has 
#     event 3651 has 
#     event 3663 has 
#     event 3668 has 
#     event 3697 has 
#     event 3708 has 
#     event 3732 has 
#     event 3765 has 
#     event 3772 has 
#     event 3782 has 
#     event 3785 has 
#     event 3801 has 
#     event 3879 has 
#     event 3891 has 
#     event 3894 has 
#     event 3910 has 
#     event 3918 has 
#     event 3947 has 
#     event 3954 has 
#     event 3960 has 
#     event 3978 has 
#     event 3980 has 
#     event 3981 has 
#     event 3988 has 
#     event 4004 has 
#     event 4082 has 
#     event 4095 has 
#     event 4105 has 
#     event 4106 has 
#     event 4107 has 
#     event 4116 has 
#     event 4127 has 
#     event 4145 has 
#     event 4155 has 
#     event 4156 has 
#     event 4173 has 
#     event 4182 has 
#     event 4216 has 
#     event 4217 has 
#     event 4229 has 
#     event 4230 has 
#     event 4236 has 
#     event 4302 has 
#     event 4308 has 
#     event 4319 has 
#     event 4322 has 
#     event 4342 has 
#     event 4382 has 
#     event 4404 has 
#     event 4429 has 
#     event 4436 has 
#     event 4439 has 
#     event 4445 has 
#     event 4452 has 
#     event 4456 has 
#     event 4462 has 
#     event 4466 has 
#     event 4467 has 
#     event 4471 has 
#     event 4514 has 
#     event 4545 has 
#     event 4549 has 
#     event 4561 has 
#     event 4564 has 
#     event 4569 has 
#     event 4586 has 
#     event 4616 has 
#     event 4633 has 
#     event 4644 has 
#     event 4649 has 
#     event 4684 has 
#     event 4693 has 
#     event 4698 has 
#     event 4701 has 
#     event 4724 has 
#     event 4736 has 
#     event 4772 has 
#     event 4788 has 
#     event 4797 has 
#     event 4808 has 
#     event 4830 has 
#     event 4837 has 
#     event 4853 has 
#     event 4855 has 
#     event 4857 has 
#     event 4861 has 
#     event 4887 has 
#     event 4915 has 
#     event 4937 has 
#     event 4961 has 
#     event 4973 has 
#     event 4987 has 
#     event 4989 has 
#     event 5012 has 
#     event 5064 has 
#     event 5089 has 
#     event 5090 has 
#     event 5109 has 
#     event 5120 has 
#     event 5146 has 
#     event 5174 has 
#     event 5178 has 
#     event 5197 has 
#     event 5201 has 
#     event 5247 has 
#     event 5250 has 
#     event 5254 has 
#     event 5255 has 
#     event 5281 has 
#     event 5318 has 
#     event 5331 has 
#     event 5420 has 
#     event 5423 has 
#     event 5430 has 
#     event 5447 has 
#     event 5459 has 
#     event 5481 has 
#     event 5494 has 
#     event 5521 has 
#     event 5529 has 
#     event 5573 has 
#     event 5577 has 
#     event 5580 has 
#     event 5616 has 
#     event 5627 has 
#     event 5632 has 
#     event 5635 has 
#     event 5642 has 
#     event 5667 has 
#     event 5674 has 
#     event 5683 has 
#     event 5685 has 
#     event 5710 has 
#     event 5722 has 
#     event 5745 has 
#     event 5754 has 
#     event 5769 has 
#     event 5819 has 
#     event 5821 has 
#     event 5835 has 
#     event 5841 has 
#     event 5872 has 
#     event 5881 has 
#     event 5889 has 
#     event 5893 has 
#     event 5924 has 
#     event 5941 has 
#     event 5951 has 
#     event 5960 has 
#     event 5971 has 
#     event 5983 has 
#     event 5985 has 
#     event 5986 has 
#     event 6000 has 
#     event 6011 has 
#     event 6026 has 
#     event 6048 has 
#     event 6049 has 
#     event 6060 has 
#     event 6066 has 
#     event 6076 has 
#     event 6092 has 
#     event 6100 has 
#     event 6101 has 
#     event 6108 has 
#     event 6113 has 
#     event 6154 has 
#     event 6162 has 
#     event 6165 has 
#     event 6174 has 
#     event 6179 has 
#     event 6250 has 
#     event 6257 has 
#     event 6269 has 
#     event 6278 has 
#     event 6302 has 
#     event 6318 has 
#     event 6328 has 
#     event 6336 has 
#     event 6351 has 
#     event 6360 has 
#     event 6373 has 
#     event 6394 has 
#     event 6400 has 
#     event 6409 has 
#     event 6439 has 
#     event 6452 has 
#     event 6488 has 
#     event 6513 has 
#     event 6516 has 
#     event 6524 has 
#     event 6530 has 
#     event 6563 has 
#     event 6573 has 
#     event 6587 has 
#     event 6590 has 
#     event 6597 has 
#     event 6637 has 
#     event 6651 has 
#     event 6691 has 
#     event 6696 has 
#     event 6703 has 
#     event 6736 has 
#     event 6740 has 
#     event 6777 has 
#     event 6783 has 
#     event 6802 has 
#     event 6824 has 
#     event 6850 has 
#     event 6866 has 
#     event 6918 has 
#     event 6924 has 
#     event 6935 has 
#     event 6948 has 
#     event 6953 has 
#     event 6998 has 
#     event 7031 has 
#     event 7041 has 
#     event 7045 has 
#     event 7059 has 
#     event 7079 has 
#     event 7090 has 
#     event 7110 has 
#     event 7117 has 
#     event 7135 has 
#     event 7143 has 
#     event 7160 has 
#     event 7176 has 
#     event 7184 has 
#     event 7198 has 
#     event 7220 has 
#     event 7225 has 
#     event 7234 has 
#     event 7235 has 
#     event 7243 has 
#     event 7251 has 
#     event 7270 has 
#     event 7300 has 
#     event 7315 has 
#     event 7319 has 
#     event 7334 has 
#     event 7335 has 
#     event 7361 has 
#     event 7380 has 
#     event 7396 has 
#     event 7409 has 
#     event 7414 has 
#     event 7465 has 
#     event 7482 has 
#     event 7489 has 
#     event 7490 has 
#     event 7505 has 
#     event 7531 has 
#     event 7535 has 
#     event 7559 has 
#     event 7560 has 
#     event 7583 has 
#     event 7591 has 
#     event 7596 has 
#     event 7605 has 
#     event 7628 has 
#     event 7636 has 
#     event 7645 has 
#     event 7646 has 
#     event 7662 has 
#     event 7667 has 
#     event 7668 has 
#     event 7676 has 
#     event 7712 has 
#     event 7744 has 
#     event 7747 has 
#     event 7761 has 
#     event 7772 has 
#     event 7781 has 
#     event 7790 has 
#     event 7794 has 
#     event 7807 has 
#     event 7811 has 
#     event 7829 has 
#     event 7830 has 
#     event 7836 has 
#     event 7841 has 
#     event 7862 has 
#     event 7868 has 
#     event 7881 has 
#     event 7931 has 
#     event 7934 has 
#     event 7960 has 
#     event 7961 has 
#     event 7966 has 
#     event 7999 has 
#     event 8019 has 
#     event 8020 has 
#     event 8049 has 
#     event 8064 has 
#     event 8094 has 
#     event 8103 has 
#     event 8111 has 
#     event 8129 has 
#     event 8135 has 
#     event 8145 has 
#     event 8152 has 
#     event 8172 has 
#     event 8179 has 
#     event 8198 has 
#     event 8227 has 
#     event 8239 has 
#     event 8248 has 
#     event 8270 has 
#     event 8284 has 
#     event 8296 has 
#     event 8300 has 
#     event 8330 has 
#     event 8350 has 
#     event 8357 has 
#     event 8358 has 
#     event 8363 has 
#     event 8368 has 
#     event 8392 has 
#     event 8397 has 
#     event 8411 has 
#     event 8416 has 
#     event 8428 has 
#     event 8440 has 
#     event 8444 has 
#     event 8488 has 
#     event 8493 has 
#     event 8522 has 
#     event 8542 has 
#     event 8548 has 
#     event 8554 has 
#     event 8566 has 
#     event 8590 has 
#     event 8593 has 
#     event 8599 has 
#     event 8623 has 
#     event 8636 has 
#     event 8649 has 
#     event 8653 has 
#     event 8664 has 
#     event 8702 has 
#     event 8705 has 
#     event 8711 has 
#     event 8717 has 
#     event 8729 has 
#     event 8775 has 
#     event 8787 has 
#     event 8810 has 
#     event 8845 has 
#     event 8894 has 
#     event 8933 has 
#     event 8949 has 
#     event 8952 has 
#     event 8954 has 
#     event 8984 has 
#     event 8985 has 
#     event 8998 has 
#     event 9005 has 
#     event 9015 has 
#     event 9070 has 
#     event 9086 has 
#     event 9113 has 
#     event 9133 has 
#     event 9176 has 
#     event 9192 has 
#     event 9218 has 
#     event 9222 has 
#     event 9269 has 
#     event 9277 has 
#     event 9279 has 
#     event 9280 has 
#     event 9283 has 
#     event 9285 has 
#     event 9286 has 
#     event 9294 has 
#     event 9330 has 
#     event 9349 has 
#     event 9353 has 
#     event 9363 has 
#     event 9367 has 
#     event 9371 has 
#     event 9372 has 
#     event 9393 has 
#     event 9408 has 
#     event 9431 has 
#     event 9450 has 
#     event 9473 has 
#     event 9474 has 
#     event 9488 has 
#     event 9521 has 
#     event 9546 has 
#     event 9574 has 
#     event 9590 has 
#     event 9595 has 
#     event 9600 has 
#     event 9620 has 
#     event 9624 has 
#     event 9631 has 
#     event 9655 has 
#     event 9703 has 
#     event 9728 has 
#     event 9758 has 
#     event 9764 has 
#     event 9770 has 
#     event 9795 has 
#     event 9802 has 
#     event 9807 has 
#     event 9830 has 
#     event 9842 has 
#     event 9888 has 
#     event 9892 has 
#     event 9929 has 
#     event 9931 has 
#     event 9935 has 
#     event 9979 has 
#     event 10002 has 
#     event 10020 has 
#     event 10023 has 
#     event 10053 has 
#     event 10065 has 
#     event 10148 has 
#     event 10150 has 
#     event 10161 has 
#     event 10186 has 
#     event 10190 has 
#     event 10227 has 
#     event 10245 has 
#     event 10313 has 
#     event 10332 has 
#     event 10336 has 
#     event 10345 has 
#     event 10357 has 
#     event 10406 has 
#     event 10420 has 
#     event 10428 has 
#     event 10442 has 
#     event 10443 has 
#     event 10507 has 
#     event 10509 has 
#     event 10510 has 
#     event 10518 has 
#     event 10531 has 
#     event 10546 has 
#     event 10587 has 
#     event 10611 has 
#     event 10619 has 
#     event 10623 has 
#     event 10645 has 
#     event 10650 has 
#     event 10671 has 
#     event 10697 has 
#     event 10712 has 
#     event 10717 has 
#     event 10727 has 
#     event 10762 has 
#     event 10766 has 
#     event 10796 has 
#     event 10799 has 
#     event 10818 has 
#     event 10834 has 
#     event 10838 has 
#     event 10844 has 
#     event 10902 has 
#     event 10915 has 
#     event 10925 has 
#     event 10939 has 
#     event 10941 has 
#     event 10955 has 
#     event 10978 has 
#     event 11004 has 
#     event 11006 has 
#     event 11045 has 
#     event 11067 has 
#     event 11079 has 
#     event 11092 has 
#     event 11107 has 
#     event 11108 has 
#     event 11129 has 
#     event 11150 has 
#     event 11152 has 
#     event 11153 has 
#     event 11195 has 
#     event 11209 has 
#     event 11215 has 
#     event 11276 has 
#     event 11302 has 
#     event 11354 has 
#     event 11370 has 
#     event 11372 has 
#     event 11421 has 
#     event 11422 has 
#     event 11423 has 
#     event 11472 has 
#     event 11478 has 
#     event 11486 has 
#     event 11508 has 
#     event 11525 has 
#     event 11531 has 
#     event 11538 has 
#     event 11560 has 
#     event 11577 has 
#     event 11606 has 
#     event 11618 has 
#     event 11633 has 
#     event 11660 has 
#     event 11742 has 
#     event 11762 has 
#     event 11768 has 
#     event 11783 has 
#     event 11813 has 
#     event 11834 has 
#     event 11846 has 
#     event 11863 has 
#     event 11878 has 
#     event 11900 has 
#     event 11906 has 
#     event 11913 has 
#     event 11915 has 
#     event 11919 has 
#     event 11932 has 
#     event 11970 has 
#     event 11984 has 
#     event 12055 has 
#     event 12077 has 
#     event 12080 has 
#     event 12090 has 
#     event 12095 has 
#     event 12100 has 
#     event 12110 has 
#     event 12140 has 
#     event 12149 has 
#     event 12174 has 
#     event 12176 has 
#     event 12179 has 
#     event 12198 has 
#     event 12201 has 
#     event 12215 has 
#     event 12236 has 
#     event 12259 has 
#     event 12276 has 
#     event 12279 has 
#     event 12294 has 
#     event 12302 has 
#     event 12308 has 
#     event 12314 has 
#     event 12357 has 
#     event 12450 has 
#     event 12451 has 
#     event 12457 has 
#     event 12475 has 
#     event 12502 has 
#     event 12515 has 
#     event 12524 has 
#     event 12545 has 
#     event 12550 has 
#     event 12562 has 
#     event 12603 has 
#     event 12608 has 
#     event 12623 has 
#     event 12632 has 
#     event 12635 has 
#     event 12643 has 
#     event 12655 has 
#     event 12657 has 
#     event 12720 has 
#     event 12727 has 
#     event 12728 has 
#     event 12739 has 
#     event 12752 has 
#     event 12762 has 
#     event 12766 has 
#     event 12780 has 
#     event 12791 has 
#     event 12839 has 
#     event 12851 has 
#     event 12854 has 
#     event 12899 has 
#     event 12934 has 
#     event 12958 has 
#     event 12973 has 
#     event 12984 has 
#     event 12996 has 
#     event 13002 has 
#     event 13006 has 
#     event 13013 has 
#     event 13029 has 
#     event 13045 has 
#     event 13069 has 
#     event 13074 has 
#     event 13096 has 
#     event 13110 has 
#     event 13118 has 
#     event 13134 has 
#     event 13136 has 
#     event 13153 has 
#     event 13160 has 
#     event 13164 has 
#     event 13189 has 
#     event 13222 has 
#     event 13233 has 
#     event 13296 has 
#     event 13309 has 
#     event 13314 has 
#     event 13341 has 
#     event 13377 has 
#     event 13400 has 
#     event 13413 has 
#     event 13444 has 
#     event 13451 has 
#     event 13480 has 
#     event 13502 has 
#     event 13538 has 
#     event 13572 has 
#     event 13589 has 
#     event 13614 has 
#     event 13654 has 
#     event 13659 has 
#     event 13677 has 
#     event 13713 has 
#     event 13757 has 
#     event 13785 has 
#     event 13815 has 
#     event 13833 has 
#     event 13856 has 
#     event 13862 has 
#     event 13896 has 
#     event 13914 has 
#     event 13930 has 
#     event 13964 has 
#     event 13990 has 
#     event 14009 has 
#     event 14028 has 
#     event 14032 has 
#     event 14042 has 
#     event 14048 has 
#     event 14050 has 
#     event 14068 has 
#     event 14081 has 
#     event 14096 has 
#     event 14150 has 
#     event 14238 has 
#     event 14239 has 
#     event 14242 has 
#     event 14250 has 
#     event 14259 has 
#     event 14268 has 
#     event 14283 has 
#     event 14288 has 
#     event 14295 has 
#     event 14319 has 
#     event 14320 has 
#     event 14339 has 
#     event 14365 has 
#     event 14423 has 
#     event 14446 has 
#     event 14506 has 
#     event 14510 has 
#     event 14528 has 
#     event 14585 has 
#     event 14598 has 
#     event 14648 has 
#     event 14667 has 
#     event 14702 has 
#     event 14735 has 
#     event 14744 has 
#     event 14745 has 
#     event 14755 has 
#     event 14762 has 
#     event 14774 has 
#     event 14790 has 
#     event 14818 has 
#     event 14828 has 
#     event 14871 has 
#     event 14878 has 
#     event 14879 has 
#     event 14900 has 
#     event 14911 has 
#     event 14922 has 
#     event 14944 has 
#     event 14962 has 
#     event 14992 has 
#     event 15014 has 
#     event 15017 has 
#     event 15034 has 
#     event 15036 has 
#     event 15062 has 
#     event 15071 has 
#     event 15072 has 
#     event 15110 has 
#     event 15113 has 
#     event 15114 has 
#     event 15120 has 
#     event 15127 has 
#     event 15168 has 
#     event 15222 has 
#     event 15228 has 
#     event 15263 has 
#     event 15285 has 
#     event 15292 has 
#     event 15297 has 
#     event 15385 has 
#     event 15395 has 
#     event 15401 has 
#     event 15443 has 
#     event 15471 has 
#     event 15485 has 
#     event 15513 has 
#     event 15532 has 
#     event 15538 has 
#     event 15584 has 
#     event 15592 has 
#     event 15601 has 
#     event 15609 has 
#     event 15633 has 
#     event 15634 has 
#     event 15664 has 
#     event 15665 has 
#     event 15674 has 
#     event 15726 has 
#     event 15737 has 
#     event 15745 has 
#     event 15763 has 
#     event 15805 has 
#     event 15816 has 
#     event 15853 has 
#     event 15879 has 
#     event 15887 has 
#     event 15908 has 
#     event 15924 has 
#     event 15962 has 
#     event 16014 has 
#     event 16056 has 
#     event 16069 has 
#     event 16120 has 
#     event 16130 has 
#     event 16150 has 
#     event 16156 has 
#     event 16161 has 
#     event 16162 has 
#     event 16164 has 
#     event 16193 has 
#     event 16196 has 
#     event 16198 has 
#     event 16210 has 
#     event 16230 has 
#     event 16321 has 
#     event 16323 has 
#     event 16329 has 
#     event 16331 has 
#     event 16337 has 
#     event 16338 has 
#     event 16341 has 
#     event 16367 has 
#     event 16390 has 
#     event 16405 has 
#     event 16458 has 
#     event 16494 has 
#     event 16522 has 
#     event 16534 has 
#     event 16549 has 
#     event 16553 has 
#     event 16560 has 
#     event 16562 has 
#     event 16573 has 
#     event 16588 has 
#     event 16592 has 
#     event 16596 has 
#     event 16625 has 
#     event 16634 has 
#     event 16687 has 
#     event 16688 has 
#     event 16689 has 
#     event 16718 has 
#     event 16724 has 
#     event 16748 has 
#     event 16802 has 
#     event 16805 has 
#     event 16815 has 
#     event 16825 has 
#     event 16831 has 
#     event 16857 has 
#     event 16864 has 
#     event 16880 has 
#     event 16904 has 
#     event 16909 has 
#     event 16952 has 
#     event 16960 has 
#     event 16963 has 
#     event 16978 has 
#     event 16990 has 
#     event 17006 has 
#     event 17047 has 
#     event 17060 has 
#     event 17070 has 
#     event 17090 has 
#     event 17110 has 
#     event 17130 has 
#     event 17137 has 
#     event 17206 has 
#     event 17214 has 
#     event 17228 has 
#     event 17262 has 
#     event 17274 has 
#     event 17283 has 
#     event 17312 has 
#     event 17323 has 
#     event 17334 has 
#     event 17336 has 
#     event 17354 has 
#     event 17408 has 
#     event 17411 has 
#     event 17434 has 
#     event 17437 has 
#     event 17438 has 
#     event 17497 has 
#     event 17501 has 
#     event 17574 has 
#     event 17614 has 
#     event 17644 has 
#     event 17648 has 
#     event 17669 has 
#     event 17697 has 
#     event 17758 has 
#     event 17764 has 
#     event 17817 has 
#     event 17819 has 
#     event 17829 has 
#     event 17845 has 
#     event 17875 has 
#     event 17909 has 
#     event 17910 has 
#     event 17918 has 
#     event 17925 has 
#     event 17940 has 
#     event 17964 has 
#     event 17987 has 
#     event 18019 has 
#     event 18040 has 
#     event 18046 has 
#     event 18049 has 
#     event 18051 has 
#     event 18095 has 
#     event 18132 has 
#     event 18146 has 
#     event 18154 has 
#     event 18157 has 
#     event 18198 has 
#     event 18208 has 
#     event 18210 has 
#     event 18251 has 
#     event 18276 has 
#     event 18293 has 
#     event 18299 has 
#     event 18300 has 
#     event 18327 has 
#     event 18345 has 
#     event 18384 has 
#     event 18385 has 
#     event 18393 has 
#     event 18426 has 
#     event 18467 has 
#     event 18473 has 
#     event 18529 has 
#     event 18536 has 
#     event 18574 has 
#     event 18578 has 
#     event 18654 has 
#     event 18667 has 
#     event 18696 has 
#     event 18706 has 
#     event 18728 has 
#     event 18762 has 
#     event 18763 has 
#     event 18773 has 
#     event 18808 has 
#     event 18809 has 
#     event 18823 has 
#     event 18880 has 
#     event 18921 has 
#     event 18929 has 
#     event 18986 has 
#     event 19004 has 
#     event 19061 has 
#     event 19069 has 
#     event 19087 has 
#     event 19088 has 
#     event 19098 has 
#     event 19103 has 
#     event 19107 has 
#     event 19134 has 
#     event 19135 has 
#     event 19149 has 
#     event 19181 has 
#     event 19188 has 
#     event 19206 has 
#     event 19245 has 
#     event 19246 has 
#     event 19266 has 
#     event 19314 has 
#     event 19354 has 
#     event 19403 has 
#     event 19451 has 
#     event 19477 has 
#     event 19497 has 
#     event 19531 has 
#     event 19539 has 
#     event 19548 has 
#     event 19556 has 
#     event 19561 has 
#     event 19571 has 
#     event 19583 has 
#     event 19601 has 
#     event 19629 has 
#     event 19630 has 
#     event 19681 has 
#     event 19689 has 
#     event 19719 has 
#     event 19758 has 
#     event 19777 has 
#     event 19820 has 
#     event 19826 has 
#     event 19836 has 
#     event 19844 has 
#     event 19850 has 
#     event 19917 has 
#     event 19925 has 
#     event 19931 has 
#     event 19944 has 
#     event 19962 has 
#     event 20037 has 
#     event 20041 has 
#     event 20125 has 
#     event 20162 has 
#     event 20165 has 
#     event 20197 has 
#     event 20220 has 
#     event 20234 has 
#     event 20241 has 
#     event 20262 has 
#     event 20285 has 
#     event 20316 has 
#     event 20342 has 
#     event 20374 has 
#     event 20378 has 
#     event 20383 has 
#     event 20399 has 
#     event 20415 has 
#     event 20419 has 
#     event 20431 has 
#     event 20436 has 
#     event 20443 has 
#     event 20505 has 
#     event 20507 has 
#     event 20529 has 
#     event 20539 has 
#     event 20547 has 
#     event 20570 has 
#     event 20589 has 
#     event 20595 has 
#     event 20682 has 
#     event 20690 has 
#     event 20700 has 
#     event 20708 has 
#     event 20718 has 
#     event 20722 has 
#     event 20723 has 
#     event 20743 has 
#     event 20755 has 
#     event 20764 has 
#     event 20800 has 
#     event 20853 has 
#     event 20855 has 
#     event 20864 has 
#     event 20868 has 
#     event 20883 has 
#     event 20904 has 
#     event 20919 has 
#     event 20925 has 
#     event 20946 has 
#     event 20961 has 
#     event 21001 has 
#     event 21024 has 
#     event 21029 has 
#     event 21056 has 
#     event 21061 has 
#     event 21073 has 
#     event 21116 has 
#     event 21120 has 
#     event 21121 has 
#     event 21127 has 
#     event 21146 has 
#     event 21164 has 
#     event 21167 has 
#     event 21168 has 
#     event 21169 has 
#     event 21235 has 
#     event 21257 has 
#     event 21264 has 
#     event 21284 has 
#     event 21355 has 
#     event 21370 has 
#     event 21379 has 
#     event 21405 has 
#     event 21416 has 
#     event 21431 has 
#     event 21435 has 
#     event 21450 has 
#     event 21486 has 
#     event 21499 has 
#     event 21519 has 
#     event 21530 has 
#     event 21558 has 
#     event 21589 has 
#     event 21631 has 
#     event 21645 has 
#     event 21665 has 
#     event 21678 has 
#     event 21707 has 
#     event 21744 has 
#     event 21753 has 
#     event 21758 has 
#     event 21761 has 
#     event 21768 has 
#     event 21807 has 
#     event 21819 has 
#     event 21824 has 
#     event 21826 has 
#     event 21833 has 
#     event 21844 has 
#     event 21949 has 
#     event 21953 has 
#     event 21956 has 
#     event 21964 has 
#     event 21989 has 
#     event 21996 has 
#     event 21997 has 
#     event 22035 has 
#     event 22051 has 
#     event 22059 has 
#     event 22083 has 
#     event 22086 has 
#     event 22093 has 
#     event 22119 has 
#     event 22131 has 
#     event 22135 has 
#     event 22184 has 
#     event 22207 has 
#     event 22217 has 
#     event 22264 has 
#     event 22287 has 
#     event 22345 has 
#     event 22356 has 
#     event 22377 has 
#     event 22398 has 
#     event 22402 has 
#     event 22410 has 
#     event 22423 has 
#     event 22446 has 
#     event 22449 has 
#     event 22451 has 
#     event 22464 has 
#     event 22472 has 
#     event 22482 has 
#     event 22495 has 
#     event 22505 has 
#     event 22520 has 
#     event 22548 has 
#     event 22554 has 
#     event 22557 has 
#     event 22564 has 
#     event 22579 has 
#     event 22612 has 
#     event 22613 has 
#     event 22645 has 
#     event 22665 has 
#     event 22668 has 
#     event 22674 has 
#     event 22675 has 
#     event 22707 has 
#     event 22711 has 
#     event 22712 has 
#     event 22713 has 
#     event 22744 has 
#     event 22745 has 
#     event 22760 has 
#     event 22787 has 
#     event 22791 has 
#     event 22795 has 
#     event 22813 has 
#     event 22870 has 
#     event 22914 has 
#     event 22920 has 
#     event 22936 has 
#     event 22979 has 
#     event 23027 has 
#     event 23036 has 
#     event 23059 has 
#     event 23075 has 
#     event 23092 has 
#     event 23095 has 
#     event 23103 has 
#     event 23118 has 
#     event 23123 has 
#     event 23129 has 
#     event 23167 has 
#     event 23188 has 
#     event 23203 has 
#     event 23232 has 
#     event 23249 has 
#     event 23296 has 
#     event 23314 has 
#     event 23381 has 
#     event 23400 has 
#     event 23429 has 
#     event 23437 has 
#     event 23465 has 
#     event 23477 has 
#     event 23478 has 
#     event 23515 has 
#     event 23529 has 
#     event 23541 has 
#     event 23567 has 
#     event 23600 has 
#     event 23613 has 
#     event 23617 has 
#     event 23620 has 
#     event 23624 has 
#     event 23625 has 
#     event 23659 has 
#     event 23681 has 
#     event 23701 has 
#     event 23727 has 
#     event 23731 has 
#     event 23739 has 
#     event 23783 has 
#     event 23790 has 
#     event 23793 has 
#     event 23831 has 
#     event 23833 has 
#     event 23834 has 
#     event 23836 has 
#     event 23840 has 
#     event 23860 has 
#     event 23924 has 
#     event 23940 has 
#     event 23945 has 
#     event 23967 has 
#     event 23971 has 
#     event 23990 has 
#     event 23994 has 
#     event 23996 has 
#     event 24053 has 
#     event 24078 has 
#     event 24128 has 
#     event 24136 has 
#     event 24161 has 
#     event 24165 has 
#     event 24182 has 
#     event 24222 has 
#     event 24229 has 
#     event 24252 has 
#     event 24253 has 
#     event 24270 has 
#     event 24314 has 
#     event 24322 has 
#     event 24345 has 
#     event 24349 has 
#     event 24383 has 
#     event 24410 has 
#     event 24431 has 
#     event 24443 has 
#     event 24485 has 
#     event 24510 has 
#     event 24516 has 
#     event 24525 has 
#     event 24526 has 
#     event 24557 has 
#     event 24559 has 
#     event 24570 has 
#     event 24571 has 
#     event 24576 has 
#     event 24580 has 
#     event 24609 has 
#     event 24626 has 
#     event 24634 has 
#     event 24635 has 
#     event 24639 has 
#     event 24651 has 
#     event 24656 has 
#     event 24706 has 
#     event 24717 has 
#     event 24727 has 
#     event 24742 has 
#     event 24763 has 
#     event 24781 has 
#     event 24814 has 
#     event 24818 has 
#     event 24823 has 
#     event 24824 has 
#     event 24879 has 
#     event 24897 has 
#     event 24906 has 
#     event 24953 has 
#     event 24957 has 
#     event 24971 has 
#     event 24981 has 
#     event 24983 has 
#     event 25009 has 
#     event 25012 has 
#     event 25045 has 
#     event 25046 has 
#     event 25047 has 
#     event 25056 has 
#     last is 25099
# 121969 25099

# Run 123013:
#     last is 37841
# 123013 37841

# Run 122808:
#     last is 30490
# 122808 30490

# Run 124708:
#     last is 239615
# 124708 239615

# Run 123638:
#     last is 28927
# 123638 28927

# Run 126906:
#     last is 24052
# 126906 24052

# Run 126521:
#     last is 36635
# 126521 36635

# Run 126531:
#     event 20882 has 
#     event 20883 has 
#     event 20884 has 
#     last is 20908
# 126531 20908

# Run 130268:
#     last is 31321
# 130268 31321

# Run 130316:
#     last is 22670
# 130316 22670

# Run 127318:
#     last is 26867
# 127318 26867

# Run 129850:
#     last is 56545
# 129850 56545

# Run 129674:
#     event 1677 has 
#     last is 25696
# 129674 25696

# Run 127955:
#     last is 34112
# 127955 34112

# Run 127418:
#     event 26377 has 
#     event 26378 has 
#     event 26379 has 
#     event 26382 has 
#     event 26398 has 
#     event 26399 has 
#     event 26450 has 
#     event 26453 has 
#     event 26454 has 
#     event 26456 has 
#     event 26459 has 
#     event 26462 has 
#     event 26465 has 
#     event 26466 has 
#     event 26470 has 
#     event 26471 has 
#     event 26472 has 
#     event 26945 has 
#     event 26946 has 
#     event 26947 has 
#     event 26954 has 
#     event 26966 has 
#     event 26967 has 
#     event 26971 has 
#     event 26973 has 
#     event 26976 has 
#     event 26983 has 
#     event 26988 has 
#     event 26991 has 
#     event 27228 has 
#     event 27234 has 
#     event 27235 has 
#     event 27236 has 
#     event 27239 has 
#     event 27240 has 
#     event 27243 has 
#     event 27247 has 
#     event 27248 has 
#     event 27249 has 
#     event 27251 has 
#     event 27252 has 
#     event 27253 has 
#     event 27257 has 
#     event 27258 has 
#     event 27259 has 
#     event 27261 has 
#     event 27262 has 
#     event 27263 has 
#     event 27264 has 
#     event 27266 has 
#     event 27267 has 
#     event 27268 has 
#     event 27269 has 
#     event 27271 has 
#     event 27272 has 
#     event 27273 has 
#     event 27274 has 
#     event 27275 has 
#     event 27276 has 
#     event 27277 has 
#     event 27279 has 
#     event 27280 has 
#     event 27281 has 
#     event 27282 has 
#     event 27284 has 
#     event 27285 has 
#     event 27286 has 
#     event 27287 has 
#     event 27288 has 
#     event 27289 has 
#     event 27290 has 
#     event 27291 has 
#     event 27293 has 
#     event 27294 has 
#     event 27295 has 
#     event 27296 has 
#     event 27297 has 
#     event 27298 has 
#     event 27299 has 
#     event 27300 has 
#     event 27301 has 
#     event 27302 has 
#     event 27303 has 
#     event 27304 has 
#     event 27305 has 
#     event 27306 has 
#     event 27307 has 
#     event 27311 has 
#     event 27312 has 
#     event 27313 has 
#     event 27314 has 
#     event 27315 has 
#     event 27316 has 
#     event 27317 has 
#     event 27323 has 
#     event 27326 has 
#     event 27327 has 
#     event 27328 has 
#     event 27329 has 
#     event 27334 has 
#     event 27340 has 
#     event 27341 has 
#     event 27344 has 
#     event 27345 has 
#     event 27346 has 
#     event 27347 has 
#     event 27348 has 
#     event 27357 has 
#     event 27362 has 
#     event 27364 has 
#     event 27365 has 
#     event 27366 has 
#     event 27368 has 
#     event 27371 has 
#     event 27372 has 
#     event 27373 has 
#     event 27376 has 
#     event 27377 has 
#     event 27378 has 
#     event 27380 has 
#     event 27381 has 
#     event 27382 has 
#     event 27383 has 
#     event 27384 has 
#     event 27385 has 
#     event 27386 has 
#     event 27388 has 
#     event 27389 has 
#     event 27390 has 
#     event 27392 has 
#     event 27395 has 
#     event 27397 has 
#     event 27399 has 
#     event 27404 has 
#     event 27405 has 
#     event 27406 has 
#     event 27407 has 
#     event 27408 has 
#     event 27409 has 
#     event 27410 has 
#     event 27413 has 
#     event 27414 has 
#     event 27415 has 
#     event 27416 has 
#     event 27418 has 
#     event 27419 has 
#     event 27421 has 
#     event 27422 has 
#     event 27424 has 
#     event 27426 has 
#     event 27427 has 
#     event 27428 has 
#     event 27429 has 
#     event 27430 has 
#     event 27431 has 
#     event 27432 has 
#     event 27433 has 
#     event 27434 has 
#     event 27436 has 
#     event 27437 has 
#     event 27438 has 
#     event 27439 has 
#     event 27440 has 
#     event 27441 has 
#     event 27442 has 
#     event 27443 has 
#     event 27444 has 
#     event 27445 has 
#     event 27446 has 
#     event 27447 has 
#     event 27448 has 
#     event 27449 has 
#     last is 27450
# 127418 27474

