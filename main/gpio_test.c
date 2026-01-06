#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_http_server.h"

#define MOTOR_EN   GPIO_NUM_1
#define MOTOR_DIR  GPIO_NUM_4

static const char *TAG = "MOTOR_HTTP";

/* ========== HTTP HANDLER ========== */
static esp_err_t motor_handler(httpd_req_t *req)
{
    char query[64];
    char cmd[16];

    if (httpd_req_get_url_query_str(req, query, sizeof(query)) == ESP_OK) {
        if (httpd_query_key_value(query, "cmd", cmd, sizeof(cmd)) == ESP_OK) {

            if (strcmp(cmd, "forward") == 0) {
                gpio_set_level(MOTOR_DIR, 1);
                gpio_set_level(MOTOR_EN, 1);
                httpd_resp_sendstr(req, "Motor FORWARD\n");
                return ESP_OK;
            }

            if (strcmp(cmd, "reverse") == 0) {
                gpio_set_level(MOTOR_DIR, 0);
                gpio_set_level(MOTOR_EN, 1);
                httpd_resp_sendstr(req, "Motor REVERSE\n");
                return ESP_OK;
            }

            if (strcmp(cmd, "stop") == 0) {
                gpio_set_level(MOTOR_EN, 0);
                httpd_resp_sendstr(req, "Motor STOP\n");
                return ESP_OK;
            }
        }
    }

    httpd_resp_sendstr(req, "Invalid command\n");
    return ESP_OK;
}

/* ========== START HTTP SERVER ========== */
static void start_http_server(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_start(&server, &config);

    httpd_uri_t motor_uri = {
        .uri      = "/motor",
        .method   = HTTP_GET,
        .handler  = motor_handler,
        .user_ctx = NULL
    };

    httpd_register_uri_handler(server, &motor_uri);
}

/* ========== WIFI AP ========== */
static void wifi_init_softap(void)
{
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "ESP32_S3_TEST",
            .ssid_len = 0,
            .password = "12345678",
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA2_PSK
        },
    };

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();
}

/* ========== MAIN ========== */
void app_main(void)
{
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << MOTOR_EN) | (1ULL << MOTOR_DIR),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&io_conf);

    wifi_init_softap();
    start_http_server();

    ESP_LOGI(TAG, "HTTP Motor Control Ready");
}
