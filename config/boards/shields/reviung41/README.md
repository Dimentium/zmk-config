# Reviung41 на SparkFun Pro Micro RP2040

Цель сборки ZMK main: `sparkfun_pro_micro_rp2040//zmk`, shield `reviung41`, snippet `studio-rpc-usb-uart`.

ZMK Studio включена и всегда разблокирована: `CONFIG_ZMK_STUDIO=y`, `CONFIG_ZMK_STUDIO_LOCKING=n`. Подключение по USB к https://zmk.studio/ позволяет менять раскладку без unlock-клавиши. Блокировка после перезапуска, простоя или отключения клиента отсутствует.

`config/reviung41.keymap` подключает существующий keymap из этой папки, который использует общий `keymap_30.dtsi`. `config/reviung41.conf` — символическая ссылка на настройки из этой папки. Без этих точек входа текущая ZMK выбирает встроенные keymap/conf Reviung41. Матрица и физические позиции 41 клавиши берутся из встроенного shield ZMK.

Для RP2040 отключены неподдерживаемые sleep/soft-off, убраны неприменимые BLE-настройки. В локальном keymap `MIDDLE_TRANS` пустой: общий `THUMBS_TRANS` уже содержит пять `&trans`, соответствующих пяти нижним клавишам Reviung41. Общий `keymap_30.dtsi` не изменён.

Результат сборки: `firmware/reviung41/reviung41-sparkfun_pro_micro_rp2040-studio.uf2`. Рядом контрольная сумма и manifest с точными версиями зависимостей. Сборка проверена 2026-10-22; испытания на физической плате не выполнялись.

Для прошивки войти в BOOTSEL-режим RP2040 и скопировать UF2 на диск `RPI-RP2`. Изменения раскладки, сохранённые ранее через Studio, могут переопределять исходную раскладку и после перепрошивки.

Локальная сборка из корня настроенного west workspace:

```sh
west build -s zmk/app -d build/reviung41 -b sparkfun_pro_micro_rp2040//zmk \
  -S studio-rpc-usb-uart -- -DSHIELD=reviung41 \
  -DZMK_CONFIG="$HOME/git/zmk-config/config" \
  -DCONFIG_ZMK_STUDIO=y -DCONFIG_ZMK_STUDIO_LOCKING=n
```
