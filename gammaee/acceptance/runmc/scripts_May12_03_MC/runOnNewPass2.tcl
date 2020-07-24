##########################################################################
## This is a script that loads some of the producers you might need
## to run on the official pass2 or on privately made "pass2" files.
## To use, add to your tcl script before any other processors are selected
##
## run_file $env(C3_SCRIPTS)/runOnNewPass2.tcl
##
##########################################################################

# may need this to avoid some exceptions: use with great care!!
#exception continueEventLoop on 

# may want this to avoid getting prompted: use with great care!!
#default prompt off

# tabular source constants file access
run_file $env(C3_SCRIPTS)/RunInfo.tcl
run_file $env(C3_SCRIPTS)/CcRunGain.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

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

## magnetic field  // not needed when running with runinfo
#prod sel MagFieldProd

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
#module sel RunStatisticsSourceModule // not needed with runinfo
#runstatistics in

## these are the constants needed by Dedx
module sel ConstantsModule
constants in $env(C3_CONST) meta Dedx MetaListRetrieval
#constants in $env(C3_CONST) meta FieldMap MetaListRetrieval
#constants in $env(C3_CONST) meta MagFudge MetaListRetrieval // not needed with runinfo

