library(magrittr)

n_vec <- c(10L, 20L, 50L, 100L, 200L, 500L, 1000L, 2000L, 5000L, 10000L)

n_samp <- 10L




# collect algorithm runtimes ---------------------------------------------------

collect_runtimes <- function(n_vec, n_samp) {

    runtimes <- list()

    for (i in seq_along(n_vec)) {

        n <- n_vec[i]

        runtimes[[paste0("n", n)]] <- replicate(n_samp, {
            start_time <- proc.time()
            system(paste0("./exer_1a -n ", n, " -k 4"))
            (proc.time() - start_time)[["elapsed"]]
        })
    }

    runtimes
}




# plot runtimes ----------------------------------------------------------------


# mean_runtimes <- sapply(runtimes, mean) %>% log2

# x_vals <- log2(n_vec)

# plot(x_vals, mean_runtimes, type = "o")



# print runtimes ---------------------------------------------------------------

runtimes <- collect_runtimes(n_vec, n_samp)
mean_runtimes <- sapply(runtimes, mean)

quantile_runtimes <- sapply(runtimes, quantile, probs = c(0.5, 0.025, 0.975))

format(quantile_runtimes, nsmall = 2, digits = 2) %>% t %>% noquote
