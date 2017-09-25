GRAV_CONST <- 1
dt <- 1e-6

r0 <- c(-0.97000436,  0.24308753)
r1 <- c( 0.97000436, -0.24308753)
r2 <- c( 0,           0)

v0 <- c(-0.46620368, -0.43236573)
v1 <- c(-0.46620368, -0.43236573)
v2 <- c( 0.93240737,  0.86473146)




# define sim functions ---------------------------------------------------------

calc_f_ij <- function(r_i, r_j, m_i, m_j) {
    r_ij <- r_j - r_i
    scalar_mult <- GRAV_CONST * m_i * m_j / sum(r_ij^2)^1.5
    scalar_mult * r_ij
}

calc_a_i <- function(r, v, m, i) {

    f_i <- rep(0, length(r[[1]]))
    for (j in setdiff(seq_along(r), i)) {
        f_i <- f_i + calc_f_ij(r[[i]], r[[j]], m[i], m[j])
    }

    f_i / m[i]
}

update_r <- function(r, v, dt) {
    r_new <- vector("list", length(r))
    for (i in seq_along(r_new)) {
        r_new[[i]] <- r[[i]] + (dt * v[[i]])
    }
    r_new
}

update_v <- function(r, v, m, dt) {

    a <- vector("list", length(v))
    for (i in seq_along(a)) {
        a[[i]] <- calc_a_i(r, v, m, i)
    }

    v_new <- setNames(vector("list", length(v)), names(v))
    for (i in seq_along(v_new)) {
        v_new[[i]] <- v[[i]] + (dt * a[[i]])
    }
    v_new
}




# step 1 -----------------------------------------------------------------------

r <- list(r0 = r0, r1 = r1, r2 = r2)
v <- list(v0 = v0, v1 = v1, v2 = v2)
m <- c(1, 1, 1)

r_out <- r
v_out <- v

start_time <- proc.time()
for (t in 1:(3.162957 / dt)) {

    v_new <- update_v(r_out, v_out, m, dt)
    r_out <- update_r(r_out, v_out, dt)

    v_out <- v_new
}
end_time <- proc.time()
end_time - start_time

r_out
v_out




# step 2 -----------------------------------------------------------------------

start_time <- proc.time()
for (t in 1:(3.162957 / dt)) {

    v_new <- update_v(r_out, v_out, m, dt)
    r_out <- update_r(r_out, v_out, dt)

    v_out <- v_new
}
end_time <- proc.time()
end_time - start_time

r_out
v_out
