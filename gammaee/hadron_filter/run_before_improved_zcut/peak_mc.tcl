default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/peak_mc.rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) meta FieldMap MetaListRetrieval

source_format sel MagFudgeFileSourceFormat
file in normal.magfudge

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
prod sel MagFieldProd
prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121339_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121340_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121343_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121344_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121346_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121348_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121349_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121361_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121362_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121365_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121369_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121370_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121373_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121374_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121375_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121378_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121379_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121381_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121382_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121384_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121385_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121387_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121390_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121391_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121394_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121395_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121396_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121397_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121398_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121399_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121400_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121401_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121402_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121406_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121407_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121408_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121409_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121414_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121416_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121418_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121419_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121420_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121421_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121422_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121424_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121425_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121426_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121427_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121428_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121429_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121430_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121432_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121433_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121434_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121435_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121436_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121437_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121441_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121442_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121446_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121448_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121449_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121454_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121456_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121458_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121459_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121474_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121476_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121477_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121479_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121480_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121519_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121523_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121525_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121526_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121527_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121528_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121529_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121530_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121531_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121534_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121535_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121536_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121539_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121540_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121542_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121543_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121544_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121545_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121547_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121548_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121549_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121550_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121551_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121552_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121553_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121554_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121555_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121556_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121557_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121558_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121559_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121560_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121561_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121563_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121565_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121567_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121568_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121569_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121574_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121576_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121579_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121580_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121581_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121582_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121585_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121588_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121590_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121592_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121593_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121595_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121608_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121609_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121623_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121624_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121626_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121628_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121631_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121633_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121636_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121637_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121638_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121639_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121640_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121641_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121649_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121650_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121651_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121652_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121653_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121656_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121678_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121681_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121683_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121684_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121687_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121688_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121689_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121694_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121698_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121704_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121705_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121706_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121707_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121708_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121710_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121711_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121713_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121714_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121715_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121716_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121718_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121721_cu_1_pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol197/disk1/c3mc/data16/ups3s/output/ups3s_121722_cu_1_pass2.pds event startrun beginrun endrun physics

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize 100000
param HadronFilterProc noBeamSpot true
param HadronFilterProc beamSpotX 0.18e-3
param HadronFilterProc beamSpotY 0.
param HadronFilterProc fillBuffer false
go

hbook terminate
exit
