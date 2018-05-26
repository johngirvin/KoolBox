#ifndef KOOLBOX_GRAPHICS_COLOURS_H
#define KOOLBOX_GRAPHICS_COLOURS_H

#include "KoolBoxShared.h"

namespace KoolBox
{
    extern Colour LIGHTGRAY = { };
#define LIGHTGRAY  CLITERAL{ 200, 200, 200, 255 }   // Light Gray
#define GRAY       CLITERAL{ 130, 130, 130, 255 }   // Gray
#define DARKGRAY   CLITERAL{ 80, 80, 80, 255 }      // Dark Gray
#define YELLOW     CLITERAL{ 253, 249, 0, 255 }     // Yellow
#define GOLD       CLITERAL{ 255, 203, 0, 255 }     // Gold
#define ORANGE     CLITERAL{ 255, 161, 0, 255 }     // Orange
#define PINK       CLITERAL{ 255, 109, 194, 255 }   // Pink
#define RED        CLITERAL{ 230, 41, 55, 255 }     // Red
#define MAROON     CLITERAL{ 190, 33, 55, 255 }     // Maroon
#define GREEN      CLITERAL{ 0, 228, 48, 255 }      // Green
#define LIME       CLITERAL{ 0, 158, 47, 255 }      // Lime
#define DARKGREEN  CLITERAL{ 0, 117, 44, 255 }      // Dark Green
#define SKYBLUE    CLITERAL{ 102, 191, 255, 255 }   // Sky Blue
#define BLUE       CLITERAL{ 0, 121, 241, 255 }     // Blue
#define DARKBLUE   CLITERAL{ 0, 82, 172, 255 }      // Dark Blue
#define PURPLE     CLITERAL{ 200, 122, 255, 255 }   // Purple
#define VIOLET     CLITERAL{ 135, 60, 190, 255 }    // Violet
#define DARKPURPLE CLITERAL{ 112, 31, 126, 255 }    // Dark Purple
#define BEIGE      CLITERAL{ 211, 176, 131, 255 }   // Beige
#define BROWN      CLITERAL{ 127, 106, 79, 255 }    // Brown
#define DARKBROWN  CLITERAL{ 76, 63, 47, 255 }      // Dark Brown

#define WHITE      CLITERAL{ 255, 255, 255, 255 }   // White
#define BLACK      CLITERAL{ 0, 0, 0, 255 }         // Black
#define BLANK      CLITERAL{ 0, 0, 0, 0 }           // Blank (Transparent)
#define MAGENTA    CLITERAL{ 255, 0, 255, 255 }     // Magenta
#define RAYWHITE   CLITERAL{ 245, 245, 245, 255 }   // My own White (raylib logo)

}

#endif
