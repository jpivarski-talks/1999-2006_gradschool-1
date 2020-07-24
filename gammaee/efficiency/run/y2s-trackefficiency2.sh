#!/usr/bin/sh

paw << EOF
0
h/file 1 /cdat/sol300/disk5/mccann/mcres16_01-track.rzn
h/file 2 /cdat/sol300/disk5/mccann/mcres17_01-track.rzn
h/file 3 y2s-trackhistos.rzn ! 'N'
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
h/file 30 /cdat/sol300/disk5/mccann/y2s-may28-02-peak.rzn
h/file 3 y2s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 3
cd //lun3
exec trackefficiency_macros#writehistograms 3
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y2s-jun11-02-peak.rzn
h/file 3 y2s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 4
cd //lun3
exec trackefficiency_macros#writehistograms 4
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y2s-jun28-02-peak.rzn
h/file 3 y2s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 5
cd //lun3
exec trackefficiency_macros#writehistograms 5
exit
EOF

