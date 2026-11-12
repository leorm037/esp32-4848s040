#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);  // tempo para o monitor serial conectar

  // Modo estação e desconecta de qualquer rede anterior
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Scanner Wi-Fi iniciado");
}

void loop() {
  Serial.println("Procurando redes...");

  int n = WiFi.scanNetworks();

  if (n < 0) {
    Serial.println("Erro ao escanear redes");
  } else if (n == 0) {
    Serial.println("Nenhuma rede encontrada");
  } else {
    Serial.print(n);
    Serial.println(" rede(s) encontrada(s):");
    for (int i = 0; i < n; i++) {
      Serial.println(WiFi.SSID(i));  // nome da rede
    }
  }

  WiFi.scanDelete();  // libera a memória do resultado
  Serial.println();
  delay(5000);        // novo scan a cada 5 segundos
}