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

#include "mpi.h"
#include "string.h"
#include "unistd.h"
#include "sys/stat.h"
#include "shell.h"
#include "error.h"

/* ---------------------------------------------------------------------- */

void Shell::command(int narg, char **arg)
{
  if (narg < 1) error->all("Illegal shell command");

  int me;
  MPI_Comm_rank(world,&me);

  if (strcmp(arg[0],"cd") == 0) {
    if (narg != 2) error->all("Illegal shell command");
    chdir(arg[1]);

  } else if (strcmp(arg[0],"mkdir") == 0) {
    if (narg < 2) error->all("Illegal shell command");
    if (me == 0)
      for (int i = 1; i < narg; i++)
	mkdir(arg[i], S_IRWXU | S_IRGRP | S_IXGRP);

  } else if (strcmp(arg[0],"mv") == 0) {
    if (narg != 3) error->all("Illegal shell command");
    if (me == 0) rename(arg[1],arg[2]);

  } else if (strcmp(arg[0],"rm") == 0) {
    if (narg < 2) error->all("Illegal shell command");
    if (me == 0)
      for (int i = 1; i < narg; i++)
	unlink(arg[i]);

  } else if (strcmp(arg[0],"rmdir") == 0) {
    if (narg < 2) error->all("Illegal shell command");
    if (me == 0)
      for (int i = 1; i < narg; i++)
	rmdir(arg[i]);

  } else error->all("Illegal shell command");
}
