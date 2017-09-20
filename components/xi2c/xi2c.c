#include "xi2c.h"


static esp_err_t XI2CWrite(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t* data_wr, size_t size);
static esp_err_t XI2CRead(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t* data_rd, size_t size);

static esp_err_t XI2CWrite(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t* data_wr, size_t size) {

  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, ( i2c_add << 1 ), ACK_CHECK_DIS);
  i2c_master_write(cmd, data_wr, size, ACK_CHECK_DIS);
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  return ret;
}

static esp_err_t XI2CRead(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t* data_rd, size_t size) {
  if (size == 0) {
      return ESP_OK;
  }
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, ( i2c_add << 1 ), ACK_CHECK_DIS);
  if (size > 1) {
      i2c_master_read(cmd, data_rd, size, ACK_VAL);
  }
  i2c_master_read_byte(cmd, data_rd + size, ACK_VAL);
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  return ret;
}

esp_err_t X_WriteMulti(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint32_t count, uint8_t* data_wr) {
  if (count > sizeof(XI2CBuffer) - 1) {
      return ESP_FAIL;
  }
  XI2CBuffer[0] = index;
  memcpy(&XI2CBuffer[1], data_wr, count);
  esp_err_t ret = XI2CWrite(i2c_num, i2c_add, XI2CBuffer, count+1);
  return ret;
}

esp_err_t X_ReadMulti(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint32_t count, uint8_t* data_rd) {
    esp_err_t ret;

    ret = XI2CWrite(i2c_num, i2c_add, &index, 0x1);
    if (ret == ESP_FAIL) {
      return ret;
    }

    ret = XI2CRead(i2c_num, i2c_add, data_rd, count);
    return ret;
}

esp_err_t X_WrByte(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint8_t data_wr) {

    XI2CBuffer[0] = index;
    XI2CBuffer[1] = data_wr;
    esp_err_t ret = XI2CWrite(i2c_num, i2c_add, XI2CBuffer, 0x2);
    return ret;

}

esp_err_t X_RdByte(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint8_t *data_rd) {

    esp_err_t ret;

    ret = XI2CWrite(i2c_num, i2c_add, &index, 0x1);
    if (ret == ESP_FAIL) {
      return ret;
    }

    ret = XI2CRead(i2c_num, i2c_add, data_rd, 0x1);
    return ret;
}

esp_err_t X_WrBit(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint8_t bitNum, uint8_t data_wr) {

   uint8_t b;
   esp_err_t ret;
   ret = X_RdByte(i2c_num, i2c_add, index, &b);
   if (ret == ESP_FAIL) {
       return ret;
   }
   b = (data_wr != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
   ret = X_WrByte(i2c_num, i2c_add, index, b);
   return ret;

}

esp_err_t X_WrBits(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint8_t bitStart, uint8_t length, uint8_t data_wr) {

   uint8_t b;
 	 // 010 value to write
 	 // 76543210 bit numbers
 	 // args: bitStart=4, length=3
 	 // 00011100 mask byte
 	 // 10101111 original value (sample)
 	 // 10100011 original & ~mask
 	 // 10101011 masked | value
   esp_err_t ret;
   ret = X_RdByte(i2c_num, i2c_add, index, &b);
   if (ret == ESP_FAIL) {
       return ret;
   }
   uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
   data_wr <<= (bitStart - length + 1); // shift data into correct position
   data_wr &= mask; // zero all non-important bits in data
   b &= ~(mask); // zero all important bits in existing byte
   b |= data_wr; // combine data with existing byte
   ret = X_WrByte(i2c_num, i2c_add, index, b);
   return ret;

}

esp_err_t X_WrWord(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint8_t data_wr) {

    XI2CBuffer[0] = index;
    XI2CBuffer[1] = data_wr >> 8;
    XI2CBuffer[2] = data_wr & 0x00FF;
    esp_err_t ret = XI2CWrite(i2c_num, i2c_add, XI2CBuffer, 0x3);
    return ret;

}

esp_err_t X_WrDWord(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint8_t data_wr) {

    XI2CBuffer[0] = index;
    XI2CBuffer[1] = (data_wr >> 24) & 0xFF;
    XI2CBuffer[2] = (data_wr >> 16) & 0xFF;
    XI2CBuffer[3] = (data_wr >> 8)  & 0xFF;
    XI2CBuffer[4] = (data_wr >> 0 ) & 0xFF;
    esp_err_t ret = XI2CWrite(i2c_num, i2c_add, XI2CBuffer, 0x5);
    return ret;

}

/*X_Error X_UpdateByte(SensorsData Dev, uint8_t index, uint8_t AndData, uint8_t OrData) {
    X_Error Status = X_ERROR_NONE;
    uint8_t data;

    Status = X_RdByte(Dev, index, &data);
    if (Status == 0) {
        goto done;
    }
    data = (data & AndData) | OrData;
    Status = X_WrByte(Dev, index, data);
done:
    return Status;
}*/

esp_err_t X_RdBit(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint8_t bitNum, uint8_t *data_rd) {

   uint8_t b;
   esp_err_t ret;
   ret = X_RdByte(i2c_num, i2c_add, index, &b);
   if (ret == ESP_FAIL) {
       return ret;
   }
   *data_rd = b & (1 << bitNum);
   return ret;

}

esp_err_t X_RdBits(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint8_t bitStart, uint8_t length, uint8_t *data_rd) {

   uint8_t b;
   esp_err_t ret;
   ret = X_RdByte(i2c_num, i2c_add, index, &b);
   if (ret == ESP_FAIL) {
       return ret;
   }
   uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
 	 b &= mask;
 	 b >>= (bitStart - length + 1);
 	 *data_rd = b;
   return ret;

}

esp_err_t X_RdWord(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint16_t *data_rd) {

  esp_err_t ret;

  ret = XI2CWrite(i2c_num, i2c_add, &index, 0x1);
  if (ret == ESP_FAIL) {
    return ret;
  }

  ret = XI2CRead(i2c_num, i2c_add, XI2CBuffer, 0x2);

  *data_rd = ((uint16_t)XI2CBuffer[0]<<8) + (uint16_t)XI2CBuffer[1];
  return ret;

}

esp_err_t X_RdDWord(i2c_port_t i2c_num, uint8_t i2c_add, uint8_t index, uint32_t *data_rd) {

  esp_err_t ret;

  ret = XI2CWrite(i2c_num, i2c_add, &index, 0x1);
  if (ret == ESP_FAIL) {
    return ret;
  }

  ret = XI2CRead(i2c_num, i2c_add, XI2CBuffer, 0x4);

  *data_rd = ((uint32_t)XI2CBuffer[0]<<24) + ((uint32_t)XI2CBuffer[1]<<16) + ((uint32_t)XI2CBuffer[2]<<8) + (uint32_t)XI2CBuffer[3];
  return ret;

}

esp_err_t X_PollingDelay(void) {

  esp_err_t ret;
  X_OsDelay();
  ret = ESP_OK;
  return ret;

}
