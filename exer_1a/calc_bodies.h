#include "vec_2d.h"

void calc_bodies(struct vec_2d *r,
		     struct vec_2d *v,
		     const double *m,
		     double g,
		     double dt,
		     size_t n,
		     size_t k);

void calc_bodies_blk(struct vec_2d *r,
		     struct vec_2d *v,
		     const double *m,
		     double g,
		     double dt,
		     size_t n,
		     size_t k,
		     size_t blk_size);

void calc_a_tilde(struct vec_2d *a_tilde, const struct vec_2d *r, const double *m, size_t n);

void calc_a_tilde_blk(struct vec_2d *a_tilde,
		      const struct vec_2d *r,
		      const double *m,
		      size_t n,
		      size_t blk_size);
