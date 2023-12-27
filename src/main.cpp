// 載入程式庫
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// 定義
#define DHTPIN D2 // DHT所連接的PIN腳位置，此處預設為D2
#define DHTTYPE DHT11 // DHT型號款式

DHT dht(DHTPIN, DHTTYPE);

// WiFi 資訊(帳號與密碼)
const char *ssid = "<YOUR_WIFI_SSID>";
const char *password = "<YOUR_WIFI_PASSWORD>";

// 伺服器連接埠
ESP8266WebServer server(80);

// 設定
void setup()
{
  // 監聽序列埠
  Serial.begin(9600);
  // 啟動DHT
  dht.begin();

  // 連接 Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(3000);
    Serial.println("Connecting to WiFi...");
  }
  // 設定WiFi主機名稱 hostname 及檢視連接埠IP
  WiFi.hostname("YourESP8266Hostname");
  Serial.println(WiFi.hostname());
  Serial.println("Connected to WiFi");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up API endpoint 設定要讓前端可以使用的API
  server.on("/api/data", HTTP_GET, []()
            {
              Serial.println("Received request with headers:");
              for (int i = 0; i < server.headers(); i++)
              {
                Serial.println(server.headerName(i) + ": " + server.header(i));
              }

              // Read temperature and humidity from DHT 包裝要傳送的溫濕度資料
              float temperature = dht.readTemperature();
              float humidity = dht.readHumidity();
              String response = "{\"temperature\":" + String(temperature) + ", \"humidity\":" + String(humidity) + "}";

              // Send response 發送回應
              server.send(200, "application/json", response);
            }
  );

  // 啟動伺服器
  server.begin();
}

void loop()
{
  // 伺服器監聽
  server.handleClient();
}
