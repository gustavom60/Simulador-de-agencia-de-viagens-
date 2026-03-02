#include <string.h>
#include "inserir.h"
#include "entidades.h"
#include "extras.h"
#include "salvar_entidades.h"

// Funcao para inserir um novo Turista via terminal
void InserirTuristaInterativo(FILE *arq, FILE *destinos) {
    Turista t;
    Destino d;

    // Define o id com base no total de registros ja existentes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Turista);
    t.id = total + 1;

    printf("Digite o nome do turista: ");
    fgets(t.nome, MAX_NOME, stdin);
    t.nome[strcspn(t.nome, "\n")] = '\0';

    printf("Digite o CPF (formato 000.000.000-00): ");
    fgets(t.cpf, 15, stdin);
    t.cpf[strcspn(t.cpf, "\n")] = '\0';
    LimpaBuffer();

    // Exibe a lista de países disponíveis
    printf("\n--- Lista de destinos disponiveis ---\n");
    fseek(destinos, 0, SEEK_SET);
    int numDestinos = 0;
    while (fread(&d, sizeof(Destino), 1, destinos)) {
        printf("ID: %d - Pais: %s\n", d.id, d.nomePais);
        numDestinos++;
    }

    if (numDestinos == 0) {
        printf("Nenhum destino cadastrado. Nao e possivel registrar paises de interesse.\n");
        return;
    }

    for (int i = 0; i < MAX_PAISES_INTERESSE; i++) {
        int idEscolhido;
        printf("Digite o ID do pais de interesse %d: ", i + 1);
        scanf("%d", &idEscolhido);
        LimpaBuffer();

        // Busca o nome do país pelo ID
        fseek(destinos, 0, SEEK_SET);
        while (fread(&d, sizeof(Destino), 1, destinos)) {
            if (d.id == idEscolhido) {
                strncpy(t.paisesInteresse[i], d.nomePais, MAX_NOME);
                break;
            }
        }
    }

    printf("Digite o orcamento: ");
    scanf("%f", &t.orcamento);
    LimpaBuffer();

    // Substitui a escrita manual pela chamada da função SalvarTurista
    SalvarTurista(&t, t.id);
    printf("Turista inserido com sucesso!\n");
}


// Funcao para inserir um novo Destino via terminal
void InserirDestinoInterativo(FILE *arq) {
    Destino d;
    // Define o id com base no total de registros ja existentes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Destino);
    d.id = total + 1;

    printf("Digite o nome do pais: ");
    fgets(d.nomePais, MAX_NOME, stdin);
    d.nomePais[strcspn(d.nomePais, "\n")] = '\0';

    printf("Digite a principal atracao: ");
    fgets(d.principalAtracao, MAX_ATRACOES, stdin);
    d.principalAtracao[strcspn(d.principalAtracao, "\n")] = '\0';

    printf("Digite o clima: ");
    fgets(d.clima, 20, stdin);
    d.clima[strcspn(d.clima, "\n")] = '\0';

    printf("Digite o custo medio da estadia: ");
    scanf("%f", &d.custoMedioEstadia);
    LimpaBuffer();

    // Substitui a escrita manual pela chamada da função SalvarDestino
    SalvarDestino(&d, d.id);
    printf("Destino inserido com sucesso!\n");
}


