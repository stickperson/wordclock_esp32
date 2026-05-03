# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Flash

This project uses [PlatformIO](https://platformio.org/) via the VSCode extension. Use the PlatformIO toolbar in VSCode to build, upload, and open the serial monitor (9600 baud).

Firmware output: `.pio/build/esp32doit-devkit-v1/firmware.bin`

## Architecture

An ESP32-based word clock. The main loop runs a web server and ticks the clock every iteration.

**`src/main.cpp`** — entry point. Wires together WiFiManager (captive portal for WiFi setup), NTPClient, `WordClock`, `EnglishLayout`, `FastLedDisplay`, and `ClockServer`.

**`lib/WordClock`** — orchestrator. Owns the NTP sync loop (every minute), calls `layout->setTime()`, checks birthdays, and handles physical button input (brightness + color buttons via OneButton).

**`lib/Layout`** — `AbstractLayout` base; `EnglishLayout` concrete implementation. Maps hours/minutes to `Word` structs (LED index ranges). The grid has 130 LEDs. LED indices follow the physical strip wiring; words are defined as `Word{startIndex, endIndex}` macros in `EnglishLayout.h`.

**`lib/Displays`** — `AbstractDisplay` base; `FastLedDisplay<NUM_LEDS>` template (header-only, APA102 strip on pins 26/27). Handles brightness (persisted in NVS under namespace `"display"`, key `"brightness"`), color, and a 3-flash orange boot indicator on LED 12.

**`lib/Birthday`** — static class storing up to 20 `{month, day, year}` entries in NVS (namespace `"birthdays"`). Month is stored 0-indexed internally; year is stored only for UI round-tripping. `isBirthday()` ignores year.

**`lib/ClockServer`** — subclasses `WebServer`. Serves the setup UI and handles API endpoints. Persists timezone in NVS (namespace `"clock"`, key `"tz"`) and restores it on `begin()`.

**`lib/Templates/Templates.h`** — the entire setup UI as a single PROGMEM string (`rootContent`). Vanilla JS, no framework. The wizard has 3 steps: timezone, birthdays, firmware OTA.

## API Endpoints

| Method | Path | Description |
|--------|------|-------------|
| GET | `/` | Setup UI |
| POST | `/setDate` | Set timezone + unix time |
| GET | `/getBirthdays` | Returns stored birthdays as JSON |
| POST | `/setBirthday` | Add a birthday `{month, day, year}` (month 1-indexed) |
| POST | `/clearBirthdays` | Clear all birthdays |
| POST | `/update` | OTA firmware upload |

## NVS Layout

| Namespace | Key | Type | Content |
|-----------|-----|------|---------|
| `display` | `brightness` | `uint8_t` | Current brightness (max 64) |
| `birthdays` | `data` | blob | `BirthdayStore` struct |
| `clock` | `tz` | string | POSIX timezone string |

## Adding a New Layout or Display

- Subclass `AbstractLayout` or `AbstractDisplay`
- Swap the concrete type in `src/main.cpp`
