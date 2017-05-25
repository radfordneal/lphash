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

#include "lphash-app.h"

int lphash_match (lphash_entry_t entry, lphash_key_t key)
{
  return entry == atoi(key);
}

lphash_entry_t lphash_make_entry (lphash_key_t key)
{
  return atoi(key);
}

lphash_hash_t hash (lphash_key_t key)
{
  lphash_hash_t h;
  int i;

  h = 0;
  for (i = 0; key[i] != 0; i++)
  { h = 5*h + (key[i]-'0');
  }

  return h;
}

char *tests[] = { "4", "10", "5", "12", "1050", "7", "1100", "1045" };

int main (int argc, char **argv)
{
  lphash_table_t tbl;

  tbl = lphash_create (64);
  if (tbl == NULL)
  { fprintf (stderr, "Can't create table\n");
    exit(1);
  }

  int s, t;
  for (t = 0; ; t++)
  { 
    printf("\n");
    for (s = 0; tests[s]; s++)
    { printf(" %4s",tests[s]);
    }
    printf("\n");
    for (s = 0; tests[s]; s++)
    { printf(" %4d",hash(tests[s]));
    }
    printf("\n");
    for (s = 0; tests[s]; s++)
    { printf(" %4d",lphash_lookup(tbl,hash(tests[s]),tests[s]));
    }
    printf("\n");

    if (tests[t] == 0)
    { break;
    }

    printf ("\nInserting %s: %d\n", tests[t], 
            lphash_insert(tbl,hash(tests[t]),tests[t]));
  }

  lphash_destroy(tbl);

  return 0;
}
