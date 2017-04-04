#ifndef Control
#define g 16384
void stayStable() {
	  while (acc[1] < g + 100 && acc[1] > g - 100) {
		if (acc[0] > 0.01 * g || acc[0] < -0.01 * g) {
			moveInXDir(-0.01 * acc[0]);
		}
		if (acc[2] > 0.01 * g || acc[2] < -0.01 * g) {
			moveInZDir(-0.01 * acc[2]);
		}

}

#endif
