#ifndef _MAIN_H
#define _MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "nodes.h"
#include "components.h"
#include "degrees.h"
#include "paths.h"

#define MODE_COMPONENTSTAT 1
#define MODE_COMPONENTLIST 2
#define MODE_DEGREESTAT 4
#define MODE_DEGREELIST 8
#define MODE_PATH 16

#define MODE_COMPONENTS MODE_COMPONENTSTAT | MODE_COMPONENTLIST
#define MODE_DEGREES MODE_DEGREESTAT | MODE_DEGREELIST
#define MODE_STATS MODE_COMPONENTSTAT | MODE_DEGREESTAT

#endif
