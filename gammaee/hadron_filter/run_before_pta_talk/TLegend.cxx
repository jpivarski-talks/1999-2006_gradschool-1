<BASE HREF="http://root.cern.ch/root/html/src/TLegend.cxx.html">
<!DOCTYPE HTML PUBLIC "-// IETF/DTD HTML 2.0// EN">
<html>
<!--                                             -->
<!-- Author: ROOT team (rootdev@hpsalo.cern.ch)  -->
<!--                                             -->
<!--   Date: Fri May 24 10:57:18 2002            -->
<!--                                             -->
<head>
<title>TLegend - source file</title>
<link rev=made href="mailto:rootdev@root.cern.ch">
<meta name="rating" content="General">
<meta name="objecttype" content="Manual">
<meta name="keywords" content="software development, oo, object oriented, unix, x11, windows, c++, html, rene brun, fons rademakers">
<meta name="description" content="ROOT - An Object Oriented Framework For Large Scale Data Analysis.">
</head>
<body BGCOLOR="#ffffff" LINK="#0000ff" VLINK="#551a8b" ALINK="#ff0000" TEXT="#000000">
<a name="TopOfPage"></a>
<pre>
<b>// @(#)root/graf:$Name:  $:$Id: <a href=".././TLegend.html">TLegend</a>.cxx,v 1.14 2002/05/18 08:21:59 brun Exp $</b>
<b>// Author: Matthew.Adam.Dobbs   06/09/99</b>

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#include &lt;stdio.h&gt;

#include "<a href="../TLatex.h">TLatex.h</a>"
#include "<a href="../TLine.h">TLine.h</a>"
#include "<a href="../TBox.h">TBox.h</a>"
#include "<a href="../TMarker.h">TMarker.h</a>"
#include "<a href="../TLegend.h">TLegend.h</a>"
#include "<a href="../TList.h">TList.h</a>"
#include "<a href="../TVirtualPad.h">TVirtualPad.h</a>"
#include "<a href="../TMath.h">TMath.h</a>"
#include "<a href="../TROOT.h">TROOT.h</a>"
#include "<a href="../TLegendEntry.h">TLegendEntry.h</a>"
#include "<a href="../Riostream.h">Riostream.h</a>"


ClassImp(TLegend)

<b>//____________________________________________________________________________</b>
<b>// <a href=".././TLegend.html">TLegend</a>   Matthew.Adam.Dobbs@Cern.CH, September 1999</b>
<b>// <A  name="first_hit"><B ><FONT COLOR="#FF0000">Legend</FONT></B ></A> of markers/lines/boxes to represent objects with marker/line/fill</b>
<b>//   attributes</b>
<b>//   (the methods employed are very similar to those in <a href=".././TPaveText.html">TPaveText</a> class)</b>
<b>//</b>

