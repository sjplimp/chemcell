/* ----------------------------------------------------------------------
   ChemCell - Cell simulator for particle diffusion and reactions
   Steve Plimpton (sjplimp@sandia.gov)
   Alex Slepoy (alexander.slepoy@nnsa.doe.gov)
   Sandia National Laboratories, www.cs.sandia.gov/~sjplimp/chemcell.html

   Copyright (2004) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under 
   the GNU General Public License.

   See the README file in the top-level ChemCell directory.
------------------------------------------------------------------------- */

#include "string.h"
#include "stdio.h"
#include "mpi.h"
#include "universe.h"
#include "version.h"
#include "memory.h"

/* ----------------------------------------------------------------------
   create & initialize the universe of processors in communicator
------------------------------------------------------------------------- */

Universe::Universe(MPI_Comm communicator)
{
  version = (char *) CHEMCELL_VERSION;

  uworld = communicator;
  MPI_Comm_rank(uworld,&me);
  MPI_Comm_size(uworld,&nprocs);

  uscreen = stdout;
  ulogfile = NULL;

  nworlds = 0;
  procs_per_world = NULL;
  root_proc = NULL;
}

/* ---------------------------------------------------------------------- */

Universe::~Universe()
{
  memory->sfree(procs_per_world);
  memory->sfree(root_proc);
}

/* ----------------------------------------------------------------------
   add 1 or more worlds to universe
   str == NULL -> add 1 world with all procs in universe
   str = NxM -> add N worlds, each with M procs
   str = P -> add 1 world with P procs
------------------------------------------------------------------------- */

void Universe::add_world(char *str)
{
  int n,nper;
  char *ptr;

  if (str == NULL) {
    n = 1;
    nper = nprocs;
  } else if ((ptr = strchr(str,'x')) != NULL) {
    *ptr = '\0';
    n = atoi(str);
    nper = atoi(ptr+1);
  } else {
    n = 1;
    nper = atoi(str);
  }

  procs_per_world = 
    (int *) memory->srealloc(procs_per_world,(nworlds+n)*sizeof(int),
			     "universe:procs_per_world");
  root_proc = 
    (int *) memory->srealloc(root_proc,(nworlds+n)*sizeof(int),
			     "universe:root_proc");

  for (int i = 0; i < n; i++) {
    procs_per_world[nworlds] = nper;
    if (nworlds == 0) root_proc[nworlds] = 0;
    else
      root_proc[nworlds] = root_proc[nworlds-1] + procs_per_world[nworlds-1];
    if (me >= root_proc[nworlds]) iworld = nworlds;
    nworlds++;
  }
}

/* ----------------------------------------------------------------------
   check if total procs in all worlds = procs in universe
------------------------------------------------------------------------- */

int Universe::consistent()
{
  int n = 0;
  for (int i = 0; i < nworlds; i++) n += procs_per_world[i];
  if (n == nprocs) return 1;
  else return 0;
}
