/**
 * SlaveSPI Class
 * - adopt from gist:shaielc/SlaveSPIClass.cpp at https://gist.github.com/shaielc/e0937d68978b03b2544474b641328145
 * - Forked by Fasani.de
 */
#include "SlaveSPI.h"
#include <SPI.h>

#define SO   (gpio_num_t)19
#define SI   (gpio_num_t)23
#define SCLK (gpio_num_t)18
#define SS   (gpio_num_t)32 /** DATA puts DC only to 0 */
#define DC   (gpio_num_t)27 /** CMD puts DC & SS to 0 before transmission, 1 afterwards */

SPISettings spi_setting(2000000, MSBFIRST, SPI_MODE);

SlaveSPI slave(HSPI_HOST);  // VSPI_HOST

// ----------------------------------------------------------------------------
#include "SimpleArray.h"
typedef SimpleArray<uint8_t, int> array_t;

array_t slave_msg(SPI_DEFAULT_MAX_BUFFER_SIZE);

void setup() {
    Serial.begin(115200);
    Serial.println("SPI SNIFFER");
    pinMode(SS, INPUT_PULLUP);
    pinMode(DC, INPUT_PULLUP);
    // Setup Slave-SPI
    // slave.begin(SO, SI, SCLK, SS, 8, callback_after_slave_tx_finish);  // seems to work with groups of 4 bytes
    // slave.begin(SO, SI, SCLK, SS, 4, callback_after_slave_tx_finish);
    slave.begin(SO, SI, SCLK, SS, 1);
    // slave.begin(SO, SI, SCLK, SS, 1, callback_after_slave_tx_finish);  // at least 2 word in an SPI frame
}

/******************************************************************************
 * Loop 
 */

void loop() {
    uint8_t ilen = slave.getInputStream()->length();
    uint8_t rSS = digitalRead(SS);
    uint8_t rDC = digitalRead(DC);
    if (ilen && rSS == 0) {  // Slave SPI has got CMD
        
        uint8_t *buff = new uint8_t[ilen];
        slave.readToBytes(buff,ilen);

        String type = "D";
        if (rDC == 1) {
            type = "C";
        }
        for (int i=0;i<=ilen;++i) {
        Serial.printf("%s %x ", type, buff[i]);
        }
    
    }

}
