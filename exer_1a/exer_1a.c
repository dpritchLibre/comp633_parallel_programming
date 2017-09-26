#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <getopt.h>
#include <time.h>

#include "vec_2d.h"
#include "calc_bodies.h"

#define DT_DEFAULT 0.001
#define GRAV_CONST 0.00000000006673 // gravitational constant
#define NANO_MULT  0.000000001      // nano multiplier, i.e. 1e-9

#define N_DEFAULT  100
#define K_DEFAULT    4

void process_args(int argc, char *argv[], size_t *n, size_t *k, double *g, double *dt, size_t *blk_size);
void initialize_bodies(double *m, struct vec_2d *r, struct vec_2d *v, size_t n);
double timer_calc_bodies(struct vec_2d *r,
			 struct vec_2d *v,
			 const double *m,
			 double g,
			 double dt,
			 size_t n,
			 size_t k,
			 size_t blk_size);




int main(int argc, char *argv[]) {

    size_t n, k, blk_size;
    double dt, g;
    process_args(argc, argv, &n, &k, &g, &dt, &blk_size);

    double *m = (double *) malloc(n * sizeof(double));
    struct vec_2d *r = (struct vec_2d *) malloc (n * sizeof(struct vec_2d));
    struct vec_2d *v = (struct vec_2d *) malloc (n * sizeof(struct vec_2d));
    if ((m == NULL) || (r == NULL) || (v == NULL)) {
	fprintf(stderr, "Error: memory allocation failure\n");
	exit(EXIT_FAILURE);
    }
    initialize_bodies(m, r, v, n);

    double elapsed = timer_calc_bodies(r, v, m, g, dt, n, k, blk_size);

    printf("%f  n: %zu,  k: %zu,  g: %e,  dt: %e\n", elapsed, n, k, g, dt);

    return 0;
}




void process_args(int argc, char *argv[], size_t *n, size_t *k, double *g, double *dt, size_t *blk_size) {

    *dt = 0.0;
    *g  = 0.0;
    *k = 0;
    *n = 0;
    *blk_size = 0;

    // read command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, "b:d:g:k:n:")) != -1) {
	switch (opt) {
	case 'b':
	    *blk_size = atoi(optarg);
	    if (*blk_size <= 0) {
		fprintf(stderr, "Error: blk_size must be a positive integer\n");
	    }
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




double timer_calc_bodies(struct vec_2d *r,
			 struct vec_2d *v,
			 const double *m,
			 double g,
			 double dt,
			 size_t n,
			 size_t k,
			 size_t blk_size) {

    // storage for function starting and ending times
    struct timespec start;
    struct timespec end;

    // start timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    // all-pairs n-body simulation
    if (blk_size == 0) {
	calc_bodies(r, v, m, g, dt, n, k);
    } else {
	calc_bodies_blk(r, v, m, g, dt, n, k, blk_size);
    }

    // end timer
    clock_gettime(CLOCK_MONOTONIC, &end);

    return end.tv_sec - start.tv_sec + ((end.tv_nsec - start.tv_nsec) * NANO_MULT);
}
