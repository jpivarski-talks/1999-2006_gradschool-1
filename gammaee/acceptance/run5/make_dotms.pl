#!/usr/local/bin/perl

foreach $name ("all1_bblumi_normcc",
	       "all1_gglumi_normcc",
	       "all2_bblumi_normcc",
	       "all2_gglumi_normcc",
	       "all3_bblumi_normcc",
	       "all3_gglumi_normcc",
	       "db16_bblumi_normcc",
	       "db16_gglumi_normcc",
	       "db17_bblumi_normcc",
	       "db17_gglumi_normcc",
	       "db18_bblumi_normcc",
	       "db18_gglumi_normcc",
	       "db19_bblumi_normcc",
	       "db19_gglumi_normcc",
	       "db21_bblumi_normcc",
	       "db21_gglumi_normcc",
	       "db23_bblumi_normcc",
	       "db23_gglumi_normcc",
	       "big3_bblumi_normcc",
	       "big3_gglumi_normcc",
	       "small3_bblumi_normcc",
	       "small3_gglumi_normcc",
	       
	       "all1_bblumi_coolcc",
	       "all1_gglumi_coolcc",
	       "all2_bblumi_coolcc",
	       "all2_gglumi_coolcc",
	       "all3_bblumi_coolcc",
	       "all3_gglumi_coolcc",
	       "db16_bblumi_coolcc",
	       "db16_gglumi_coolcc",
	       "db17_bblumi_coolcc",
	       "db17_gglumi_coolcc",
	       "db18_bblumi_coolcc",
	       "db18_gglumi_coolcc",
	       "db19_bblumi_coolcc",
	       "db19_gglumi_coolcc",
	       "db21_bblumi_coolcc",
	       "db21_gglumi_coolcc",
	       "db23_bblumi_coolcc",
	       "db23_gglumi_coolcc",
	       "big3_bblumi_coolcc",
	       "big3_gglumi_coolcc",
	       "small3_bblumi_coolcc",
	       "small3_gglumi_coolcc",
	       
	       "all1_bblumi_aggrcc",
	       "all1_gglumi_aggrcc",
	       "all2_bblumi_aggrcc",
	       "all2_gglumi_aggrcc",
	       "all3_bblumi_aggrcc",
	       "all3_gglumi_aggrcc",
	       "db16_bblumi_aggrcc",
	       "db16_gglumi_aggrcc",
	       "db17_bblumi_aggrcc",
	       "db17_gglumi_aggrcc",
	       "db18_bblumi_aggrcc",
	       "db18_gglumi_aggrcc",
	       "db19_bblumi_aggrcc",
	       "db19_gglumi_aggrcc",
	       "db21_bblumi_aggrcc",
	       "db21_gglumi_aggrcc",
	       "db23_bblumi_aggrcc",
	       "db23_gglumi_aggrcc",
	       "big3_bblumi_aggrcc",
	       "big3_gglumi_aggrcc",
	       "small3_bblumi_aggrcc",
	       "small3_gglumi_aggrcc",
	       ) {

    open(NAME, "> $name.m");
    $truth = "True";
    $truth = "False" if $name =~ /gglumi/;

    print NAME "<< classic_plots_and_tables.m

isbblumi = $truth;
RunThrough[\"perl mathemetize_table.pl $name.table\", Null];
wholeblock[1000];
DumpSave[\"$name.mx\", {themc, errmc, thedata, errdata1, errdata2}];
plotagreement[\"$name.eps\", 110, 101, 92, 80];
";
}
