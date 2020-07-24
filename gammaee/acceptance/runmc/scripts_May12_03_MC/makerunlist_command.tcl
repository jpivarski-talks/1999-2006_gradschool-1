tcl_proc makerunlist args {

   global runList
   set lineList [ split $args ]

# specify which formats are known and what their keywords are:
# ------------------------------------------------------------
   global listOfFormats
   set listOfFormats {.runinfo .hanna}
   global formatarray
   set formatarray(.runinfo) {run nrevents nhad lastevt bhalum bhastaterr bhasyserr ebeamcor ebeamuncor bfieldcor bfielduncor gglum ggstaterr ggsyserr dataset} 
   set formatarray(.hanna) {run goodmood badmood}

# various help functions:
# -----------------------
   if { (-1 != [lsearch $args "help"]) || (-1 != [lsearch $args "HELP"]) } {
     puts " makerunlist"
     puts " ===========" 
     puts " Creates a list of valid runs within a user specified run range."
     puts " Validity is established by checking on user specified criteria,"
     puts " based on a tabular text file, assuming it consists of one line of"
     puts " information per run. The condition is specified as columns having"
     puts " to match certain criteria, evaluated as tcl expressions."
     puts " Nothing is assumed about the position or type of information per"
     puts " run, except that the run number must be the first entry in each row."
     puts " The column whose value is to be checked is identified by the keyword"
     puts " \"col\", as in echo \" col <columnumber> \". The spaces are important."
     puts " Note that the first column will be number 0."
     puts " For known formats, keywords can be used instead of \" col <columnumber> \"."
     puts " The keywords are only recognizable if enclosed in blanks."
     puts " Find out which formats are known and what their keywords are like this:"
     puts "     makerunlist whichformats - gives a list of known formats"
     puts "     makerunlist format <formatname> - gives a list of keywords for this format" 
     puts " Arguments:"
     puts "     lowest run number"
     puts "     highest run number"
     puts "     name of ascii text file" 
     puts "     Boolean expression that shall be TRUE"
     puts " Example: runs 113517 to 113527, text file \$C3_INFO/data/runinfo.runinfo,"
     puts "     condition to fulfil: beam energy > 5.17810"
     puts "     The beam energy is stored in column 7 in this text file." 
     puts "     However, since .runinfo is a known format, you may also specify "
     puts "     that you wish ebeamuncor to have this value. In this case, the "
     puts "     following commands are equivalent: " 
     puts "     makerunlist 113517 113527 \$env(C3_INFO)/data/runinfo.runinfo ( ebeamuncor > 5.17810 )"
     puts "     makerunlist 113517 113527 \$env(C3_INFO)/data/runinfo.runinfo ( col 7 > 5.17810 )"
     return 
   }

   if { ( [lindex $lineList 0] == "whichformats" )} {
      puts "Known formats are:"
      puts "$listOfFormats"
      puts "To find out which keywords are known for each format, do: "
      puts "makerunlist format <formatname> "
      return
   }

   if { ( [ llength $lineList ] == 2 ) && ( [lindex $lineList 0] == "format" )} {
      foreach knownformat $listOfFormats {
         if { ( $knownformat == [lindex $lineList 1] ) } {
           echo The following keywords are recognized for file format $knownformat:
           echo $formatarray($knownformat) 
           return
         }
      }      
      echo I do not know this format.
      return
   }

   if { ( [ llength $lineList ] < 4) } {
     echo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     echo Too few arguments!
     echo Usage: makerunlist runlower runupper listfile condition
     echo Other commands: makerunlist format <.yourformat>
     echo or makerunlist help
     echo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     set runList []
     return 
   }

# process the command:
# --------------------
   set inputfile [lindex $lineList 2]

####################################################################
# open input file, remove blanks, put into a list:
# ------------------------------------------------
   set fileHandler [ open $inputfile ]
   set runInfoList [list]
   global keywordlist
   load_keywords $inputfile

   echo This is my input list:
   echo ++++++++++++++++++++++
#   echo (not printing, too long...)
   while { [ gets $fileHandler lineManyBlanks ] > 0 } {
# remove blanks...
#        leading ones:
         set lineManyBlanks [ string trim $lineManyBlanks ]
#        ones in between (leave one to separate the entries):
         while { ( [regsub -all "  " $lineManyBlanks " " lineLessBlanks] != 0 ) } {
           set lineManyBlanks $lineLessBlanks
         }
         set line $lineLessBlanks
          echo |$line|
         lappend runInfoList $line
   }
   echo ++++++++++++++++++++++
   echo End of my list.
   close $fileHandler

####################################################################
# go through the list of user specified requirements.
# First, try to recognize keywords for this format and replace them
# by their column number, second, replace all the col <nn> with tcl
# commands.

   echo 
   echo Setting up list of requirements.
   set useFormatList []
   global noteindex
   global keywordnumber

# process the tail part of the command line, using the file format's keywords:
   for { set cindex 3 } { $cindex < [ llength $lineList ] } { incr cindex} {
     set next [ lindex $lineList $cindex ]
     set keywordnumber -1

     foreach keyword $keywordlist {
#        echo $keyword, $next
        if { ( $next == $keyword ) } {
#           echo I found a keyword I know!! $next
           set keywordnumber [lsearch $keywordlist $keyword]
#           echo $keywordnumber
           break
        }
     }
#     echo keywordnumber is: $keywordnumber
     if {-1 == $keywordnumber} {
          lappend useFormatList $next 
     } else {
          lappend useFormatList " col "
          lappend useFormatList $keywordnumber 
     }
#     echo useformatlist: $useFormatList
   }
   
   regsub -all "{" $useFormatList "" useFormatList 
   regsub -all "}" $useFormatList "" useFormatList 
#   echo UseFormatList is: $useFormatList 
   set requirementList "expr "

   set addbracket {}
   set noteindex {}  
   for { set cindex 0 } { $cindex < [ llength $useFormatList ] } { incr cindex} {
     set next [ lindex $useFormatList $cindex ]
#     echo $cindex, $next

     if { ( $next == "col") } {
#       echo Found col!
       set addbracket 1 
       set noteindex [ expr [ expr $cindex ] + 1 ]
       lappend requirementList "\[ lindex \$thisRunLineList"
     } else { 
       lappend requirementList $next
     }
     
      if { $cindex == $noteindex  } {
#        echo $noteindex, $cindex
        lappend requirementList " \] "
#        set addbracket 0
     }
   }
   echo This is my list of requirements:
#   echo $requirementList
# pretty up list of requirements:
   regsub -all "{" $requirementList "" requirementList 
   regsub -all "}" $requirementList "" requirementList
#   echo And now: 
   echo $requirementList

####################################################################
# compose the list of good runs:
   set runList []
# for each run in run range, check if it is valid:
   set runlower [lindex $lineList 0]
   set runupper [lindex $lineList 1]

   echo
   echo Will now check each run from $runlower to $runupper.
   global ldothisrun

   for { set index $runlower } { $index <= $runupper } {incr index} {
      echo ===================================
      echo Checking on run $index

# look through the check list:
      foreach runNumberLine $runInfoList {
         set lineList [ split $runNumberLine ]
         set runNumber [ lindex $lineList 0 ]
# Now we have a list of items in this line and the run number it is about.

         set ldothisrun 0

# evaluate whether we like this run:
#         set happy [ expr ( $runNumber == $index ) ]
#         echo $happy

         if { $runNumber == $index } {
            echo Found run $runNumber, checking whether it is good...
            checkrun $runNumber $lineList $requirementList
            break 
         }
      }
      if { $ldothisrun == 1} {
# Add this run to the list of good runs:
#         echo I like run $runNumber 
         lappend runList $runNumber 
      } 
    }
    echo Finished

    echo This is my list of good runs:
    foreach run $runList {
      echo $run
    }
}

###########################################################################
tcl_proc checkrun { thisRun thisRunLineList condition } {
    global ldothisrun
#     set ldothisrun 1
#    echo $thisRun
#    echo $thisRunLineList
#    echo You want me to check this: $condition
#    echo I think [ eval $condition ]
    set ldothisrun [ eval $condition ]

#    set ldothisrun [ expr ( [ lindex $thisRunLineList 8 ] == 5.29110 )]
#    echo Do I like this run? $ldothisrun
}


###########################################################################
tcl_proc load_keywords { inputfile } {
   global listOfFormats
   global formatarray 
   global keywordlist
   set keywordlist {}

   foreach format $listOfFormats {
#       echo [string length $format]
#       echo [string range $inputfile end-[string length $format] end]
#       echo [string range $inputfile end-[expr [string length $format] -1] end]
#       echo [string compare $format [string range $inputfile end-[expr [string length $format] -1] end] ]
       if { 0 == [string compare $format [string range $inputfile end-[expr [string length $format] -1] end] ] } {
          set keywordlist $formatarray($format)
          echo List of known keywords for format $format: $keywordlist
          return
      }
   }
   echo I do not know this format.
}

