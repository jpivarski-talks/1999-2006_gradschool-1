*
* $Id: mc_rich_responses.F,v 1.4 2000/07/14 20:23:59 lkg Exp $
*
* $Log: mc_rich_responses.F,v $
* Revision 1.4  2000/07/14 20:23:59  lkg
* store decay tree, not geant, particle id in rich response
*
* Revision 1.3  2000/04/19 00:44:26  pg
* Added protection against TOO MANY HITS case. Extract Si geometry from SVAlignment stream.
*
* Revision 1.2  1999/07/08 06:11:17  ts
* first actual implementation of Rich Response
*
* Revision 1.1.1.1  1999/04/16 20:07:33  jjo
* Move MCxxResponseProxy from MCResponse library to this library.
* Make Geant calls from this library as fetching the hits (via GFHITS)
* currently couples this library to Geant.  Also, use bindable proxies. (jjo)
*
* Revision 1.1  1999/02/25 21:31:08  bkh
* Update
*
*
      SUBROUTINE MC_RICH_RESPONSES
*
* begin_doc
*
*  Documentation for subroutine mc_rich_responses
*
*  Purpose:
*  --------
*
*  Input Parameters:  (Name - Type - Meaning)
*  ----------------
*
*  Output Parameters:  (Name - Type - Meaning)
*  -----------------
*
*  Other routines:
*  ---------------
*
*  Notes:
*  ------
*
*  Author:   Brian K. Heltsley      Created:  Fri Feb 19 16:17:34 EST 1999
*  -------
*
*  Major revisions:
*  ----------------
*
*            Tomasz Skwarnicki  adopt old rirawm.F to do the job.   June 25, 99
*     
*
* end_doc
*
#if defined(CLEO_TYPECHEK)
      IMPLICIT NONE
#endif
*
* begin_inc
*  Include files :
*  ---------------------
#include "seq/clutil/mesrep.inc"

#include "cl3seq/zfiles/usbank.inc"

#ifndef CLEO_GEANT315
#include "geant321/gcflag.inc"
#include "geant321/gcbank.inc"
#else
#include "geant/gcdes/gcflag.inc"
#include "geant/gcdes/gcbank.inc"
#endif

#include "Cleog3/cg3cdes/cgspec.inc"
#include "Cleog3/cg3cdes/cgname.inc"

#include "RichGeom/rich_geom.inc"
#include "RichGeom/rich_optic.inc"
#include "RichGeom/rich_radiators.inc"
#include "RichGeom/rich_chambers.inc"

* end_inc
*
* begin_var
*  input/output variables:
*  -----------------------
*
*  Local pre-defined variables:
*  ---------------------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: mc_rich_responses.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.4 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2000/07/14 20:23:59 $')
      PARAMETER(CHRCSA='$Author: lkg $')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'MC_RICH_RESPONSES' )
*
*  Local User defined variables:
*  -----------------------------
*
      INTEGER NWRITE
      INTEGER DKTREE_ID
*
* end_var
*
*  Data statements:
*  ----------------
*
      SAVE RCSINI
      SAVE NWRITE
*
      DATA RCSINI/.TRUE./
      DATA NWRITE/0/
*
* -------------------- Local    declarations ---------------
      character*4 CUSET,CUDET
* -------------------- GEANT hit banks communication variables
* MAXHIT - Maximum number of hits accepted
* NWDVOL - Number of words specifying volume number
* NWDHIT - Number of words required per hit
*
      INTEGER    MAXHIT,              NWDVOL,     NWDHIT
      PARAMETER( MAXHIT = 5000,       NWDVOL = 1, NWDHIT = 9 )
* NUMBV  - Volume numbers
* ITRM   - Track number for a given hit
* VHIT   - Hits from GEANT
* NHITS  - Number of hits returned by GEANT
* IHIT   - hit number (loop index over hits 1..NHITS)
*
      INTEGER NUMBV(NWDVOL,MAXHIT), ITRM(MAXHIT)
      INTEGER NUMVS(NWDVOL), NHITS, IHIT
      INTEGER IOERR
      REAL    VHIT (NWDHIT,MAXHIT)
* ----------------------------------------------------------------------
* Map to GEANT workspace
* ----------------------------------------------------------------------
      EQUIVALENCE( NUMBV(1,1), WS(21) )
      EQUIVALENCE( VHIT (1,1), WS((       NWDVOL)*MAXHIT+21) )
      EQUIVALENCE( ITRM (1  ), WS((NWDVOL+NWDHIT)*MAXHIT+21) )
* --------------------------------------------------------------
      integer modri,nbox,j,i_ch,i_win,i_rad,i_optbox1
* hit position in local coordinate system of chamber module
      double precision cx,cy,cz,r
      real cxs,cys,czs
