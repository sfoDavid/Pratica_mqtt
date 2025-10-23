
# Consider dependencies only in project.
set(CMAKE_DEPENDS_IN_PROJECT_ONLY OFF)

# The set of languages for which implicit dependencies are needed:
set(CMAKE_DEPENDS_LANGUAGES
  "ASM"
  )
# The set of files for implicit dependencies of each language:
set(CMAKE_DEPENDS_CHECK_ASM
  "/home/david/mqtt_led/build/AmazonRootCA1.pem.S" "/home/david/mqtt_led/build/esp-idf/main/CMakeFiles/__idf_main.dir/__/__/AmazonRootCA1.pem.S.obj"
  "/home/david/mqtt_led/build/certificate.pem.crt.S" "/home/david/mqtt_led/build/esp-idf/main/CMakeFiles/__idf_main.dir/__/__/certificate.pem.crt.S.obj"
  "/home/david/mqtt_led/build/private.pem.key.S" "/home/david/mqtt_led/build/esp-idf/main/CMakeFiles/__idf_main.dir/__/__/private.pem.key.S.obj"
  )
set(CMAKE_ASM_COMPILER_ID "GNU")

# Preprocessor definitions for this target.
set(CMAKE_TARGET_DEFINITIONS_ASM
  "ESP_PLATFORM"
  "IDF_VER=\"v6.0-dev-2954-g5ab96242e8\""
  "MBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\""
  "SOC_MMU_PAGE_SIZE=CONFIG_MMU_PAGE_SIZE"
  "SOC_XTAL_FREQ_MHZ=CONFIG_XTAL_FREQ"
  "_GLIBCXX_HAVE_POSIX_SEMAPHORE"
  "_GLIBCXX_USE_POSIX_SEMAPHORE"
  "_GNU_SOURCE"
  "_POSIX_READER_WRITER_LOCKS"
  )

