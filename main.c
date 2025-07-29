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
    printf(GREEN);
    printf("1.生成pn532的唤醒命令\n");
    printf("2.生成pn532的被动读卡命令\n");
    int command = 0;
    int len = 0;
    printf("请输入命令：");
    scanf("%d",&command);
    switch(command){
        case 1:
            len =  build_sam_configuration_command().len;
            for(int i=0;i<len;i++){
                printf("%02X ",build_sam_configuration_command().data[i]);
            }
            break;
        case 2:
            len =  build_inlistpassivetarget_command().len;
            for(int i=0;i<len;i++){
                printf("%02X ",build_inlistpassivetarget_command().data[i]);
            }
            break;
    }
    return 0;
}