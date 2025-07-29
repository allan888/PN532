#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
#include <stdio.h>
#include "pn532.h"
int main(){
    printf("\033[38;2;57;197;187m");
    printf("欢迎来到自动生成pn532串口命令小工具\n");
    printf("\033[0m");
    while(1){
        printf(GREEN);
        printf("1.生成pn532的唤醒命令\n");
        printf("2.生成pn532的被动读卡命令\n");
        printf("3.生成pn532的块认证命令\n");
        printf("4.生成pn532的读卡命令\n");
        int command = 0;
        int len = 0;
        uint8_t block = 0;
        printf("请输入命令：");
        scanf("%d",&command);
        switch(command){
            case 1:
                len =  build_sam_configuration_command().len;
                printf(BLUE);
                for(int i=0;i<len;i++){
                    if(i!=(len - 1)) printf("%02X ",build_sam_configuration_command().data[i]);
                    else printf("%02X\n",build_sam_configuration_command().data[i]);
                }
                printf(RESET);
                break;
            case 2:
                printf(BLUE);
                len =  build_inlistpassivetarget_command().len;
                for(int i=0;i<len;i++){
                    if(i!=(len-1)) printf("%02X ",build_inlistpassivetarget_command().data[i]);
                    else printf("%02X\n",build_inlistpassivetarget_command().data[i]);
                }
                printf(RESET);
                break;
            case 3:
                const uint8_t uid[4];
                const uint8_t keyA[6];
                const uint8_t keyB[6];
                printf("请输入UID：");
                scanf("%hhX %hhx %hhx %hhx",&uid[0],&uid[1],&uid[2],&uid[3]);
                printf("请输入keyA：");
                scanf("%hhX %hhx %hhx %hhx %hhx %hhx",&keyA[0],&keyA[1],&keyA[2],&keyA[3],&keyA[4],&keyA[5]);
                printf("请输入keyB：");
                scanf("%hhX %hhx %hhx %hhx %hhx %hhx",&keyB[0],&keyB[1],&keyB[2],&keyB[3],&keyB[4],&keyB[5]);
                printf("请输入block：");
                scanf("%hhx",&block);
                printf(BLUE);
                len = build_authenticate_keyA(uid,keyA,block).len;
                for(int i=0;i<len;i++){
                    if(i!=(len-1)) printf("%02X ",build_authenticate_keyA(uid,keyA,block).data[i]);
                    else printf("%02X\n",build_authenticate_keyA(uid,keyA,block).data[i]);
                }
                len = build_authenticate_keyB(uid,keyB,0x00).len;
                for(int i=0;i<len;i++){
                    if(i!=(len-1)) printf("%02X ",build_authenticate_keyB(uid,keyB,block).data[i]);
                    else printf("%02X\n",build_authenticate_keyB(uid,keyB,block).data[i]);
                }
                printf(RESET);
                break;
            case 4:
                printf("请输入block：");
                scanf("%hhx",&block);
                len = build_read_card(block).len;
                printf(BLUE);
                for(int i=0;i<len;i++){
                    if(i!=(len-1)) printf("%02X ",build_read_card(block).data[i]);
                    else printf("%02X\n",build_read_card(block).data[i]);
                }
                printf(RESET);
                break;
        }
    }
    return 0;
}