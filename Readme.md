# 關於本專案
>本專案為簡易模板。<br>

示範ESP8266以HTTP協定的方式建立API，供前端網頁可以取得DHT感應器溫度、濕度數據。<br>

以PlatformIO建立新專案，更改位於 *src > main.cpp* 的主要程式，需設定WiFi名稱與密碼，以及欲使用的連接埠、主機名稱及API路由。

## 設備
- ESP8266 開發板
- DHT 溫濕度感應器
- 開發板電源供應線

## 環境及套件設置
-  PlatformIO on VS Code
-  adafruit/DHT sensor library@^1.4.6