/* LPHASH - LOCALLY-PROBED HASH TABLE FACILITY - PROGRAM FOR TEST #1.

   Copyright (c) 2017 Radford M. Neal.

   The lphash library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#include <stdio.h>
#include "lphash-app.h"

int main (int argc, char **argv)
{
  lphash_table_t tbl;

  tbl = lphash_create (64);
  if (tbl == NULL)
  { fprintf (stderr, "Can't create table\n");
    exit(1);
  }

  lphash_destroy(tbl);

  return 0;
}
