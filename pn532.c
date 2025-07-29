//
// Created by 张轩搏 on 2025/7/28.
//
#include "pn532.h"
result build_inlistpassivetarget_command() {
    // 用户数据区（TFI + Command + Params）
    uint8_t payload[] = {0xD4, 0x4A, 0x01, 0x00};
    int payload_len = sizeof(payload);
    return build_template(payload,payload_len);
}
result build_sam_configuration_command() {
    // 指令字段（包含 TFI）
    uint8_t payload[] = {0xD4,0x14,0x01};
    int payload_len = sizeof(payload);
    return build_template(payload,payload_len);
}
result build_authenticate_keyA(const uint8_t* uid,const uint8_t* keyA,uint8_t block){
    uint8_t payload[15]={0xD4,0x40,0x01,0x60};
    payload[4]=block;
    for(int i=0;i<6;i++){
        payload[5+i]=keyA[i];
    }
    for(int i=0;i<4;i++){
        payload[11+i]=uid[i];
    }
    return build_template(payload,15);
}
result build_authenticate_keyB(const uint8_t* uid,const uint8_t* keyB,uint8_t block){
    uint8_t payload[15]={0xD4,0x40,0x01,0x61};
    payload[4]=block;
    for(int i=0;i<6;i++){
        payload[5+i]=keyB[i];
    }
    for(int i=0;i<4;i++){
        payload[11+i]=uid[i];
    }
    return build_template(payload,15);
}
result build_read_card(uint8_t block){
    uint8_t payload[5] = {0xD4,0x40,0x01,0x30};
    payload[4] = block;
    return build_template(payload,5);
}
result build_template(uint8_t* payload,int payload_len) {
    result r;
    r.len = 7 + payload_len; // 00 FF LEN LCS ... DCS 00
    r.data = (uint8_t *)malloc(r.len);

    int i = 0;
    r.data[i++] = 0x00;                            // PREAMBLE
    r.data[i++] = 0x00;                            // PREAMBLE
    r.data[i++] = 0xFF;                            // START CODE
    r.data[i++] = payload_len;                     // LEN
    r.data[i++] = (uint8_t)(0x100 - payload_len);  // LCS

    uint8_t sum = 0;
    for (int j = 0; j < payload_len; j++) {
        r.data[i++] = payload[j];
        sum += payload[j];
    }

    r.data[i++] = (uint8_t)(0x100 - sum);  // DCS
    r.data[i++] = 0x00;                    // POSTAMBLE

    return r;
}
