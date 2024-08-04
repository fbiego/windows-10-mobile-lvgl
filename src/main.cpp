#include <stdint.h>
#include "app_hal.h"


#ifdef USE_SDL
// emulator with SDL
int main(void){

    hal_setup();
    
    hal_loop();

    return 0;
};
#else
// esp32 hardware
void setup(){
    hal_setup();
}

void loop(){
    hal_loop();
}
#endif