# FlipperZero-PhantomCN-Firmware

Flipper Zero 汉化定制固件· Phantom 版

基于 **mntm-012** 的全量中文汉化 + 功能增强固件，由 **Phantom** 汉化开发。

宋体中文界面、桌面播放 Bad Apple 动画，内置 BLE Killer、SubGHz 暴力破解（PT2262）以及一批射频干扰 / 特斯拉信号包，开箱即用。

---

## 一、相对原版新增 / 改动

### 1. 全量中文汉化（宋体）
- 界面文案内联汉化，覆盖菜单、设置、各应用主流程，约 600+ 处字符串。
- 自带 **宋体（SimSun）风格** 中文字库，以 asset pack（`PhantomCN`）形式随资源写入 SD 卡，不占用固件 flash 空间。
- 字库为 u8g2 格式：`Primary.u8f` / `Secondary.u8f`，包含常用 CJK 字符。
- 开机默认启用资源包 `PhantomCN`（见“自定义”一节，可在 设置 → Momentum → 资源包 中切换）。

### 2. 桌面 Bad Apple 动画
- 经典《Bad Apple!!》开场（灵梦 → 魔理沙）片段，转换为 Flipper 桌面动画格式。
- 共 **255 帧**，128×64 单色，默认 24 fps。
- 作为 `PhantomCN` 资源包的 Anim 随包加载，开机桌面即播放。

### 3. 新增应用（Apps）
| 应用 | 名称 | 说明 |
|---|---|---|
| BLE Killer | `[BLE] BLE Killer` | 蓝牙广播干扰 / 设备压制工具 |
| SubGHz BF PT2262 | `SubGHz BF PT2262` | SubGHz 暴力破解，强化 PT2262 等固定码芯片支持 |

两个应用均针对 mntm-012 SDK 重新编译为 `.fap`，随固件资源安装到 SD 卡 `apps/` 目录。

### 4. 内置 SubGHz 信号包
| 目录 | 数量 | 内容 |
|---|---|---|
| `subghz/RF_Jammer/` | 52 | 各频段射频干扰 `.sub` |
| `subghz/Tesla_kaigai/` | 9 | 特斯拉充电口 / 信号 `.sub` |

刷入后在 SubGHz → 已保存 中即可直接调用。

---

## 二、核心功能详解

### 1. 内置主功能
| 模块 | 功能 |
|---|---|
| Sub-GHz | 支持读取、保存、重放、频率分析、Read RAW、协议解码、外部 `.sub` 文件加载；本包额外内置 RF Jammer 与 Tesla 信号资源。 |
| NFC | 支持读卡、保存、模拟、写入、MIFARE Classic 工具链、字典资源、Magic 卡相关功能，并打包 Amiibo、Metroflip、Seader、PicoPass 等扩展。 |
| 125kHz RFID | 支持低频卡读取、保存、模拟、写入、RAW 处理、T5577 写卡与 RFID Fuzzer 扩展。 |
| Infrared | 支持红外学习、保存、发送、通用遥控器、空调码库、外部 `.ir` 资源；内置 AC、TV、Audio、Projector、Fan 等资产。 |
| iButton | 支持 Dallas、Cyfral、Metakom 等钥匙读取、保存、模拟、写入，并包含 fuzzer 与转换工具。 |
| GPIO | 支持 UART、I2C、SPI、1-Wire、GPIO 控制、传感器、调试探针、ESP/NRF24/VGM/Mayhem/FlipBoard 等外设生态。 |
| BadUSB / BadKB | 支持 USB HID 脚本、键盘布局资源、BadKB 蓝牙/USB 输入类工具。 |
| U2F / HID | 支持 U2F 安全密钥、USB/BLE HID Remote、USB Consumer Control、XInput 控制器等。 |
| Archive / Storage | 文件浏览、资源管理、SD 卡信息、格式化、更新包管理。 |
| JS / uPython | 内置 JavaScript Runner 与 uPython 扩展，可运行脚本与轻量自动化。 |
| Momentum 设置 | 支持资源包、字体、桌面动画、界面外观、协议与系统行为等 Momentum 扩展设置。 |

