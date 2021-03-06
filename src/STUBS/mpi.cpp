/* -----------------------------------------------------------------------
   LAMMPS 2003 (July 31) - Molecular Dynamics Simulator
   Sandia National Laboratories, www.cs.sandia.gov/~sjplimp/lammps.html
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under 
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------ */

/* Single-processor "stub" versions of MPI routines */

#include "stdlib.h"
#include "stdio.h"
#include <sys/time.h>
#include "mpi.h"

/* lo-level function prototypes */

void mpi_copy_int(void *, void *, int);
void mpi_copy_float(void *, void *, int);
void mpi_copy_double(void *, void *, int);
void mpi_copy_char(void *, void *, int);
void mpi_copy_byte(void *, void *, int);

/* MPI Functions */

void MPI_Init(int *argc, char ***argv) {}

void MPI_Comm_rank(MPI_Comm comm, int *me)
{
  *me = 0;
}

void MPI_Comm_size(MPI_Comm comm, int *nprocs)
{
  *nprocs = 1;
}

void MPI_Abort(MPI_Comm comm, int errorcode)
{
  exit(1);
}

void MPI_Finalize() {}

double MPI_Wtime()
{
  double time;
  struct timeval tv;

  gettimeofday(&tv,NULL);
  time = 1.0 * tv.tv_sec + 1.0e-6 * tv.tv_usec;
  return time;
}

void MPI_Send(void *buf, int count, MPI_Datatype datatype,
	      int dest, int tag, MPI_Comm comm)
{
  printf("MPI Stub WARNING: Should not send message to self\n");
}

void MPI_Rsend(void *buf, int count, MPI_Datatype datatype,
	       int dest, int tag, MPI_Comm comm)
{
  printf("MPI Stub WARNING: Should not rsend message to self\n");
}

void MPI_Recv(void *buf, int count, MPI_Datatype datatype,
	      int source, int tag, MPI_Comm comm, MPI_Status *status)
{
  printf("MPI Stub WARNING: Should not recv message from self\n");
}

void MPI_Irecv(void *buf, int count, MPI_Datatype datatype,
	       int source, int tag, MPI_Comm comm, MPI_Request *request)
{
  printf("MPI Stub WARNING: Should not recv message from self\n");
}

void MPI_Wait(MPI_Request *request, MPI_Status *status)
{
  printf("MPI Stub WARNING: Should not wait on message from self\n");
}

void MPI_Waitany(int count, MPI_Request *request, int *index, 
		 MPI_Status *status)
{
  printf("MPI Stub WARNING: Should not wait on message from self\n");
}

void MPI_Get_count(MPI_Status *status, MPI_Datatype datatype, int *count)
{
  printf("MPI Stub WARNING: Should not get count of message to self\n");
}

void MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *comm_out)
{
  *comm_out = comm;
}

void MPI_Comm_dup(MPI_Comm comm, MPI_Comm *comm_out)
{
  *comm_out = comm;
}

void MPI_Comm_free(MPI_Comm *comm) { }

void MPI_Cart_create(MPI_Comm comm_old, int ndims, int *dims, int *periods,
		     int reorder, MPI_Comm *comm_cart)
{
  *comm_cart = comm_old;
}

void MPI_Cart_get(MPI_Comm comm, int maxdims, int *dims, int *periods,
		  int *coords)
{
  dims[0] = dims[1] = dims[2] = 1;
  periods[0] = periods[1] = periods[2] = 1;
  coords[0] = coords[1] = coords[2] = 0;
}

void MPI_Cart_shift(MPI_Comm comm, int direction, int displ,
		    int *source, int *dest)
{
  *source = *dest = 0;
}

void MPI_Barrier(MPI_Comm comm) {}

void MPI_Bcast(void *buf, int count, MPI_Datatype datatype,
	       int root, MPI_Comm comm) {}

/* copy values from data1 to data2 */

void MPI_Allreduce(void *sendbuf, void *recvbuf, int count,
		   MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
  if (datatype == MPI_INT)
    mpi_copy_int(sendbuf,recvbuf,count);
  else if (datatype == MPI_FLOAT)
    mpi_copy_float(sendbuf,recvbuf,count);
  else if (datatype == MPI_DOUBLE)
    mpi_copy_double(sendbuf,recvbuf,count);
  else if (datatype == MPI_CHAR)
    mpi_copy_char(sendbuf,recvbuf,count);
  else if (datatype == MPI_BYTE)
    mpi_copy_byte(sendbuf,recvbuf,count);
}

