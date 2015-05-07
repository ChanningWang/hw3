#include<stdio.h>
#include<stdlib.h>
#include <boost/filesystem.hpp>
#include <iostream>

#include "mpi.h"

#include "Logging.hpp"


using namespace boost::filesystem;
using namespace std;

int main(int argc, char **argv){

log4cpp::Category & root=InitLogging::getRoot();
  int rank, nprocs;
  MPI_File fh;
  MPI_Status status;
  long bufsize, nints;
  long long FILESIZE=file_size("FedData.csv");
  std::ostringstream os;
  os<<"MPI Input File Size:"<<FILESIZE<<endl;
  root.info(os.str());


  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);


  bufsize = FILESIZE/nprocs;
  nints = bufsize/sizeof(char);
  char buf[nints];

  MPI_File_open(MPI_COMM_WORLD, "FedData.csv",
              MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
  MPI_File_seek(fh, rank * bufsize, MPI_SEEK_SET);
  MPI_File_read(fh, buf, nints, MPI_CHAR, &status);
  std::ostringstream os1;
  os1<<"Process -"<<rank<<endl;
  root.info(os1.str());
  root.info(buf);
  MPI_File_close(&fh);
}
