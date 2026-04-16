# ASDO Firmware

Repository to house the code for the raspberry pi pico to replace the Ott Data Logger for the Parsivel Present Weather Sensor.

## Build Instructions

```sh
cmake -B build
make -C build
```

## Flash to Pico

```sh
picotool load build/<target>.uf2 -f
```
