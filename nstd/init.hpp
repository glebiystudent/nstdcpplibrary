#pragma once

// init.hpp
// includes all the needed features of a library
// use this!


// extra features that are not included if you #define __compressed before including this file
#include "extra/log.hpp"
#include "extra/argsindexing.hpp"
#include "extra/format.hpp"

// main library features that are always gonna be included in
#include "main/map.hpp"
#include "main/string.hpp"
#include "main/vector.hpp"
#include "main/stack.hpp"