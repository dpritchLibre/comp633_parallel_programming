#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "calc_bodies.h"
#include "vec_2d.h"




// updates position and velocity arrays `r` and `v`, after `k * dt` time.  `m`
// is an array of the masses of the corresponding bodies, `g` is the
// gravitational constant, `dt` is the amount of time passing in each increment,
// `n` is the number of bodies in the system, and `k` is the number of time
// increments to update.

void calc_bodies(struct vec_2d *r,
		 struct vec_2d *v,
		 const double *m,
		 double g,
		 double dt,
		 size_t n,
		 size_t k) {

    const double dtG = dt * g;

    // obtain memory for `a_tilde` and initialize to 0
    struct vec_2d *a_tilde = (struct vec_2d *) malloc (n * sizeof(struct vec_2d));
    if (a_tilde == NULL) {
	fprintf(stderr, "Error: memory allocation failure\n");
	exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < n; i++) {
	a_tilde[i].x1 = 0;
	a_tilde[i].x2 = 0;
    }

    // the `t`-th iteration updates every element in `r` and `v` to the position
    // and velocity of the respective element at time `delta * t`
    for (size_t t = 1; t <= k; t++) {

	// update the elements of `a_tilde`
	calc_a_tilde(a_tilde, r, m, n);

	// update the `i`-th elements of `r` and `v` to be position and velocity
	// at time `delta * t`
	for (size_t i = 0; i < n; i++) {

	    // update `r[i]` given the current velocity
	    r[i].x1 += dt * v[i].x1;
	    r[i].x2 += dt * v[i].x2;

	    // update the current velocity
	    v[i].x1 += dtG * a_tilde[i].x1;
	    v[i].x2 += dtG * a_tilde[i].x2;

	    // reset `a_tilde_i` to 0 in preparation for the next iteration
	    a_tilde[i].x1 = 0;
	    a_tilde[i].x2 = 0;
	}
    }
}



#include <stdio.h>
// update the elements of `a_tilde`, where the i-th element is defined as `a_i /
// G`

void calc_a_tilde(struct vec_2d *a_tilde,
		  const struct vec_2d *r,
		  const double *m,
		  size_t n) {

    // calculate `a_i / G` for each value of `i`
    for (size_t i = 0; i < n; i++) {

	// each iteration adds the value of `f_ij` to `a_i_tilde`
	for (size_t j = i + 1; j < n; j++) {

	    // `r_ij = r_j - r_i`
	    double r_ij_x1 = r[j].x1 - r[i].x1;
	    double r_ij_x2 = r[j].x2 - r[i].x2;

	    // `scalar_mult` is defined as
	    //
	    //          m_j
	    //     -------------
	    //     || r_ij ||^3
	    //
	    double scalar_mult = m[j] * pow((r_ij_x1 * r_ij_x1) + (r_ij_x2 * r_ij_x2), -1.5);

	    // `f_ij / G`
	    double x1 = scalar_mult * r_ij_x1;
	    double x2 = scalar_mult * r_ij_x2;

	    // add `f_ij / G` to the running total for `a_i / G`
	    a_tilde[i].x1 += x1;
	    a_tilde[i].x2 += x2;

	    // add `-f_ij / G = f_ji / G` to the running total for `a_j / G`
	    a_tilde[j].x1 -= x1;
	    a_tilde[j].x2 -= x2;
	}
    }
}
