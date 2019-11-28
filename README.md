# Mazzy (File Manager Emulator)

*As I remember, this code was written in 2006*

## What is it?

File Manager Emulator (FME) emulates the details of creating, removing, copying and moving files and directories. It also handles commands related to these file management tasks. FME shall be capable to read and execute a batch file with different kind of commands. After the batch file execution it shall generate and print out formatted directory structure or an error message if something went wrong to standard output. Note that program should do nothing with the real file structure on local hard drives and shall only emulate these activities.

## Structure

Namespaceses and basic objects structure

<table width="100%" border="0" cellpadding="5" cellspacing="1" bgcolor="#000000">

<tbody>

<tr bgcolor="#ffffff">

<td valign="top">

<strong>Mazzy</strong>

<table width="100%" valign="top">

<tbody>

<tr valign="top">

<td width="33%">

<div class="obj">Cmd</div>

<div class="obj">Parser</div>

<div class="obj">Display</div>

</td>

<td width="34%" valign="top">
<strong>Commands</strong>


<table width="100%" border="0" cellpadding="5" cellspacing="1" bgcolor="#000000">

<tbody>

<tr bgcolor="#c0c0c0" valign="top">

<td>

<div class="obj">MakeDir</div>

<div class="obj">ChangeDir</div>

<div class="obj">RemoveDir</div>

<div class="obj">MakeFile</div>

<div class="obj">DelTree</div>

<div class="obj">Del</div>

<div class="obj">Copy</div>

<div class="obj">Move</div>

<div class="obj">MakeHardLink</div>

<div class="obj">MakeDynLink</div>

</td>

</tr>

</tbody>

</table>

</td>

<td width="33%" valign="top">
<strong>FS</strong>
<table width="100%" border="0" cellpadding="5" cellspacing="1" bgcolor="#000000">

<tbody>

<tr bgcolor="#7da7d8" valign="top">

<td>

<div class="obj">Path</div>

<div class="obj">FileSystem</div>

<div class="obj">Object</div>

<div class="obj">Dir</div>

<div class="obj">File</div>

<div class="obj">HLink</div>

<div class="obj">DLink</div>

</td>

</tr>

</tbody>

</table>

</td>

</tr>

</tbody>

</table>

</td>

</tr>

</tbody>

</table>

Simple object structure in memory.

For example, if we have path like **_C:\mazzy\mazzy.cpp_**  Mazzy will store in memory the next data structure:

<table align="center">

<tbody>

<tr>

<td>

<table border="0" cellpadding="5" cellspacing="1" bgcolor="#000000">

<tbody>

<tr bgcolor="#7da7d8">

<td colspan="2" align="center"><strong>Dir (Object)</strong></td>

</tr>

<tr bgcolor="#ffffff">

<td>Name</td>

<td>C:</td>

</tr>

<tr bgcolor="#ffffff">

<td>Type</td>

<td>DIR</td>

</tr>

<tr bgcolor="#ffffff">

<td>Childs</td>

<td>[0] » » »</td>

</tr>

<tr bgcolor="#ffffff">

<td>0 « « « </td>

<td>Parent</td>

</tr>

</tbody>

</table>

</td>

<td>

<table border="0" cellpadding="5" cellspacing="1" bgcolor="#000000">

<tbody>

<tr bgcolor="#7da7d8">

<td colspan="2" align="center"><strong>Dir (Object)</strong></td>

</tr>

<tr bgcolor="#ffffff">

<td>Name</td>

<td>mazzy</td>

</tr>

<tr bgcolor="#ffffff">

<td>Type</td>

<td>DIR</td>

</tr>

<tr bgcolor="#ffffff">

<td>Childs</td>

<td>[0] » » »</td>

</tr>

<tr bgcolor="#ffffff">

<td>« « « </td>

<td>Parent</td>

</tr>

</tbody>

</table>

</td>

<td>

<table border="0" cellpadding="5" cellspacing="1" bgcolor="#000000">

<tbody>

<tr bgcolor="#7da7d8">

<td colspan="2" align="center"><strong>File (Object)</strong></td>

</tr>

<tr bgcolor="#ffffff">

<td>Name</td>

<td>mazzy.cpp</td>

</tr>

<tr bgcolor="#ffffff">

<td>Type</td>

<td>FILE</td>

</tr>

<tr bgcolor="#ffffff">

<td>Childs</td>

<td>empty</td>

</tr>

<tr bgcolor="#ffffff">

<td>« « « </td>

<td>Parent</td>

</tr>

</tbody>

</table>

</td>

</tr>

</tbody>

</table>

## Design patterns used

1.  [Singleton](http://en.wikipedia.org/wiki/Singleton_pattern)
2.  [Composite](http://en.wikipedia.org/wiki/Composite_pattern)
3.  [Command](http://en.wikipedia.org/wiki/Command_pattern)
4.  [Facade](http://en.wikipedia.org/wiki/Fa%C3%A7ade_pattern)

## Using

1.  Compile:
     just run **g++ mazzy.cpp -o mazzy** or run **make**
2.  Run batch files:
     **mazzy < batch.file**
