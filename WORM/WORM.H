/* Arsentev Artemy, 09-4, 21.10.2024 */
#include "GFX.H"

#define WRM_COLOR_BACK GFX_RGB(0, 0, 0)
#define WRM_COLOR_GOOD GFX_RGB(0, 255, 0)
#define WRM_COLOR_BAD GFX_RGB(255, 0, 0)
#define WRM_COLOR_FREE GFX_RGB(0, 0, 0)
#define WRM_COLOR_WORM GFX_RGB(100, 100, 100)

#define WRM_FIELD_W 77
#define WRM_FIELD_H 45

#define WRM_SPOT_FREE 0
#define WRM_SPOT_GOOD 1
#define WRM_SPOT_BAD 2
#define WRM_SPOT_WORM 3
#define WRM_SPOT_HEAD 4

#define WRM_SPOT_SIZE 5
#define WRM_MAX_LENGTH 10

#define WORM_MAX 5

#define WRM_FIELD_X 0
#define WRM_FIELD_Y 0

void WRM_Init( void );
void WRM_Step( void );
void WRM_Kbd( unsigned char Key );