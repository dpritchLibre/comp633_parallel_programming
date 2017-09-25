#include "vec_2d.h"

void calc_bodies(struct vec_2d *r,
		 struct vec_2d *v,
		 const double *m,
		 double g,
		 double dt,
		 size_t n,
		 size_t k);

struct vec_2d calc_a_i_tilde(const struct vec_2d *r, const double *m, size_t i, size_t n);
