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
    printf("传入参数：%d\n", argc);
    char para;//需求
    char fpara[] = "";
    char *func;//-需求
    //判断输入多少需求
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

//计算行数
int countLines(char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    char ch;
    int cl = 0;

    if(fp == NULL) {
        printf("打开文件失败！\n");
    } else {
        ch = fgetc(fp);
        if(ch == EOF) {
            printf("行数：0\n");
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
        printf("行数：%d\n", ++cl);
    }

    fclose(fp);
    return cl;
}


//计算单词数
int countWords(char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    char ch;
    int cw = 0;
    int word = 0;

    if(fp == NULL) {
        printf("打开文件失败！\n");
    } else {
        //printf("打开文件成功！\n");
        //printf("单词为：");
        ch = fgetc(fp);
        if(ch == EOF) {
            printf("单词数：0\n");
            return 0;
        }
        while(ch != EOF) {
            /*if(ch != ' ' && ch != '\n') {
                //putchar(ch);
                ch = fgetc(fp);
            }else {
                cw++;
                //printf("单词数：%d\n", cw);
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
        printf("单词数：%d\n", cw);
    }

    fclose(fp);
    return cw;
}

//计算字数
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
        printf("字数：%d\n", cc);
    } else {
        printf("打开文件失败！\n");
    }

    fclose(fp);
    return cc;
}

//递归处理文件
int recursion(char *fpara) {
    long handle;//用于查找的句柄
    struct _finddata_t fileinfo;//文件信息的结构体
    handle = _findfirst(fpara, &fileinfo);
    if(-1 == handle) {
        printf("查找失败！");
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

//特殊行
int justify(char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    if(NULL == fp) {
        printf("打开文件失败!");
        system("pause");
        return 0;
    }
    int zs_f = 0;
    char ch_fp, ch_next;//ch_next：下一个字符
    int k=0, d=0, z=0, f=0;//k: 空行 d：代码行 z：注释行 f：是否顶格
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
    printf("\n空格行：%d\n代码行：%d\n注释行：%d\n", k, d, z);

    printf("文档结束！\n");
    return 0;
}
