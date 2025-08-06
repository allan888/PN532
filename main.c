#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
#include <stdio.h>
#include "pn532.h"
#include <windows.h>
int CopyIntoClipboard(result r);
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
        result r;
        printf("请输入命令：");
        scanf("%d",&command);
        switch(command){
            case 1:
                r = build_sam_configuration_command();
                len =  r.len;
                printf(BLUE);
                for(int i=0;i<len;i++){
                    if(i!=(len - 1)) printf("%02X ",r.data[i]);
                    else printf("%02X\n",r.data[i]);
                }
                printf(RESET);
                CopyIntoClipboard(r);
                break;
            case 2:
                printf(BLUE);
                r = build_inlistpassivetarget_command();
                len =  r.len;
                for(int i=0;i<len;i++){
                    if(i!=(len-1)) printf("%02X ",r.data[i]);
                    else printf("%02X\n",r.data[i]);
                }
                printf(RESET);
                CopyIntoClipboard(r);
                break;
            case 3:
                const uint8_t uid[4];
                const uint8_t keyA[6];
                const uint8_t keyB[6];
                printf("请输入UID：");
                scanf("%hhX %hhx %hhx %hhx",&uid[0],&uid[1],&uid[2],&uid[3]);
                printf("请输入keyA：");
                scanf("%hhX %hhx %hhx %hhx %hhx %hhx",&keyA[0],&keyA[1],&keyA[2],&keyA[3],&keyA[4],&keyA[5]);
                printf("请输入block：");
                scanf("%hhx",&block);
                r = build_authenticate_keyA(uid,keyA,block);
                printf(BLUE);
                len = r.len;
                for(int i=0;i<len;i++){
                    if(i!=(len-1)) printf("%02X ",r.data[i]);
                    else printf("%02X\n",r.data[i]);
                }
                CopyIntoClipboard(r);
                printf("请输入keyB：");
                scanf("%hhX %hhx %hhx %hhx %hhx %hhx",&keyB[0],&keyB[1],&keyB[2],&keyB[3],&keyB[4],&keyB[5]);
                r = build_authenticate_keyB(uid,keyB,block);
                len = r.len;
                for(int i=0;i<len;i++){
                    if(i!=(len-1)) printf("%02X ",r.data[i]);
                    else printf("%02X\n",r.data[i]);
                }
                printf(RESET);
                CopyIntoClipboard(r);
                break;
            case 4:
                printf("请输入block：");
                scanf("%hhx",&block);
                r = build_read_card(block);
                len = r.len;
                printf(BLUE);
                for(int i=0;i<len;i++){
                    if(i!=(len-1)) printf("%02X ",r.data[i]);
                    else printf("%02X\n",r.data[i]);
                }
                printf(RESET);
                CopyIntoClipboard(r);
                break;
        }
    }
    return 0;
}
int CopyIntoClipboard(result r){
    int len = r.len;
    char temp[8];
    char final[512] = {0};  // 最终字符串缓冲区

    for(int i = 0; i < len; i++){
        if(i != (len - 1))
            sprintf(temp, "%02X ", r.data[i]);
        else
            sprintf(temp, "%02X\n", r.data[i]);

        strcat(final, temp);  // 累加内容
    }

    size_t length = strlen(final) + 1;

    if(!OpenClipboard(NULL)){
        printf(RED "未打开剪贴板\n" RESET);
        return -1;
    }

    EmptyClipboard();

    HGLOBAL hem = GlobalAlloc(GMEM_MOVEABLE, length);
    if(!hem){
        CloseClipboard();
        printf(RED "未能分配全局内存\n" RESET);
        return -1;
    }

    memcpy(GlobalLock(hem), final, length);
    GlobalUnlock(hem);
    SetClipboardData(CF_TEXT, hem);
    CloseClipboard();

    printf("成功写入剪贴板：%s", final);
    return 0;
}