### 2. Phantom 定制功能
| 功能 | 说明 |
|---|---|
| 中文汉化 | 菜单、设置、核心应用流程约 600+ 处中文化，默认使用 `PhantomCN` 资源包。 |
| 宋体字库 | `Primary.u8f` / `Secondary.u8f` 放在 `asset_packs/PhantomCN/Fonts/`，随 SD 资源包加载 |
| BLE Killer | `[BLE] BLE Killer`，用于 BLE 广播压测、广播包刷屏与近场蓝牙干扰测试。 |
| SubGHz BF PT2262 | `SubGHz BF PT2262`，针对 PT2262 等固定码芯片的 Sub-GHz 暴力枚举工具。 |
| RF Jammer 资源 | `subghz/RF_Jammer/` 内置 52 个 `.sub` 信号文件。 |
| Tesla 资源 | `subghz/Tesla_kaigai/` 内置 9 个特斯拉相关 `.sub` 信号文件。 |

## 三、完整应用清单

最终资源包内共包含 **260 个 `.fap` 应用**。下面按 SD 卡菜单目录列出，名称和说明来自源码 `application.fam`、随包 README 与最终打包路径。

### Bluetooth（6 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[BLE] BLE Killer` | `ble_killer.fap` | Bluetooth 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `BLE Spam` | `ble_spam.fap` | Flood BLE advertisements to cause spammy and annoying popups/notifications |
| `BT Trigger` | `bt_trigger.fap` | Control your smartphone camera via your Flipper Zero |
| `FindMy Flipper` | `findmy.fap` | BLE FindMy Location Beacon |
| `Bluetooth Remote` | `hid_ble.fap` | Use Flipper as a HID remote control over Bluetooth |
| `PC Monitor` | `pc_monitor.fap` | Application for monitoring PC resources |

