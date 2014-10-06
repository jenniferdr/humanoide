#ifndef HUMANOIDE_POSES
#define HUMANOIDE_POSES

#include <avr/pgmspace.h>

PROGMEM prog_uint16_t pi2[] = {18, 258, 757, 282, 705, 463, 610, 353, 663, 512, 512, 482, 539, 517, 522, 490, 513, 558, 565};
PROGMEM prog_uint16_t pi3[] = {18, 264, 757, 282, 705, 463, 610, 352, 664, 512, 512, 487, 599, 517, 530, 495, 534, 555, 551};
PROGMEM prog_uint16_t pi1[] = {18, 259, 757, 274, 705, 463, 612, 355, 666, 512, 512, 497, 532, 503, 524, 504, 516, 514, 513};

PROGMEM transition_t patadaIzquierda[] = {{0,5} ,{pi1,500} ,{pi2,500} ,{pi3,50} ,{pi2,600} ,{pi1,600} };

#endif
