#include <ESP8266WiFi.h>
/* 依赖 PubSubClient 2.4.0 */
#include <PubSubClient.h>
/* 依赖 ArduinoJson 5.13.4 */
//不可使用ArduinoJson6以上版本，因为两个版本不兼容
#include <ArduinoJson.h>
#include "ALINK.h"
#include "HCSR04.h"

unsigned long lastMs = 0;   //用于周期性上报
WiFiClient espClient;
PubSubClient  client(espClient);

void payload_processing(char *topic,byte *payload);

//监听云端下发指令并处理 
void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    payload[length] = '\0';
    Serial.println((char *)payload);

    payload_processing(topic,payload);

}


void wifiInit()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }

    Serial.println("Connected to AP");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    
Serial.print("espClient [");


    client.setServer(MQTT_SERVER, MQTT_PORT);   /* 连接WiFi之后，连接MQTT服务器 */
    client.setCallback(callback);
}

//连接MQTT服务器
void mqttCheckConnect()
{
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT Server ...");
        if (client.connect(CLIENT_ID, MQTT_USRNAME, MQTT_PASSWD))

        {

            Serial.println("MQTT Connected!");

        }
        else
        {
            Serial.print("MQTT Connect err:");
            Serial.println(client.state());
            delay(5000);
        }
    }
}


void mqttIntervalPost()
{
    char param[32];
    char jsonBuf[128];

    sprintf(param, "{\"LightSwitch\":%d,\"warning\":%d,\"length\":%d,}", digitalRead(LED) ,digitalRead(Bee),cm_length);
    sprintf(jsonBuf, ALINK_BODY_FORMAT, ALINK_METHOD_PROP_POST, param);
    Serial.println(jsonBuf);
    boolean d = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf); //发布操作，向指定Topic上报
    Serial.print("publish:0 失败;1成功");
    Serial.println(d);
}

//设备响应云端指令
void payload_processing(char *topic,byte *payload)
{
  int32_t LedState;
  int32_t BeeState;
  //判断是否为设备属性设置主题
   if(strstr(topic,ALINK_TOPIC_PROP_SET))
   {
    StaticJsonBuffer<400> jsonBuffer;
    JsonObject &info = jsonBuffer.parseObject(payload);
    //判断Json是否解析成功
    if(!info.success())
    {
      Serial.println("Json解析失败");
    }
    else
    {
      LedState = info["params"]["LightSwitch"];//params:参数，LightSwitch：开关状态
      BeeState = info["params"]["warning"];
      Serial.print("LED(1:开启,0:关闭)");
      Serial.println(LedState);
      digitalWrite(LED,LedState);
      digitalWrite(Bee,BeeState);
    }
   }
}

void setup() 
{

    pinMode(LED,  OUTPUT);
    pinMode(Bee,  OUTPUT);
    pinMode(TRIG,  OUTPUT);
    pinMode(ECHO,  INPUT);
    /* initialize serial for debugging */
    Serial.begin(115200);
    Serial.println("Demo Start");
    Serial.println("Debug!!!");

    wifiInit();
}


// the loop function runs over and over again forever
void loop()
{
//millis()用于返回Arduino板开始运行当前程序时的毫秒数。这个数字在大约50天后溢出，即回到零。
//一下程序用于5秒上报一次数据
    
    if (millis() - lastMs >= 5000)  
    {
        lastMs = millis();
        mqttCheckConnect(); 
        Waves();
        /* 上报 */
        mqttIntervalPost();
    }

    client.loop();

    delay(10);

}