### Games（41 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `4 in a Row` | `4inrow.fap` | 4 in row Game |
| `Air Arkanoid` | `air_arkanoid.fap` | Arkanoid game that supports the Video Game Module motion sensor |
| `Air Labyrinth` | `air_labyrinth.fap` | Labyrinth game v0.1 that supports the Video Game Module motion sensor. Written by @CodeAllNight (https://youtube.com/MrDerekJamison/about) |
| `Arkanoid` | `arkanoid.fap` | Arkanoid Game |
| `Asteroids` | `asteroids.fap` | Asteroids game |
| `BlackJack` | `blackjack.fap` | Blackjack Game |
| `Bomberduck` | `bomberduck.fap` | Bomberduck(Bomberman) Game |
| `Chess` | `chess.fap` | Chess for Flipper |
| `Color Guess` | `color_guess.fap` | Color Guessing Game |
| `DOOM` | `doom.fap` | Will it run Doom? |
| `Flappy Bird` | `flappy_bird.fap` | Flappy Bird Game |
| `Pong` | `flipper_pong.fap` | Simple pong game |
| `2048` | `game_2048.fap` | Play the port of the 2048 game on Flipper Zero. |
| `Game 15` | `game15.fap` | Logic Game |
| `Game of Life` | `gameoflife.fap` | Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. |
| `Geometry Flip` | `geometry_flip.fap` | A simple app |
| `Heap Defence` | `heap_defence.fap` | Heap Defence game from hackathon (aka Stack Attack) |
| `Jetpack Joyride` | `jetpack_joyride.fap` | Games 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Laser Tag` | `laser_tag.fap` | Laser Tag game for Flipper Zero |
| `Mine Sweeper` | `minesweeper_redux.fap` | Flipper Zero Minesweeper Implementation |
| `Multi-Dice` | `multi_dice.fap` | Games 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Pinball0` | `pinball0.fap` | Pinball game |
| `Quadrastic` | `quadrastic.fap` | Quadrastic is a simple addicting game inspired by the Arduboy game of the same name |
| `Reversi` | `reversi.fap` | Reversi game, the game controls should be intuitive. Longs press on OK opens the menu to start a new game. |
| `Roots of Life` | `roots_of_life.fap` | A zen-puzzle game for FlipperZero, puzzle made on GlobalGameJam23 (theme: Roots) |
| `Rubik's Cube Scrambler` | `rubiks_cube_scrambler.fap` | App generates random moves to scramble a Rubik's cube. |
| `Scorched Tanks` | `scorched_tanks.fap` | A Flipper Zero game inspired by scorched earth |
| `Simon Says` | `simon_says.fap` | A Simon Says Game |
| `Slot Machine` | `slotmachine.fap` | Simple Slots simulator game |
| `Snake 2.0` | `snake20.fap` | Advanced Snake Game (Remake of original Snake) |
| `Solitaire` | `solitaire.fap` | Klondike Solitaire card game |
| `T-Rex Runner` | `t_rex_runner.fap` | Play the port of the Chrome browser T-Rex game on your Flipper Zero. |
| `Tamagotchi` | `tama_p1.fap` | Games 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Tanks` | `tanks.fap` | Games 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Tetris` | `tetris.fap` | Tetris Game |
| `Tic Tac Toe` | `tictactoe.fap` | Tic Tac Toe game, for 2 players, play on one device |
| `Umpire Indicator` | `umpire_indicator.fap` | Umpire indicators keep track of balls, strikes, and outs for Baseball and Softball |
| `Video Poker` | `videopoker.fap` | Video poker is a casino game based on five-card draw poker |
| `Yappy Invaders` | `yapinvaders.fap` | Yappy version of Space Invaders. |
| `Yatzee` | `yatzee.fap` | Yahtzee game |
| `Zombiez` | `zombiez.fap` | Defend your walls from the zombies |

### GPIO（23 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[BMI/LSM] Air Mouse` | `air_mouse.fap` | GPIO 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[A33] Flipper Blackhat` | `blackhat.fap` | Control of the flipper blackhat device |
| `[RC2014] ColecoVision` | `coleco.fap` | GPIO 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[LED] Flashlight` | `flashlight.fap` | Enables 3.3v on pin 7/C3 when you press Ok and leaves it on when you exit app |
| `[SPI] Terminal` | `flipper_spi_terminal.fap` | A Terminal Application for the SPI interface |
| `[GPIO] Oscilloscope` | `flipperscope.fap` | Oscilloscope application - apply signal to pin 16/PC0, with a voltage ranging from 0V to 2.5V and ground to pin 18/GND |
| `[TEA5767] FM Radio` | `fm_radio.fap` | FM Radio App |
| `[KT0803] FM Transmitter` | `fmtx_app.fap` | GPIO 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `GPIO` | `gpio.fap` | GPIO 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[DIAG] GPIO Badge` | `gpio_badge.fap` | GPIO 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[GPIO] Controller` | `gpio_controller.fap` | GPIO 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[GPIO] Explorer` | `gpio_explorer_app.fap` | The most complete app to start exploring the GPIO functionalities |
| `[GPIO] Reader (aureli1c)` | `gpio_reader_a.fap` | Read GPIO pins states, and display them on the screen |
| `[GPIO] Reader (biotinker)` | `gpio_reader_b.fap` | GPIO 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[GPIO] Sentry Safe` | `gpio_sentry_safe.fap` | App exploiting vulnerability to open any Sentry Safe and Master Lock electronic safes without pin code. |
| `[GPIO] Longwave Clock` | `longwave_clock.fap` | Decode or demonstrate long wave time signals |
| `[MAG] MagSpoof` | `magspoof.fap` | Enables wireless transmission of magstripe data |
| `[GB] Pokemon Trading` | `pokemon.fap` | Pokemon exchange from Flipper Zero to Game Boy, supports Generation I & II non-Japanese games |
| `[GPIO] Signal Generator` | `signal_generator.fap` | Control GPIO pins to generate digital signals |
| `[GPIO] Timelapse` | `timelapse.fap` | Simple intervalometer/timelapse app |
| `[UART] UART Terminal` | `uart_terminal.fap` | Control various devices via the Flipper Zero UART interface. |
| `[WII] EC Analyser` | `wii_ec_anal.fap` | Wii Extension Controller Protocol Analyser |
| `[GPIO] Wire Tester` | `wire_tester.fap` | Beeps if a wire is continuous |

### GPIO/Debug（8 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[AVR] AVR Flasher` | `avr_isp.fap` | Application for flashing AVR microcontrollers |
| `[SWD-JTAG] DAP Link` | `dap_link.fap` | Enables use of Flipper as a debug probe for ARM devices, implements the CMSIS-DAP protocol |
| `[W5500] Ethernet` | `eth_troubleshooter.fap` | Test your Ethernet connection with W5500 module and Flipper |
| `[FTDI232H] FlipTDI` | `flip_tdi.fap` | Flipper FTDI232H emulator. |
| `[I2C] i2c Tools` | `i2ctools.fap` | Set of i2c tools |
| `[INA2xx] INA Meter` | `ina_meter.fap` | Application for reading TI INAxxx sensors. |
| `[SPI] SPI Mem Manager` | `spi_mem_manager.fap` | Application for reading and writing 25-series SPI memory chips |
| `[SWD] SWD Probe` | `swd_probe.fap` | ARM SWD (Single Wire Debug) Probe |

### GPIO/ESP（10 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[ESP32CAM] Camera Suite` | `camera_suite.fap` | A camera suite application for the Flipper Zero ESP32-CAM module. |
| `[ESP] ESP Flasher` | `esp_flasher.fap` | GPIO/ESP 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[ESP32] WiFi Marauder` | `esp32_wifi_marauder.fap` | GPIO/ESP 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[ESP8266] Deauther` | `esp8266_deauther.fap` | DSTIKE Deauther module interface, based on ESP8266 |
| `[ESP8266] IFTTT Btn` | `esp8266_ifttt_virtual_button.fap` | GPIO/ESP 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[ESP8266] Deauther v2` | `esp8266_wifi_deauther_v2.fap` | Works with ESP8266 Deauther v2 by @SpacehuhnTech (github) |
| `[ESP32] Evil Portal` | `evil_portal.fap` | Create an evil captive portal Wi-Fi access point |
| `[ESP32] Ghost ESP` | `ghost_esp.fap` | GPIO/ESP 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[ESP32GPS] Wardriver` | `wardriver.fap` | Sniff WiFi access points with GPS location coordinates |
| `[ESP] WiFi Scanner` | `wifi_scanner.fap` | WiFi scanner module interface, based on ESP8266 |

### GPIO/FlipBoard（4 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `FlipBoard Blinky` | `flipboard_blinky.fap` | FlipBoard Blinky turns your FlipBoard into a blinky badge. |
| `FlipBoard Keyboard` | `flipboard_keyboard.fap` | FlipBoard Keyboard turns your FlipBoard into a keyboard. |
| `FlipBoard Signal` | `flipboard_signal.fap` | FlipBoard Signal turns your FlipBoard into a signal sender. |
| `FlipBoard Simon` | `flipboard_simon.fap` | Simon memory game for the FlipBoard. |

### GPIO/FlipperHTTP（11 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `FlipDownloader` | `flip_downloader.fap` | Download apps and assets via WiFi directly to your Flipper Zero |
| `FlipLibrary` | `flip_library.fap` | Utilize WiFi to retrieve data from 20 different APIs |
| `FlipMap` | `flip_map.fap` | Find Flipper Zero Users |
| `FlipSocial` | `flip_social.fap` | Social media platform for the Flipper Zero. |
| `FlipTelegram` | `flip_telegram.fap` | Flipper Zero Telegram Client |
| `FlipTrader` | `flip_trader.fap` | Use WiFi to get the price of stocks and currency pairs on your Flipper Zero. |
| `FlipWeather` | `flip_weather.fap` | Use WiFi to get GPS and Weather information on your Flipper Zero. |
| `FlipWiFi` | `flip_wifi.fap` | FlipperHTTP companion app. |
| `FlipWorld` | `flip_world.fap` | The first open-world multiplayer game, best played with the VGM. |
| `Free Roam` | `free_roam.fap` | 3D Open World Multiplayer Game |
| `Web Crawler` | `web_crawler.fap` | Browse the web, fetch API data, and more. |

### GPIO/GPS（2 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[NMEA] GPS` | `gps_nmea.fap` | Works with GPS modules via UART, using NMEA protocol. |
| `[NMEA] Nearby Files` | `nearby_files.fap` | A GPS-enabled file browser that displays files sorted by distance from your current location. |

### GPIO/MALVEKE（7 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[GB/GBC] Cartridge` | `malveke_gb_cartridge.fap` | GPIO/MALVEKE 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[GB] Emulator` | `malveke_gb_emulator.fap` | GAME BOY Emulator (POC). |
| `[GB] Link-Camera` | `malveke_gb_link_camera.fap` | extract your GAME BOY Camera picture via WIFI, so they can be easily shared with your phone, tablet or pc. Easy to use, just hook up to your GAME BOY… |
| `[GB] Live Camera` | `malveke_gb_live_camera.fap` | Insert a GAME BOY Camera cartridge, you can use it as a camera and take snapshots from the Flipper Zero. |
| `[GB] Photo` | `malveke_gb_photo.fap` | Game Boy Camera save RAM photo to BMP from the Flipper Zero. |
| `[GBA] Cartridge` | `malveke_gba_cartridge.fap` | GPIO/MALVEKE 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[GB] PIN Test` | `malveke_pin_test.fap` | ESP32 GAME BOY CAMERA live feed and photo capture, use left/right for exposition and center for saving a screenshot. |

### GPIO/MAYHEM（6 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[MAYHEM] Camera` | `mayhem_camera.fap` | ESP32-CAM live feed and photo capture, use left/right for orientation/mode, up/down for brightness and center for saving a screenshot. [Unplug the US… |
| `[MAYHEM] Marauder` | `mayhem_marauder.fap` | ESP32-CAM version of Marauder. Includes all functionality from the original plus some options to trigger the camera and flashlight. [Unplug the USB c… |
| `[MAYHEM] Morse Flash` | `mayhem_morseflash.fap` | ESP32-CAM app to stream a message in morse using the powerful flashlight. [Unplug the USB cable to test with Mayhem] |
| `[MAYHEM] Motion Detection` | `mayhem_motion.fap` | ESP32-CAM Motion detection. It generates a beep when motion is detected. Can be extended to trigger more stuff in the code. [Unplug the USB cable to … |
| `[MAYHEM] Nanny Cam` | `mayhem_nannycam.fap` | ESP32-CAM simple app to start a remote camera. [Unplug the USB cable to test with Mayhem] |
| `[MAYHEM] QR Code` | `mayhem_qrcode.fap` | ESP32-CAM simple app to show a payload from QR codes. Can be extended to trigger more stuff in the code. [Unplug the USB cable to test with Mayhem] |

### GPIO/NRF24（5 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[NRF24] Batch` | `nrf24batch.fap` | GPIO/NRF24 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[NRF24] Channel Scan` | `nrf24channelscanner.fap` | Scans 2.4Ghz frequency for usage data. |
| `[NRF24] Mouse Jacker` | `nrf24mousejacker.fap` | App works with NRF24 Sniffer app to perform mousejack attacks |
| `[NRF24] Scanner` | `nrf24scan.fap` | GPIO/NRF24 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[NRF24] Sniffer` | `nrf24sniff.fap` | App captures addresses to use with NRF24 Mouse Jacker app to perform mousejack attacks |

### GPIO/Sensors（8 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[MH-Z19] CO2 Logger` | `co2_logger.fap` | CO2 Logger with CSV export |
| `[J305] Atomic Dice Roller` | `flipper_atomicdiceroller.fap` | GPIO/Sensors 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `[J305] Geiger Counter` | `flipper_geiger.fap` | Works with J305 Geiger tube on external board |
| `[HC-SR] Dist. Sensor` | `hc_sr04.fap` | HC-SR(04) Distance sensor reader |
| `[BH1750] Lightmeter` | `lightmeter.fap` | Lightmeter app for photography |
| `[RCWL0516] Radar Scan` | `radar_scanner.fap` | Detects the movement of living things using radar |
| `[GPIO] Unitemp` | `unitemp.fap` | Application for reading temperature, humidity and pressure sensors like a DHT11/22, DS18B20, BMP280, HTU21 and more |
| `[AS7331] UV Meter` | `uv_meter_as7331.fap` | Measure UV radiation using the AS7331 sensor |

### GPIO/VGM（2 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `[VGM] Air Mouse` | `vgm_air_mouse.fap` | Turn Flipper Zero with the Video Game Module into an air mouse |
| `[VGM] Video Game Module Tool` | `video_game_module_tool.fap` | This app is a standalone firmware updater/installer for the Video Game Module |

### iButton（3 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `iButton Fuzzer` | `fuzzer_ibtn.fap` | Fuzzer for ibutton readers |
| `iButton` | `ibutton.fap` | iButton 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `iButton Converter` | `ibutton_converter.fap` | Cyfral and Metakom to Dallas converter |

### Infrared（12 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `Flame RNG` | `flame_rng.fap` | An RNG intended for use with flames and other IR sources. |
| `XRemote` | `flipper_xremote.fap` | Advanced infrared remote application |
| `Hitachi AC Remote` | `hitachi_ac_remote.fap` | Hitachi Air Conditioner remote controller |
| `Infrared` | `infrared.fap` | Infrared 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `IR Intervalometer` | `ir_intervalometer.fap` | Intervalometer for Pentax, Canon, Nikon, and Sony cameras. Uses IR shutter release. |
| `IR Remote` | `ir_remote.fap` | Bind any IR remote button to each button on flipper d-pad, provides another way to use flipper as IR remote. |
| `IR Scope` | `ir_scope.fap` | App allows to see incoming IR signals. |
| `LIDAR Emulator` | `lidar_emulator.fap` | Infrared 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Midea AC Remote` | `midea_ac_remote.fap` | Midea Electric Air Conditioner remote control |
| `Mitsubishi AC Remote` | `mitsubishi_ac_remote.fap` | Mitsubishi Electric Air Conditioner remote control |
| `Xbox Controller` | `xbox_controller.fap` | Infrared remote control for Xbox One |
| `Cross Remote` | `xremote.fap` | One-Click, sends multiple commands |

### Media（15 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `BPM Tapper` | `bpm_tapper.fap` | Tap center button to measure BPM |
| `Etch a Sketch` | `etch.fap` | Turn the Flipper Zero into an Etch A Sketch |
| `Flizzer Tracker` | `flizzer_tracker.fap` | An advanced Flipper Zero chiptune tracker with 4 channels |
| `Fmatrix` | `fmatrix.fap` | Displays a 'matrix rain' screensaver. |
| `Space Playground` | `fzspground.fap` | A simple space simulation playground for Flipper Zero |
| `Image Viewer` | `image_viewer.fap` | Image viewer for flipper zero! |
| `Metronome` | `metronome.fap` | Metronome app |
| `Morse Code` | `morse_code.fap` | Simple Morse Code parser |
| `Music Player` | `music_player.fap` | An app to play RTTL music files |
| `Paint` | `paint.fap` | A basic Paint app, Click Ok to draw dot, hold Ok to enable drawing continuously, hold Back to clear the screen |
| `Text to SAM` | `text2sam.fap` | Convert text to speech on your Flipper Zero with SAM (Software Automatic Mouth). |
| `Tuning Fork` | `tuning_fork.fap` | Tuning fork for tuning musical instruments and more |
| `USB-MIDI` | `usb_midi.fap` | Turn Flipper into MIDI instrument |
| `Video Player` | `video_player.fap` | An app that plays video along with sound on Flipper Zero. |
| `WAV Player` | `wav_player.fap` | Audio player for WAV files, recommended to convert files to unsigned 8-bit PCM stereo, but it may work with others too |

### NFC（19 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `Amiibo Toolkit` | `ami_tool.fap` | An Amiibo toolkit for Flipper Zero |
| `Cyborg Detector` | `cyborg_detector.fap` | App generates a continous NFC field to make body mod implant LEDs glow. Tested on a Dangerous Things xSIID. |
| `Metroflip` | `metroflip.fap` | An implementation of metrodroid on the flipper |
| `MIFARE Classic Editor` | `mfc_editor.fap` | Application for viewing and editing MIFARE Classic .nfc files |
| `MFKey` | `mfkey.fap` | MIFARE Classic key recovery tool |
| `Mifare Fuzzer` | `mifare_fuzzer.fap` | App emulates Mifare Classic cards with various UIDs to check how reader reacts on them |
| `NFC` | `nfc.fap` | NFC 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `NFC APDU Runner` | `nfc_apdu_runner.fap` | Run APDU commands from script files |
| `NFC-Eink` | `nfc_eink.fap` | Application for emulation and writing to NFC Eink tags |
| `NFC PC Login` | `nfc_login.fap` | NFC based desktop login using USB HID or BLE HID |
| `NFC Magic` | `nfc_magic.fap` | Application for writing to NFC tags with modifiable sector 0 |
| `NFC Maker` | `nfc_maker.fap` | Create NFC files for BT MACs, Contacts, Links, Emails, Phones, Text and WiFis |
| `NFC Playlist` | `nfc_playlist.fap` | A Tool used to running through a list of NFC cards |
| `Passport Reader` | `passy.fap` | eMRTD Reader |
| `HID iClass (PicoPass)` | `picopass.fap` | App to communicate with PicoPass(iClass) tags |
| `SaFlip` | `saflip.fap` | SaFlip Hospitality Tool for Flipper Zero |
| `Seader` | `seader.fap` | NFC 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Seos Compatible` | `seos.fap` | Seos compatible reader/emulator |
| `Weebo` | `weebo.fap` | An NTAG215 parser, writer, emulator, remixer, duplicator |

### RFID（7 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `EM4100 Key Generator` | `em4100_generator.fap` | Generates EM4100 key lists from selected rfid key file for RFID fuzzer app |
| `RFID Fuzzer` | `fuzzer_rfid.fap` | Fuzzer for lfrfid readers |
| `125 kHz RFID` | `lfrfid.fap` | RFID 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Simultaneous UHF RFID Reader` | `simultaneous_rfid_reader.fap` | Simultaneous UHF RFID Reader that supports the M6E Nano, M7E Hecto, and YRM1000 series Readers. Read up to 150 UHF tags per second [Using ThingMagic … |
| `T5577 Multiwriter` | `t5577_multiwriter.fap` | Application for writing several keys to one t5577 |
| `T5577 Raw Writer` | `t5577_writer.fap` | 见随包 README，提供更完整的应用说明。 |
| `YRM100 UHF RFID` | `uhf_rfid.fap` | RFID 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |

### Settings（13 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `About` | `about.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Bluetooth` | `bt_settings.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Clock & Alarm` | `clock_settings.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Desktop` | `desktop_settings.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Expansion Modules` | `expansion_settings.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Input` | `input_settings.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `JS Runner` | `js_app.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Momentum` | `momentum_app.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `LCD and Notifications` | `notification_settings.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Passport` | `passport.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Power` | `power_settings.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Storage` | `storage_settings.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `System` | `system_settings.fap` | Settings 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |

### Sub-GHz（21 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `Chief Cooker` | `chief_cooker.fap` | A simple app |
| `Enhanced Sub-Ghz Chat` | `esubghz_chat.fap` | Send text messages over Sub-GHz radio to another Flippers |
| `Flipper Share` | `flipper_share.fap` | Direct file transfer between flippers via Sub-GHz |
| `Music to Sub-GHz Radio` | `fmf_to_sub.fap` | Converts Flipper music files (.FMF and .TXT) into Sub-GHz files (.SUB). |
| `HC-11 Modem` | `hc11_modem.fap` | HC-11 wireless modem |
| `Restaurant Pager` | `meal_pager.fap` | This app triggers restaurant pagers in a brute force manner, useful to test if devices are still functional. |
| `POCSAG Pager` | `pocsag_pager.fap` | App can capture POCSAG 1200 messages on CC1101 supported frequencies. |
| `ProtoView` | `protoview.fap` | Digital signal detection, visualization, editing and reply tool |
| `Radio Scanner` | `radio_scanner.fap` | Scanner for Flipper |
| `Rolling Flaws` | `rolling_flaws.fap` | Rolling code receiver (version 1.5), used to learn about rolling code flaws. Watch video at https://youtu.be/gMnGuDC9EQo |
| `Spectrum Analyzer` | `spectrum_analyzer.fap` | Displays a spectrogram chart to visually represent RF signals around you. |
| `Sub Analyzer` | `sub_analyzer.fap` | Analyze SubGhz .sub files to extract all signal properties |
| `SubGHz BF PT2262` | `subbrute_pt2262.fap` | Sub-GHz 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Sub-GHz Bruteforcer` | `subghz_bruteforcer.fap` | Sub-GHz 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Sub-GHz` | `subghz_fap.fap` | Sub-GHz 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Sub-GHz Playlist` | `subghz_playlist.fap` | App works with list of sub-ghz files from .txt file that contains paths to target files. |
| `Sub-GHz Playlist Creator` | `subghz_playlist_creator.fap` | App for creating or editing SubGhz playlists |
| `Sub-GHz Remote` | `subghz_remote.fap` | SubGhz Remote, uses up to 5 .sub files |
| `Sub-GHz Scheduler` | `subghz_scheduler.fap` | Send a Sub-GHz signal repeatedly at a given interval. |
| `TPMS Reader` | `tpms.fap` | Use SubGHz and RFID to read or activate TPMS sensors |
| `Weather Station` | `weather_station.fap` | Receive weather data from a wide range of supported Sub-1GHz remote sensor |

### Tools（30 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `Bad KB` | `bad_kb.fap` | Tools 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `Barcode` | `barcode_app.fap` | App allows you to display various barcodes on flipper screen |
| `Caesar Cipher` | `caesar_cipher.fap` | Encrypt and decrypt text using Caesar Cipher |
| `Calculator` | `calculator.fap` | Calculator, that can calculate simple expressions |
| `CAN Tools` | `can_tools.fap` | CAN Tools, DBC creation, Data decoding |
| `Count Down Timer` | `cntdown_tim.fap` | Simple count down timer |
| `Combo Cracker` | `combo_cracker.fap` | Crack combo locks in 8 attempts or less |
| `Counter` | `counter.fap` | Simple counter |
| `DTMF Dolphin` | `dtmf_dolphin.fap` | DTMF (Dual-Tone Multi-Frequency) dialer, Bluebox, and Redbox. |
| `FlipCrypt` | `flip_crypt.fap` | Encrypt, decrypt, and hash text using a wide variety of classic and modern crypto tools. |
| `FlipBIP Crypto Wallet` | `flipbip.fap` | Crypto wallet for Flipper |
| `Flipp Pomodoro` | `flipp_pomodoro.fap` | Tools 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `HEX Editor` | `hex_editor.fap` | Read text files line by line and edit them without a computer or smartphone. |
| `HEX Viewer` | `hex_viewer.fap` | App allows to view various files as HEX |
| `IconEdit` | `iconedit.fap` | Icon editor |
| `Key Copier` | `key_copier.fap` | 见随包 README，提供更完整的应用说明。 |
| `Multi Converter` | `multi_converter.fap` | A multi-unit converter written with an easy and expandable system for adding new units and conversion methods |
| `NFC/RFID Detector` | `nfc_rfid_detector.fap` | Identify the reader type: NFC (13 MHz) and/or RFID (125 KHz). |
| `Nightstand Clock` | `nightstand.fap` | Clock with screen brightness controls |
| `Password Generator` | `passgen.fap` | Simple password generator |
| `Programmer Calculator` | `programmercalc.fap` | Calculator, for Programmers! |
| `QR Code` | `qrcode.fap` | Display qrcodes |
| `Quac!` | `quac.fap` | Quick Action remote control app |
| `Resistance Calculator` | `resistors.fap` | Resistor calculations |
| `Tasks` | `tasks.fap` | A simple to-do application. |
| `Text Viewer` | `text_viewer.fap` | Text viewer application |
| `Tone Generator` | `tone_gen.fap` | A simple app to generate sound tones. |
| `Authenticator` | `totp.fap` | Software-based TOTP/HOTP authenticator for Flipper Zero device |
| `uPython` | `upython.fap` | Compile and execute MicroPython scripts |
| `Voltage Calculator` | `voltcalc_app.fap` | Voltage (VRI) calculations |

### USB（7 个）
| 应用 | 文件 | 功能 |
|---|---|---|
| `USB Remote` | `hid_usb.fap` | Use Flipper as a HID remote control over USB |
| `LEGO Dimensions Toy Pad` | `ldtoypad.fap` | USB Toy Pad emulator for Lego Dimensions |
| `Mass Storage` | `mass_storage.fap` | Implements a mass storage device over USB for disk images |
| `Portal Of Flipper` | `portal_of_flipper.fap` | USB emulator |
| `U2F` | `u2f.fap` | USB 分类扩展应用，随固件资源包安装到 SD 卡菜单。 |
| `USB Consumer Control` | `usb_ccb.fap` | USB Consumer Control |
| `USB Game Controller` | `xinput_controller.fap` | An app that emulates XInput controllers |

## 四、安装

固件版本号：`mntm-012cn-phantom`。安装产物在 `dist/f7-C/`。

> ⚠️ 安装前确保 SD 卡健康（FAT32、读写正常）。卡损坏 / 过慢会导致 `SD card IO error` 或校验超时。可在 设置 → 存储 → 格式化 SD 卡 重建文件系统。

### 方法 A：qFlipper（推荐）
1. 连接 Flipper，打开 qFlipper；
2. 「Install from file」选择
   `dist/f7-C/flipper-z-f7-update-mntm-012cn-phantom.tgz`；
3. 等待写入 + 校验 + 自动重启。

### 方法 B：SD 卡自更新（绕开 qFlipper 校验，适合慢卡）
1. 将 `dist/f7-C/f7-update-mntm-012cn-phantom/` 整个文件夹拷到 SD 卡 `/update/` 下；
2. Flipper 文件浏览器进入该目录 → 选 `update.fuf` → 确认安装。

> updater.bin 已控制在 128KB 以内，支持设备端自更新，不会引发更新器引导失败。

---

## 五、自定义

### 切换 / 关闭资源包
设置 → Momentum → 资源包（Asset Pack），可切换为其它包或留空（恢复默认外观与字体）。

### 调整 Bad Apple 帧率
编辑 SD 卡 `/ext/asset_packs/PhantomCN/Anims/BadApple/meta.txt` 中 `Frame rate`（默认 24，觉得卡可改 12~15），重启生效。

### 字库 / 动画工程文件
- 字库源：`assets/packs/PhantomCN/Fonts/`
- 动画源：`assets/packs/PhantomCN/Anims/BadApple/`

---

## 六、从源码编译

```bash
# Windows (PowerShell)
$env:DIST_SUFFIX = "mntm-012cn-phantom"
.\fbt.cmd updater_package "COPRO_DISCLAIMER=--I-understand-what-I-am-doing=yes"
```

---

## 七、许可与致谢

- 本固件基于 [Momentum Firmware](https://github.com/Next-Flip/Momentum-Firmware)（以及上游 Flipper Zero 官方固件）二次开发，遵循其开源许可（见 `LICENSE`）。
- 汉化、定制、资源整合：**Phantom**。
- 集成的第三方应用版权归各自作者所有。
