#!/usr/local/bin/perl

%lumi = (
	 124080 => [1012.0, 8.3],
	 124081 => [1067.2, 8.5],
	 124083 => [172.6, 3.4],
	 124084 => [903.0, 7.8],
	 124085 => [967.0, 8.1],
	 124086 => [855.2, 7.6],
	 124087 => [926.8, 7.9],
	 124088 => [161.3, 3.3],
	 124089 => [527.5, 6.0],
	 124091 => [1095.4, 8.6],
	 124092 => [636.3, 6.6],
	 124102 => [2419.1, 12.8],
	 124103 => [617.0, 6.5],
	 124106 => [584.2, 6.3],
	 124107 => [545.5, 6.1],
	 124109 => [543.3, 6.1],
	 124110 => [602.9, 6.4],
	 124111 => [969.8, 8.1],
	 124112 => [857.1, 7.6],
	 124113 => [1481.3, 10.0],
	 124114 => [1833.7, 11.1],
	 124115 => [1856.2, 11.2],
	 124117 => [418.0, 5.3],
	 124118 => [76.4, 2.3],
	 124119 => [226.0, 3.9],
	 124121 => [990.1, 8.2],
	 124122 => [174.4, 3.4],
	 124123 => [1801.3, 11.0],
	 124125 => [1871.1, 11.2],
	 124126 => [1659.3, 10.6],
	 124127 => [1905.2, 11.3],
	 124128 => [1797.5, 11.0],
	 124129 => [1855.4, 11.2],
	 124132 => [976.8, 8.1],
	 124134 => [921.8, 7.9],
	 124137 => [1863.7, 11.2],
	 124138 => [1918.6, 11.4],
	 124139 => [1904.4, 11.3],
	 124140 => [1831.4, 11.1],
	 124141 => [1852.4, 11.2],
	 124142 => [338.3, 4.8],
	 124144 => [1704.1, 10.7],
	 124146 => [1106.2, 8.6],
	 124148 => [367.5, 5.0],
	 124149 => [832.9, 7.5],
	 124150 => [1672.8, 10.6],
	 124152 => [1902.6, 11.3],
	 124153 => [1869.3, 11.2],
	 124154 => [1804.9, 11.0],
	 124155 => [544.6, 6.1],
	 124156 => [1904.4, 11.3],
	 124158 => [170.7, 3.4],
	 124159 => [1061.8, 8.5],
	 124161 => [1408.5, 9.8],
	 124162 => [1728.9, 10.8],
	 124163 => [1203.1, 9.0],
	 124164 => [171.3, 3.4],
	 124165 => [1882.0, 11.3],
	 124166 => [1841.3, 11.2],
	 124167 => [1752.8, 10.9],
	 124170 => [1203.0, 9.0],
	 124171 => [1820.6, 11.1],
	 124172 => [2134.2, 12.0],
	 124173 => [2275.9, 12.4],
	 124174 => [2259.8, 12.4],
	 124175 => [2313.1, 12.5],
	 124176 => [2235.2, 12.3],
	 124177 => [2039.0, 11.7],
	 124178 => [414.8, 5.3],
	 124179 => [2178.3, 12.1],
	 124181 => [1815.9, 11.1],
	 124185 => [863.8, 7.6],
	 124186 => [1958.9, 11.5],
	 124187 => [2237.9, 12.3],
	 124188 => [1604.7, 10.4],
	 124190 => [2160.8, 12.1],
	 124192 => [2109.8, 11.9],
	 124193 => [2213.4, 12.2],
	 124194 => [2216.4, 12.2],
	 124195 => [2259.1, 12.4],
	 124196 => [2241.3, 12.3],
	 124197 => [2012.1, 11.7],
	 124200 => [479.5, 5.7],
	 124201 => [1175.4, 8.9],
	 124202 => [2186.7, 12.2],
	 124203 => [49.8, 1.8],
	 124205 => [1910.4, 11.4],
	 124206 => [78.2, 2.3],
	 124208 => [1613.0, 10.4],
	 124209 => [1993.2, 11.6],
	 124210 => [1818.4, 11.1],
	 124212 => [1974.9, 11.6],
	 124213 => [1963.6, 11.5],
	 124214 => [2489.4, 13.0]
	 );

%energy = (
	   124080 => 4.72846,
	   124081 => 4.73792,
	   124084 => 4.72597,
	   124085 => 4.73585,
	   124086 => 4.72684,
	   124087 => 4.73391,
	   124089 => 4.73190,
	   124091 => 4.72830,
	   124092 => 4.73028,
	   124102 => 4.72830,
	   124103 => 4.73791,
	   124106 => 4.73600,
	   124107 => 4.72680,
	   124109 => 4.73390,
	   124110 => 4.73184,
	   124111 => 4.72842,
	   124112 => 4.73023,
	   124113 => 4.71668,
	   124114 => 4.71671,
	   124115 => 4.71671,
	   124117 => 4.71674,
	   124118 => 4.71668,
	   124119 => 4.71671,
	   124121 => 4.71671,
	   124122 => 4.71671,
	   124123 => 4.71671,
	   124125 => 4.71668,
	   124126 => 4.71671,
	   124127 => 4.71671,
	   124128 => 4.71671,
	   124129 => 4.71671,
	   124132 => 4.71671,
	   124134 => 4.71671,
	   124137 => 4.71674,
	   124138 => 4.71674,
	   124139 => 4.71674,
	   124140 => 4.71674,
	   124141 => 4.71674,
	   124142 => 4.73021,
	   124144 => 4.73023,
	   124146 => 4.73029,
	   124149 => 4.73027,
	   124150 => 4.73029,
	   124152 => 4.73029,
	   124153 => 4.73033,
	   124154 => 4.73032,
	   124155 => 4.73032,
	   124156 => 4.73035,
	   124158 => 4.73032,
	   124159 => 4.73036,
	   124162 => 4.73035,
	   124164 => 4.73038,
	   124165 => 4.73033,
	   124166 => 4.73039,
	   124167 => 4.73038,
	   124170 => 4.73038,
	   124171 => 4.73039,
	   124172 => 4.73038,
	   124173 => 4.73035,
	   124174 => 4.73039,
	   124175 => 4.73041,
	   124176 => 4.73041,
	   124177 => 4.73041,
	   124178 => 4.73044,
	   124179 => 4.73040,
	   124181 => 4.73041,
	   124185 => 4.73043,
	   124186 => 4.73044,
	   124188 => 4.73043,
	   124190 => 4.73043,
	   124192 => 4.73043,
	   124193 => 4.73043,
	   124194 => 4.73043
	   );

while ( <> ) {
    chop;
    my ($run, $number, $stat, $syst) = split(/\s+/);

#     $number += $syst;
#     $number -= $syst;

    die if ( !defined($energy{$run}) );
    $en = 2000. * $energy{$run};

    die if ( !defined($lumi{$run}) );
    my $l = $lumi{$run}->[0];
    my $le = $lumi{$run}->[1];

    my $hxc = $number / $l;
    my $hxce = $hxc * sqrt(($stat/$number)*($stat/$number) + ($le/$l)*($le/$l));

    print("$en $hxc $hxce\n");
}
