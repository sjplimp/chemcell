/* ----------------------------------------------------------------------
   ChemCell - Cell simulator for particle diffusion and reactions
   Steve Plimpton (sjplimp@sandia.gov), Alex Slepoy (aslepoy@sandia.gov)
   Sandia National Laboratories, www.cs.sandia.gov/~sjplimp/chemcell.html

   Copyright (2004) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under 
   the GNU General Public License.

   See the README file in the top-level ChemCell directory.
------------------------------------------------------------------------- */

#include "string.h"
#include "stdlib.h"
#include "fix_rate_saturate.h"
#include "simulator.h"
#include "particle.h"
#include "react.h"
#include "random.h"
#include "memory.h"
#include "error.h"

/* ---------------------------------------------------------------------- */

FixRateSaturate::FixRateSaturate(int narg, char **arg) : Fix(narg, arg)
{
  if (narg < 6) error->all("Illegal fix rate/saturate command");
  if (simulator->spatial_flag == 1)
    error->all("Cannot use fix rate/saturate with spatial simulations");

  nevery = atoi(arg[2]);

  int n = strlen(arg[3]) + 1;
  species = new char[n];
  strcpy(species,arg[3]);

  half = atof(arg[4]);

  nlist = narg - 5;
  list = new int[nlist];
  rate_initial = new double[nlist];

  reactions = new char*[nlist];
  int ilist = 0;
  for (int i = 5; i < narg; i++) {
    n = strlen(arg[i]) + 1;
    reactions[ilist] = new char[n];
    strcpy(reactions[ilist],arg[i]);
    ilist++;
  }
}

/* ---------------------------------------------------------------------- */

FixRateSaturate::~FixRateSaturate()
{
  delete [] list;
  delete [] rate_initial;
  for (int i = 0; i < nlist; i++) delete [] reactions[i];
  delete [] reactions;
}

/* ---------------------------------------------------------------------- */

int FixRateSaturate::setmask()
{
  int mask = 0;
  mask |= INITIAL;
  return mask;
}

/* ---------------------------------------------------------------------- */

void FixRateSaturate::init()
{
  rate = react->rate;

  ispecies = particle->find(species);
  if (ispecies < 0)
    error->all("Invalid species ID in fix rate/saturate command");

  for (int i = 0; i < nlist; i++) {
    list[i] = react->find(reactions[i]);
    if (list[i] < 0)
      error->all("Invalid reaction ID in fix rate/saturate command");
    rate_initial[list[i]] = rate[list[i]];
  }
}

/* ---------------------------------------------------------------------- */

void FixRateSaturate::initial()
{
  if (simulator->ntimestep % nevery) return;

  /*
  double dynamic = count[ispecies];
  scale = half / (half + dynamic);

  int index;
  double propensity;

  if (stochastic) {
    for (int i = 0; i < nlist; i++) {
      index = list[i];
      rate[index] = rate_initial[index] * scale;
      propensity = chem->compute_propensity(index);
      chem->set(index,propensity);
    }
  }

  if (ode) {
    for (int i = 0; i < nlist; i++) {
      index = list[i];
      rate[index] = rate_initial[index] * scale;
    }
  }
  */
}
