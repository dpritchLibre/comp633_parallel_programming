library(magrittr)

n_vec <- c(10L, 20L, 50L, 100L, 200L, 500L, 1000L, 2000L, 5000L, 10000L)

n_samp <- 10L




# collect algorithm runtimes ---------------------------------------------------

collect_runtimes <- function(n_vec, n_samp) {

    get_runtime <- function(n) {
        arg_text <- paste0("./exer_1a -n ", n, " -k 4 | cut -f1 -d' '")
        system(arg_text, intern = TRUE) %>% as.numeric
    }

    runtimes <- list()
    for (i in seq_along(n_vec)) {

        n <- n_vec[i]
        runtimes[[paste0("n", n)]] <- replicate(n_samp, get_runtime(n))
    }

    runtimes
}

collect_runtimes_blk <- function(blk_size_vec, n, n_samp) {

    get_runtime <- function(blk_size, n) {
        arg_text <- paste0("./exer_1a -n ", format(n, scientific = FALSE),
                           " -k 4 -b ", blk_size, " | cut -f1 -d' '")
        system(arg_text, intern = TRUE) %>% as.numeric
    }

    runtimes <- list()
    for (i in seq_along(blk_size_vec)) {

        blk_size <- blk_size_vec[i]
        runtimes[[paste0("b", blk_size)]] <- replicate(n_samp, get_runtime(blk_size, n))
    }

    runtimes
}




# plot runtimes ----------------------------------------------------------------


# mean_runtimes <- sapply(runtimes, mean) %>% log2

# x_vals <- log2(n_vec)

# plot(x_vals, mean_runtimes, type = "o")



# print runtimes ---------------------------------------------------------------

perf_metric <- function(x, n, k) {
    k * n^2 / x
}

runtimes <- collect_runtimes(n_vec, n_samp)
mean_runtimes <- sapply(runtimes, mean)


blk_size_vec <- c(100L, 200L, 500L, 1000L, 2500L, 5000L, 7500L, 10000L, 20000L)
runtimes_blk <- collect_runtimes_blk(blk_size_vec, 100000L, 3L)

trans_times <- mapply(perf_metric, runtimes, n_vec, 4)

boxplot(trans_times)
boxplot(lapply(runtimes, log2))
boxplot(lapply(runtimes, log10), add = TRUE)

quantile_runtimes <- sapply(runtimes, quantile, probs = c(0.5, 0.025, 0.975))

format(quantile_runtimes, nsmall = 2, digits = 2) %>% t %>% noquote




# formula to calc block size ---------------------------------------------------

# calculates largest value `l` such that `sum(start_idx : (start_idx + l) <=
# blk_size_bnd`, using the quadratic formula

get_blk_upp_idx <- function(n, start_idx, blk_size_bnd) {

    b <- ((2 * start_idx) - 1) / 2

    four_a_c <- -2 * blk_size_bnd

    upp_idx <- floor(-b + sqrt(b^2 - four_a_c))
    if (upp_idx > n) { return(n) }

    upp_idx
}


get_blk_upp_idx(100000, 0, 105)
get_blk_upp_idx(100000, 15, 105)
get_blk_upp_idx(100000, 21, 105)
get_blk_upp_idx(100000, 25, 105)
get_blk_upp_idx(100000, 28, 105)
