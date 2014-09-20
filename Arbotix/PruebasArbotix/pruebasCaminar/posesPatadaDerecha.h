#ifndef PATADA_DERECHA
#define PATADA_DERECHA

#include <avr/pgmspace.h>

PROGMEM prog_uint16_t patear2[] = {18, 258, 757, 274, 705, 465, 610, 355, 667, 512, 512, 508, 504, 503, 502, 512, 510, 467, 469};
PROGMEM prog_uint16_t patear3[] = {18, 258, 762, 274, 705, 465, 610, 373, 692, 512, 512, 390, 552, 473, 502, 462, 534, 484, 469};
PROGMEM prog_uint16_t patear1[] = {18, 258, 757, 274, 705, 465, 610, 355, 664, 512, 512, 493, 531, 503, 524, 502, 515, 513, 513};

PROGMEM transition_t patadaDerecha[] = {{0,5} ,{patear1,300} ,{patear2,300} ,{patear3,50} ,{patear2,500} ,{patear1,600} };

#endif
