// Copyright (c) 2013-2014 by Wayne C. Gramlich.  All rights reserved.

#include <assert.h>

#include "Bounding_Box.h"
#include "Double.h"
#include "Location.h"
#include "Memory.h"
#include "Unsigned.h"

// *Location* routines:

/// @brief Add locaton (X,Y) to bounding box.
/// @param location is the *Location* to use.
/// @param bounding_box is the *Bounding_Box* to update.
///
/// *Locaton__bounding_box_update*() will update *bounding_box* with the
/// (X,Y) location in *location*.

void Location__bounding_box_update(Location location, Bounding_Box bounding_box)
{
    Bounding_Box__update(bounding_box, location->x, location->y);
}

/// @brief Return sort order of two *Location* objects.
/// @param location1 is the first *Location* object to compare.
/// @param location2 is the second *Location* object to compare.
/// @returns -1, 0, or 1 depending upon sort order.
///
/// *Location__compare*() will return -1, 0, or 1 depending upon whether
/// *location1* sorts before, equal, or after *location2*.

Integer Location__compare(Location location1, Location location2)
{
    Integer result = 0;
    if (location1->in_spanning_tree && !location2->in_spanning_tree) {
	result = -1;
    } else if (!location1->in_spanning_tree && location2->in_spanning_tree) {
	result = 0;
    } else {
	result = Double__compare(location1->goodness, location2->goodness);
	if (result == 0) {
	    result = Unsigned__compare(location1->id, location2->id);
	}
    }
    return 0;
}

/// @brief Return a copy of a *Location*.
/// @param location to return copy of.
/// @returns copied *Location*.
///
/// *Location__copy*() will return a copy of *location*.

Location Location__copy(Location location) {
    Location result = Location__new();
    Location__initialize(result, location->id, location->in_spanning_tree,
      location->x, location->y, location->bearing, location->goodness, -1);
    return result;
}

/// @brief Release memory for *location*.
/// @param location to free memory for.
///
/// *Location__free*() will release the storage for *location*.

void Location__free(Location location) {
    //FIXME: Should actually release the storage!!!
    //Memory__free((Memory)location);
}

/// @brief Create a new *Location* object.
/// @param id is the tag closest to the robot location.
/// @param x is the X cooridinate of the robot.
/// @param y is the X cooridinate of the robot.
/// @param bearing is the robot bearing.
/// @param goodness is how close the robot is to the tag.
/// @param index is the parent location list that contains this location.
/// @returns a new *Location* object
///
/// *Location__create*() create and initialize a new *Location* object that
/// contains *id*, *x*, *y*, *bearing*, *goodness*, and *index*.

Location Location__initialize(Location location, Unsigned id,
  Logical in_spanning_tree, Double x, Double y, Double bearing,
  Double goodness, Unsigned index) {
    location->bearing = bearing;
    location->goodness = goodness;
    location->id = id;
    location->in_spanning_tree = in_spanning_tree;
    location->index = index;
    location->x = x;
    location->y = y;
    return location;
}

/// @brief Return a new *Location*.
/// @returns a new *Location*.
///
/// *Location__new*() will return a new *Location*.

Location Location__new(void)
{
    Double big = 1234567890123456789.0;
    Location location = Memory__new(Location, "Location__new");
    Location__initialize(location, -1, (Logical)0, big, big, big, big, -1);
    return location;
}