<b>//____________________________________________________________________________</b>
<a name="TLegend:TLegend"> </a><a href=".././TLegend.html#TLegend:TLegend">TLegend::TLegend</a>(): <a href=".././TPave.html">TPave</a>(), <a href=".././TAttText.html">TAttText</a>()
{
<b>  // TPadLegend do-nothing default constructor</b>
  <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> = 0;
  <a href="#TLegend:SetDefaults">SetDefaults</a>();
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:TLegend"> </a><a href=".././TLegend.html#TLegend:TLegend">TLegend::TLegend</a>( <a href="../ListOfTypes.html#Double_t">Double_t</a> x1, <a href="../ListOfTypes.html#Double_t">Double_t</a> y1,<a href="../ListOfTypes.html#Double_t">Double_t</a> x2, <a href="../ListOfTypes.html#Double_t">Double_t</a> y2, const <a href="../ListOfTypes.html#char">char</a> *header, <a href="../ListOfTypes.html#Option_t">Option_t</a> *option)
        :<a href=".././TPave.html">TPave</a>(x1,y1,x2,y2,4,option), <a href=".././TAttText.html">TAttText</a>(12,0,1,42,0)
{
<b>  //___________________________________</b>
<b>  // <a href=".././TLegend.html">TLegend</a> normal Contructor</b>
<b>  // A <a href=".././TLegend.html">TLegend</a> is a Pave with several <a href=".././TLegendEntry.html">TLegendEntry</a>(s)</b>
<b>  // The pave is defined with default coords, bordersize and option</b>
<b>  // x1,y1,x2,y2 are the coordinates of the <B ><FONT COLOR="#FF0000">Legend</FONT></B > in the current pad</b>
<b>  // (in NDC by default!)</b>
<b>  // text is left adjusted and vertically centered = 12</b>
<b>  //      Angle=0 (degrees), color=1 (black)</b>
<b>  //      helvetica-medium-r-normal scalable font = 42</b>
<b>  //      (will use bold = 62 for header)</b>
<b>  //      size =0 (calculate this later when number of entries is known)</b>
<b>  // header is the "title" that will be displayed at the top of the <B ><FONT COLOR="#FF0000">legend</FONT></B ></b>
<b>  //   it is treated like a regular entry and supports <a href=".././TLatex.html">TLatex</a>. The default</b>
<b>  //   is no header (header = 0).</b>
<b>  // Options are the same as for <a href=".././TPave.html">TPave</a> <a href=".././TStyle.html">Default</a> = "brNDC"</b>
<b>  //</b>
<b>  // Here's an example of a <B ><FONT COLOR="#FF0000">Legend</FONT></B > created with <a href=".././TLegend.html">TLegend</a></b>
<b>  //</b>
  /*
    <IMG SRC="gif/example_legend.gif">
  */
<b>  //</b>
<b>  //</b>
<b>  // The <B ><FONT COLOR="#FF0000">Legend</FONT></B > part of this plot was created as follows:</b>
<b>  //</b>
<b>  //    leg = new <a href=".././TLegend.html">TLegend</a>(0.4,0.6,0.89,0.89);</b>
<b>  //    leg-&gt;<a href="#TLegend:AddEntry">AddEntry</a>(fun1,"One Theory","l");</b>
<b>  //    leg-&gt;<a href="#TLegend:AddEntry">AddEntry</a>(fun3,"Another Theory","f");</b>
<b>  //    leg-&gt;<a href="#TLegend:AddEntry">AddEntry</a>(gr,"The Data","p");</b>
<b>  //    leg-&gt;<a href="#TLegend:Draw">Draw</a>();</b>
<b>  //    // oops we forgot the blue line... add it after</b>
<b>  //    leg-&gt;<a href="#TLegend:AddEntry">AddEntry</a>(fun2,"#sqrt{2#pi} P_{T} (#gamma)  latex formula","f");</b>
<b>  //    // and add a header (or "title") for the <B ><FONT COLOR="#FF0000">legend</FONT></B ></b>
<b>  //    leg-&gt;<a href="#TLegend:SetHeader">SetHeader</a>("The <B ><FONT COLOR="#FF0000">Legend</FONT></B > Title");</b>
<b>  //    leg-&gt;<a href="#TLegend:Draw">Draw</a>();</b>
<b>  //</b>
<b>  // where fun1,fun2,fun3 and gr are pre-existing functions and graphs</b>
<b>  //</b>
<b>  // You can edit the <a href=".././TLegend.html">TLegend</a> by right-clicking on it.</b>
<b>  //</b>
  <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> = new <a href=".././TList.html">TList</a>;
  if ( header &amp;&amp; strlen(header) &gt; 0) {
    <a href=".././TLegendEntry.html">TLegendEntry</a> *headerEntry = new <a href=".././TLegendEntry.html">TLegendEntry</a>( 0, header, "h" );
    headerEntry-&gt;SetTextAlign(0);
    headerEntry-&gt;SetTextAngle(0);
    headerEntry-&gt;SetTextColor(0);
    headerEntry-&gt;SetTextFont(62); // default font is 62 for the header
    headerEntry-&gt;SetTextSize(0);
    <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;<a href=".././TList.html#TList:AddFirst">AddFirst</a>(headerEntry);
  }
  <a href="#TLegend:SetDefaults">SetDefaults</a>();
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:TLegend"> </a><a href=".././TLegend.html#TLegend:TLegend">TLegend::TLegend</a>( const <a href=".././TLegend.html">TLegend</a> &amp;<B ><FONT COLOR="#FF0000">legend</FONT></B > ) : <a href=".././TPave.html">TPave</a>(<B ><FONT COLOR="#FF0000">legend</FONT></B >), <a href=".././TAttText.html">TAttText</a>(<B ><FONT COLOR="#FF0000">legend</FONT></B >)
{
<b>  // copy constuctor</b>
  ((<a href=".././TLegend.html">TLegend</a>&amp;)<B ><FONT COLOR="#FF0000">legend</FONT></B >).<a href="#TLegend:Copy">Copy</a>(*this);
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:~TLegend"> </a><a href=".././TLegend.html">TLegend</a>::~<a href=".././TLegend.html">TLegend</a>()
{
<b>  // <a href=".././TLegend.html">TLegend</a> default destructor</b>
  if (<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>) <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;<a href=".././TList.html#TList:Delete">Delete</a>();
  delete <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>;
  <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> = 0;
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:AddEntry"> </a><a href=".././TLegendEntry.html">TLegendEntry</a> *<a href=".././TLegend.html#TLegend:AddEntry">TLegend::AddEntry</a>(<a href=".././TObject.html">TObject</a> *obj, const <a href="../ListOfTypes.html#char">char</a> *label, <a href="../ListOfTypes.html#Option_t">Option_t</a> *option)
{
<b>  // Add a new entry to this <B ><FONT COLOR="#FF0000">legend</FONT></B ></b>
<b>  // obj is the object to be represented</b>
<b>  // label is the text you wish to associate with obj in the <B ><FONT COLOR="#FF0000">legend</FONT></B ></b>
<b>  // Options are:</b>
<b>  //    L draw line associated w/ <a href=".././TAttLine.html">TAttLine</a> if obj inherits from <a href=".././TAttLine.html">TAttLine</a></b>
<b>  //    P draw polymarker assoc. w/ <a href=".././TAttMarker.html">TAttMarker</a> if obj inherits from <a href=".././TAttMarker.html">TAttMarker</a></b>
<b>  //    F draw a box with fill associated w/ <a href=".././TAttFill.html">TAttFill</a> if obj inherits <a href=".././TAttFill.html">TAttFill</a></b>
<b>  //</b>
  <a href=".././TLegendEntry.html">TLegendEntry</a> *newentry = new <a href=".././TLegendEntry.html">TLegendEntry</a>( obj, label, option );
  if ( !<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> ) <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> = new <a href=".././TList.html">TList</a>;
  <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;<a href=".././TList.html#TList:Add">Add</a>(newentry);
  return newentry;
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:AddEntry"> </a><a href=".././TLegendEntry.html">TLegendEntry</a> *<a href=".././TLegend.html#TLegend:AddEntry">TLegend::AddEntry</a>(const <a href="../ListOfTypes.html#char">char</a> *name, const <a href="../ListOfTypes.html#char">char</a> *label, <a href="../ListOfTypes.html#Option_t">Option_t</a> *option)
{
<b>  // Add a new entry to this <B ><FONT COLOR="#FF0000">legend</FONT></B ></b>
<b>  // name is the name of an object in the pad to be represented</b>
<b>  // label is the text you wish to associate with obj in the <B ><FONT COLOR="#FF0000">legend</FONT></B ></b>
<b>  // Options are:</b>
<b>  //    L draw line associated w/ <a href=".././TAttLine.html">TAttLine</a> if obj inherits from <a href=".././TAttLine.html">TAttLine</a></b>
<b>  //    P draw polymarker assoc. w/ <a href=".././TAttMarker.html">TAttMarker</a> if obj inherits from <a href=".././TAttMarker.html">TAttMarker</a></b>
<b>  //    F draw a box with fill associated w/ <a href=".././TAttFill.html">TAttFill</a> if obj inherits <a href=".././TAttFill.html">TAttFill</a></b>
<b>  //</b>
  <a href=".././TObject.html">TObject</a> *obj = gPad-&gt;FindObject(name);
  return <a href="#TLegend:AddEntry">AddEntry</a>( obj, label, option );
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:Clear"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:Clear">TLegend::Clear</a>( <a href="../ListOfTypes.html#Option_t">Option_t</a> *)
{
<b>  // Clear all entries in this <B ><FONT COLOR="#FF0000">legend</FONT></B > --- including the header!</b>
  if (!<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>) return;
  <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;<a href=".././TList.html#TList:Delete">Delete</a>();
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:Copy"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:Copy">TLegend::Copy</a>( <a href=".././TObject.html">TObject</a> &amp;obj )
{
<b>  // copy this <B ><FONT COLOR="#FF0000">legend</FONT></B > into obj</b>
  <a href=".././TPave.html#TPave:Copy">TPave::Copy</a>(obj);
  <a href=".././TAttText.html#TAttText:Copy">TAttText::Copy</a>((<a href=".././TLegend.html">TLegend</a>&amp;)obj);
  ((<a href=".././TLegend.html">TLegend</a>&amp;)obj).<a href=".././TLegend.html#TLegend:fEntrySeparation">fEntrySeparation</a> = <a href=".././TLegend.html#TLegend:fEntrySeparation">fEntrySeparation</a>;
  ((<a href=".././TLegend.html">TLegend</a>&amp;)obj).<a href=".././TLegend.html#TLegend:fMargin">fMargin</a> = <a href=".././TLegend.html#TLegend:fMargin">fMargin</a>;
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:DeleteEntry"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:DeleteEntry">TLegend::DeleteEntry</a>()
{
<b>  // Delete entry at the mouse position</b>
  if ( !<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> ) return;
  <a href=".././TLegendEntry.html">TLegendEntry</a>* entry = <a href="#TLegend:GetEntry">GetEntry</a>();   // get entry pointed to be mouse
  if ( !entry ) return;
  <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;<a href=".././TList.html#TList:Remove">Remove</a>(entry);
  delete entry;
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:Draw"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:Draw">TLegend::Draw</a>( <a href="../ListOfTypes.html#Option_t">Option_t</a> *option )
{
<b>  // Draw this <B ><FONT COLOR="#FF0000">legend</FONT></B > with its current attributes</b>
  AppendPad(option);
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:EditEntryAttFill"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:EditEntryAttFill">TLegend::EditEntryAttFill</a>()
{
<b>  // Edit the fill attributes for the entry pointed to be the mouse</b>
  <a href=".././TLegendEntry.html">TLegendEntry</a>* entry = <a href="#TLegend:GetEntry">GetEntry</a>();   // get entry pointed to be mouse
  if ( !entry ) return;
  <a href=".././TROOT.html">gROOT</a>-&gt;<a href=".././TROOT.html#TROOT:SetSelectedPrimitive">SetSelectedPrimitive</a>( entry );
  entry-&gt;SetFillAttributes();
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:EditEntryAttLine"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:EditEntryAttLine">TLegend::EditEntryAttLine</a>()
{
<b>  // Edit the line attributes for the entry pointed to be the mouse</b>
  <a href=".././TLegendEntry.html">TLegendEntry</a>* entry = <a href="#TLegend:GetEntry">GetEntry</a>();   // get entry pointed to be mouse
  if ( !entry ) return;
  <a href=".././TROOT.html">gROOT</a>-&gt;<a href=".././TROOT.html#TROOT:SetSelectedPrimitive">SetSelectedPrimitive</a>( entry );
  entry-&gt;SetLineAttributes();
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:EditEntryAttMarker"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:EditEntryAttMarker">TLegend::EditEntryAttMarker</a>()
{
<b>  // Edit the marker attributes for the entry pointed to be the mouse</b>
  <a href=".././TLegendEntry.html">TLegendEntry</a>* entry = <a href="#TLegend:GetEntry">GetEntry</a>();   // get entry pointed to be mouse
  if ( !entry ) return;
  <a href=".././TROOT.html">gROOT</a>-&gt;<a href=".././TROOT.html#TROOT:SetSelectedPrimitive">SetSelectedPrimitive</a>( entry );
  entry-&gt;SetMarkerAttributes();
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:EditEntryAttText"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:EditEntryAttText">TLegend::EditEntryAttText</a>()
{
<b>  // Edit the text attributes for the entry pointed to be the mouse</b>
  <a href=".././TLegendEntry.html">TLegendEntry</a>* entry = <a href="#TLegend:GetEntry">GetEntry</a>();   // get entry pointed to be mouse
  if ( !entry ) return;
  <a href=".././TROOT.html">gROOT</a>-&gt;<a href=".././TROOT.html#TROOT:SetSelectedPrimitive">SetSelectedPrimitive</a>( entry );
  entry-&gt;SetTextAttributes();
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:GetEntry"> </a><a href=".././TLegendEntry.html">TLegendEntry</a> *<a href=".././TLegend.html#TLegend:GetEntry">TLegend::GetEntry</a>() const
{
<b>  // Get entry pointed to by the mouse</b>
<b>  // This method is mostly a tool for other methods inside this class</b>
  <a href="../ListOfTypes.html#Int_t">Int_t</a> nEntries = 0;
  if ( <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> ) nEntries = <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;GetSize();
  if ( nEntries == 0 ) return 0;

  <a href="../ListOfTypes.html#Double_t">Double_t</a> ymouse = gPad-&gt;AbsPixeltoY(gPad-&gt;GetEventY());
  <a href="../ListOfTypes.html#Double_t">Double_t</a> yspace = (<a href=".././TBox.html#TBox:fY2">fY2</a> - <a href=".././TBox.html#TBox:fY1">fY1</a>)/nEntries;

  <a href="../ListOfTypes.html#Double_t">Double_t</a> ybottomOfEntry = <a href=".././TBox.html#TBox:fY2">fY2</a>;  // y-location of bottom of 0th entry
  <a href=".././TIter.html">TIter</a> next(<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>);
  <a href=".././TLegendEntry.html">TLegendEntry</a> *entry;
  while (( entry = (<a href=".././TLegendEntry.html">TLegendEntry</a> *)next() )) {
    ybottomOfEntry -= yspace;
    if ( ybottomOfEntry &lt; ymouse ) return entry;
  }
  return 0;
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:GetHeader"> </a>const <a href="../ListOfTypes.html#char">char</a> *<a href=".././TLegend.html#TLegend:GetHeader">TLegend::GetHeader</a>() const
{
<b>  // returns the header, which is the title that appears at the top</b>
<b>  //  of the <B ><FONT COLOR="#FF0000">legend</FONT></B ></b>
  if ( !<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> ) return 0;
    <a href=".././TIter.html">TIter</a> next(<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>);
  <a href=".././TLegendEntry.html">TLegendEntry</a> *first;   // header is always the first entry
  if ((  first = (<a href=".././TLegendEntry.html">TLegendEntry</a>*)next()  )) {
    <a href=".././TString.html">TString</a> opt = first-&gt;GetOption();
    opt.ToLower();
    if ( opt.Contains("h") ) return first-&gt;GetLabel();
  }
  return 0;
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:InsertEntry"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:InsertEntry">TLegend::InsertEntry</a>( const <a href="../ListOfTypes.html#char">char</a>* objectName, const <a href="../ListOfTypes.html#char">char</a>* label, <a href="../ListOfTypes.html#Option_t">Option_t</a>* option)
{
<b>  // Add a new entry before the entry at the mouse position</b>

  <a href=".././TLegendEntry.html">TLegendEntry</a>* beforeEntry = <a href="#TLegend:GetEntry">GetEntry</a>();   // get entry pointed to be mouse
  <a href=".././TObject.html">TObject</a> *obj = gPad-&gt;FindObject( objectName );

<b>  // note either obj OR beforeEntry may be zero at this point</b>

  <a href=".././TLegendEntry.html">TLegendEntry</a> *newentry = new <a href=".././TLegendEntry.html">TLegendEntry</a>( obj, label, option );

  if ( !<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> ) <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> = new <a href=".././TList.html">TList</a>;
  if ( beforeEntry ) {
    <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;<a href=".././TList.html#TList:AddBefore">AddBefore</a>( (<a href=".././TObject.html">TObject</a>*)beforeEntry, (<a href=".././TObject.html">TObject</a>*)newentry );
  } else {
    <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;<a href=".././TList.html#TList:Add">Add</a>((<a href=".././TObject.html">TObject</a>*)newentry);
  }
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:Paint"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:Paint">TLegend::Paint</a>( <a href="../ListOfTypes.html#Option_t">Option_t</a>* option )
{
<b>  // Paint this <B ><FONT COLOR="#FF0000">legend</FONT></B > with its current attributes</b>
  <a href=".././TPave.html#TPave:ConvertNDCtoPad">TPave::ConvertNDCtoPad</a>();
  <a href=".././TPave.html#TPave:PaintPave">TPave::PaintPave</a>(<a href=".././TBox.html#TBox:fX1">fX1</a>,<a href=".././TBox.html#TBox:fY1">fY1</a>,<a href=".././TBox.html#TBox:fX2">fX2</a>,<a href=".././TBox.html#TBox:fY2">fY2</a>,GetBorderSize(),option);
  <a href="#TLegend:PaintPrimitives">PaintPrimitives</a>();
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:PaintPrimitives"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:PaintPrimitives">TLegend::PaintPrimitives</a>()
{
<b>  // Paint the entries (list of primitives) for this <B ><FONT COLOR="#FF0000">legend</FONT></B ></b>
<b>  //</b>
<b>  // NOTE: if we want an     <a href="../ListOfTypes.html#Int_t">Int_t</a> mode</b>
<b>  //       it can be added later... but I understand whyaas</b>

  <a href="../ListOfTypes.html#Int_t">Int_t</a> nEntries = 0;
  if ( <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> ) nEntries = <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;GetSize();
  if ( nEntries == 0 ) return;

<b>  // Evaluate text size as a function of the number of entries</b>
<b>  //  taking into account their real size after drawing latex</b>
<b>  // Note: in pixel coords y1 &gt; y2=0, but x2 &gt; x1=0</b>
<b>  //       in NDC          y2 &gt; y1,   and x2 &gt; x1</b>
<b>  //</b>
  <a href="../ListOfTypes.html#Double_t">Double_t</a> margin = <a href=".././TLegend.html#TLegend:fMargin">fMargin</a>*( <a href=".././TBox.html#TBox:fX2">fX2</a> - <a href=".././TBox.html#TBox:fX1">fX1</a> );
  <a href="../ListOfTypes.html#Double_t">Double_t</a> yspace = (<a href=".././TBox.html#TBox:fY2">fY2</a> - <a href=".././TBox.html#TBox:fY1">fY1</a>)/nEntries;
  <a href="../ListOfTypes.html#Double_t">Double_t</a> textsize = GetTextSize();
  <a href="../ListOfTypes.html#Double_t">Double_t</a> save_textsize = textsize;

  if ( textsize == 0 ) {
    textsize = ( 1. - <a href=".././TLegend.html#TLegend:fEntrySeparation">fEntrySeparation</a> ) * yspace;
    textsize /= gPad-&gt;GetY2() - gPad-&gt;GetY1();

<b>    // find the max width and height (in pad coords) of one latex entry label</b>
    <a href="../ListOfTypes.html#Double_t">Double_t</a> maxentrywidth = 0, maxentryheight = 0;
    <a href=".././TIter.html">TIter</a> nextsize(<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>);
    <a href=".././TLegendEntry.html">TLegendEntry</a> *entrysize;
    while (( entrysize = (<a href=".././TLegendEntry.html">TLegendEntry</a> *)nextsize() )) {
      <a href=".././TLatex.html">TLatex</a> entrytex( 0, 0, entrysize-&gt;GetLabel() );
      entrytex.SetTextSize(textsize);
      if ( entrytex.GetYsize() &gt; maxentryheight ) {
        maxentryheight = entrytex.GetYsize();
      }
      if ( entrytex.GetXsize() &gt; maxentrywidth ) {
        maxentrywidth = entrytex.GetXsize();
      }
    }
<b>    // make sure all labels fit in the allotted space</b>
    <a href="../ListOfTypes.html#Double_t">Double_t</a> tmpsize_h = textsize * ( textsize/maxentryheight ) *
                         (gPad-&gt;GetY2() - gPad-&gt;GetY1());
    <a href="../ListOfTypes.html#Double_t">Double_t</a> tmpsize_w = textsize * ( (<a href=".././TBox.html#TBox:fX2">fX2</a> - (<a href=".././TBox.html#TBox:fX1">fX1</a>+margin))/maxentrywidth);
    textsize = <a href=".././TMath.html#TMath:Min">TMath::Min</a>( textsize, <a href=".././TMath.html#TMath:Min">TMath::Min</a>(tmpsize_h,tmpsize_w) );
    SetTextSize( textsize );
  }

  <a href="../ListOfTypes.html#Double_t">Double_t</a> ytext = <a href=".././TBox.html#TBox:fY2">fY2</a> + 0.5*yspace;  // y-location of 0th entry

<b>  // iterate over and paint all the TLegendEntries</b>
  <a href=".././TIter.html">TIter</a> next(<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>);
  <a href=".././TLegendEntry.html">TLegendEntry</a> *entry;
  while (( entry = (<a href=".././TLegendEntry.html">TLegendEntry</a> *)next() )) {
    ytext -= yspace;

<b>    // Draw Label in Latex</b>

    <a href="../ListOfTypes.html#Short_t">Short_t</a> talign = entry-&gt;GetTextAlign();
    <a href="../ListOfTypes.html#Float_t">Float_t</a> tangle = entry-&gt;GetTextAngle();
    <a href="../ListOfTypes.html#Color_t">Color_t</a> tcolor = entry-&gt;GetTextColor();
    <a href="../ListOfTypes.html#Style_t">Style_t</a> tfont  = entry-&gt;GetTextFont();
    <a href="../ListOfTypes.html#Size_t">Size_t</a>  tsize  = entry-&gt;GetTextSize();
<b>    // if the user hasn't set a parameter, then set it to the <a href=".././TLegend.html">TLegend</a> value</b>
    if (talign == 0) entry-&gt;SetTextAlign(GetTextAlign());
    if (tangle == 0) entry-&gt;SetTextAngle(GetTextAngle());
    if (tcolor == 0) entry-&gt;SetTextColor(GetTextColor());
    if (tfont  == 0) entry-&gt;SetTextFont(GetTextFont());
    if (tsize  == 0) entry-&gt;SetTextSize(GetTextSize());
<b>    // set x,y according to the requested alignment</b>
    <a href="../ListOfTypes.html#Double_t">Double_t</a> x=0,y=0;
    <a href="../ListOfTypes.html#Int_t">Int_t</a> halign = entry-&gt;GetTextAlign()/10;
    <a href="../ListOfTypes.html#Double_t">Double_t</a> entrymargin = margin;
<b>    // for the header the margin is near zero</b>
    <a href=".././TString.html">TString</a> opt = entry-&gt;GetOption();
    opt.ToLower();
    if ( opt.Contains("h") ) entrymargin = margin/10.;
    if (halign == 1) x = <a href=".././TBox.html#TBox:fX1">fX1</a> + entrymargin;
    if (halign == 2) x = 0.5*( (<a href=".././TBox.html#TBox:fX1">fX1</a>+entrymargin) + <a href=".././TBox.html#TBox:fX2">fX2</a> );
    if (halign == 3) x = <a href=".././TBox.html#TBox:fX2">fX2</a> - entrymargin/10.;
    <a href="../ListOfTypes.html#Int_t">Int_t</a> valign = entry-&gt;GetTextAlign()%10;
    if (valign == 1) y = ytext - (1. - <a href=".././TLegend.html#TLegend:fEntrySeparation">fEntrySeparation</a>)* yspace/2.;
    if (valign == 2) y = ytext;
    if (valign == 3) y = ytext + (1. - <a href=".././TLegend.html#TLegend:fEntrySeparation">fEntrySeparation</a>)* yspace/2.;
<b>    //</b>
    <a href=".././TLatex.html">TLatex</a> entrytex( x, y, entry-&gt;GetLabel() );
    entry-&gt;<a href=".././TAttText.html#TAttText:Copy">TAttText::Copy</a>(entrytex);
    entrytex.<a href="#TLegend:Paint">Paint</a>();
<b>    // reset attributes back to their original values</b>
    entry-&gt;SetTextAlign(talign);
    entry-&gt;SetTextAngle(tangle);
    entry-&gt;SetTextColor(tcolor);
    entry-&gt;SetTextFont(tfont);
    entry-&gt;SetTextSize(tsize);

<b>    // define x,y as the center of the symbol for this entry</b>
    <a href="../ListOfTypes.html#Double_t">Double_t</a> xsym = <a href=".././TBox.html#TBox:fX1">fX1</a> + margin/2.;
    <a href="../ListOfTypes.html#Double_t">Double_t</a> ysym = ytext;

    <a href=".././TObject.html">TObject</a> *eobj = entry-&gt;GetObject();

<b>    // Draw fill pattern (in a box)</b>

    if ( opt.Contains("f")) {
      if (eobj &amp;&amp; eobj-&gt;InheritsFrom(<a href=".././TAttFill.html#TAttFill:Class">TAttFill::Class</a>())) {
         <a href="../ListOfTypes.html#char">char</a> cmd[50];
         sprintf(cmd,"((%s*)0x%lx)-&gt;GetFillColor();",
              entry-&gt;GetObject()-&gt;ClassName(),(<a href="../ListOfTypes.html#Long_t">Long_t</a>)eobj);
         entry-&gt;Execute("SetFillColor",cmd);
         sprintf(cmd,"((%s*)0x%lx)-&gt;GetFillStyle();",
              entry-&gt;GetObject()-&gt;ClassName(),(<a href="../ListOfTypes.html#Long_t">Long_t</a>)eobj);
         entry-&gt;Execute("SetFillStyle",cmd);
      }

<b>      // box total height is yspace*0.7</b>
      <a href="../ListOfTypes.html#Double_t">Double_t</a> boxwidth = yspace*
        (gPad-&gt;GetX2()-gPad-&gt;GetX1())/(gPad-&gt;GetY2()-gPad-&gt;GetY1());
      if ( boxwidth &gt; margin ) boxwidth = margin;
      entry-&gt;<a href=".././TAttFill.html#TAttFill:Modify">TAttFill::Modify</a>();
      <a href="../ListOfTypes.html#Double_t">Double_t</a> xf[4],yf[4];
      xf[0] = xsym - boxwidth*0.35;
      yf[0] = ysym - yspace*0.35;
      xf[1] = xsym + boxwidth*0.35;
      yf[1] = yf[0];
      xf[2] = xf[1];
      yf[2] = ysym + yspace*0.35;
      xf[3] = xf[0];
      yf[3] = yf[2];
      gPad-&gt;PaintFillArea(4,xf,yf);
    }

<b>    // Draw line</b>

    if ( opt.Contains("l") || opt.Contains("f")) {

      <a href="../ListOfTypes.html#Color_t">Color_t</a> lcolor = entry-&gt;GetLineColor();
      <a href="../ListOfTypes.html#Style_t">Style_t</a> lstyle = entry-&gt;GetLineStyle();
      <a href="../ListOfTypes.html#Width_t">Width_t</a> lwidth = entry-&gt;GetLineWidth();
      if (eobj &amp;&amp; eobj-&gt;InheritsFrom(<a href=".././TAttLine.html#TAttLine:Class">TAttLine::Class</a>())) {
         <a href="../ListOfTypes.html#char">char</a> cmd[50];
         sprintf(cmd,"((%s*)0x%lx)-&gt;GetLineColor();",
                entry-&gt;GetObject()-&gt;ClassName(),(<a href="../ListOfTypes.html#Long_t">Long_t</a>)eobj);
         entry-&gt;Execute("SetLineColor",cmd);
         sprintf(cmd,"((%s*)0x%lx)-&gt;GetLineStyle();",
                entry-&gt;GetObject()-&gt;ClassName(),(<a href="../ListOfTypes.html#Long_t">Long_t</a>)eobj);
         entry-&gt;Execute("SetLineStyle",cmd);
         sprintf(cmd,"((%s*)0x%lx)-&gt;GetLineWidth();",
                entry-&gt;GetObject()-&gt;ClassName(),(<a href="../ListOfTypes.html#Long_t">Long_t</a>)eobj);
         entry-&gt;Execute("SetLineWidth",cmd);
      }
<b>      // line total length (in x) is margin*0.8</b>
      <a href=".././TLine.html">TLine</a> entryline( xsym - margin*0.4, ysym, xsym + margin*0.4, ysym );
      entry-&gt;<a href=".././TAttLine.html#TAttLine:Copy">TAttLine::Copy</a>(entryline);
<b>      // if the entry is filled, then surround the box with the line instead</b>
      if ( opt.Contains("f") &amp;&amp; !opt.Contains("l")) {
<b>        // box total height is yspace*0.7</b>
        <a href="../ListOfTypes.html#Double_t">Double_t</a> boxwidth = yspace*
          (gPad-&gt;GetX2()-gPad-&gt;GetX1())/(gPad-&gt;GetY2()-gPad-&gt;GetY1());
        if ( boxwidth &gt; margin ) boxwidth = margin;

        entryline.PaintLine( xsym - boxwidth*0.35, ysym + yspace*0.35,
                             xsym + boxwidth*0.35, ysym + yspace*0.35);
        entryline.PaintLine( xsym - boxwidth*0.35, ysym - yspace*0.35,
                             xsym + boxwidth*0.35, ysym - yspace*0.35);
        entryline.PaintLine( xsym + boxwidth*0.35, ysym - yspace*0.35,
                             xsym + boxwidth*0.35, ysym + yspace*0.35);
        entryline.PaintLine( xsym - boxwidth*0.35, ysym - yspace*0.35,
                             xsym - boxwidth*0.35, ysym + yspace*0.35);
      } else {
         entryline.<a href="#TLegend:Paint">Paint</a>();
      }

      entry-&gt;SetLineColor(lcolor);
      entry-&gt;SetLineStyle(lstyle);
      entry-&gt;SetLineWidth(lwidth);
    }

<b>    // Draw Polymarker</b>

    if ( opt.Contains("p")) {

      <a href="../ListOfTypes.html#Color_t">Color_t</a> mcolor = entry-&gt;GetMarkerColor();
      <a href="../ListOfTypes.html#Style_t">Style_t</a> mstyle = entry-&gt;GetMarkerStyle();
      <a href="../ListOfTypes.html#Size_t">Size_t</a> msize = entry-&gt;GetMarkerSize();
      if (eobj &amp;&amp; eobj-&gt;InheritsFrom(<a href=".././TAttMarker.html#TAttMarker:Class">TAttMarker::Class</a>())) {
        <a href="../ListOfTypes.html#char">char</a> cmd[50];
        sprintf(cmd,"((%s*)0x%lx)-&gt;GetMarkerColor();",
                entry-&gt;GetObject()-&gt;ClassName(),(<a href="../ListOfTypes.html#Long_t">Long_t</a>)eobj);
        entry-&gt;Execute("SetMarkerColor",cmd);
        sprintf(cmd,"((%s*)0x%lx)-&gt;GetMarkerStyle();",
                entry-&gt;GetObject()-&gt;ClassName(),(<a href="../ListOfTypes.html#Long_t">Long_t</a>)eobj);
        entry-&gt;Execute("SetMarkerStyle",cmd);
        sprintf(cmd,"((%s*)0x%lx)-&gt;GetMarkerSize();",
                entry-&gt;GetObject()-&gt;ClassName(),(<a href="../ListOfTypes.html#Long_t">Long_t</a>)eobj);
        entry-&gt;Execute("SetMarkerSize",cmd);
      }
      <a href=".././TMarker.html">TMarker</a> entrymarker( xsym, ysym, 0 );
      entry-&gt;<a href=".././TAttMarker.html#TAttMarker:Copy">TAttMarker::Copy</a>(entrymarker);
      entry-&gt;SetMarkerColor(mcolor);
      entry-&gt;SetMarkerStyle(mstyle);
      entry-&gt;SetMarkerSize(msize);
      entrymarker.<a href="#TLegend:Paint">Paint</a>();
    }
  }

  SetTextSize(save_textsize);
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:Print"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:Print">TLegend::Print</a>( <a href="../ListOfTypes.html#Option_t">Option_t</a>* option ) const
{
<b>  // dump this <a href=".././TLegend.html">TLegend</a> and its contents</b>
  <a href=".././TPave.html#TPave:Print">TPave::Print</a>( option );
  if (<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>) <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;<a href="#TLegend:Print">Print</a>();
}

<b>//______________________________________________________________________________</b>
<a name="TLegend:RecursiveRemove"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:RecursiveRemove">TLegend::RecursiveRemove</a>(<a href=".././TObject.html">TObject</a> *obj)
{
<b>//  Reset TLegendEntrys pointing to obj</b>
   
  <a href=".././TIter.html">TIter</a> next(<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>);
  <a href=".././TLegendEntry.html">TLegendEntry</a> *entry;
  while (( entry = (<a href=".././TLegendEntry.html">TLegendEntry</a> *)next() )) {
     if (entry-&gt;GetObject() == obj) entry-&gt;SetObject((<a href=".././TObject.html">TObject</a>*)0);
  }
}


<b>//____________________________________________________________________________</b>
<a name="TLegend:SavePrimitive"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:SavePrimitive">TLegend::SavePrimitive</a>( ofstream &amp;out, <a href="../ListOfTypes.html#Option_t">Option_t</a>* )
{
<b>  // Save this <B ><FONT COLOR="#FF0000">legend</FONT></B > as C++ statements on output stream out</b>
<b>  //  to be used with the SaveAs .C option</b>
  out &lt;&lt; "   " &lt;&lt; endl;
  <a href="../ListOfTypes.html#char">char</a> quote = '"';
  if ( <a href=".././TROOT.html">gROOT</a>-&gt;<a href=".././TROOT.html#TROOT:ClassSaved">ClassSaved</a>( <a href=".././TLegend.html#TLegend:Class">TLegend::Class</a>() ) ) {
    out &lt;&lt; "   ";
  } else {
    out &lt;&lt; "   <a href=".././TLegend.html">TLegend</a> *";
  }
<b>  // note, we can always use NULL header, since its included in primitives</b>
  out &lt;&lt; "leg = new <a href=".././TLegend.html">TLegend</a>("&lt;&lt;GetX1NDC()&lt;&lt;","&lt;&lt;GetY1NDC()&lt;&lt;","
      &lt;&lt;GetX2NDC()&lt;&lt;","&lt;&lt;GetY2NDC()&lt;&lt;","
      &lt;&lt; "NULL" &lt;&lt; "," &lt;&lt;quote&lt;&lt; <a href=".././TPave.html#TPave:fOption">fOption</a> &lt;&lt;quote&lt;&lt;");" &lt;&lt; endl;
  SaveTextAttributes(out,"leg",12,0,1,42,0);
  SaveLineAttributes(out,"leg",0,0,0);
  SaveFillAttributes(out,"leg",0,0);
  if ( <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> ) {
    <a href=".././TIter.html">TIter</a> next(<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>);
    <a href=".././TLegendEntry.html">TLegendEntry</a> *entry;
    while (( entry = (<a href=".././TLegendEntry.html">TLegendEntry</a> *)next() )) entry-&gt;SaveEntry(out,"leg");
  }
  out &lt;&lt; "   leg-&gt;<a href="#TLegend:Draw">Draw</a>();"&lt;&lt;endl;
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:SetEntryLabel"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:SetEntryLabel">TLegend::SetEntryLabel</a>( const <a href="../ListOfTypes.html#char">char</a>* label )
{
<b>  // edit the label of the entry pointed to by the mouse</b>
  <a href=".././TLegendEntry.html">TLegendEntry</a>* entry = <a href="#TLegend:GetEntry">GetEntry</a>();   // get entry pointed to be mouse
  if ( entry ) entry-&gt;SetLabel( label );
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:SetEntryOption"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:SetEntryOption">TLegend::SetEntryOption</a>( <a href="../ListOfTypes.html#Option_t">Option_t</a>* option )
{
<b>  // edit the option of the entry pointed to by the mouse</b>
  <a href=".././TLegendEntry.html">TLegendEntry</a>* entry = <a href="#TLegend:GetEntry">GetEntry</a>();   // get entry pointed to be mouse
  if ( entry ) entry-&gt;SetOption( option );
}

<b>//____________________________________________________________________________</b>
<a name="TLegend:SetHeader"> </a><a href="../ListOfTypes.html#void">void</a> <a href=".././TLegend.html#TLegend:SetHeader">TLegend::SetHeader</a>( const <a href="../ListOfTypes.html#char">char</a> *header )
{
<b>  // Sets the header, which is the "title" that appears at the top of the</b>
<b>  //  <a href=".././TLegend.html">TLegend</a></b>
  if ( !<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a> ) new <a href=".././TList.html">TList</a>;
  <a href=".././TIter.html">TIter</a> next(<a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>);
  <a href=".././TLegendEntry.html">TLegendEntry</a> *first;   // header is always the first entry
  if ((  first = (<a href=".././TLegendEntry.html">TLegendEntry</a>*)next() )) {
    <a href=".././TString.html">TString</a> opt = first-&gt;GetOption();
    opt.ToLower();
    if ( opt.Contains("h") ) {
      first-&gt;SetLabel(header);
      return;
    }
  }
  first = new <a href=".././TLegendEntry.html">TLegendEntry</a>( 0, header, "h" );
  first-&gt;SetTextAlign(0);
  first-&gt;SetTextAngle(0);
  first-&gt;SetTextColor(0);
  first-&gt;SetTextFont(GetTextFont()); // default font is <a href=".././TLegend.html">TLegend</a> font for the header
  first-&gt;SetTextSize(0);
  <a href=".././TLegend.html#TLegend:fPrimitives">fPrimitives</a>-&gt;<a href=".././TList.html#TList:AddFirst">AddFirst</a>((<a href=".././TObject.html">TObject</a>*)first);
}



</pre>

<!--SIGNATURE-->
<br>
<address>
<hr>
<center>
<a href="http://root.cern.ch/root/Welcome.html">ROOT page</a> - <a href="../ClassIndex.html">Class index</a> - <a href="#TopOfPage">Top of the page</a><br>
</center>
<hr>This page has been automatically generated. If you have any comments or suggestions about the page layout send a mail to <a href="mailto:rootdev@root.cern.ch">ROOT support</a>, or contact <a href="mailto:rootdev@root.cern.ch">the developers</a> with any questions or problems regarding ROOT.
</address>
</body>
</html>
