# Versão alternativa que não depende do RStudio
setwd("scripts")  # Assume que você está na pasta pai do diretório scripts

# Verifica e cria diretórios necessários
if (!dir.exists("plots")) {
  dir.create("plots")
}

plot_comparisons <- function(data, x_col, y_col, title, filename) {
  suppressMessages({
    png(filename = paste0("plots/", filename), width = 800, height = 600)
    plot(data[[x_col]], data[[y_col]], 
         main = title,
         xlab = "Tamanho da Estrutura",
         ylab = "Número de Comparações",
         pch = 19, col = "blue")
    invisible(dev.off())
  })
}

# Leitura dos dados
insert_data <- read.csv("insercao.csv")
remove_data <- read.csv("remocao.csv")

# Geração dos gráficos individuais
plot_comparisons(insert_data, "tamanho", "ins_heap_comp", 
                 "Inserção - Heap", "ins_heap.png")
plot_comparisons(insert_data, "tamanho", "ins_list_comp", 
                 "Inserção - Lista", "ins_list.png")
plot_comparisons(remove_data, "tamanho", "rem_heap_comp", 
                 "Remoção - Heap", "rem_heap.png")
plot_comparisons(remove_data, "tamanho", "rem_list_comp", 
                 "Remoção - Lista", "rem_list.png")

# Gráficos combinados
png(filename = "plots/combined_insert.png", width = 1000, height = 600)
par(mfrow = c(1, 2))
plot(insert_data$tamanho, insert_data$ins_heap_comp, 
     main = "Inserção - Heap",
     xlab = "Tamanho", ylab = "Comparações", pch = 19, col = "blue")
plot(insert_data$tamanho, insert_data$ins_list_comp, 
     main = "Inserção - Lista",
     xlab = "Tamanho", ylab = "Comparações", pch = 19, col = "red")
dev.off()

png(filename = "plots/combined_remove.png", width = 1000, height = 600)
par(mfrow = c(1, 2))
plot(remove_data$tamanho, remove_data$rem_heap_comp, 
     main = "Remoção - Heap",
     xlab = "Tamanho", ylab = "Comparações", pch = 19, col = "blue")
plot(remove_data$tamanho, remove_data$rem_list_comp, 
     main = "Remoção - Lista",
     xlab = "Tamanho", ylab = "Comparações", pch = 19, col = "red")
dev.off()

cat("Gráficos gerados com sucesso na pasta 'plots/'\n")