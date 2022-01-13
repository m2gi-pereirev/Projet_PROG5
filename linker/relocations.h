#ifndef __RELOCATIONS_H__
#define __RELOCATIONS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "section_manipulator.h"
#include "freed.h"
#include "reorganization.h"


void relocations_execution(Elf32_file *elf);

#endif