* rich logical address stuff
      integer risec,rimod,rix,riy,riadd
      integer i_optbox,id
* id - radiator/window/chamber identifier for the photon origin
*  executable code for routine mc_rich_responses:
#if WRITE_RCS_INFO
      IF(RCSINI)THEN
        RCSINI = .FALSE.
        WRITE(6,*)'-------- CVSinfo --------'
        WRITE(6,*)CHRCSS
        WRITE(6,*)CHRCSR//' '//CHRCST
        WRITE(6,*)CHRCSD//' '//CHRCSA
      ENDIF
#endif
*----6----------------------------------------------------------------72
*
      IF (NWRITE .LT. 1) THEN
        NWRITE = NWRITE + 1
        CHMESS='This is a real routine, this message written once'
        CALL MESLOG(CRNAME,1,MSINFO)
      ENDIF

C ==================================================================
C  Get the hit workspace from GEANT (to store GEANT hits info)
C ==================================================================
      CALL GWORK( (NWDVOL+NWDHIT+1)*MAXHIT )
      IF( IEOTRI.NE.0 ) THEN
         call rich_error(CRNAME,
     $ ' Failed to get workspace from GEANT, skipped event' )
         RETURN
      ENDIF
C ==============================================================
C get hits from GEANT
C ==============================================================
      CUSET='RICH'
      CUDET='RICH'
      CALL GFHITS( CUSET, CUDET, NWDVOL, NWDHIT, MAXHIT, 0, NUMVS,
     +   ITRM, NUMBV, VHIT, NHITS )
C ==============================================================
C protect against too many hits (GFHITS returns NHITS=MAXHIT+1 -> BAD!
C ==============================================================
      IF( NHITS .GT. MAXHIT ) THEN

        WRITE( CHMESS, 10020, IOSTAT = IOERR ) MAXHIT
10020   FORMAT(' Too many hits for local buffer, using', I6 )
        CALL MESLOG( CRNAME, 2, MSERRO )
        
        NHITS = MAXHIT
        
      ENDIF
C ==============================================================
C calulate logical addresses and local coordinates of hits
C ==============================================================

      do 1 ihit=1,nhits

        modri = ifix( vhit(9,ihit) )

        nbox = ch_optbox(modri)
        if( nbox.lt.1 .or. nbox.gt.n_optbox )then
           call rich_error(CRNAME,' Wrong optical box number ')
           goto 1
        endif

        cx = 0.0
        cy = 0.0
        cz = 0.0
        do j = 1, 3
           r = VHIT(j,ihit)- optbox_vert(j,0,nbox)
           cx = cx + r * optbox_axis(j,1,nbox)
           cy = cy + r * optbox_axis(j,2,nbox)
           cz = cz + r * optbox_axis(j,3,nbox)
        end do
        cxs = sngl(cx)
        cys = sngl(cy)
        czs = sngl(cz)

        risec = ( modri - 1 )/nrimod + 1
        rimod = mod ( modri - 1, nrimod ) + 1
        rix = ifix(sngl((cx + sx_pad*nx_pads*0.5)/sx_pad)) + 1
        rix = min( nx_pads, max( 1, rix ) )
        riy = ifix(sngl((cy + sy_pad*ny_pads*0.5)/sy_pad)) + 1
        riy = min( ny_pads, max( 1, riy ) )
        riadd = (risec-1)*nrisecxy+(rimod-1)*nrimodxy+(riy-1)*nrix+rix

        i_optbox = ifix( vhit(4,ihit) )
        id=0
        if( i_optbox.ne.0 )then
        if( volume_name(optbox_link(1,i_optbox)).eq.ch_name )then
          call rich_find_chamber(optbox_vert(1,0,i_optbox),
     $                   i_ch, i_optbox1)
          if( i_ch.eq.0 )then
            call rich_error(CRNAME,' cannot find chamber')
          else
            id = id + i_ch
          endif
        else
          id = id + max_chambers
          call rich_find_window( optbox_vert(1,0,i_optbox),
     $                  i_win, i_optbox1 )
          if( i_win.ne.0 )then
            id = id+i_win
          else
            id = id + max_windows
            call rich_find_radiator( optbox_vert(1,0,i_optbox),
     $                  i_rad, i_optbox1 )
            if( i_rad.eq.0 )then
               call rich_error(CRNAME,' Radiator/window not found ')
            else
               id = id + i_rad
            endif
          endif
        endif
        endif

        call gdt_geant_to_dktree_partid( itrm(ihit), dktree_id )
        call mc_rich_add_response( riadd, dktree_id, cxs, cys, czs, 
     $                vhit(6,ihit),
     $                id, ifix( vhit(5,ihit) ),
     $                vhit(7,ihit), vhit(8,ihit) )

 1    continue

      RETURN
      END



