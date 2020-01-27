#include "xd60.h"

uint32_t bottom_rgb = 0x00800000;
uint32_t bottom_center_rgb = 0x00800000;
bool is_caps_lock = false;

void set_bottom_light(void) {
#define RR(var) ((var>>16) & 0xFF)
#define GG(var) ((var>>8) & 0xFF)
#define BB(var) ((var>>0) & 0xFF)
#define RGB(var) RR(var), GG(var), BB(var)

    // led 0-1, 4-5
    setrgb(RGB(bottom_rgb), led+0);
    setrgb(RGB(bottom_rgb), led+1);
    setrgb(RGB(bottom_rgb), led+4);
    setrgb(RGB(bottom_rgb), led+5);

    // led 2-3, bottom center (mood light / caps lock)
    setrgb(RGB(bottom_center_rgb), led+2);
    setrgb(RGB(bottom_center_rgb), led+3);

#undef RGB
#undef BB
#undef GG
#undef RR

    rgblight_set();
}

#undef IS_BACKLIT_FLAG_SET

extern inline void xd60_caps_led_on(void);
extern inline void xd60_bl_led_on(void);

extern inline void xd60_caps_led_off(void);
extern inline void xd60_bl_led_off(void);

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
	    xd60_caps_led_on();
        is_caps_lock = true;
    } else {
	    xd60_caps_led_off();
        is_caps_lock = false;
    }

    led_set_user(usb_led);
}