void MPI_Scan(void *sendbuf, void *recvbuf, int count,
	      MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
  if (datatype == MPI_INT)
    mpi_copy_int(sendbuf,recvbuf,count);
  else if (datatype == MPI_FLOAT)
    mpi_copy_float(sendbuf,recvbuf,count);
  else if (datatype == MPI_DOUBLE)
    mpi_copy_double(sendbuf,recvbuf,count);
  else if (datatype == MPI_CHAR)
    mpi_copy_char(sendbuf,recvbuf,count);
  else if (datatype == MPI_BYTE)
    mpi_copy_byte(sendbuf,recvbuf,count);
}

/* copy values from data1 to data2 */

void MPI_Allgather(void *sendbuf, int sendcount, MPI_Datatype sendtype,
		   void *recvbuf, int recvcount, MPI_Datatype recvtype,
		   MPI_Comm comm)
{
  if (sendtype == MPI_INT)
    mpi_copy_int(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_FLOAT)
    mpi_copy_float(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_DOUBLE)
    mpi_copy_double(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_CHAR)
    mpi_copy_char(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_BYTE)
    mpi_copy_byte(sendbuf,recvbuf,sendcount);
}

/* copy values from data1 to data2 */

void MPI_Allgatherv(void *sendbuf, int sendcount, MPI_Datatype sendtype,
		    void *recvbuf, int *recvcounts, int *displs,
		    MPI_Datatype recvtype, MPI_Comm comm)
{
  if (sendtype == MPI_INT)
    mpi_copy_int(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_FLOAT)
    mpi_copy_float(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_DOUBLE)
    mpi_copy_double(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_CHAR)
    mpi_copy_char(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_BYTE)
    mpi_copy_byte(sendbuf,recvbuf,sendcount);
}

/* copy values from data1 to data2 */

void MPI_Reduce_scatter(void *sendbuf, void *recvbuf, int *recvcounts,
			MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
  if (datatype == MPI_INT)
    mpi_copy_int(sendbuf,recvbuf,*recvcounts);
  else if (datatype == MPI_FLOAT)
    mpi_copy_float(sendbuf,recvbuf,*recvcounts);
  else if (datatype == MPI_DOUBLE)
    mpi_copy_double(sendbuf,recvbuf,*recvcounts);
  else if (datatype == MPI_CHAR)
    mpi_copy_char(sendbuf,recvbuf,*recvcounts);
  else if (datatype == MPI_BYTE)
    mpi_copy_byte(sendbuf,recvbuf,*recvcounts);
}

/* copy values from data1 to data2 */

void MPI_Gather(void *sendbuf, int sendcount, MPI_Datatype sendtype,
		   void *recvbuf, int recvcount, MPI_Datatype recvtype,
		   int root, MPI_Comm comm)
{
  if (sendtype == MPI_INT)
    mpi_copy_int(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_FLOAT)
    mpi_copy_float(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_DOUBLE)
    mpi_copy_double(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_CHAR)
    mpi_copy_char(sendbuf,recvbuf,sendcount);
  else if (sendtype == MPI_BYTE)
    mpi_copy_byte(sendbuf,recvbuf,sendcount);
}

/* ------------------------------------------------------------------------ */
/* Added routines for data copying */

void mpi_copy_int(void *data1, void *data2, int n)
{
  int i;
  int *pdata1 = (int *) data1;
  int *pdata2 = (int *) data2;

  for (i = 0; i < n; i++) pdata2[i] = pdata1[i];
}

void mpi_copy_float(void *data1, void *data2, int n)
{
  int i;
  float *pdata1 = (float *) data1;
  float *pdata2 = (float *) data2;

  for (i = 0; i < n; i++) pdata2[i] = pdata1[i];
}

void mpi_copy_double(void *data1, void *data2, int n)
{
  int i;
  double *pdata1 = (double *) data1;
  double *pdata2 = (double *) data2;

  for (i = 0; i < n; i++) pdata2[i] = pdata1[i];
}

void mpi_copy_char(void *data1, void *data2, int n)
{
  int i;
  char *pdata1 = (char *) data1;
  char *pdata2 = (char *) data2;

  for (i = 0; i < n; i++) pdata2[i] = pdata1[i];
}

void mpi_copy_byte(void *data1, void *data2, int n)
{
  int i;
  char *pdata1 = (char *) data1;
  char *pdata2 = (char *) data2;

  for (i = 0; i < n; i++) pdata2[i] = pdata1[i];
}
