#ifndef __ALINK_H__
#define __ALINK_H__

const int LED = D5;
const int Bee = D6;

/* 连接您的WIFI SSID和密码 */
#define WIFI_SSID         "CR400BF-5033"
#define WIFI_PASSWD       "1234567890aa"

/*
 * @zhanghui
 * time:2020.4.3
 * 以下三元组第一个为李明康IoT平台，第二个为zhanghui‘s IoT平台
 */

/* 设备的三元组信息*/
#define PRODUCT_KEY       /*"a1byEbX6zbk"*/"a1LCGuqGjv9"
#define DEVICE_NAME       /*"Testdome2"*/"ESP12E"
#define DEVICE_SECRET     /*"EZ5WuB1AmR3x7y2ZH5mTZIosqLfa4kpt"*/"iQwAjIPPPxTYhJuBsWSmFJwg3Pg41vrH"
#define REGION_ID         "cn-shanghai"

/* 线上环境域名和端口号，不需要改 */
#define MQTT_SERVER       PRODUCT_KEY ".iot-as-mqtt." REGION_ID ".aliyuncs.com"
#define MQTT_PORT         1883
#define MQTT_USRNAME      DEVICE_NAME "&" PRODUCT_KEY

#define CLIENT_ID         "esp1|securemode=3,signmethod=hmacsha1,timestamp=789|"
// 算法工具: http://iot-face.oss-cn-shanghai.aliyuncs.com/tools.htm 进行加密生成password
// password教程 https://www.yuque.com/cloud-dev/iot-tech/mebm5g
#define MQTT_PASSWD       /*"8ba96d81a5e347a3f5e8c2fdd3dbc312a43bdb52"*/"a31067c72af65cb47e5292d12c64541c4ba7379d"

//MQTT订阅和发布所需的主题
#define ALINK_BODY_FORMAT         "{\"id\":\"123\",\"version\":\"1.0\",\"method\":\"%s\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"
#define ALINK_TOPIC_PROP_POSTRSP "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post_reply"
#define ALINK_TOPIC_PROP_SET "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/service/property/set"
#define ALINK_METHOD_PROP_POST "thing.event.property.post"
#define ALINK_METHOD_PROP_POSTRSP "thing.event.property.post_reply"
#define ALINK_METHOD_PROP_SET "thing.service.property.set"

#endif
