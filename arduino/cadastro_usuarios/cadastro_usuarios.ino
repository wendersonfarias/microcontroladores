#include <LiquidCrystal_I2C.h>  
LiquidCrystal_I2C lcd(0x27,20,4);  // 
#include <Keypad.h>

// Definição do teclado matricial 4x3
const byte LINHAS = 4;
const byte COLUNAS = 3;
char teclas[LINHAS][COLUNAS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte pinosLinhas[LINHAS] ={ 19, 18, 5, 17 };
byte pinosColunas[COLUNAS] ={ 16, 4, 15};
Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);


// Estrutura de dados do usuário
struct Usuario {
  String matricula;
  String senha;
  bool ativo;
};

// Variáveis globais
const int maxUsuarios = 10;
Usuario usuarios[maxUsuarios];
int numUsuarios = 0;

// Pino do LED
const int ledPin = 33;

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  // Inicialização do LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Bem-vindo!");

  // Configuração do pino do LED
  pinMode(ledPin, OUTPUT);
}

void loop() {
  lcd.clear();
  lcd.print("Digite a matricula:");
  String matricula = readInput();
  lcd.clear();
  lcd.print("Digite a senha:");
  String senha = readInput();

  if (verificarCredenciais(matricula, senha)) {
    lcd.clear();
    lcd.print("Credenciais corretas");
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
  } else if (matricula == "*") {
    menuAdministrador();
  } else {
    lcd.clear();
    lcd.print("Credenciais incorretas");
    delay(1000);
  }
}

void menuAdministrador() {
  while (true) {
    lcd.clear();
    lcd.print("Menu Adm");
    lcd.setCursor(0, 1);
    lcd.print("1-Cadastrar");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("2-Ativar/Desativar");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("0-Voltar");
    delay(500);

    char key = waitForKeyPress();

    switch (key) {
      case '1':
        cadastrarUsuario();
        break;
      case '2':
        ativarDesativarUsuario();
        break;
      case '0':
        return; // Sai do menu do administrador e retorna ao menu de login
      default:
        break;
    }
  }
}


void cadastrarUsuario() {
  lcd.clear();
  lcd.print("Matricula:");
  String matricula = readInput();
  lcd.clear();
  lcd.print("Senha:");
  String senha = readInput();

  if (numUsuarios < maxUsuarios) {
    usuarios[numUsuarios].matricula = matricula;
    usuarios[numUsuarios].senha = senha;
    usuarios[numUsuarios].ativo = true;
    numUsuarios++;

    lcd.clear();
    lcd.print("Usuario cadastrado");
    delay(1000);
  } else {
    lcd.clear();
    lcd.print("Limite de usuarios");
    delay(1000);
  }
}

void ativarDesativarUsuario() {
  lcd.clear();
  lcd.print("Matricula:");
  String matricula = readInput();

  int usuarioIndex = buscarUsuario(matricula);

  if (usuarioIndex != -1) {
    lcd.clear();
    lcd.print("1-Ativar");
    lcd.setCursor(0, 1);
    lcd.print("2-Desativar");

    char key = waitForKeyPress();

    switch (key) {
      case '1':
        usuarios[usuarioIndex].ativo = true;
        lcd.clear();
        lcd.print("Usuario ativado");
        delay(1000);
        break;
      case '2':
        usuarios[usuarioIndex].ativo = false;
        lcd.clear();
        lcd.print("Usuario desativado");
        delay(1000);
        break;
      default:
        break;
    }
  } else {
    lcd.clear();
    lcd.print("Usuario nao encontrado");
    delay(1000);
  }
}

bool verificarCredenciais(String matricula, String senha) {
  for (int i = 0; i < numUsuarios; i++) {
    if (usuarios[i].matricula == matricula && usuarios[i].senha == senha && usuarios[i].ativo) {
      return true;
    }
  }
  return false;
}

int buscarUsuario(String matricula) {
  for (int i = 0; i < numUsuarios; i++) {
    if (usuarios[i].matricula == matricula) {
      return i;
    }
  }
  return -1;
}

char waitForKeyPress() {
  char key = NO_KEY;
  while (key == NO_KEY) {
    key = teclado.getKey();
  }
  return key;
}

String readInput() {
  String input = "";
  while (true) {
    char key = waitForKeyPress();
    if (key == '#') {
      break;
    }
    input += key;
    lcd.print('*');
  }
  return input;
}
