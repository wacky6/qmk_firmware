#include "xd60.h"

uint32_t backlit_flags;
uint8_t  backlit_base;

uint8_t get_base_g(void) {
    switch (backlit_base) {
        case 1:   return 127;
        default:  return 0;
    }
}

uint8_t get_base_b(void) {
    switch (backlit_base) {
        default:  return 0;
    }
}

uint8_t get_base_r(void) {
    switch (backlit_base) {
        case 1:   return 0;
        default:  return 127;
    }
}

#define IS_BACKLIT_FLAG_SET(flag) ( backlit_flags & (1<<(flag) ) )

void set_backlit(void) {
    uint8_t r = get_base_r(),
            g = get_base_g(),
            b = get_base_b();

    // led 0-1
    setrgb(r, g, b, led+0);
    setrgb(r, g, b, led+1);
    // led 2-3, used as caps_lock indicator
    if ( IS_BACKLIT_FLAG_SET(BF_CAPS) ) {
        setrgb(r, g, 255, led+2);
        setrgb(r, g, 255, led+3);
    } else {
		setrgb(r, g, b, led+2);
		setrgb(r, g, b, led+3);
	}
    // led 4-5
    setrgb(r, g, b, led+4);
    setrgb(r, g, b, led+5);

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
    } else {
	    xd60_caps_led_off();
    }

    led_set_user(usb_led);
}
