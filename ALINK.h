#ifndef __ALINK_H__
#define __ALINK_H__

const int LED = D5;
const int Bee = D6;

/* 连接您的WIFI SSID和密码 */
#define WIFI_SSID         "你的SSID"
#define WIFI_PASSWD       "WiFi密码"

/*
 * @zhanghui
 * time:2020.4.3
 */

/* 设备的三元组信息*/
#define PRODUCT_KEY       "填写你的三元组信息"
#define DEVICE_NAME       /"ESP12E"
#define DEVICE_SECRET     "填写你的三元组信息"
#define REGION_ID         "cn-shanghai"

/* 线上环境域名和端口号，不需要改 */
#define MQTT_SERVER       PRODUCT_KEY ".iot-as-mqtt." REGION_ID ".aliyuncs.com"
#define MQTT_PORT         1883
#define MQTT_USRNAME      DEVICE_NAME "&" PRODUCT_KEY

#define CLIENT_ID         "esp1|securemode=3,signmethod=hmacsha1,timestamp=789|"
// 算法工具: http://iot-face.oss-cn-shanghai.aliyuncs.com/tools.htm 进行加密生成password
// password教程 https://www.yuque.com/cloud-dev/iot-tech/mebm5g
#define MQTT_PASSWD       "密钥"

//MQTT订阅和发布所需的主题
#define ALINK_BODY_FORMAT         "{\"id\":\"123\",\"version\":\"1.0\",\"method\":\"%s\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"
#define ALINK_TOPIC_PROP_POSTRSP "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post_reply"
#define ALINK_TOPIC_PROP_SET "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/service/property/set"
#define ALINK_METHOD_PROP_POST "thing.event.property.post"
#define ALINK_METHOD_PROP_POSTRSP "thing.event.property.post_reply"
#define ALINK_METHOD_PROP_SET "thing.service.property.set"

#endif
