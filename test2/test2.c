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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "lphash-app.h"

#define hash(k) ((k) >> 3)

#define BUCKETS_PER_LINE 8

int main (int argc, char **argv)
{
  int entries, log2_buckets;

  if (argc != 3 || (entries = atoi(argv[1])) < 1 
       || (log2_buckets = atoi(argv[2])) < 3 || log2_buckets > 30)
  { fprintf (stderr, "Usage: test2 entries log2-buckets\n");
    exit(1);
  }

  lphash_table_t tbl;

  tbl = lphash_create (1 << log2_buckets);
  if (tbl == NULL)
  { fprintf (stderr, "Can't create table\n");
    exit(1);
  }

  lphash_entry_t e = 123456789;
  int lines = 0;
  int i;

  for (i = 0; i < entries; i++)
  { 
    e = ((int64_t)e * 9876543) % 0x7fffffff;

    lphash_hash_t h = hash(e);
    int old_probes = tbl->probes;

    lphash_insert(tbl,h,e);

    int probes_done = tbl->probes - old_probes;

#   ifdef LPHASH_LINEAR
      lines += 1 + (h+probes_done-1) / BUCKETS_PER_LINE - h / BUCKETS_PER_LINE;
#   else
      lines += 1 + (probes_done-1) / BUCKETS_PER_LINE;
#   endif
  }

  printf ("load %d/%d = %.3f\n",
           tbl->occupied, tbl->size, (double)tbl->occupied / tbl->size);
  printf ("%d probes (%d matches)\n", tbl->probes, tbl->matches);
  printf ("%d cache line accesses\n", lines);
  printf ("%.3f probes/insertion, %.3f lines/insertion\n",
           (double)tbl->probes/entries, (double)lines/entries);

  lphash_destroy(tbl);

  return 0;
}
