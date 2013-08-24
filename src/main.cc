#include <Arduino.h>
#include <Stepper.h>

#define LENGTH 15

/*
 * Stepper 1 Config
 */
#define SP1_1 10
#define SP1_2 11
#define SP1_3 12
#define SP1_4 13
#define SP1_STEPS 48
#define SP1_MAXSPD 60
#define SP1_DH -1
#define SP1_DL  1

/*
 * Stepper 2 Config
 */
#define SP2_1 6
#define SP2_2 7
#define SP2_3 8
#define SP2_4 9
#define SP2_STEPS 48
#define SP2_MAXSPD 60
#define SP2_DH  1
#define SP2_DL -1

int d1, d2, ft = 0;
int p1, p2 = 0;
void Bresenham(int, int, int const, int const);
void carterToBipolar(int, int);

void stepperInit(Stepper &sp, int speed) {
    // set the speed
    sp.setSpeed(speed);
}

/**
 * Draw a pattern
 *
 * sp1: Stepper 1
 * sp2: Stepper 2
 * size: Pattern Size
 * dir: Direction
 */
void draw_pattern_3(Stepper &sp1, Stepper &sp2, int size, int d1, int d2) {
    while (size) {

        sp1.step(d1);
        sp2.step(d2);
        delay(25);

        size--;
    }
}



//int main()
//{
//  Bresenham(3,4,8,7);

//    return 0;
//}

void setup() {
    Stepper s1(SP1_STEPS, SP1_1, SP1_2, SP1_3, SP1_4);
    Stepper s2(SP2_STEPS, SP2_1, SP2_2, SP2_3, SP2_4);

    stepperInit(s1, SP1_MAXSPD);
    stepperInit(s2, SP2_MAXSPD);
    draw_pattern_3(s1, s2, 48, SP1_DH, SP2_DH);
}

void carterToBipolar(int x, int y) {
    int l1, l2;
    l1 = abs(sqrt(x * x + y * y));
    l2 = abs(sqrt(pow(LENGTH - x, 2) + y * y));

    d1 = p1 - l1; //diferencia 1
    d2 = p2 - l2; //diferencia 2
    p1 = l1; //pasos 1
    p2 = l2; //pasos 2


 //   printf("cart (%d,%d)\tbipol(%d,%d)\t D(%d,%d) \n", x, y, l1, l2, d1, d2);

}

void Bresenham(int x1, int y1, int const x2, int const y2) {
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = abs(delta_y) << 1;

    carterToBipolar(x1, y1);

    if (delta_x >= delta_y) {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2) {
            if ((error >= 0) && (error || (ix > 0))) {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;
            carterToBipolar(x1, y1);
        }
    } else {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2) {
            if ((error >= 0) && (error || (iy > 0))) {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing
            error += delta_x;
            y1 += iy;
            carterToBipolar(x1, y1);
        }
    }
}

void loop() {
}
