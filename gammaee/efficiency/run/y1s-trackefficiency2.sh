#!/usr/bin/sh

paw << EOF
0
h/file 1 /cdat/sol300/disk5/mccann/mcres16_01-track.rzn
h/file 2 /cdat/sol300/disk5/mccann/mcres17_01-track.rzn
h/file 3 y1s-trackhistos.rzn ! 'N'
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
h/file 30 /cdat/sol300/disk5/mccann/y1s-jan16-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 3
cd //lun3
exec trackefficiency_macros#writehistograms 3
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-jan30-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 4
cd //lun3
exec trackefficiency_macros#writehistograms 4
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-feb06-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 5
cd //lun3
exec trackefficiency_macros#writehistograms 5
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-feb14-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 6
cd //lun3
exec trackefficiency_macros#writehistograms 6
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-feb20-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 7
cd //lun3
exec trackefficiency_macros#writehistograms 7
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-feb28-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 8
cd //lun3
exec trackefficiency_macros#writehistograms 8
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-mar06-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 9
cd //lun3
exec trackefficiency_macros#writehistograms 9
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-mar14-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 10
cd //lun3
exec trackefficiency_macros#writehistograms 10
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-mar21-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 11
cd //lun3
exec trackefficiency_macros#writehistograms 11
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-apr02-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 12
cd //lun3
exec trackefficiency_macros#writehistograms 12
exit
EOF

paw << EOF
0
h/file 30 /cdat/sol300/disk5/mccann/y1s-apr08-02-peak.rzn
h/file 3 y1s-trackhistos.rzn ! 'U'
cd //lun30/trackefficiency
nt/recover 1
exec trackefficiency_macros#fillhistograms 13
cd //lun3
exec trackefficiency_macros#writehistograms 13
exit
EOF

