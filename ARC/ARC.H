/* Arsentev Artemy, 09-4, 16.10.2024 */

#include "GFX.H"

#define BACK_COLOR GFX_RGB(0, 0, 0)
#define ITEM_COLOR GFX_RGB(255, 255, 255)
#define DEBUG_COLOR GFX_RGB(255, 0, 0)
#define INTERFACE_COLOR GFX_RGB(0, 0, 255)
#define BR_NY 15
#define BR_NX 15
#define BR_W 15
#define BR_H 10
#define BR_X 75
#define BR_Y 40
#define MAX 30


void Game_Init( void );
void Game_Step( void );

static int StartGameFlag = 0;