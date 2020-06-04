# esp32-spi-slave

esp32 SPI slave in case you need to sniff what the master sends.
I'm trying to reverse enginner GxEPD epaper library to make my own object oriented [epaper driver component for ESP-IDF](https://github.com/martinberlin/cale-idf/wiki)

## The problem 

One epaper so far is working but others are not. Even though I'm sending exactly the same commands using ESP32 as SPI master comtroller.
Why not?
Because there is something different. Or because there is a missing command that without it the epaper wont boot up...
Thats why I though ok lets try to fimd a library to flash one ESP32 and let it work as a SPI slave. 

## The wiring

    Master    | Slave
    MOSI        MOSI
    CLK         CLK
    SS          SS Chip select
    DC          DC Data command
    
The epaper expects commands that are sent with both SS and DC low, hi on transfer termination. Data commands are sent turning only DC low (but not SS)

The part of the library that does that can be seen here:
https://github.com/ZinggJM/GxEPD/blob/master/src/GxIO/GxIO_SPI/GxIO_SPI.cpp#L114

### Credits

https://github.com/iPAS/esp32-slave-spi iPAS
[Espressif ESP32 documentation about SPI](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_slave.html)
