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
  
## For R5 and further

+ abstract compose, too many duplicated code!
+ Formatted class, modified via config file
+ ceshi mode
+ Parse options, change 
  + string fileName = argv[1];

## Dreams

+ User defined compiler
+ Open-source compiler downloader
+ More complicated parameter structure to enable file structured dedicate testing process.
