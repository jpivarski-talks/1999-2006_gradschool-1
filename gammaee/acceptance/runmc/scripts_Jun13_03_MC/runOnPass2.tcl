##########################################################################
## This is a script that loads some of the producers you might need
## to run on the official pass2 or on privately made "pass2" files.
## To use, add to your tcl script
##
## run_file $env(C3_SCRIPTS)/runOnPass2.tcl
##
##########################################################################

## produce navigation objects
prod sel NavigationProd
prod sel TrackDeliveryProd

## produce high level CC info
prod sel C3ccProd

## make pi0s, etas
prod sel PhotonDecaysProd

## Some people's local "pass2" already has k shorts stored
## If you want k shorts in pass2, you will need VFinderProd
#prod sel VFinderProd

## magnetic field
prod sel MagFieldProd

## does analysis time corrections to Dedx
prod sel DedxConstProd
prod sel DedxInfoProd

# Electron and Muon fits (and sometimes Proton) were not done in Pass2
prod sel ElectronFromPionFitProd
prod sel MuonFromPionFitProd
#prod sel ProtonFromPionFitProd

## get magnetic field and beam energy from run statistics
module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in

## these are the constants needed by Dedx
module sel ConstantsModule
constants in $env(C3_CONST) meta Dedx MetaListRetrieval
constants in $env(C3_CONST) meta FieldMap MetaListRetrieval
constants in $env(C3_CONST) meta MagFudge MetaListRetrieval
