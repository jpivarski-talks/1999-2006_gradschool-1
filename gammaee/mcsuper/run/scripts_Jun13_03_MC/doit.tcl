#
#  This is an example script to run the DOIT processor
#
#  There's no bunch finding here
#
#  Remember, for now you must do suez_zfiles!!
#
#   $Id: doit.tcl,v 1.4 2001/11/27 14:59:13 bkh Exp $
#
#   $Log: doit.tcl,v $
#   Revision 1.4  2001/11/27 14:59:13  bkh
#   Add new PreliminaryDRHitProd
#
#   Revision 1.3  1999/09/23 14:56:39  cdj
#   script loads CalibratedDR/CathodeHitProd instead of CalibratedDataProd
#
#   Revision 1.2  1999/07/19 18:09:49  bkh
#   Update with new producer names
#
#   Revision 1.1  1998/10/06 15:36:57  lyon
#   Just Doit
#
#
#
#

# Load raw data producer
prod sel RawDataProd
#

# Load CD Offline Calibration Algorithms
prod sel CDOffCal
#

# Load the Producers that make Calibrated hits from the DR
prod sel PreliminaryDRHitProd
prod sel CalibratedDRHitProd
prod sel CalibratedCathodeHitProd
#

# Load DOIT Track Finder
prod sel DoitProd
#

# Set the DOIT diagnostics level, if desired (0=quiet, 1=spew)
#param DoitProcessor parmDiagLevel 1
#

# Your code would go here
# e.g.
# proc sel LookAtSeeds


