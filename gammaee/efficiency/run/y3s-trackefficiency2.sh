#!/usr/bin/sh

paw << EOF
0
h/file 1 /cdat/sol300/disk5/mccann/mcres16_01-track.rzn
h/file 2 /cdat/sol300/disk5/mccann/mcres17_01-track.rzn
h/file 3 y3s-trackhistos.rzn ! 'N'
cd //lun1/trackefficiency
exec trackefficiency_macros#fillhistograms 1
cd //lun3
exec trackefficiency_macros#writehistograms 1
cd //lun2/trackefficiency
exec trackefficiency_macros#fillhistograms 2
cd //lun3
exec trackefficiency_macros#writehistograms 2
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y3s-nov29-01-peak.rzn
h/file 3 y3s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 3
cd //lun3
exec trackefficiency_macros#writehistograms 3
exit
EOF

paw << EOF
0
h/file 31 /cdat/sol300/disk5/mccann/y3s-dec06-01-peak.rzn
h/file 3 y3s-trackhistos.rzn ! 'U'
cd //lun31/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 4
cd //lun3
exec trackefficiency_macros#writehistograms 4
exit
EOF

paw << EOF
0
h/file 32 /cdat/sol300/disk5/mccann/y3s-dec13-01-peak.rzn
h/file 3 y3s-trackhistos.rzn ! 'U'
cd //lun32/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 5
cd //lun3
exec trackefficiency_macros#writehistograms 5
exit
EOF

paw << EOF
0
h/file 33 /cdat/sol300/disk5/mccann/y3s-dec20-01-peak.rzn
h/file 3 y3s-trackhistos.rzn ! 'U'
cd //lun33/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 6
cd //lun3
exec trackefficiency_macros#writehistograms 6
exit
EOF

paw << EOF
0
h/file 34 /cdat/sol300/disk5/mccann/y3s-dec25-01-peak.rzn
h/file 3 y3s-trackhistos.rzn ! 'U'
cd //lun34/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 7
cd //lun3
exec trackefficiency_macros#writehistograms 7
exit
EOF

paw << EOF
0
h/file 35 /cdat/sol300/disk5/mccann/y3s-jan03-02-peak.rzn
h/file 3 y3s-trackhistos.rzn ! 'U'
cd //lun35/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 8
cd //lun3
exec trackefficiency_macros#writehistograms 8
exit
EOF

paw << EOF
0
h/file 36 /cdat/sol300/disk5/mccann/y3s-jan10-02-peak.rzn
h/file 3 y3s-trackhistos.rzn ! 'U'
cd //lun36/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 9
cd //lun3
exec trackefficiency_macros#writehistograms 9
exit
EOF

