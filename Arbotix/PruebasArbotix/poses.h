#ifndef J_POSES
#define J_POSES

#include <avr/pgmspace.h>

PROGMEM prog_uint16_t pose_1[] = {18, 204, 812, 265, 757, 468, 548, 360, 672, 512, 512, 508, 507, 512, 501, 518, 507, 510, 506};
PROGMEM prog_uint16_t pose_2[] = {18, 181, 744, 262, 749, 468, 548, 366, 674, 512, 512, 458, 544, 481, 501, 517, 527, 460, 484};
PROGMEM prog_uint16_t pose_3[] = {18, 183, 765, 263, 760, 468, 548, 349, 667, 512, 512, 458, 497, 435, 501, 528, 508, 488, 488};
PROGMEM prog_uint16_t pose_4[] = {18, 207, 775, 261, 757, 468, 548, 340, 657, 512, 512, 422, 517, 435, 501, 515, 510, 510, 503};
PROGMEM prog_uint16_t pose_5[] = {18, 238, 766, 262, 757, 468, 548, 359, 674, 512, 512, 492, 498, 517, 501, 495, 497, 509, 501};
PROGMEM prog_uint16_t pose_6[] = {18, 277, 784, 260, 756, 468, 548, 363, 668, 512, 512, 494, 495, 517, 502, 509, 487, 538, 562};
PROGMEM prog_uint16_t pose_7[] = {18, 275, 783, 260, 756, 468, 548, 361, 668, 512, 512, 493, 552, 517, 557, 507, 487, 538, 558};
PROGMEM prog_uint16_t pose_8[] = {18, 238, 755, 261, 757, 469, 548, 355, 670, 512, 512, 485, 554, 480, 554, 531, 494, 551, 553};
PROGMEM prog_uint16_t pose_9[] = {18, 237, 793, 260, 756, 468, 548, 356, 674, 512, 512, 533, 553, 517, 565, 523, 496, 541, 525};
PROGMEM prog_uint16_t pose_10[] = {18, 251, 782, 258, 755, 468, 548, 355, 661, 512, 512, 508, 533, 492, 503, 534, 517, 468, 472};

PROGMEM transition_t camina[] = {{0,10} ,{pose_2,300} ,{pose_3,300} ,{pose_4,500} ,{pose_5,300} ,{pose_6,300} ,{pose_7,300} ,{pose_8,300} ,{pose_9,300} ,{pose_10,300} ,{pose_1,300}};

#endif
