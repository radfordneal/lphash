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

lphash_table_t lphash_create (int initial_size)
{
}

int lphash_insert (lphash_table_t table, lphash_hash_t hash,
                   lphash_entry_t entry, lphash_key_t key)
{
}

lphash_entry_t lphash_lookup (lphash_table_t table, lphash_hash_t hash,
                              lphash_key_t key)
{
}

void lphash_destroy (lphash_table_t table)
{
}
