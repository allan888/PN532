#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
#include <stdio.h>
#include "pn532.h"
int main(){
    printf("\033[38;2;57;197;187m");
    printf("��ӭ�����Զ�����pn532��������С����\n");
    printf("\033[0m");
    printf(GREEN);
    printf("1.����pn532�Ļ�������\n");
    printf("2.����pn532�ı�����������\n");
    int command = 0;
    int len = 0;
    printf("���������");
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