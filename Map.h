// Copyright (c) by Wayne C. Gramlich.  All rights reserved.

#if !defined(MAP_H_INCLUDED)
#define MAP_H_INCLUDED 1

/// @brief *Map* is the representation of a fiducial marker map.
typedef struct Map__Struct *Map;

#include "File.h"
#include "List.h"
#include "Map.h"
#include "Table.h"
#include "Tag.h"
#include "Unsigned.h"

/// @brief A *Map__Struct* represents the fiducial location map.
struct Map__Struct {
    /// @brief The list of tags (i.e. fiducial markers.)
    List tags;

    /// @brief Table of all *tags* indexed by *id.
    Table tags_table;
};

// *Map* routines:

extern Integer Map__compare(Map map1, Map map2);
extern Map Map__new(void);
extern Map Map__read(File in_file);
extern Map Map__restore(String file_name);
extern void Map__save(Map map, String file_name);
extern void Map__sort(Map map);
extern Tag Map__tag_lookup(Map map, Unsigned tag_id);
extern void Map__write(Map map, File out_file);

#endif // !defined(MAP_H_INCLUDED)
