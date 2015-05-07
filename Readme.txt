--------------------------------------------------------Read me-----------------------------------------------------------------------



----------------------
Tool Used
----------------------
c++ 11
log4cpp
boost 
open mpi
unix scripting
git
hadoop
java

----------------------
File Description
----------------------

DataEngineMain.cpp             --- Main class to generate synthetic data
DataEngine.cpp               --- defines core components for synthetic data generation
Timer.cpp              --- Timer utitilies
Logging.cpp     --- class to provide functions to filter out noise from signal data

                           
hadoop_run                   --- scripts to kick off hadoop program
HadoopEngine.java         ---main map reduce class for hadoop

mpi_run      -----scripts to kick off mpi program
MpiEngine     ----main entrance for mpi program
chengbin_makefile       --- hw3 makefile
log4cpp.properties      --- config file for log4cpp appenders


----------------------
Execution Description
----------------------

1)  git clone https://github.com/Baruch-College-New-York-MFE-Program/BDiF2015-Channing-Wang/tree/master/Assignment_C
2) cd Assignment_C
3)  make -f chengbin_makefile
4) chmod 777 *
5) ./hadoop_run
6)  vi log.out
7) ./mapi_run
8) vi log.out  






