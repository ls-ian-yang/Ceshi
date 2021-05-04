# 

## For R4 and further

+ File name with file type to avoid conflict
+ Compile-execute functionality
  + Just like executing python

## R4 Update

+ f2l2c: file to language to compiler
+ Add python and .py recognition including:
  + python compiler class
  + array expan f2l .py->python
  + l2c python->python compiler
  + default script is 'python', not specifying version of python
+ standard of adding compiler:
  + Inherit compiler
    + Override compose
  + declare a compiler container and create a new instance
    + like cuda cudaCompiler;
  + Update f2l
  + Update l2c
+ Rearrange code
  
## R5

+ abstract compose, too many duplicated code!
+ ceshi mode
+ Rearranged code

## R6

+ release.bat added to simplify the workflow
+ Now use V for version instead R for realease to resolve the conflict of initial
+ Added the prototype of terminal mode

## R7 Plan

+ simple compile -- shit
  + shit to compile the file that is changed most recently
  + shit to match the test named files
  + shit file to modify the compilation

## Dreams

+ Formatted class, modified via config file
+ User defined compiler
+ Open-source compiler downloader
+ More complicated parameter structure to enable file structured dedicate testing process.
+ Full functioning terminal mode
+ Parse options, change 
  + string fileName = argv[1];
