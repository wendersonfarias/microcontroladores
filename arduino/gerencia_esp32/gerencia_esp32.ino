#include <Keypad.h>               // Biblioteca para lidar com o teclado numérico
#include <WiFi.h>                 // Biblioteca para a conexão Wi-Fi
#include <HTTPClient.h>           // Biblioteca para fazer requisições HTTP
#include <ArduinoJson.h>          // Biblioteca para manipulação de JSON
#include <LiquidCrystal_I2C.h>    // Biblioteca para controlar o display LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Cria uma instância do objeto lcd para controlar o display LCD

const char* ssid = "NOME_WIFI";      // Nome (SSID) da rede Wi-Fi
const char* password = "SENHA_WIFI"; // Senha da rede Wi-Fi
const String url = "https://acessousuarioesp32-production.up.railway.app/usuarios/"; // URL base da API

const byte LINHAS = 4;   // Número de linhas do teclado numérico
const byte COLUNAS = 3;  // Número de colunas do teclado numérico

char teclas[LINHAS][COLUNAS] = {     // Definição das teclas do teclado numérico
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pinosLinhas[LINHAS] = {19, 18, 5, 17};    // Pinos conectados às linhas do teclado numérico
byte pinosColunas[COLUNAS] = {16, 4, 15};      // Pinos conectados às colunas do teclado numérico

Keypad keypad = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);   // Cria uma instância do objeto keypad

void setup() {
  lcd.init();                      // Inicializa o display LCD
  lcd.backlight();                 // Habilita a luz de fundo do display
  lcd.setCursor(0, 0);             // Posiciona o cursor na primeira linha, primeira coluna

  Serial.begin(115200);            // Inicializa a comunicação serial com velocidade de 115200 bps
  WiFi.begin(ssid, password);      // Conecta-se à rede Wi-Fi especificada

  lcd.print("Conectando ");
  lcd.setCursor(0, 1);
  lcd.print("ao wifi");

  while (WiFi.status() != WL_CONNECTED) {   // Aguarda até que a conexão Wi-Fi seja estabelecida
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  lcd.clear();
  lcd.print("Conectado! ");
  Serial.println("Conectado ao WiFi!");
  lcd.clear();
}

void loop() {
  lcd.print("1 cadastro");
  lcd.setCursor(0, 1);
  lcd.print("2 fazer login");

  Serial.println("1 cadastrar usuário");
  Serial.println("2 fazer login");

  char tecla = keypad.getKey();    // Obtém a tecla pressionada pelo usuário

  if (tecla) {
    if (tecla == '1') {
      lcd.clear();
      lcd.print("Insira a senha");
      lcd.setCursor(0, 1);
      lcd.print("de Administrador!");

      Serial.println("Opção 1 selecionada. Por favor, insira a senha de administrador:");
      if (verificarSenhaAdmin()) {
        cadastrarUsuario();    // Executa a função para cadastrar um usuário
      } else {
        lcd.clear();
        lcd.print("Senha");
        lcd.setCursor(0, 1);
        lcd.print("Incorreta!");
        Serial.println("Senha de administrador incorreta. Operação cancelada.");
      }
    } else if (tecla == '2') {
      Serial.println("Opção 2 selecionada. Efetue o login:");
      fazerLogin();    // Executa a função para fazer login
    }
  }
}

void cadastrarUsuario() {
  String matricula = obterMatricula();    // Obtém a matrícula do usuário
  Serial.println("Digite a senha:");
  String senha = obterSenha();            // Obtém a senha do usuário

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin("https://acessousuarioesp32-production.up.railway.app/usuarios");
    http.addHeader("Content-Type", "application/json");

    String requestBody = "{\"id\": null, \"matricula\":\"" + matricula + "\", \"senha\":\"" + senha + "\", \"ativo\":\"a\" }";

    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode == 201) {
      lcd.clear();
      lcd.print("Usuário");
      lcd.setCursor(0, 1);
      lcd.print("Cadastrado!");
      Serial.println("Usuário cadastrado");
    } else {
      lcd.clear();
      lcd.print("Tente");
      lcd.setCursor(0, 1);
      lcd.print("Novamente!");
      Serial.print("Falha no cadastro");
      //Serial.println(httpResponseCode);
    }

    http.end();
  }

  delay(500); // Aguarda 5 segundos antes de fazer a próxima requisição
}

