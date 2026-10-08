#include <bn_backdrop.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_log.h>

#include "bn_sprite_items_bun.h"

#define FLOOR (80 - 8)

static constexpr int jump_limit = 2;

int main()
{
    bn::core::init();

    bn::backdrop::set_color(bn::color(12, 26, 28));

    auto dot = bn::sprite_items::bun.create_sprite(0, 0);

    bn::fixed speed = 3.5;

    bn::fixed dy = 0;
    bn::fixed gravity = .03;

    bn::fixed jump_strength = 1.3;

    int jump_counter = 0;
    bool is_at_jump_limit = false;

    while (true)
    {

        BN_LOG("Bunny current Y POS | ", dot.y());

        if (bn::keypad::left_held())
        {
            dot.set_horizontal_flip(false);
            if (dot.x() <= -130)
            {
                dot.set_x(130);
            }
            else
            {
                dot.set_x(dot.x() - speed);
            }
        }
        if (bn::keypad::right_held())
        {
            dot.set_horizontal_flip(true);

            if (dot.x() >= 130)
            {
                dot.set_x(-130);
            }
            else
            {
                dot.set_x(dot.x() + speed);
            }
        }
        if (bn::keypad::a_pressed())
        {
            dy -= jump_strength;
        }

        dy += gravity;

        dot.set_y(dot.y() + dy);

        if (dot.y() > FLOOR)
        {
            dot.set_y(FLOOR);
            dy = 0;
        }
        bn::core::update();
    }
}