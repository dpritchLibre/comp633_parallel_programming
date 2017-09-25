#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <getopt.h>

#include "vec_2d.h"
#include "calc_bodies.h"

#define DT_DEFAULT 0.001
#define GRAV_CONST 0.00000000006673

#define N_DEFAULT  100
#define K_DEFAULT    4

void process_args(int argc, char *argv[], int *n, int *k, double *g, double *dt);
void initialize_bodies(double *m, struct vec_2d *r, struct vec_2d *v, size_t n);




int main(int argc, char *argv[]) {

    int n, k;
    double dt, g;
    process_args(argc, argv, &n, &k, &g, &dt);

    double m[n];
    struct vec_2d r[n];
    struct vec_2d v[n];
    initialize_bodies(m, r, v, n);

    calc_bodies(r, v, m, dt, n, g, k);

    printf("n: %d,  k: %d,  g: %e,  dt: %e\n", n, k, g, dt);

    return 0;
}




void process_args(int argc, char *argv[], int *n, int *k, double *g, double *dt) {

    *dt = 0.0;
    *g  = 0.0;
    *k = 0;
    *n = 0;

    // read command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, "d:g:k:n:")) != -1) {
	switch (opt) {
	case 'd':
	    *dt = atof(optarg);
	    if (*dt <= 0) {
		fprintf(stderr, "Error: dt must be a positive float\n");
	    }
	    break;
	case 'g':
	    *g = atof(optarg);
	    if (*dt <= 0) {
		fprintf(stderr, "Error: dt must be a positive float\n");
	    }
	    break;
	case 'k':
	    *k = atoi(optarg);
	    if (*k <= 0) {
		fprintf(stderr, "Error: k must be a positive integer\n");
	    }
	    break;
	case 'n':
	    *n = atoi(optarg);
	    if (*n <= 0) {
		fprintf(stderr, "Error: n must be a positive integer\n");
	    }
	    break;
	default:
	    fprintf(stderr, "Usage: %s [-n num_bodies] [-k num_timesteps]\n", argv[0]);
	    exit(EXIT_FAILURE);
	}
    }

    // case: dt unspecified
    if (*dt == 0.0) { *dt = DT_DEFAULT; }

    // case: g unspecified
    if (*g == 0.0) { *g = GRAV_CONST; }

    // case: k unspecified
    if (*k == 0) { *k = 4; }

    // case: n unspecified
    if (*n == 0) { *n = N_DEFAULT; }
}




void initialize_bodies(double *m, struct vec_2d *r, struct vec_2d *v, size_t n) {

    int square_size       = ceil(sqrt(n));
    double increment_size = 2.0 / ((double) (square_size - 1));

    for (size_t i = 0; i < square_size; i++) {

	double x1_val = -1.0;

	for (size_t j = 0; j < square_size; j++) {

	    // case: all bodies have been initialized
	    if ((i * square_size) + j == n) {
		return;
	    }

	    double x2_val = -1.0;

	    *m++ = 1.0;

	    r->x1 = x1_val;
	    r->x2 = x2_val += increment_size;
	    r++;

	    v->x1 = 0.0;
	    v->x2 = 0.0;
	    v++;
	}

	x1_val += increment_size;
    }
}
