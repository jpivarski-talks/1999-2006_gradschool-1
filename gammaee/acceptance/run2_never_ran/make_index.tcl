default prompt off
exception continueEventLoop on

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 hadron
database run $env(USER_RUN)

sink_format sel IndexAsciiSinkFormat
file sink ../idxa/$env(USER_DIR)/r$env(USER_RUN).idxa event

proc sel ../build_SunOS/shlib/Trivial
go
exit
