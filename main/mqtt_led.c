#include <string.h>
#include <ctype.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "mqtt_client.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

/* =================== CONFIGURAÇÕES RÁPIDAS =================== */

// Wi-Fi
#define WIFI_SSID      "Galaxy"
#define WIFI_PASS      "pedro123"

// Tópicos MQTT
#define MQTT_TOPIC_CMD     "esp32/cmd"
#define MQTT_TOPIC_STATUS  "esp32/status"

// LED
#define LED_GPIO 2
#define LED_ACTIVE_HIGH 1

// Botão (GPIO0 como exemplo)
#define BUTTON_GPIO 0
#define BUTTON_ACTIVE_LOW 1

// I2C + AHT20
#define I2C_MASTER_NUM      I2C_NUM_0
#define I2C_MASTER_SDA_IO   12
#define I2C_MASTER_SCL_IO   14
#define I2C_MASTER_FREQ_HZ  100000
#define AHT20_ADDR          0x38

// --- AWS IoT Core ---
#define MQTT_BROKER_URI "mqtts://aty5pgrrgu3i2-ats.iot.eu-north-1.amazonaws.com"
#define USE_AWS_IOT 1

#if USE_AWS_IOT
// MUDANÇA 1: Removidas as declarações 'extern'. Em vez disso, cole suas chaves aqui.
// O formato deve ser "linha1\n" "linha2\n" ...

// Cole o conteúdo do seu AmazonRootCA1.pem aqui
static const char AWS_ROOT_CA[] =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"
    "ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"
    "b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"

    "MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"
    "b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"
    "ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"
    "9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"
    "IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"
    "VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"
    "93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"
    "jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
    "AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"
    "A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"
    "U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"
    "N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"
    "o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"
    "5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"
    "rqXRfboQnoZsG4q5WTP468SQvvG5\n"
    "-----END CERTIFICATE-----\n";

// Conteúdo do seu certificate.pem.crt
static const char AWS_CLIENT_CERT[] =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDWTCCAkGgAwIBAgIUbfdCm7JD1r9hAlWAihN9jMQ3rrkwDQYJKoZIhvcNAQEL\n"
    "BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"
    "SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MTAxNTE3MTAy\n"
    "MloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"
    "ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMjE8A3GEmGWUWEE49zQ\n"
    "X7U/tDlyog00panV1rRHY+QUCpoHBQct3qca4Qb6gqVlbtc4+B/b4kPUg0rANnhG\n"
    "/i19TTWztXMY/0yFRud9DnTqpUkFCJeoAmHJ3bZrSBI+fHZVHC3kf6lqbIyLMVBD\n"
    "Ymjboq2P63OfAr7YoohxeFSEuUzy+5SbdqPehf80e5OLIzFG6uwIXx7bpenS0Xu1\n"
    "1R5mb6TX4CtNQtksq1xXjZdRb5uGIYHbG+yfUF547KAoQpTEQ15Eug3jh5pTZL8Y\n"
    "IgehSQ3oAJGg308oVQBVjPfPwIWs0PBMO8e9fYA3tg9iLa7PWYxAHURpCmoUpRH1\n"
    "ZjsCAwEAAaNgMF4wHwYDVR0jBBgwFoAUAQfpI1jPsxiywAt9+dvRohJ7vW0wHQYD\n"
    "VR0OBBYEFPvq1ldTTAQe3GeFXSTIygCBsewSMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"

    "AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAPZZSB1p9sYAZXQZKkGlqt/wve\n"
    "WtpDneS6kDcS//W4ZeOdrSCEPwzvByeObgTJ/ELCWvpgDduWaFB03OwBUc0O/4iZ\n"
    "YDWWS55mtPToU/dlS78fNesO11xt9RbeINV4v1V8LJuutlATdEOJKlVSdE383taq\n"
    "CdMpFcNT0DAR4pnGq21x4mJpVPuEVtq/bkuLtpsrFKF0mWNqH5Z1gMDkFaHrZ1I9\n"
    "81K3IgYcj6A/GTR0jn96JgscBB/FyO/11wskn2NSAXEDo//WUX8nEt4myhHIoI15\n"
    "oRysK+E/7CScXQ8RXkWAnXYUoFOPnxkBRnJwyLyTDVVAuva/DSAloA0ajnQ5\n"
    "-----END CERTIFICATE-----\n";