bool verificarSenhaAdmin() {
  Serial.println("Digite a senha adm #:");
  String senha = obterSenha();

  if (senha == "1234") {
    return true;
  }

  return false;
}

void fazerLogin() {
  String matricula = obterMatricula();    // Obtém a matrícula do usuário
  Serial.println("Digite a senha seguida de #:");
  String senha = obterSenha();            // Obtém a senha do usuário

  Serial.print("Matrícula: ");
  Serial.println(matricula);
  Serial.print("Senha: ");
  Serial.println(senha);

  verificaUsuario(matricula, senha);    // Executa a função para verificar o usuário
}

String obterMatricula() {
  lcd.clear();
  lcd.print("Informe a matricula");
  lcd.setCursor(0, 1);
  lcd.print("seguida de #");
  Serial.println("Digite a matrícula seguida de #:");
  String matricula = "";
  char tecla = keypad.getKey();
  while (tecla != '#') {
    if (tecla) {
      Serial.print(tecla);
      matricula += tecla;
    }
    tecla = keypad.getKey();
  }

  Serial.println();
  return matricula;
}

String obterSenha() {
  String senha = "";
  lcd.clear();
  lcd.print("Informe a Senha");
  lcd.setCursor(0, 1);
  lcd.print("seguida de #");
  char tecla = keypad.getKey();
  while (tecla != '#') {
    if (tecla) {
      Serial.print("*");
      senha += tecla;
    }
    tecla = keypad.getKey();
  }
  Serial.println();
  return senha;
}

void verificaUsuario(String matricula, String senha) {
  String urlCompleta = url + matricula;

  HTTPClient http;
  http.begin(urlCompleta);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("Código de resposta: ");
    Serial.println(httpResponseCode);

    String responseBody = http.getString();
    Serial.println("Resposta:");
    Serial.println(responseBody);

    // Analisa a resposta JSON
    DynamicJsonDocument doc(200);
    DeserializationError error = deserializeJson(doc, responseBody);

    if (error) {
      lcd.clear();
      lcd.print("Não foi possível");
      lcd.setCursor(0, 1);
      lcd.print("Fazer Login");
      Serial.print("Erro na análise JSON: ");
      Serial.println(error.c_str());
    } else {
      String senhaRetornada = doc["senha"].as<String>();
      String ativo = doc["ativo"].as<String>();

      if (senha == senhaRetornada) {
        if (ativo == "a") {
          lcd.clear();
          lcd.print("ACESSO");
          lcd.setCursor(0, 1);
          lcd.print("LIBERADO");
          Serial.println("Acesso liberado!");
          pinMode(33, OUTPUT);
          digitalWrite(33, HIGH);
          delay(5000);
          digitalWrite(33, LOW);
        } else {
          lcd.clear();
          lcd.print("ACESSO");
          lcd.setCursor(0, 1);
          lcd.print("NEGADO");
          Serial.println("Acesso negado!");
          pinMode(32, OUTPUT);
          digitalWrite(32, HIGH);
          delay(5000);
          digitalWrite(32, LOW);
        }
      } else {
        lcd.clear();
        lcd.print("ACESSO");
        lcd.setCursor(0, 1);
        lcd.print("NEGADO");
        Serial.println("Acesso negado!");
        pinMode(32, OUTPUT);
        digitalWrite(32, HIGH);
        delay(5000);
        digitalWrite(32, LOW);
      }
    }
  } else {
    lcd.clear();
    lcd.print("ACESSO");
    lcd.setCursor(0, 1);
    lcd.print("NEGADO");
    pinMode(32, OUTPUT);
    digitalWrite(32, HIGH);
    delay(5000);
    digitalWrite(32, LOW);
    Serial.print("Erro na requisição: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
