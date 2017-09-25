#include <stddef.h>
#include <math.h>

#include "calc_bodies.h"
#include "vec_2d.h"




// updates position and velocity arrays `r` and `v`, after `k * dt` time.  `m`
// is an array of the masses of the corresponding bodies, and `n` specifies how
// many bodies are in the system.

void calc_bodies(struct vec_2d *r,
		 struct vec_2d *v,
		 const double *m,
		 double g,
		 double dt,
		 size_t n,
		 size_t k) {

    double dtG = dt * g;
    struct vec_2d a_tilde[n];

    // the `t`-th iteration updates every element in `r` and `v` to the position
    // and velocity of the respective element at time `delta * t`
    for (size_t t = 1; t <= k; t++) {

	for (int i = 0; i < n; i++) {
	    a_tilde[i] = calc_a_i_tilde(r, m, i, n);
	}

	// update the `i`-th elements of `r` and `v` to be position and velocity
	// at time `delta * t`
	for (int i = 0; i < n; i++) {

	    // update `r[i]` given the current velocity
	    r[i].x1 += dt * v[i].x1;
	    r[i].x2 += dt * v[i].x2;

	    // update the current velocity
	    // struct vec_2d a_i_tilde = calc_a_i_tilde(r, m, i, n);
	    v[i].x1 += dtG * a_tilde[i].x1;
	    v[i].x2 += dtG * a_tilde[i].x2;
	}
    }
}




// returns the value of `a_i / G`

struct vec_2d calc_a_i_tilde(const struct vec_2d *r,
			     const double *m,
			     size_t i,
			     size_t n) {

    // define `a_i_tilde = a_i / G` where `G` is the gravitational constant
    struct vec_2d a_i_tilde;
    a_i_tilde.x1 = 0;
    a_i_tilde.x2 = 0;

    // each iteration adds the value of `f_ij` to `a_i_tilde`
    for (size_t j = 0; j < n; j++) {
	if (j == i) {
	    continue;
	}

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

	// `a_i_tilde = scalar_mult * r_ij`
	a_i_tilde.x1 += scalar_mult * r_ij_x1;
	a_i_tilde.x2 += scalar_mult * r_ij_x2;
    }

    return a_i_tilde;
}
