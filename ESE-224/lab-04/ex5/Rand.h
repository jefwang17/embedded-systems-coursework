#ifndef RAND_H
#define RAND_H

class Rand {
public:
    static void seed(unsigned s);
    static int  nextInt(int minIncl, int maxIncl); // inclusive
    static double next01();                        // [0,1)
};

#endif
