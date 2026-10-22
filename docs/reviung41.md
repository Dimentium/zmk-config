# Reviung41 на SparkFun Pro Micro RP2040

Цель сборки ZMK main: `sparkfun_pro_micro_rp2040//zmk`, shield `reviung41`, snippet `studio-rpc-usb-uart`.

ZMK Studio включена и всегда разблокирована: `CONFIG_ZMK_STUDIO=y`, `CONFIG_ZMK_STUDIO_LOCKING=n`. Подключение по USB к https://zmk.studio/ позволяет менять раскладку без unlock-клавиши. Блокировка после перезапуска, простоя или отключения клиента отсутствует.

Пользовательские файлы находятся в стандартных местах: `config/reviung41.conf` и `config/reviung41.keymap`. Keymap подключает общий `keymap_30.dtsi` из корня репозитория. Локального shield Reviung41 больше нет: матрица, контакты, Kconfig и физические позиции 41 клавиши берутся из встроенного shield ZMK.

Миграция выполнена отдельно в ветке `modernize-reviung41`. Контрольный коммит до миграции: `2401eb9`. Остальные клавиатуры в `config/boards/shields/` пока не перенесены; из-за них ZMK ещё выводит общее предупреждение об устаревшем `config/boards`. Оно не относится к новому расположению Reviung41.

Для RP2040 в его цели сборки отключены неподдерживаемые sleep/soft-off и BLE. В локальном keymap `MIDDLE_TRANS` пустой: общий `THUMBS_TRANS` уже содержит пять `&trans`, соответствующих пяти нижним клавишам Reviung41. Общий `keymap_30.dtsi` не изменён.

Результат сборки: `firmware/reviung41/reviung41-sparkfun_pro_micro_rp2040-studio.uf2`. Рядом контрольная сумма и manifest с точными версиями зависимостей. Сборка проверена 2026-10-22; испытания на физической плате не выполнялись.

Для прошивки войти в BOOTSEL-режим RP2040 и скопировать UF2 на диск `RPI-RP2`. Изменения раскладки, сохранённые ранее через Studio, могут переопределять исходную раскладку и после перепрошивки.

Локальная сборка из корня настроенного west workspace:

```sh
west build -s zmk/app -d build/reviung41 -b sparkfun_pro_micro_rp2040//zmk \
  -S studio-rpc-usb-uart -- -DSHIELD=reviung41 \
  -DZMK_CONFIG="$HOME/git/zmk-config/config" \
  -DCONFIG_ZMK_STUDIO=y -DCONFIG_ZMK_STUDIO_LOCKING=n
```

## nice!nano v2: USB + BLE

В `build.yaml` добавлена отдельная цель `nice_nano//zmk` (ревизия 2.0.0 по умолчанию), shield `reviung41`, artifact `reviung41-nice_nano-studio`. Она использует ту же раскладку и всегда разблокированную Studio; USB и BLE включены одновременно. Также включены сон через 6000000 мс простоя и отчёт об аккумуляторе через штатный драйвер nice!nano. Studio имеет USB и BLE транспорты; для BLE использовать нативное приложение.

Общий `config/reviung41.conf` больше не отключает BLE. Параметры контроллеров задаются отдельно в `cmake-args` соответствующих целей: nice!nano включает BLE/сон/батарею, RP2040 явно отключает BLE/сон/soft-off. Для локальной сборки необходимо передать те же аргументы из `build.yaml`.

UF2 для nice!nano нельзя прошивать в RP2040 и наоборот. Сохранённые Studio настройки сохраняются при обычной перепрошивке. Для выбора USB/BLE выхода можно назначить `&out OUT_USB` / `&out OUT_BLE` в Studio; профили Bluetooth выбираются через `&bt BT_SEL`.
