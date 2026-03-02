Este sistema é um Planejador de Viagens desenvolvido para simular as operações de uma agência de turismo. O projeto foi realizado como parte da disciplina Algoritmos e Estruturas de Dados II (CSI429) no curso de Engenharia de Computação da Universidade Federal de Ouro Preto (UFOP)
A aplicação foca no gerenciamento eficiente de grandes volumes de dados através de arquivos binários, implementando algoritmos clássicos de ordenação externa, busca e indexação.
Funcionalidades principais: Gerenciamento de Entidades: Cadastro, edição e listagem de Turistas, Destinos e Roteiros.

Associação Inteligente: 
Sistema que vincula turistas a roteiros validando automaticamente o orçamento disponível, a existência de vagas e o interesse geográfico do cliente.

Geração de Bases Aleatórias: Ferramenta para criar grandes volumes de dados desordenados para testes de performance.

Logs de Execução: Registro detalhado de métricas (tempo de CPU e número de comparações) em um arquivo log.txt para análise de eficiência.

Aspectos Tecnicos: 
Seleção por Substituição: Gera partições classificadas utilizando uma estrutura de Min-Heap.

Intercalação por Árvore Binária de Vencedores: Combina as partições geradas em um único arquivo ordenado de forma eficiente.

Bubble Sort: Disponível para ordenação simples diretamente em disco.

Estruturas de Busca:
Busca Binária: Implementada para consultas rápidas por ID em arquivos ordenados.

Busca Sequencial: Utilizada para consultas por campos de texto, como nomes de turistas ou países.

Tabela Hash : Indexação secundária para turistas utilizando a técnica de Sondagem Linear para resolução de colisões, garantindo acesso em tempo quase constante.

PARA RODAR O CODIGO :
tem q ultilizar o comando gcc no terminal dessa maneira: 
gcc -o planejador main.c base.c bubble.c busca.c editar.c entidades.c extras.c hash.c imprimir.c inserir.c ordenacao_ext.c salvar_entidades.c
