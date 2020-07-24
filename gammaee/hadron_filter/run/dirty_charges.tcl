default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/dirty_charges.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

proc sel ../build_SunOS/shlib/DirtyCharges

proc sel HistogramViewerProc

module sel DBModule
database in /nfs/cleo3/database/data16/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122080
go
database run 122081
go
database run 122082
go
database run 122083
go
database run 122085
go
database run 122086
go
database run 122090
go
database run 122091
go
database run 121899
go
database run 121901
go
database run 121902
go
database run 121903
go
database run 121904
go
database run 121905
go
database run 121906
go
database run 121909
go
database run 121911
go
database run 121912
go
database run 121914
go
database run 121915
go

database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122264
go
database run 122268
go
database run 122269
go
database run 122272
go
database run 122273
go
database run 122418
go
database run 122420
go
database run 122421
go
database run 122422
go
database run 122423
go
database run 122424
go
database run 122425
go
database run 122426
go
database run 122427
go
database run 122428
go
database run 122429
go
database run 122430
go
database run 122432
go
database run 122433
go
database run 122434
go
database run 122585
go
database run 122586
go
database run 122587
go
database run 122588
go
database run 122590
go
database run 122593
go
database run 122594
go
database run 122595
go
database run 122596
go
database run 122599
go
database run 122600
go
database run 122601
go
database run 122602
go
database run 122603
go
database run 122604
go
database run 122605
go
database run 122606
go
database run 122783
go
database run 122784
go
database run 122786
go
database run 122789
go
database run 122796
go
database run 122797
go
database run 122798
go
database run 122799
go
database run 122800
go
database run 122801
go
database run 122802
go
database run 122803
go
database run 122804
go
database run 122805
go
database run 122807
go
database run 122808
go
database run 122809
go
database run 122810
go
database run 123011
go
database run 123012
go
database run 123013
go
database run 123014
go
database run 123015
go
database run 123016
go
database run 123018
go
database run 123019
go

hbook terminate
exit