# The include file search paths:
set(CMAKE_ASM_TARGET_INCLUDE_PATH
  "config"
  "/home/david/mqtt_led/main"
  "/home/david/esp/esp-idf/components/esp_libc/platform_include"
  "/home/david/esp/esp-idf/components/freertos/config/include"
  "/home/david/esp/esp-idf/components/freertos/config/include/freertos"
  "/home/david/esp/esp-idf/components/freertos/config/xtensa/include"
  "/home/david/esp/esp-idf/components/freertos/FreeRTOS-Kernel/include"
  "/home/david/esp/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include"
  "/home/david/esp/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos"
  "/home/david/esp/esp-idf/components/freertos/esp_additions/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/include/soc"
  "/home/david/esp/esp-idf/components/esp_hw_support/dma/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/ldo/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/debug_probe/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/etm/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/mspi_timing_tuning/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/mspi_timing_tuning/tuning_scheme_impl/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/power_supply/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/modem/include"
  "/home/david/esp/esp-idf/components/esp_hw_support/port/esp32/."
  "/home/david/esp/esp-idf/components/esp_hw_support/port/esp32/include"
  "/home/david/esp/esp-idf/components/heap/include"
  "/home/david/esp/esp-idf/components/heap/tlsf"
  "/home/david/esp/esp-idf/components/log/include"
  "/home/david/esp/esp-idf/components/soc/include"
  "/home/david/esp/esp-idf/components/soc/esp32"
  "/home/david/esp/esp-idf/components/soc/esp32/include"
  "/home/david/esp/esp-idf/components/soc/esp32/register"
  "/home/david/esp/esp-idf/components/hal/platform_port/include"
  "/home/david/esp/esp-idf/components/hal/esp32/include"
  "/home/david/esp/esp-idf/components/hal/include"
  "/home/david/esp/esp-idf/components/esp_rom/include"
  "/home/david/esp/esp-idf/components/esp_rom/esp32/include"
  "/home/david/esp/esp-idf/components/esp_rom/esp32/include/esp32"
  "/home/david/esp/esp-idf/components/esp_rom/esp32"
  "/home/david/esp/esp-idf/components/esp_common/include"
  "/home/david/esp/esp-idf/components/esp_system/include"
  "/home/david/esp/esp-idf/components/esp_system/port/soc"
  "/home/david/esp/esp-idf/components/esp_system/port/include/private"
  "/home/david/esp/esp-idf/components/xtensa/esp32/include"
  "/home/david/esp/esp-idf/components/xtensa/include"
  "/home/david/esp/esp-idf/components/xtensa/deprecated_include"
  "/home/david/esp/esp-idf/components/lwip/include"
  "/home/david/esp/esp-idf/components/lwip/include/apps"
  "/home/david/esp/esp-idf/components/lwip/include/apps/sntp"
  "/home/david/esp/esp-idf/components/lwip/lwip/src/include"
  "/home/david/esp/esp-idf/components/lwip/port/include"
  "/home/david/esp/esp-idf/components/lwip/port/freertos/include"
  "/home/david/esp/esp-idf/components/lwip/port/esp32xx/include"
  "/home/david/esp/esp-idf/components/lwip/port/esp32xx/include/arch"
  "/home/david/esp/esp-idf/components/lwip/port/esp32xx/include/sys"
  "/home/david/esp/esp-idf/components/driver/i2c/include"
  "/home/david/esp/esp-idf/components/driver/touch_sensor/include"
  "/home/david/esp/esp-idf/components/driver/twai/include"
  "/home/david/esp/esp-idf/components/driver/touch_sensor/esp32/include"
  "/home/david/esp/esp-idf/components/esp_hal_i2c/esp32/include"
  "/home/david/esp/esp-idf/components/esp_hal_i2c/include"
  "/home/david/esp/esp-idf/components/esp_event/include"
  "/home/david/esp/esp-idf/components/esp_wifi/include"
  "/home/david/esp/esp-idf/components/esp_wifi/include/local"
  "/home/david/esp/esp-idf/components/esp_wifi/wifi_apps/include"
  "/home/david/esp/esp-idf/components/esp_wifi/wifi_apps/nan_app/include"
  "/home/david/esp/esp-idf/components/esp_phy/include"
  "/home/david/esp/esp-idf/components/esp_phy/esp32/include"
  "/home/david/esp/esp-idf/components/esp_netif/include"
  "/home/david/esp/esp-idf/components/mqtt/esp-mqtt/include"
  "/home/david/esp/esp-idf/components/tcp_transport/include"
  "/home/david/esp/esp-idf/components/esp-tls"
  "/home/david/esp/esp-idf/components/esp-tls/esp-tls-crypto"
  "/home/david/esp/esp-idf/components/mbedtls/port/include"
  "/home/david/esp/esp-idf/components/mbedtls/mbedtls/include"
  "/home/david/esp/esp-idf/components/mbedtls/mbedtls/library"
  "/home/david/esp/esp-idf/components/mbedtls/esp_crt_bundle/include"
  "/home/david/esp/esp-idf/components/esp_security/include"
  "/home/david/esp/esp-idf/components/mbedtls/mbedtls/3rdparty/everest/include"
  "/home/david/esp/esp-idf/components/mbedtls/mbedtls/3rdparty/p256-m"
  "/home/david/esp/esp-idf/components/mbedtls/mbedtls/3rdparty/p256-m/p256-m"
  "/home/david/esp/esp-idf/components/esp_timer/include"
  "/home/david/esp/esp-idf/components/nvs_flash/include"
  "/home/david/esp/esp-idf/components/esp_partition/include"
  "/home/david/esp/esp-idf/components/esp_blockdev/include"
  "/home/david/esp/esp-idf/components/esp_driver_gpio/include"
  "/home/david/esp/esp-idf/components/esp_driver_i2c/include"
  )

# The set of dependency files which are needed:
set(CMAKE_DEPENDS_DEPENDENCY_FILES
  "/home/david/mqtt_led/main/mqtt_led.c" "esp-idf/main/CMakeFiles/__idf_main.dir/mqtt_led.c.obj" "gcc" "esp-idf/main/CMakeFiles/__idf_main.dir/mqtt_led.c.obj.d"
  )

# Targets to which this target links which contain Fortran sources.
set(CMAKE_Fortran_TARGET_LINKED_INFO_FILES
  )

# Targets to which this target links which contain Fortran sources.
set(CMAKE_Fortran_TARGET_FORWARD_LINKED_INFO_FILES
  )

# Fortran module output directory.
set(CMAKE_Fortran_TARGET_MODULE_DIR "")
