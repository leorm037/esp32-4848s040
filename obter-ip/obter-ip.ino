#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "secrets.h"

const char* URL = "https://www.paginaemconstrucao.com.br/ip/";

void setup() {
  Serial.begin(115200);
  delay(1000);  // tempo para o monitor serial conectar

  // ---------- Conexão Wi-Fi ----------
  Serial.print("Conectando na rede ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long inicio = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - inicio > 20000) {  // timeout de 20 s
      Serial.println("\nFalha ao conectar no Wi-Fi");
      return;
    }
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado");
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());

  // ---------- Requisição HTTPS ----------
  WiFiClientSecure client;
  client.setInsecure();  // não valida o certificado (apenas para testes)

  HTTPClient http;
  http.setTimeout(15000);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  Serial.print("Acessando: ");
  Serial.println(URL);

  if (!http.begin(client, URL)) {
    Serial.println("Erro ao iniciar a requisição");
    return;
  }

  int codigo = http.GET();
  Serial.print("Código HTTP: ");
  Serial.println(codigo);

  if (codigo > 0) {
    String corpo = http.getString();
    Serial.println("----- Conteúdo retornado -----");
    Serial.println(corpo);
    Serial.println("----- Fim do conteúdo -----");
  } else {
    Serial.print("Erro na requisição: ");
    Serial.println(HTTPClient::errorToString(codigo));
  }

  http.end();

  // ---------- Encerra ----------
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  Serial.println("Execução concluída");
}

void loop() {
  // vazio: o fluxo roda apenas uma vez no setup()
}