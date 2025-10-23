idf_component_register(
    SRCS "mqtt_led.c"
    INCLUDE_DIRS "."
    REQUIRES driver esp_event esp_wifi esp_netif mqtt nvs_flash esp_driver_gpio esp_driver_i2c
)
# Embute os PEM no firmware
# SPIFFS partition disabled - using embedded certificates instead
# SPIFFS disabled - certificates will be embedded directly
# spiffs_create_partition_image(storage ../main/certs FLASH_IN_PROJECT)
# (Alternativa sem SPIFFS: embed txt direto no binário)

# Cert paths relative to this CMakeLists.txt (no "main/" prefix)
set(_CERT_DIR "${CMAKE_CURRENT_LIST_DIR}/certs")

if (EXISTS "${_CERT_DIR}/AmazonRootCA1.pem")
    target_add_binary_data(${COMPONENT_LIB} "certs/AmazonRootCA1.pem" TEXT)
endif()
if (EXISTS "${_CERT_DIR}/certificate.pem.crt")
    target_add_binary_data(${COMPONENT_LIB} "certs/certificate.pem.crt" TEXT)
endif()
if (EXISTS "${_CERT_DIR}/private.pem.key")
    target_add_binary_data(${COMPONENT_LIB} "certs/private.pem.key" TEXT)
endif()