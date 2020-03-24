#include<stdio.h>
#include<stdlib.h>
#include<direct.h>
#include<io.h>

int countLines(char *fileName);
int countChars(char *fileName);
int countWords(char *fileName);
int recursion(char *fpara);
int justify(char *fileName);

int main(int argc, char *argv[]) {
    printf("���������%d\n", argc);
    char para;//����
    char fpara[] = "";
    char *func;//-����
    //�ж������������
    int k=0;
    for(k=1; k<=argc; k++) {
        func = argv[k];
        if(func[0] != '-') {
            break;
        }
    }
    printf("\nk: %d\n", k);
    char *add = argv[k];

    for(int j=k; j<argc; j++) {
        add = argv[j];
        for(int i=1; i<k; i++) {
            func = argv[i];
            para = func[1];

            switch(para) {
            case 's':
                printf("\n");
                recursion(add);
                break;
            case 'a':
                justify(add);
                break;
            case 'l':
                countLines(add);
                break;
            case 'w':
                countWords(add);
                break;
            case 'c':
                countChars(add);
                break;
            default:
                break;
            }
        }
    }
}

//��������
int countLines(char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    char ch;
    int cl = 0;

    if(fp == NULL) {
        printf("���ļ�ʧ�ܣ�\n");
    } else {
        ch = fgetc(fp);
        if(ch == EOF) {
            printf("������0\n");
            return 0;
        }
        while(ch != EOF) {
            if(ch != '\n') {
                ch = fgetc(fp);
            } else {
                cl++;
                ch = fgetc(fp);
            }
        }
        printf("������%d\n", ++cl);
    }

    fclose(fp);
    return cl;
}


//���㵥����
int countWords(char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    char ch;
    int cw = 0;
    int word = 0;

    if(fp == NULL) {
        printf("���ļ�ʧ�ܣ�\n");
    } else {
        //printf("���ļ��ɹ���\n");
        //printf("����Ϊ��");
        ch = fgetc(fp);
        if(ch == EOF) {
            printf("��������0\n");
            return 0;
        }
        while(ch != EOF) {
            /*if(ch != ' ' && ch != '\n') {
                //putchar(ch);
                ch = fgetc(fp);
            }else {
                cw++;
                //printf("��������%d\n", cw);
                ch = fgetc(fp);
            }*/
            if((ch == ' ' || ch == '\n') && word == 1) {
                word = 0;
                cw+=1;
            } else if(((ch >= 'a' && ch <= 'z') || ch >= 'A' && ch <='Z') && word == 0) {
                word = 1;
                if((ch = fgetc(fp)) == EOF)
                    cw++;
            }
            //printf("%c", ch);
            ch = fgetc(fp);
        }
        printf("��������%d\n", cw);
    }

    fclose(fp);
    return cw;
}

//��������
int countChars(char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    int cc = 0;
    char ch;

    if(fp != NULL) {
        ch = fgetc(fp);
        while(ch != EOF) {
            if(ch != '\n') {
                cc++;
                ch = fgetc(fp);
            } else {
                ch = fgetc(fp);
            }
        }
        printf("������%d\n", cc);
    } else {
        printf("���ļ�ʧ�ܣ�\n");
    }

    fclose(fp);
    return cc;
}

//�ݹ鴦���ļ�
int recursion(char *fpara) {
    long handle;//���ڲ��ҵľ��
    struct _finddata_t fileinfo;//�ļ���Ϣ�Ľṹ��
    handle = _findfirst(fpara, &fileinfo);
    if(-1 == handle) {
        printf("����ʧ�ܣ�");
        system("pause");
        return -1;
    }
    printf("%s\n", fileinfo.name);
    while(!_findnext(handle, &fileinfo)) {
        printf("%s\n", fileinfo.name);
    }
    _findclose(handle);
    return 0;
}

//������
int justify(char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    if(NULL == fp) {
        printf("���ļ�ʧ��!");
        system("pause");
        return 0;
    }
    int zs_f = 0;
    char ch_fp, ch_next;//ch_next����һ���ַ�
    int k=0, d=0, z=0, f=0;//k: ���� d�������� z��ע���� f���Ƿ񶥸�
    ch_fp = fgetc(fp);
    ch_next = fgetc(fp);
    while(ch_fp != EOF) {
        if(ch_fp == ' ' || ch_fp == '}' || ch_fp == '{') {
            ch_fp = ch_next;
            ch_next = fgetc(fp);
        } else {
            if((ch_fp == '\n') && f == 0) {
                k++;
            } else if(ch_fp == '/' && ch_next == '/' && f == 0) {
                z++;
            } else if(ch_fp == '/' && ch_next == '*' && f == 0) {
                z++;
                zs_f = 1;
            }
            if(zs_f == 1) {
                while(ch_fp != '*' || ch_next != '/') {
                    if(ch_fp == '\n') {
                        z++;
                    }
                    ch_fp = ch_next;
                    ch_next = fgetc(fp);
                }
                zs_f = 0;
            }

            ch_fp = ch_next;
            ch_next = fgetc(fp);
            if(ch_fp == '{' || ch_fp == '}') {
                ch_fp = ch_next;
                ch_next = fgetc(fp);
            }
            if(f == 0) {
                f = 1;
                if(ch_next == ' ') {
                    f = 0;
                }
            }
            if(f == 2) {
                if(ch_fp == '\n') {
                    k++;
                }
                f=0;
            }
            if(ch_fp == '\n') {
                f = 2;
                if(ch_next == '\n')
                    f=0;
                if(ch_next == EOF)
                    k++;
            }
        }
    }
    d = countLines(fileName) - k - z;
    printf("\n�ո��У�%d\n�����У�%d\nע���У�%d\n", k, d, z);

    printf("�ĵ�������\n");
    return 0;
}
