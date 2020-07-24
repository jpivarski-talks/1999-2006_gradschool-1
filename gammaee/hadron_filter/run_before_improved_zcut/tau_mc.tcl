default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/tau_mc.rzn
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
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121339-E523-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121340-E792-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121343-E629-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121344-E915-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121346-E1003-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121347-E803-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121348-E1523-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121349-E3269-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121361-E1720-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121362-E835-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121365-E3077-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121369-E2219-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121370-E3355-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121373-E1328-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121374-E2245-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121375-E1888-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121378-E1371-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121379-E1819-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121381-E3845-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121382-E861-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121384-E1611-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121385-E3987-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121387-E4155-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121390-E3443-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121391-E3651-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121394-E3995-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121395-E3784-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121396-E3859-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121397-E3971-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121398-E3957-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121399-E603-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121400-E1301-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121401-E1509-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121402-E2835-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121406-E4275-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121407-E3808-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121408-E4675-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121409-E4443-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121414-E2323-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121416-E4112-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121418-E701-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121419-E3451-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121420-E4528-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121421-E2747-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121422-E2149-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121424-E645-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121425-E2461-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121426-E1955-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121427-E2707-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121428-E779-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121429-E3309-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121430-E1720-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121432-E1213-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121433-E2611-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121434-E5027-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121435-E2648-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121436-E3624-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121437-E3387-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121441-E579-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121442-E1336-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121446-E2405-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121448-E4803-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121449-E4616-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121454-E3344-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121456-E3669-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121458-E4051-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121459-E1859-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121474-E928-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121476-E4621-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121477-E4085-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121479-E4099-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121480-E1597-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121519-E3467-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121523-E2989-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121525-E608-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121526-E3101-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121527-E4032-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121528-E3712-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121529-E2160-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121530-E3824-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121531-E3445-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121534-E3245-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121535-E4045-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121536-E4051-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121539-E1851-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121540-E4075-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121542-E2323-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121543-E1339-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121544-E4011-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121545-E4005-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121547-E2800-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121548-E3989-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121549-E4056-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121550-E3981-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121551-E3819-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121552-E1797-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121553-E4867-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121554-E4848-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121555-E4987-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121556-E5075-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121557-E4779-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121558-E5312-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121559-E4835-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121560-E949-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121561-E5043-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121563-E4581-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121565-E4283-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121567-E3861-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121568-E3640-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121569-E5136-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121574-E1939-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121576-E3637-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121579-E1485-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121580-E2448-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121581-E4675-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121582-E632-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121585-E4040-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121588-E1427-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121590-E800-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121592-E3557-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121593-E4451-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121595-E3765-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121608-E1963-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121609-E3419-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121623-E715-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121624-E4472-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121626-E4187-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121628-E3437-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121631-E4211-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121633-E3651-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121636-E3584-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121637-E4637-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121638-E4376-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121639-E784-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121640-E4376-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121641-E3584-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121649-E1461-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121650-E2867-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121651-E4645-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121652-E4736-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121653-E4107-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121656-E2320-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121678-E1555-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121681-E3893-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121683-E4453-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121684-E4251-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121687-E1979-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121688-E2405-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121689-E4885-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121694-E4931-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121698-E2971-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121704-E928-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121705-E1024-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121706-E5736-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121707-E5027-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121708-E5317-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121710-E3112-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121711-E1275-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121713-E4125-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121714-E1555-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121715-E5208-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121716-E5133-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121718-E4805-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121721-E5053-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121722-E5117-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121723-E4939-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121724-E2923-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121725-E4757-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121727-E3581-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121728-E5075-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121729-E5237-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121732-E904-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121734-E1587-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121748-E691-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121750-E4125-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121751-E2904-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121752-E2112-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121753-E2563-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121754-E2731-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121756-E4963-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121758-E3323-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121760-E971-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121764-E3533-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121765-E632-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121766-E4365-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121767-E4331-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121768-E4427-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121769-E2944-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121771-E4024-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121772-E4152-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121774-E832-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121778-E4363-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121779-E1448-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121780-E4989-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121781-E3976-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121783-E5141-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121784-E5333-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121785-E5317-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121787-E5237-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121788-E5181-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121789-E3011-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121790-E949-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121792-E3013-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121794-E4787-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121795-E5011-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121799-E3061-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121800-E5040-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121801-E5128-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121802-E1736-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121803-E5235-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121804-E1832-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121808-E4800-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121811-E5200-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121812-E1683-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121813-E5320-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121814-E4768-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121815-E677-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121816-E3875-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121817-E5336-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121819-E797-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121820-E3333-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121822-E5744-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121823-E5880-pass2.pds event startrun beginrun endrun
file add pdschain /cdat/sol221/disk5/c3mc/data16/tau/output/tau-Jun27_02_MC-MN-161-R121824-E6008-pass2.pds event startrun beginrun endrun

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize 100000
param HadronFilterProc noBeamSpot true
param HadronFilterProc beamSpotX 0.18e-3
param HadronFilterProc beamSpotY 0.
param HadronFilterProc fillBuffer false
go 722363

hbook terminate
exit
