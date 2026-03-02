#ifndef ORDENACAO_EXT_H
#define ORDENACAO_EXT_H

int SelecionarPorSubstituicao(const char *nomeArquivoEntrada, const char *prefixoParticao);
void IntercalarArvoreVencedores(const char *prefixoParticao, int numParticoes, const char *nomeArquivoSaida);
int SelecionarPorSubstituicaoDestino(const char *nomeArquivoEntrada, const char *prefixoParticao);
void IntercalarArvoreVencedoresDestino(const char *prefixoParticao, int numParticoes, const char *nomeArquivoSaida);
void OrdenarTuristasExterna(const char *arquivo);
void OrdenarDestinosExterna(const char *arquivo);

#endif // ORDENACAO_EXT_H
