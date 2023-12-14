// util.h
#if !defined(UTIL_H)
#define UTIL_H

void limparBuffer(void);
void limparTela(void);
int ehDigito(char c);
char controlarMenu(void);
int validarEmail(char *email);
void tratamentoVerificaNulo(void *ponteiro, const char *mensagem_erro);
int validarNome(const char *nome);
int validarCnpj(const char *cnpj);
int validarTelefone(const char *telefone);
int validarNumero(const char *str);
int validarCpf(const char *cpf);

#endif // UTIL_H
