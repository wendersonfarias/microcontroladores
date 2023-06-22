#include <Password.h> // Biblioteca utilizada para controle de senha
#include <Keypad.h>

#define MENU_MAX 4
Password senha = Password( "1542" ); // Senha utilizada para liberacao

const int PINO_LED_VERMELHO = 32; // LED vermelho conectado ao pino 11
const int PINO_LED_VERDE = 33; // LED verde conectado ao pino 10

//prototipo de funcao
void seleciona_menu();


//definicoes de teclado
// define numero de filas
const uint8_t ROWS = 4;
// define numero de columnas
const uint8_t COLS = 3;
// define la distribucion de teclas
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
// pines correspondientes a las filas
uint8_t colPins[COLS] = { 16, 4, 15};
// pines correspondientes a las columnas
uint8_t rowPins[ROWS] = { 19, 18, 5, 17 };
// crea objeto con los prametros creados previamente
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Função para limpar a EEPROM
void clearEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
}

// Função para escrever os dados do usuário na EEPROM
void writeUserToEEPROM(int address, User user) {
  EEPROM.put(address, user);
  EEPROM.commit();
}

// Função para ler os dados do usuário da EEPROM
User readUserFromEEPROM(int address) {
  User user;
  EEPROM.get(address, user);
  return user;
}

// Função para cadastrar um novo usuário
void cadastrarUsuario() {
  for (int i = 0; i < maxUsers; i++) {
    User user = readUserFromEEPROM(i * sizeof(User));

    if (strlen(user.matricula) == 0) {
      // Solicitar matrícula
      char matricula[maxSize];
      int count = 0;
      char key;

      while (count < maxSize) {
        key = keypad.getKey();

        if (key) {
          if (key == '#') {
            matricula[count] = '\0';
            break;
          } else {
            matricula[count] = key;
            count++;
          }
        }
      }

      // Solicitar senha
      char senha[maxSize];
      count = 0;

      while (count < maxSize) {
        key = keypad.getKey();

        if (key) {
          if (key == '#') {
            senha[count] = '\0';
            break;
          } else {
            senha[count] = key;
            count++;
          }
        }
      }

      strcpy(user.matricula, matricula);
      strcpy(user.senha, senha);

      // Armazenar os dados na EEPROM
      writeUserToEEPROM(i * sizeof(User), user);

      Serial.println("Usuário cadastrado com sucesso!");
      return;
    }
  }

  Serial.println("Não foi possível cadastrar o usuário. Limite de usuários atingido.");
}

// Função para verificar o usuário e ligar o LED correspondente
void verificarUsuario() {
  // Solicitar matrícula
  char matricula[maxSize];
  int count = 0;
  char key;

  while (count < maxSize) {
    key = keypad.getKey();

    if (key) {
      if (key == '#') {
        matricula[count] = '\0';
        break;
      } else {
        matricula[count] = key;
        count++;
      }
    }
  }

  // Solicitar senha
  char senha[maxSize];
  count = 0;

  while (count < maxSize) {
    key = keypad.getKey();

    if (key) {
      if (key == '#') {
        senha[count] = '\0';
        break;
      } else {
        senha[count] = key;
        count++;
      }
    }
  }

  // Verificar se a matrícula e senha correspondem a algum usuário cadastrado
  for (int i = 0; i < maxUsers; i++) {
    User user = readUserFromEEPROM(i * sizeof(User));

    if (strcmp(user.matricula, matricula) == 0 && strcmp(user.senha, senha) == 0) {
      // Matrícula e senha correspondem a um usuário cadastrado
      digitalWrite(pinLed, HIGH);
      Serial.println("Usuário autenticado. LED ligado.");
      return;
    }
  }

  Serial.println("Matrícula ou senha inválidos. LED desligado.");
}

void setup() {
  // Inicializar a comunicação serial
  Serial.begin(9600);

  // Limpar a EEPROM (descomente essa linha caso queira limpar a EEPROM antes de começar)
  // clearEEPROM();

  // Configurar o pino do LED como saída
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);

  // Solicitar matrícula e senha para verificação
  Serial.println("Digite a matrícula:");
  char matricula[maxSize];
  int count = 0;
  char key;

  while (count < maxSize) {
    key = keypad.getKey();

    if (key) {
      if (key == '#') {
        matricula[count] = '\0';
        break;
      } else {
        matricula[count] = key;
        count++;
      }
    }
  }

  Serial.println("Digite a senha:");
  char senha[maxSize];
  count = 0;

  while (count < maxSize) {
    key = keypad.getKey();

    if (key) {
      if (key == '#') {
        senha[count] = '\0';
        break;
      } else {
        senha[count] = key;
        count++;
      }
    }
  }

  // Verificar se a matrícula e senha correspondem
  // à combinação pré-definida para entrar no modo de cadastro
  if (strcmp(matricula, "1234") == 0 && strcmp(senha, "5678") == 0) {
    Serial.println("Modo de cadastro ativado.");
    cadastrarUsuario();
  } else {
    Serial.println("Modo de verificação ativado.");
    verificarUsuario();
  }
}

void loop() {
  // Nada a fazer no loop
}