// Insere 50 registros de exemplo reais para Turistas
void InserirDadosExemploTuristas(FILE *arq) {
    Turista exemplos[MAX_TURISTAS_EXEMPLO] = {
        {1, "Joao da Silva", "123.456.789-10", {"Brasil", "Argentina", "Chile", "Peru", "Uruguai"}, 3000.00},
        {2, "Maria Oliveira", "234.567.890-11", {"Estados Unidos", "Canada", "Mexico", "Brasil", "Italia"}, 3500.00},
        {3, "Carlos Souza", "345.678.901-12", {"Franca", "Alemanha", "Holanda", "Belgica", "Espanha"}, 3200.00},
        {4, "Ana Pereira", "456.789.012-13", {"Japao", "Coreia", "China", "India", "Tailandia"}, 5000.00},
        {5, "Pedro Almeida", "567.890.123-14", {"Australia", "Nova Zelanda", "Africa do Sul", "Brasil", "Russia"}, 4000.00},
        {6, "Fernanda Costa", "678.901.234-15", {"Espanha", "Portugal", "Grecia", "Turquia", "Egito"}, 2800.00},
        {7, "Ricardo Lima", "789.012.345-16", {"Estados Unidos", "Reino Unido", "Canada", "Brasil", "Japao"}, 4500.00},
        {8, "Patricia Fernandes", "890.123.456-17", {"Italia", "Franca", "Alemanha", "Holanda", "Suica"}, 3000.00},
        {9, "Anderson Gomes", "901.234.567-18", {"Brasil", "Argentina", "Uruguai", "Chile", "Paraguai"}, 2200.00},
        {10, "Larissa Martins", "012.345.678-19", {"Portugal", "Espanha", "Franca", "Italia", "Alemanha"}, 3800.00},
        {11, "Gabriel Rocha", "111.222.333-10", {"Brasil", "Mexico", "Itália", "Japao", "Canada"}, 3600.00},
        {12, "Bruna Dias", "222.333.444-11", {"Estados Unidos", "Franca", "Alemanha", "Japao", "Australia"}, 3400.00},
        {13, "Lucas Carvalho", "333.444.555-12", {"Italia", "Brasil", "Argentina", "Espanha", "Reino Unido"}, 4100.00},
        {14, "Camila Ribeiro", "444.555.666-13", {"Franca", "Alemanha", "Italia", "Japao", "Canada"}, 3700.00},
        {15, "Felipe Castro", "555.666.777-14", {"Brasil", "Estados Unidos", "Mexico", "Italia", "Australia"}, 3900.00},
        {16, "Renata Gomes", "666.777.888-15", {"Portugal", "Espanha", "Franca", "Alemanha", "Brasil"}, 3200.00},
        {17, "Marcos Moreira", "777.888.999-16", {"Japao", "Coreia", "China", "India", "Tailandia"}, 4500.00},
        {18, "Juliana Barros", "888.999.000-17", {"Italia", "Franca", "Alemanha", "Espanha", "Portugal"}, 3000.00},
        {19, "Eduardo Almeida", "999.000.111-18", {"Brasil", "Argentina", "Chile", "Uruguai", "Paraguai"}, 4100.00},
        {20, "Carolina Figueiredo", "000.111.222-19", {"Estados Unidos", "Canada", "Mexico", "Brasil", "Italia"}, 3800.00},
        {21, "Rafael Teixeira", "101.202.303-20", {"Franca", "Alemanha", "Holanda", "Belgica", "Espanha"}, 3600.00},
        {22, "Isabela Correia", "202.303.404-21", {"Japao", "Coreia", "China", "India", "Tailandia"}, 4200.00},
        {23, "Leonardo Monteiro", "303.404.505-22", {"Australia", "Nova Zelanda", "Africa do Sul", "Brasil", "Russia"}, 4000.00},
        {24, "Sofia Mendes", "404.505.606-23", {"Estados Unidos", "Reino Unido", "Canada", "Italia", "Japao"}, 3700.00},
        {25, "Diego Pires", "505.606.707-24", {"Brasil", "Argentina", "Uruguai", "Chile", "Paraguai"}, 3300.00},
        {26, "Bianca Nunes", "606.707.808-25", {"Portugal", "Espanha", "Franca", "Alemanha", "Italia"}, 3500.00},
        {27, "Victor Santos", "707.808.909-26", {"Japao", "Coreia", "China", "India", "Tailandia"}, 3900.00},
        {28, "Amanda Guimaraes", "808.909.010-27", {"Australia", "Canada", "Estados Unidos", "Brasil", "Italia"}, 3400.00},
        {29, "Gustavo Ramos", "909.010.111-28", {"Franca", "Alemanha", "Espanha", "Reino Unido", "Holanda"}, 3600.00},
        {30, "Nicole Freitas", "010.111.212-29", {"Brasil", "Mexico", "Argentina", "Chile", "Peru"}, 3200.00},
        {31, "Felicia Souza", "111.212.313-30", {"Estados Unidos", "Canada", "Italia", "Japao", "Australia"}, 3800.00},
        {32, "Samuel Andrade", "212.313.414-31", {"Franca", "Alemanha", "Holanda", "Belgica", "Espanha"}, 4000.00},
        {33, "Lorena Silva", "313.414.515-32", {"Japao", "Coreia", "China", "India", "Tailandia"}, 3500.00},
        {34, "Thiago Ramos", "414.515.616-33", {"Australia", "Nova Zelanda", "Africa do Sul", "Brasil", "Russia"}, 3700.00},
        {35, "Julia Carvalho", "515.616.717-34", {"Estados Unidos", "Reino Unido", "Canada", "Italia", "Japao"}, 3600.00},
        {36, "Bruno Martins", "616.717.818-35", {"Brasil", "Argentina", "Uruguai", "Chile", "Paraguai"}, 3300.00},
        {37, "Carolina Dias", "717.818.919-36", {"Portugal", "Espanha", "Franca", "Alemanha", "Italia"}, 3400.00},
        {38, "Renato Fonseca", "818.919.020-37", {"Japao", "Coreia", "China", "India", "Tailandia"}, 4000.00},
        {39, "Marcela Costa", "919.020.121-38", {"Estados Unidos", "Canada", "Mexico", "Brasil", "Italia"}, 3800.00},
        {40, "Daniel Pereira", "020.121.222-39", {"Franca", "Alemanha", "Holanda", "Belgica", "Espanha"}, 3600.00},
        {41, "Patricia Silva", "121.222.323-40", {"Japao", "Coreia", "China", "India", "Tailandia"}, 3500.00},
        {42, "Victor Almeida", "222.323.424-41", {"Australia", "Nova Zelanda", "Africa do Sul", "Brasil", "Russia"}, 3700.00},
        {43, "Amanda Santos", "323.424.525-42", {"Estados Unidos", "Reino Unido", "Canada", "Italia", "Japao"}, 3400.00},
        {44, "Gabriela Souza", "424.525.626-43", {"Brasil", "Argentina", "Chile", "Peru", "Uruguai"}, 3200.00},
        {45, "Fernando Lima", "525.626.727-44", {"Estados Unidos", "Canada", "Mexico", "Brasil", "Italia"}, 3600.00},
        {46, "Rafaela Rocha", "626.727.828-45", {"Franca", "Alemanha", "Holanda", "Belgica", "Espanha"}, 3800.00},
        {47, "Igor Correia", "727.828.929-46", {"Japao", "Coreia", "China", "India", "Tailandia"}, 4000.00},
        {48, "Vanessa Martins", "828.929.030-47", {"Australia", "Nova Zelanda", "Africa do Sul", "Brasil", "Russia"}, 3500.00},
        {49, "Marcelo Ribeiro", "929.030.131-48", {"Estados Unidos", "Reino Unido", "Canada", "Italia", "Japao"}, 3700.00},
        {50, "Juliana Castro", "030.131.232-49", {"Franca", "Alemanha", "Holanda", "Belgica", "Espanha"}, 3600.00}
    };
    for (int i = 0; i < MAX_TURISTAS_EXEMPLO; i++) {
        SalvarTurista(&exemplos[i], exemplos[i].id);
    }
    printf("Dados de exemplo para Turistas inseridos.\n");
}

