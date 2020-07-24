
tcl_proc load_proper_format {fileName } {
   set extensionToType(.rp) QQDriverSourceFormat
   set extensionToType(.asct) AsciiTestSourceFormat
   set extensionToType(.pds) PDSSourceFormat
   
   foreach extension [array names extensionToType] {
      if { 0 == [string compare $extension [string range $fileName end-[expr [string length $extension] -1] end] ] } {
         source_format sel $extensionToType($extension)
         return
      }
   }
   error "load_proper_format: unknown file type for file $fileName"   
}

tcl_proc load_proper_sink_format {fileName } {
   set extensionToType(.asct) AsciiTestSinkFormat
   set extensionToType(.pds) PDSSinkFormat
   
   foreach extension [array names extensionToType] {
      if { 0 == [string compare $extension [string range $fileName end-[expr [string length $extension] -1] end] ] } {
         sink_format sel $extensionToType($extension)
         return
      }
   }
   error "load_proper_sink_format: unknown file type for file $fileName"   
}
