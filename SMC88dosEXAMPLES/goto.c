#include <stdio.h>

loop() {
        int i,s;
        i = 10;
		if (i < 20) {
			goto l1;
		}
		else {
			goto l2;
		}
		l1: s = 2;
		l2: s = 3;
        
        return s;

}