// Insere 50 registros de exemplo reais para Destinos
void InserirDadosExemploDestinos(FILE *arq) {
    Destino exemplos[MAX_DESTINOS_EXEMPLO] = {
        {1, "Brasil", "Cristo Redentor", "Tropical", 800.00},
        {2, "Estados Unidos", "Statue of Liberty", "Temperado", 1200.00},
        {3, "Franca", "Torre Eiffel", "Temperado", 1000.00},
        {4, "Japao", "Templo Kinkaku-ji", "Temperado", 1100.00},
        {5, "Italia", "Colosseum", "Mediterraneo", 900.00},
        {6, "Alemanha", "Brandenburg Gate", "Temperado", 950.00},
        {7, "Australia", "Sydney Opera House", "Subtropical", 1300.00},
        {8, "Canada", "Niagara Falls", "Frio", 1050.00},
        {9, "Espanha", "Sagrada Familia", "Mediterraneo", 850.00},
        {10, "Portugal", "Torre de Belem", "Mediterraneo", 800.00},
        {11, "Reino Unido", "Big Ben", "Temperado", 1100.00},
        {12, "China", "Great Wall", "Variado", 900.00},
        {13, "India", "Taj Mahal", "Tropical", 950.00},
        {14, "Russia", "Red Square", "Frio", 1000.00},
        {15, "Mexico", "Chichen Itza", "Tropical", 850.00},
        {16, "Argentina", "Iguazu Falls", "Subtropical", 900.00},
        {17, "Chile", "Easter Island Moai", "Variado", 950.00},
        {18, "Peru", "Machu Picchu", "Temperado", 1000.00},
        {19, "Colombia", "Cartagena Walled City", "Tropical", 850.00},
        {20, "Africa do Sul", "Table Mountain", "Mediterraneo", 1100.00},
        {21, "Nova Zelanda", "Milford Sound", "Temperado", 1200.00},
        {22, "Suica", "Matterhorn", "Frio", 1300.00},
        {23, "Holanda", "Keukenhof", "Temperado", 950.00},
        {24, "Belgica", "Grand Place", "Temperado", 900.00},
        {25, "Austria", "Schonbrunn Palace", "Temperado", 1000.00},
        {26, "Suecia", "Vasa Museum", "Frio", 1050.00},
        {27, "Noruega", "Fjords", "Frio", 1100.00},
        {28, "Dinamarca", "Nyhavn", "Temperado", 950.00},
        {29, "Finlandia", "Santa Claus Village", "Frio", 1000.00},
        {30, "Grecia", "Acropolis", "Mediterraneo", 850.00},
        {31, "Turquia", "Hagia Sophia", "Variado", 900.00},
        {32, "Israel", "Western Wall", "Mediterraneo", 950.00},
        {33, "Arabia Saudita", "Masmak Fort", "Deserto", 1100.00},
        {34, "Emirados Arabes Unidos", "Burj Khalifa", "Deserto", 1300.00},
        {35, "Singapore", "Marina Bay Sands", "Tropical", 1200.00},
        {36, "Coreia do Sul", "Gyeongbokgung", "Temperado", 1000.00},
        {37, "Thailandia", "Grand Palace", "Tropical", 900.00},
        {38, "Indonesia", "Borobudur", "Tropical", 850.00},
        {39, "Malaysia", "Petronas Towers", "Equatorial", 1100.00},
        {40, "Vietnam", "Ha Long Bay", "Tropical", 950.00},
        {41, "Egito", "Pyramids of Giza", "Deserto", 1000.00},
        {42, "Marrocos", "Koutoubia Mosque", "Deserto", 900.00},
        {43, "Nigeria", "Zuma Rock", "Tropical", 850.00},
        {44, "Kenya", "Maasai Mara", "Equatorial", 1100.00},
        {45, "Etiopia", "Lalibela Churches", "Variado", 950.00},
        {46, "Polonia", "Wawel Castle", "Temperado", 900.00},
        {47, "Republica Checa", "Prague Castle", "Temperado", 950.00},
        {48, "Hungria", "Parliament Building", "Temperado", 900.00},
        {49, "Romania", "Bran Castle", "Temperado", 850.00},
        {50, "Bulgaria", "Alexander Nevsky Cathedral", "Temperado", 800.00}
    };
    for (int i = 0; i < MAX_DESTINOS_EXEMPLO; i++) {
        SalvarDestino(&exemplos[i], exemplos[i].id);
    }
    printf("Dados de exemplo para Destinos inseridos.\n");
}
