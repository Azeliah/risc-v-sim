asm("li sp, 0x100000"); // SP set to 1 MB
asm("jal main");        // call main
asm("mv a1, x10");      // save return value in a1
asm("li a7, 10");       // prepare ecall exit
asm("ecall");           // now your simulator should stop


unsigned int getIntSquareRoot(unsigned int num) { // Determines x s.t. (x - 1)^2 < num =< x^2.
    int squareRoot = 0;
    int square = 0;
    while (square < num) {
        ++squareRoot;
        square = squareRoot;
        for (int i = 0; i < squareRoot - 1; ++i) {
            square += squareRoot;
        }
    }
    return squareRoot;
}

unsigned int rem(unsigned int num, unsigned int divisor) {
    while (num >= divisor) {
        num -= divisor;
    }
    return num;
}

int main() {
    int num = 2357;
    if (num <= 1) return 0;
    if (num & 1) {
        unsigned int sqrt = getIntSquareRoot(num);
        for (int i = 3; i < sqrt; i = i + 2) {
            if (rem(num, i) == 0) return 0;
        }
    } else {
        if (num == 2) return 1;
    }
    return 1;
}