// Conteúdo da sua private.pem.key
static const char AWS_CLIENT_KEY[] =
    "-----BEGIN RSA PRIVATE KEY-----\n"
    "MIIEpQIBAAKCAQEAyMTwDcYSYZZRYQTj3NBftT+0OXKiDTSlqdXWtEdj5BQKmgcF\n"
    "By3epxrhBvqCpWVu1zj4H9viQ9SDSsA2eEb+LX1NNbO1cxj/TIVG530OdOqlSQUI\n"
    "l6gCYcndtmtIEj58dlUcLeR/qWpsjIsxUENiaNuirY/rc58CvtiiiHF4VIS5TPL7\n"
    "lJt2o96F/zR7k4sjMUbq7AhfHtul6dLRe7XVHmZvpNfgK01C2SyrXFeNl1Fvm4Yh\n"
    "gdsb7J9QXnjsoChClMRDXkS6DeOHmlNkvxgiB6FJDegAkaDfTyhVAFWM98/AhazQ\n"
    "8Ew7x719gDe2D2Itrs9ZjEAdRGkKahSlEfVmOwIDAQABAoIBADGuEdzGq5u8T4zb\n"
    "YestING/3r/sbs8nvOqmwIdBtyUkFG+C1yqsnhDppM9OQ+/bhq75KOTxSy8PsiFY\n"
    "KOJgZtsoy2dDfd3qTJpJzH7RwjcKLTZBaZvldhluk09lgqMJFVFOxDdS+IgajpvE\n"
    "gcJjukFKQBoEp/WnXk2NW8K5mVYIRO+OUVIuv7R+vI/nuTybwA5k1xfhr4xwHkN6\n"
    "ACwfpHvEh9548ssgyNvYoqwMKAeEnkHSe3jTNyhqfuYZrfqMjdkyVerbGuJkJoin\n"
    "qhAOEEGIuCIOnH7Y1ciEpRgs//tPbsocUsmCaRAcZhngkEHMcTKeH1H1ShUjO4bV\n"
    "fYqLxdECgYEA+uJt38oln9vivJRwS/nFsKbde6W1E57SNoZ4c0hEwebLNpoe+mNL\n"
    "H6tiT5DEp+VOetljjwos31V6MJxH9QSB8JEY0MaLoPirtCT8LCN7G5+/kUAgJU10\n"
    "T84IVlJZuGwExpY/knoQmCGC8xazMiyLAkTB+hraOeJ1bYSh94pLAikCgYEAzNzq\n"
    "mRt06M4J0c4WNQ6ukCslQ3EPsWFiyby6hoQkZLKUC8SSlLw5EpPy86UTH/tn4QDT\n"
    "Misr2Gs77gH9IAQs77AYow1oFr0dy9Y7QMIAsTs9VC652H8dCHdYxF6MLJA44E5g\n"
    "jcHQEKiW2nE+A2IUYytMWAGr6fFckBfF7UHO2cMCgYEAwsOXYp0uujxcd+OQjhq4\n"
    "MtxHot7QhQvNy5B236Ah6Jm/9oKNO/prbomBB52uXVzxoQM0e+39Sd+0vRoF7pty\n"
    "OIybxC/uY6fIvE/eCHH+90H72Mn8apkHi5C5/jFt/3Kz/mrTrWXfjgqt+wMLWA8m\n"
    "VzuDjyLbeQZp/PxzNJWCh4kCgYEAiX8UbaKB+uaerJQXT5EFFHoAzp0JnVHxjdj/\n"
    "j90M2BELUEKk5vLVk2R9QY3foi2IcPmuxhM3oE+Ir5viGiTzTAPy5SzQWcKgRvkI\n"
    "V9RdxpYt+VxLG8Vk5RPFHjce+aHqqpGwODSGw0eDyCUNLBQd/tlGqiKlEaUPLR7n\n"
    "lu/+NyUCgYEAhZQ+LH3DOGEJxNHDDbsp9Styjq7u9SwOkSXJ+yGp8b4Vfu7ZEjb8\n"
    "AfEy7CZU3Bw0cuEHSdKPsWPLmxQKvP7csXjBVzkFCSJu3/QRbi5qxGS/iIY723xU\n"
    "vSd7EBEIsEYRT4iR4cVy2PO3FtBrX0iVpUPlOalG9LSNEO2355oDgrw=\n"
    "-----END RSA PRIVATE KEY-----\n";


#define MQTT_CLIENT_ID "lolin32-led"
#endif

// ... (o resto do código é idêntico)

static const char *TAG = "MQTT_LED";
static EventGroupHandle_t s_wifi_event_group;
#define WIFI_CONNECTED_BIT BIT0

static esp_mqtt_client_handle_t s_mqtt = NULL;
static volatile bool s_led_on = false;
static volatile int s_last_button_pressed = 0;
static volatile float s_last_temp_c = 0.0f;
static volatile float s_last_hum_pct = 0.0f;

/* -------------------- Wi-Fi -------------------- */
static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
        ESP_LOGW(TAG, "Wi-Fi desconectado, tentando reconectar...");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ESP_LOGI(TAG, "Wi-Fi conectado");
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

