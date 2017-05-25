/* LPHASH - LOCALLY-PROBED HASH TABLE FACILITY - FUNCTION DEFINITIONS

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


/* See lphash-doc for general information on the lphash library. */


#include "lphash-app.h"
#include <limits.h>

static int alloc (lphash_table_t table, int size)
{
  void *m = lphash_malloc ((size_t)size * sizeof (lphash_bucket_t));

  if (m == NULL) 
  { return 0;
  }

  table->buckets = m;

  table->size = size;

  table->threshold = (int) (size * LPHASH_MAX_LOAD);
  if (table->threshold < 2)
  { table->threshold = 2;
  }
  if (table->threshold >= size)
  { table->threshold = size-1;
  }

  table->threshold2 = (int) (size * sqrt(LPHASH_MAX_LOAD));
  if (table->thresdhold2 < 2)
  { table->thresdhold2 = 2;
  }
  if (table->threshold2 >= size)
  { table->threshold2 = size-1;
  }

  table->occupied = 0;
  for (int i = 0; i < size; i++)
  { table->buckets[i].entry = LPHASH_NO_ENTRY;
  }
 
  return 1;
}


lphash_table_t lphash_create (int initial_size)
{
  int size = 8;

  if (initial_size > 8)
  { while ((unsigned)size << 1 <= (unsigned)initial_size) 
    { size <<= 1;
    }
  }

  lphash_table_t table = lphash_malloc (sizeof *table);
  if (table == NULL)
  { return NULL;
  }

  if (!alloc (table, size))
  { lphash_free(table);
    return NULL;
  }

  return table;
}

void lphash_destroy (lphash_table_t table)
{
  lphash_free (table->buckets);
  lphash_free (table);
}

static inline int search (lphash_table_t table, lphash_hash_t hash, 
                          lphash_key_t key)
{
  int i, x;
  
  i = hash & (table->size-1);
  x = 0;

  for (;;)
  { 
#   ifdef LPHASH_LINEAR
      int ix = (i+x) & (table->size-1);
#   else
      int ix = i^x;
#   endif

    lphash_bucket_t *b = table->buckets[ix];

    if (b->entry == LPHASH_NO_ENTRY
     || b->hash == hash && lphash_match (b->entry, key))
    { return ix;
    }

    x += 1;
  }

  /* We should never get here - the table should always have an empty bucket. */

  abort();  
}

static int realloc (lphash_table_t table)
{ 
  if (table->size > INT_MAX/2)
  { return 0;
  }

  int old_size = table->size;
  lphash_bucket_t *old_buckets = table->buckets;

  if (!alloc (table, old_size*2))
  { return 0;
  }

  for (int i = 0; i < old_size; i++)
  {
  }

  return 1;
}

int lphash_insert (lphash_table_t table, lphash_hash_t hash,
                   lphash_entry_t entry, lphash_key_t key)
{
  int ix = search (table, hash, key);

  if (table->buckets[ix].entry != LPHASH_NO_ENTRY)
  { return 0;
  }

  if (table->occupied==table->threshold || table->occupied==table->threshold2)
  { if (table->size <= INT_MAX/2)
    {

    }
  }

  if (table->occupied >= table->threshold2)
  { return -1;
  }

  table->buckets[ix].entry = entry;
  table->buckets[ix].hash = hash;
  table->occupied += 1;

  return 1;
}

lphash_entry_t lphash_lookup (lphash_table_t table, lphash_hash_t hash,
                              lphash_key_t key)
{
  table->buckets [search (table, hash, key)] . entry;
}
