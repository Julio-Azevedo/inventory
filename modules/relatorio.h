// relatorio.h
#if !defined(RELATORIO_H)
#define RELATORIO_H

void moduloRelatorio();
void relatorioTodosFornecedores();
void relatorioFornecedoresAtivos();
void relatorioFornecedoresInativos();
void relatorioTodosProdutos();
void relatorioProdutosAtivos();
void relatorioProdutoInativos();
void relatorioProdutosOrdemAlfabetica();
void relatorioFornecedoresOrdemAlfabetica();
int compararFornecedores(const void *a, const void *b);
void relatorioTodosClientes();
void relatorioClientesInativos();
void relatorioClientesOrdemAlfabetica();

// auxiliar 

#endif // RELATORIO_H
