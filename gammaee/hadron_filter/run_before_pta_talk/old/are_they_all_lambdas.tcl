exception continueEventLoop on

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in

prod sel MCInfoDelivery

source_format sel PDSSourceFormat
#  source create pdschain
#  file add pdschain ../gamgam/run121916/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121917/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121919/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121920/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121921/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121923/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121926/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121927/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121928/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121931/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121932/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121933/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121934/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121935/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121938/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121939/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121960/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121966/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121967/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121968/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121969/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121970/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121971/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121972/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121973/cleog.pds event startrun beginrun endrun physics
#  file add pdschain ../gamgam/run121974/cleog.pds event startrun beginrun endrun physics

file in /home/chengp/build3/OSF1/cxx/tmp/test_cleog.pds event startrun beginrun endrun physics

proc sel ../build_OSF1/shlib/PrintOutProc

go
exit
