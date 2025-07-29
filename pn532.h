//
// Created by 张轩搏 on 2025/7/28.
//

#ifndef PN532_PN532_H
#define PN532_PN532_H
#include <stdint.h>
#include <malloc.h>
typedef struct {
    uint8_t *data;  // 指令数据（含标头）
    int len;        // 字节长度
} result;
result build_inlistpassivetarget_command();
result build_sam_configuration_command();
result build_template(uint8_t* payload,int payload_len);
result build_authenticate_keyA(const uint8_t* uid,const uint8_t* keyA,uint8_t block);
result build_authenticate_keyB(const uint8_t* uid,const uint8_t* keyB,uint8_t block);
result build_read_card(uint8_t block);
#endif //PN532_PN532_H