static void wifi_start(void) {
    s_wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

/* -------------------- LED, BOTÃO, I2C (Suas funções) -------------------- */
static void led_apply(bool on) {
    gpio_set_level(LED_GPIO, on ? 1 : 0);
    s_led_on = on;
}

static void led_init(void) {
    gpio_config_t io = {
        .pin_bit_mask = 1ULL << LED_GPIO,
        .mode = GPIO_MODE_OUTPUT
    };
    gpio_config(&io);
    led_apply(false);
}

static void button_init(void) {
    gpio_config_t io = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = BUTTON_ACTIVE_LOW ? 1 : 0,
    };
    gpio_config(&io);
}

static int button_read_pressed(void) {
    return gpio_get_level(BUTTON_GPIO) == (BUTTON_ACTIVE_LOW ? 0 : 1);
}

static void i2c_master_init(void) {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0));
}

static esp_err_t aht20_init(void) { /* ...sua função aqui... */ return ESP_OK; }
static esp_err_t aht20_read(float *out_temp_c, float *out_hum_pct) { /* ...sua função aqui... */ return ESP_OK; }

/* -------------------- MQTT -------------------- */
static void publish_status(void) {
    // 1. Crie variáveis locais e temporárias (não-volatile)
    float temp_c = 0.0f;
    float hum_pct = 0.0f;

    s_last_button_pressed = button_read_pressed();
    
    // 2. Passe os endereços das variáveis locais para a função
    //    Os tipos agora correspondem perfeitamente: (float *, float *)
    if (aht20_read(&temp_c, &hum_pct) == ESP_OK) {
        // 3. Atualize as variáveis globais 'volatile' de forma segura
        s_last_temp_c = temp_c;
        s_last_hum_pct = hum_pct;
    }

    char msg[128];
    snprintf(msg, sizeof(msg), "{\"led\":%d,\"temp_c\":%.2f,\"hum_pct\":%.2f}",
             s_led_on ? 1 : 0, s_last_temp_c, s_last_hum_pct);
    esp_mqtt_clis_last_button_pressed,ent_publish(s_mqtt, MQTT_TOPIC_STATUS, msg, 0, 1, 0);
    ESP_LOGI(TAG, "PUB [%s] payload=%s", MQTT_TOPIC_STATUS, msg);
}

// Sua função de lógica, não precisa mudar
static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event) {
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT conectado");
            esp_mqtt_client_subscribe(s_mqtt, MQTT_TOPIC_CMD, 1);
            publish_status();
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGW(TAG, "MQTT desconectado");
            break;
        case MQTT_EVENT_DATA: {
            char topic[128] = {0};
            char data[128]  = {0};
            memcpy(topic, event->topic, event->topic_len);
            memcpy(data,  event->data,  event->data_len);
            ESP_LOGI(TAG, "RECV [%s]: %s", topic, data);

            if (strcmp(topic, MQTT_TOPIC_CMD) == 0) {
                for (int i = 0; data[i]; ++i) data[i] = (char)toupper((unsigned char)data[i]);
                if (strstr(data, "ON")) {
                    led_apply(true);
                    publish_status();
                } else if (strstr(data, "OFF")) {
                    led_apply(false);
                    publish_status();
                }
            }
            break;
        }
        default:
            break;
    }
    return ESP_OK;
}

// Nova função "ponte" com a assinatura correta
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG, "Event dispatched from event loop, base=%s, event_id=%ld", base, event_id);
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    mqtt_event_handler_cb(event);
}

static void mqtt_start(void) {
    // MUDANÇA 2: A configuração agora aponta para as strings que você colou acima.
    const esp_mqtt_client_config_t cfg = {
        .broker.address.uri = MQTT_BROKER_URI,
#if USE_AWS_IOT
        .broker.verification.certificate = AWS_ROOT_CA,
        .credentials.authentication.certificate = AWS_CLIENT_CERT,
        .credentials.authentication.key = AWS_CLIENT_KEY,
        .credentials.client_id = MQTT_CLIENT_ID,
#endif
    };

    s_mqtt = esp_mqtt_client_init(&cfg);
    esp_mqtt_client_register_event(s_mqtt, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(s_mqtt);
}

/* -------------------- MAIN -------------------- */
/* -------------------- MAIN -------------------- */
void app_main(void) {
    ESP_ERROR_CHECK(nvs_flash_init());
    led_init();
    button_init();
    i2c_master_init();
    if (aht20_init() != ESP_OK) {
        ESP_LOGW(TAG, "AHT20 init falhou (continuando mesmo assim)");
    }
    wifi_start();
    
    xEventGroupWaitBits(s_wifi_event_group, WIFI_CONNECTED_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
    
    mqtt_start();

    // MUDANÇA CRÍTICA: Loop infinito para manter o programa principal rodando
    // e impedir que o ESP32 reinicie.
    while (1) {
        // A tarefa principal pode "dormir" para economizar energia e dar tempo para outras tarefas.
        vTaskDelay(pdMS_TO_TICKS(1000));
        publish_status();
    }
}