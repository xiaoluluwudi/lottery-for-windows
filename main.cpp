#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

#define s_c sizeof(char)
#define n_name 21
#define max_n 101
#define id_len 21
#define n_illegal 10

FILE* inf_itdc;
FILE* inf_hstr;
FILE* inf_prz;
FILE* inf_user;
FILE* inf_IDs;
FILE* inf_set;

int num = 0;
char answer[3]{};

const char id_sign[2] = "@";
const char name_sign[2] = "&";
const char prz_n_s[2] = "[";
const char prz_n_e[2] = "]";
const char prz_name[2] = "(";
const char prz_m_s[2] = "{";
const char prz_m_e[2] = "}";
const char inf_s[2] = ")";
const char illegal_word[n_illegal] = "&({}[]\\/#";
const char line[6]="=====";
const char path[10] = "user_inf/";

void Instructions();
void MainPage();
void Back_Stage();
void Lottery();
void Lottery_set();
void Lottery_set_s();
void Lottery_set_m();
void Single();
void Multi();
void Info();
void Info_set();
void Info_User();
void Info_IDs();
void Info_introduce();
void Info_prize();
void Info_prz_s();
void Info_prz_m();
void Info_history();
void User_set();
void User_add();
void User_delete();
void User_info_c();
void History_set();
void About_Us();
void Show_set();
void Sroll();
void Record_Time(FILE *file);
void F_Add(const char *f,string b,string &t);
void Get_ID(char *str, int line, FILE *file);
void Get_name(char *str, int line, FILE *file);
void clrscr();
void hitback();
void Blank(FILE* file);
int Delete_ID(string ID);
int Existe_ID(string ID);
int Illegal_word(char word);
int Used_Line(int id, int m, int line_list[]);
int Input(string &input, int min_s, int max_s);
int Input_B(string &input, int min_s, int max_s);
int Input_N(char* input);

int main()
{
    MainPage();
    return 0;
}

void Instructions()
{
    clrscr();
    cout << line <<"欢迎来到抽奖系统" << line << endl;
    cout << "1.开始抽奖" << endl;
    cout << "2.后台管理" << endl;
    cout << "3.信息查看" << endl;
    cout << "4.退出" << endl;
}

void MainPage()
{
    while(1){
        Instructions();
        num = Input_N(answer);
        switch(num){
            case 1: Lottery(); break;
            case 2: Back_Stage(); break;
            case 3: Info(); break;
            case 4: exit(0); break;
            default : num = 0; break;
        }
    }
}

void Back_Stage()
{
    while(1){
        clrscr();
        cout << line <<"欢迎来到后台" << line << endl;
        cout << "1.设置信息简介" << endl;
        cout << "2.设置奖项" << endl;
        cout << "3.删除抽奖历史信息" << endl;
        cout << "4.用户管理" << endl;
        cout << "5.显示设置" << endl;
        cout << "6.返回" << endl;
        num = Input_N(answer);
        switch(num){
            case 1: Info_set(); break;
            case 2: Lottery_set(); break;
            case 3: History_set(); break;
            case 4: User_set(); break;
            case 5: Show_set(); break;
            case 6: return;
            default: num = 0; break;
        }
    }
}

void Info_set()
{
    clrscr();
    if((inf_itdc = fopen("sys_inf/inf_itdc.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        hitback();
        return;
    }
    string inf;
    cout << line << "设置信息简介" << line << endl;
    cout << "编辑抽奖信息简介：" << endl;
    if(Input_B(inf,1,max_n)==0){
        fclose(inf_itdc); return;
    }
    fwrite(inf.data(),s_c,inf.length(),inf_itdc);
    fclose(inf_itdc);
    cout << "设置成功！" << endl;
    hitback();
}

void History_set()
{
    clrscr();
    if((inf_hstr = fopen("sys_inf/inf_hstr.txt","r")) == NULL){
        cout << "暂无抽奖历史记录" << endl;
        hitback();
        return;
    }
    fclose(inf_hstr);
    cout << "清除抽奖历史信息？" << endl;
    cout << "1.确认" << endl << "2.返回" << endl;

    while(1){
        num = Input_N(answer);
        if(num == 1) {
            if((remove("sys_inf/inf_hstr.txt"))==0)
                cout << "删除成功！" <<endl;
            else cout << "删除失败！" << endl;
            hitback();
            return;
        }
        else if(num == 2) return;
    }
}

void Lottery_set()
{
      while(1){
        clrscr();
        cout << line <<"奖品设置" << line << endl;
        cout << "1.设置单组抽奖奖品" << endl;
        cout << "2.设置多组抽奖奖品" << endl;
        cout << "3.返回" << endl;

        num = Input_N(answer);
        switch(num){
            case 1: Lottery_set_s(); break;
            case 2: Lottery_set_m(); break;
            case 3: return;
            default: num = 0; break;
        }
    }
}

void Lottery_set_s()
{
    clrscr();
    if((inf_prz = fopen("sys_inf/inf_prz.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        hitback();
        return;
    }
    string name;
    string inf;
    char N[3];
    int num_t = 0;
    int num_p = 0;
    int i = 0;

    cout << line << "设置单组抽奖奖项" << line << endl;

    while(num_t<=0||num_t>9){
        cout << "奖品种类数(1-9)：";
        num_t = Input_N(answer);
    }
    itoa(num_t,N,10);
    fwrite(N,s_c,strlen(N),inf_prz);
    Blank(inf_prz);

    for(i=0;i<num_t;i++){
        cout << i+1 << "号奖品："<< endl;
        cout << "名称：" ;
        if(Input_B(name,1,n_name) == 0) {
                fclose(inf_prz); return;
        }
        num_p = 0;
        while(num_p <=0||num_p>9){
            cout << "数量(1-9)：" ;
            num_p = Input_N(answer);
        }

        cout << "奖品详情：" ;
        if(Input_B(inf,1,max_n) == 0) {
            fclose(inf_prz); return;
        }
        itoa(num_p,N,10);
        fwrite(prz_n_s,s_c,1,inf_prz);
        fwrite(N,s_c,strlen(N),inf_prz);
        Blank(inf_prz);
        fwrite(prz_name,s_c,1,inf_prz);
        fwrite(name.data(),s_c,name.length(),inf_prz);
        Blank(inf_prz);
        fwrite(inf.data(),s_c,inf.length(),inf_prz);
        Blank(inf_prz);
        fwrite(prz_n_e,s_c,1,inf_prz);
    }
    fclose(inf_prz);
    cout << "设置成功！" << endl;
    hitback();
}

void Lottery_set_m()
{
    clrscr();
    if((inf_prz = fopen("sys_inf/inf_prz_m.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        hitback();
        return;
    }
    string name;
    char N[3]{};
    string inf;
    int num_n = 0;
    int num_t = 0;
    int num_p = 0;
    int i = 0;
    int j = 0;

    cout << line << "设置多组抽奖奖项" << line << endl;

    while(num_n<=0||num_n>=9){
        cout << "奖品组数(1-9)：" ;
        num_n = Input_N(answer);
    }
    itoa(num_n,N,10);
    fwrite(N,s_c,strlen(N),inf_prz);

    for(i=0;i<num_n;i++){
        cout <<line<< "第" << i+1 <<"组奖品"<< endl;
        num_t = 0;
        while(num_t<=0||num_t>9){
            cout << "奖品种类数(1-9)：";
            num_t = Input_N(answer);
        }
        Blank(inf_prz);
        fwrite(prz_m_s,s_c,1,inf_prz);
        itoa(num_t,N,10);
        fwrite(N,s_c,strlen(N),inf_prz);
        Blank(inf_prz);

        for(j=0;j<num_t;j++){
            cout << j+1 << "号奖品："<< endl;
            cout << "名称：" ;
            if(Input_B(name,1,n_name) == 0){
                fclose(inf_prz); return;
            }
            num_p = 0;
            while(num_p <=0||num_p>9){
                cout << "数量(1-9)：" ;
                num_p = Input_N(answer);
            }
            cout << "奖品详情：" ;
            if(Input_B(inf,1,max_n) == 0) {
                fclose(inf_prz); return;
            }
            itoa(num_p,N,10);
            fwrite(prz_n_s,s_c,1,inf_prz);
            fwrite(N,s_c,strlen(N),inf_prz);
            Blank(inf_prz);
            fwrite(prz_name,s_c,1,inf_prz);
            fwrite(name.data(),s_c,name.length(),inf_prz);
            Blank(inf_prz);
            fwrite(inf.data(),s_c,name.length(),inf_prz);
            Blank(inf_prz);
            fwrite(prz_n_e,s_c,1,inf_prz);
        }
        fwrite(prz_m_e,s_c,1,inf_prz);
    }
    fclose(inf_prz);
    cout << "设置成功！" << endl;
    hitback();
}

void Info()
{
    while(1){
        clrscr();
        cout << line << "信息查看" << line << endl;
        cout << "1.抽奖简介" << endl;
        cout << "2.奖品信息" << endl;
        cout << "3.历史抽奖信息" << endl;
        cout << "4.用户信息" << endl;
        cout << "5.用户列表" << endl;
        cout << "6.关于" << endl;
        cout << "7.返回" << endl;
        num = Input_N(answer);
        switch(num){
            case 1: Info_introduce(); break;
            case 2: Info_prize(); break;
            case 3: Info_history(); break;
            case 4: Info_User(); break;
            case 5: Info_IDs(); break;
            case 6: About_Us(); break;
            case 7: return;
            default: num = 0;break;
        }
    }
}

void Info_introduce()
{
    clrscr();
    if((inf_itdc = fopen("sys_inf/inf_itdc.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        hitback();
        return;
    }
    char word = '0';
    cout << line << "抽奖简介" << line <<endl;
    while(word!=EOF){
        word = fgetc(inf_itdc);
        cout << word;
    }
    cout << endl;
    fclose(inf_itdc);
    hitback();
}

void Info_prize()
{
    while(1){
        clrscr();
        cout << line <<"奖品信息查看" << line << endl;
        cout << "1.查看单组抽奖奖品信息" << endl;
        cout << "2.查看多组抽奖奖品信息" << endl;
        cout << "3.返回" << endl;
        num = Input_N(answer);
        switch(num){
            case 1: Info_prz_s(); break;
            case 2: Info_prz_m(); break;
            case 3: return;
            default: num = 0; break;
        }
    }
}

void Info_prz_s()
{
    clrscr();
    if((inf_prz = fopen("sys_inf/inf_prz.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        hitback();
        return;
    }
    char word = fgetc(inf_prz);
    int n_t = word - '0';
    int i = 0;

    cout << line << "奖品信息" << line << endl;
    for(i=0;i<n_t;i++){
        while(word!=prz_n_s[0]) word = fgetc(inf_prz);
        cout <<line<<"奖品"<<i+1<<endl;
        cout << "数量：" ;
        while(word!='\n') {
            word = fgetc(inf_prz);
            cout << word;
        }
        word = fgetc(inf_prz);
        cout << "名称: ";
        while((word = fgetc(inf_prz))!='\n')
            cout << word;
        word = '0';
        cout << endl <<"奖品信息：";
        while(word!='\n') {
            word = fgetc(inf_prz);
            if(word==prz_n_e[0]) break;
            cout << word;
        }
    }
    fclose(inf_prz);
    hitback();
}

void Info_prz_m()
{
    clrscr();
    if((inf_prz = fopen("sys_inf/inf_prz_m.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        hitback();
        return;
    }
    char word = fgetc(inf_prz);
    int n_t = word - '0';
    int n_p = 0;
    int i = 0;
    int j = 0;

    cout << line << "奖品信息" << line << endl;
    cout << "奖品组数：" << n_t << endl;
    for(i=0;i<n_t;i++){
        cout << line << "第" << i+1 << "组奖品："<< endl;
        cout << "奖品种类数：" ;
        while(word!=prz_m_s[0]) word = fgetc(inf_prz);
        for(j=0;word!='\n';j++) {
            word = fgetc(inf_prz);
            answer[j] = word;
            cout << word;
        }
        n_p = atoi(answer);
        for(j=0;j<n_p;j++){
            while(word!=prz_n_s[0]) word = fgetc(inf_prz);
            cout <<"奖品"<<j+1<<endl;
            cout << "数量：" ;
            while(word!='\n') {
                word = fgetc(inf_prz);
                cout << word;
            }
            word = fgetc(inf_prz);
            cout << "名称: ";
            while((word = fgetc(inf_prz))!='\n')
                cout << word;
            word = '0';
            cout << endl <<"奖品信息：";
            while(word!='\n') {
                word = fgetc(inf_prz);
                if(word==prz_n_e[0]) break;
                cout << word;
            }
        }
    }
    hitback();
    fclose(inf_prz);
}

void Info_history()
{
    clrscr();
    if((inf_hstr = fopen("sys_inf/inf_hstr.txt","r")) == NULL){
        cout << "暂无历史抽奖信息" << endl;
        hitback();
        return;
    }
    char word = '0';
    int counter = 0;
    while(word!=EOF){
        word = fgetc(inf_hstr);
        if(word == '\n') counter++;
        cout << word;
        if(counter >=20){
            cout << endl <<"a键下一页,";
            cout <<"其他键返回"<<endl;
            cin>>word;
            if(word == 'a') {
                counter = 0;
                clrscr();
            } else {
                fclose(inf_hstr); return;
            }
        }
    }
    hitback();
    fclose(inf_hstr);
}

void Info_User()
{
    clrscr();
    char word = '0';
    string id;

    cout << line << "用户信息" << endl;
    cout << "输入想要查看的用户学号: ";
    if(Input(id,0,id_len) == 0) return;
    string ID;
    F_Add(path,id,ID);
    if((inf_user = fopen(ID.data(),"r"))==NULL){
        cout << "不存在用户: " << id << endl;
        hitback();
        return;
    }
    if((inf_IDs = fopen("sys_inf/inf_IDs.txt","r"))==NULL){
        cout << "读取用户信息失败！" << endl;
        fclose(inf_user);
        hitback();
        return;
    }
    cout << "姓名：" ;
    int i = 0;
    int j = 0;
    int out = 0;
    int recorder = 0;
    int l = id.length();
    string line;
    while(!out){
        recorder = 0;
        for(i=0;i<id_len;i++) line[i] = '\0';
        for(word='a';word!=id_sign[0];word=fgetc(inf_IDs));
        for(i=0;(word = fgetc(inf_IDs))!=name_sign[0];i++)
            line[i] = word;
        if(l == i){
            for(j=0;j<i;j++){
                if(line[j]==id[j]) recorder++;
            }
            if(recorder == i) {
                while((word = fgetc(inf_IDs))!='\n') cout << word;
                out = 1;
            }
        }
        while((word=fgetc(inf_IDs))!='\n'&&word!=EOF);
    }

    word = '0';
    cout << endl<<"年龄：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = '0';
    cout << "性别：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = '0';
    cout << "年级：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = '0';
    cout << "专业：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = '0';
    cout << "简介：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    cout << endl;
    fclose(inf_user);
    fclose(inf_IDs);
    hitback();
}

void Info_IDs()
{
    clrscr();
    if((inf_IDs=fopen("sys_inf/inf_IDs.txt","r"))==NULL){
        cout << "读取用户信息失败！" << endl;
        hitback();
        return;
    }
    char word = 'a';
    int n_id = 0;

    for(word=fgetc(inf_IDs);word!=EOF;word=fgetc(inf_IDs)){
        if(word==id_sign[0]) n_id++;
    }
    fseek(inf_IDs,0,SEEK_SET);
    word = 'a';
    while(word!=EOF){
        word = fgetc(inf_IDs);
        if(word==id_sign[0]) {
            cout << "ID(学号):"; continue;}
        else if(word==name_sign[0]) {
            cout <<" 姓名:"; continue;}
        cout << word;
    }
    cout << endl;
    hitback();
}

void About_Us()
{
    clrscr();
    FILE *about ;
    char word = '0';
    if((about = fopen("sys_inf/inf_about.txt","r"))==NULL){
        cout << "读取信息失败！" << endl;
        hitback();
        return;
    }
    cout << line << line << "关于" << line << line << endl;
    while(word!=EOF){
        word = fgetc(about);
        cout << word;
    }
    cout << endl;
    fclose(about);
    hitback();
}

void User_set()
{
    while(1){
        clrscr();
        cout << line << "用户管理" << line << endl;
        cout << "1.添加用户" << endl;
        cout << "2.删除用户" << endl;
        cout << "3.修改用户信息" << endl;
        cout << "4.返回" << endl;
        num = Input_N(answer);
        switch(num){
            case 1: User_add(); break;
            case 2: User_delete(); break;
            case 3: User_info_c(); break;
            case 4: return;
            default: num = 0;break;
        }
    }
}

void User_add()
{
    int age = 0;
    int sex = 0;
    int grade = 0;
    string id;
    char AGE[3]{};
    char Grade[5]{};
    string name;
    string info;
    string Pro;
    clrscr();
    cout << line << "添加用户" << line << endl;
    cout << "登记用户信息：" << endl;
    cout << "学号(用户身份识别码): ";
    if(Input(id,4,id_len) == 0) return;
    string ID;
    F_Add(path,id,ID);
    if((inf_user = fopen(ID.data(),"r"))!=NULL){
        cout << "用户已存在" << endl;
        fclose(inf_user);
        hitback();
        return;
    }

    cout << "姓名：" ;
    if(Input(name,4,n_name) == 0) return;
    while(age<=0||age>99){
        cout << "年龄(1-99)：";
        age = Input_N(answer);
    }
    itoa(age,AGE,10);

    while(sex!=1&&sex!=2){
        cout << "性别：1.男\t2.女" << endl;
        sex = Input_N(answer);
    }

    while(grade<1990||grade>2019){
        cout << "年级：";
        grade = Input_N(Grade);
    }
    itoa(grade,Grade,10);
    cout << "系别:";
    if(Input_B(Pro,0,max_n) == 0) return;

    cout << "个人简介:" << endl;
    if(Input_B(info,0,max_n) == 0) return;

    if((inf_user = fopen(ID.data(),"w+"))==NULL){
        cout << "创建用户信息失败" << endl;
        hitback();
        return;
    }
    if((inf_IDs = fopen("sys_inf/inf_IDs.txt","a+")) == NULL){
        cout << "添加学号失败" << endl;
        fclose(inf_user);
        remove(ID.data());
        hitback();
        return;
    }

    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if(sex == 1) fwrite("男",s_c,2,inf_user);
    else fwrite("女",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(Grade,s_c,strlen(Grade),inf_user);
    Blank(inf_user);
    fwrite(Pro.data(),s_c,Pro.length(),inf_user);
    Blank(inf_user);
    fwrite(info.data(),s_c,info.length(),inf_user);

    fwrite(id_sign,s_c,1,inf_IDs);
    fwrite(id.data(),s_c,id.length(),inf_IDs);
    fwrite(name_sign,s_c,1,inf_IDs);
    fwrite(name.data(),s_c,name.length(),inf_IDs);
    Blank(inf_IDs);

    fclose(inf_IDs);
    fclose(inf_user);
    cout << "添加用户：" << id << "成功" << endl;
    hitback();
}

void User_delete()
{
    clrscr();
    string id;
    string ID;
    cout << line << "删除用户" << line << endl;
    cout << "请输入要删除的用户的学号" << endl;
    if(Input(id,4,id_len) == 0) return;
    F_Add(path,id,ID);
    if((inf_user = fopen(ID.data(),"r")) == NULL){
        cout << "不存在学号:"<< id << endl;
        hitback();
        return;
    }
    fclose(inf_user);
    clrscr();

    cout << "确定要删除学号：" << id <<"?"<< endl;

    while(1){
        cout << "1.确认删除" <<endl<<"2.返回" << endl;
        num = Input_N(answer);
        if(num == 1){
                if(Delete_ID(id)==1){
                    if((remove(ID.data()))==0)
                        cout << "删除成功！" << endl;
                    else cout << "删除失败！" << endl;
                    hitback();
                    return;
                }else cout << "删除失败！" << endl;
        }else if(num == 2) return;
    }
}

int Delete_ID(string ID)
{
    FILE *IDs_Backup;
    if((inf_IDs=fopen("sys_inf/inf_IDs.txt","r"))==NULL){
        cout << "删除用户学号失败" << endl;
        hitback();
        return 0;
    }
    if((IDs_Backup=fopen("sys_inf/IDs_Backup.txt","w+"))==NULL){
        cout << "删除用户学号失败" << endl;
        fclose(inf_IDs);
        hitback();
        return 0;
    }

    int i = 0;
    int j = 0;
    int len = ID.length();
    int s_l = id_len+n_name+2;
    int out = 0;
    int recorder = 0;
    char line[s_l]{};
    char word = '0';

    while(!out){
        recorder = 0;
        word = 'a';
        for(i=0;i<s_l;i++) line[i] = '\0';
        for(i=0;word!='\n';i++){
            word = fgetc(inf_IDs);
            if(word == EOF) {
                out = 1; break;
            }
            line[i] = word;
        }
        if(out==1) break;
        for(i=0;line[i]!=name_sign[0]&&line[i]!='\n';i++);
        i--;
        if(i==len){
            for(j=0;j<len;j++){
                if(line[j+1]==ID[j]) recorder++;
            }
            if(recorder == len) continue;
        }
        fwrite(line,s_c,strlen(line),IDs_Backup);
    }

    fclose(inf_IDs);
    fclose(IDs_Backup);
    if((remove("sys_inf/inf_IDs.txt"))!=0) {
            remove("sys_inf/IDs_Backup.txt");
            return 0;
    }
    rename("sys_inf/IDs_Backup.txt","sys_inf/inf_IDs.txt");
    return 1;
}

void User_info_c()
{
    int age = 0;
    int sex = 0;
    int grade = 0;
    char AGE[3]{};
    string id;
    string ID;
    string info;
    char Grade[5]{};
    string Pro;
    clrscr();
    cout << line << "修改用户信息：" << line << endl;
    cout << "输入要修改的学号" << endl;
    if(Input(id,4,id_len) == 0) return;
    F_Add(path,id,ID);

    if((inf_user = fopen(ID.data(),"r")) == NULL){
        cout << "读取用户数据失败" << endl;
        hitback();
        return;
    }
    fclose(inf_user);
    while(age<=0||age>99){
        cout << "年龄(1-99)：";
        age = Input_N(answer);
    }
    itoa(age,AGE,10);
    while(sex!=1&&sex!=2){
        cout << "性别：1.男\t2.女" << endl;
        sex = Input_N(answer);
    }
    while(grade<1990||grade>2019){
        cout << "年级：";
        grade = Input_N(Grade);
    }
    itoa(grade,Grade,10);
    cout << "系别:";
    if(Input_B(Pro,0,max_n) == 0) return;

    cout << "个人简介(100字节):" << endl;
    if(Input_B(info,0,max_n) == 0) {
        fclose(inf_user);
        return;
    }
    if((inf_user = fopen(ID.data(),"w"))==NULL){
        cout << "写入用户数据失败" << endl;
        fclose(inf_user);
        hitback();
        return;
    }
    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if(sex == 1) fwrite("男",s_c,2,inf_user);
    else fwrite("女",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(Grade,s_c,strlen(Grade),inf_user);
    Blank(inf_user);
    fwrite(Pro.data(),s_c,Pro.length(),inf_user);
    Blank(inf_user);
    fwrite(info.data(),s_c,info.length(),inf_user);
    fclose(inf_user);
    cout << "修改成功！" << endl;
    hitback();
    return;
}

void Lottery()
{
    while(1){
        clrscr();
        cout << line <<"抽奖"<< line <<endl;
        cout << "1.单组抽奖" <<endl;
        cout << "2.多组抽奖" <<endl;
        cout << "3.返回" << endl;

        num = Input_N(answer);
        switch(num){
            case 1: Single(); break;
            case 2: Multi(); break;
            case 3: return;
            default : num = 0; break;
        }
    }
}

void Single()
{
    if((inf_IDs = fopen("sys_inf/inf_IDs.txt","r"))==NULL){
        cout << "读取用户信息失败！" << endl;
        hitback();
        return;
    }
    if((inf_prz = fopen("sys_inf/inf_prz.txt","r"))==NULL){
        cout << "读取奖品信息失败！" << endl;
        fclose(inf_IDs);
        hitback();
        return;
    }
    if((inf_hstr = fopen("sys_inf/inf_hstr.txt","a"))==NULL){
        cout << "读取历史信息失败！" << endl;
        fclose(inf_IDs);
        fclose(inf_prz);
        hitback();
        return;
    }
    if((inf_set = fopen("sys_inf/inf_set.txt","r"))==NULL){
        cout << "读取设置信息失败！" << endl;
        fclose(inf_IDs);
        fclose(inf_prz);
        fclose(inf_hstr);
        hitback();
        return;
    }

    clrscr();
    srand((int)time(NULL));
    Sroll();
    char word = '0';
    char ID[id_len]{};
    char name[n_name]{};
    char NAME[n_name]{};
    int i = 0;
    int j = 0;
    int k = 0;
    int n_id = 0;       //用户总数
    int id_rest;     //未中奖用户数
    int n_p = 0;            //单个奖品数量
    int id_line=0;         //中奖用户的ID位置
    int counter = 0;
    int op1 = 0;
    int op2 = 0;
    char num_prz[2];        //奖品种类数
    for(i=0;i<2;i++) num_prz[i] = fgetc(inf_prz);
    int n_prz = atoi(num_prz);  //奖品种类数
    int line_list[n_prz*99];         //储存已中奖用户

    while(word!=EOF){
        word = fgetc(inf_IDs);
        if(word == id_sign[0]) n_id++;
    }
    id_rest = n_id;

    while(word!=inf_s[0]) word = fgetc(inf_set);
    op1 = (word=fgetc(inf_set)) - '0';
    while(word!=inf_s[0]) word = fgetc(inf_set);
    op2 = (word=fgetc(inf_set)) - '0';

    cout <<line << "抽奖结果" <<line << endl;
    for(i=0;i<n_prz;i++){   //循环抽奖品总数次
        while(word != prz_n_s[0]) word = fgetc(inf_prz);
        for(j=0;j<2;j++) num_prz[j] = fgetc(inf_prz);
        for(j=0;j<n_name;j++) NAME[j] = '\0';   //初始化奖品名称
        while(word != prz_name[0]) word = fgetc(inf_prz);
        for(j=0;(word = fgetc(inf_prz))!='\n';j++)
            NAME[j] = word;
        n_p = atoi(num_prz);    //读取此种奖品数量
        for(j=0;j<n_p;j++){         //循环抽此奖品数量次
            for(k=0;k<id_len;k++)   //初始化ID
                ID[k] = '\0';
            while(1){               //随机ID
                id_line = rand()%n_id;
                if(!Used_Line(id_line,counter,line_list)) break;
            }
            line_list[counter] = id_line;             //储存中奖ID
            if(op1==1) Get_ID(ID,id_line,inf_IDs);             //读取用户ID
            if(op2==1) Get_name(name,id_line,inf_IDs);
            cout <<"恭喜：" <<ID<<" " << name << " 中奖：";
            cout << NAME << endl;

            id_rest--;              //剩余ID数-1
            if(id_rest<=0){        //判断用户是否有剩余
                cout << "已无用户！" << endl;
                hitback();
                return;
            }

            Record_Time(inf_hstr);
            if(op1==1){
                fwrite("\0|\0中奖ID: ",s_c,11,inf_hstr);
                 fwrite(ID,s_c,strlen(ID),inf_hstr);
                fwrite("\0",s_c,1,inf_hstr);
            }
            if(op2==1) {
                fwrite("\0|\0中奖人：",s_c,11,inf_hstr);
                fwrite(name,s_c,strlen(name),inf_hstr);
            }
            fwrite("\0|\0",s_c,3,inf_hstr);
            fwrite(" 奖品名称：",s_c,11,inf_hstr);
            fwrite(NAME,s_c,strlen(NAME),inf_hstr);
            Blank(inf_hstr);
            counter++;
        }
    }

    fclose(inf_IDs);
    fclose(inf_prz);
    fclose(inf_hstr);
    fclose(inf_set);
    hitback();
}

void Multi()
{
    if((inf_IDs = fopen("sys_inf/inf_IDs.txt","r"))==NULL){
        cout << "读取用户信息失败！" << endl;
        hitback();
        return;
    }
    if((inf_prz = fopen("sys_inf/inf_prz_m.txt","r"))==NULL){
        cout << "读取奖品信息失败！" << endl;
        fclose(inf_IDs);
        hitback();
        return;
    }
    if((inf_hstr = fopen("sys_inf/inf_hstr.txt","a"))==NULL){
        cout << "读取历史信息失败！" << endl;
        fclose(inf_IDs);
        fclose(inf_prz);
        hitback();
        return;
    }
    if((inf_set = fopen("sys_inf/inf_set.txt","r"))==NULL){
        cout << "读取设置信息失败！" << endl;
        fclose(inf_IDs);
        fclose(inf_prz);
        fclose(inf_hstr);
        hitback();
        return;
    }

    clrscr();
    srand((int)time(NULL));
    Sroll();
    char word = '0';
    char ID[id_len]{};
    char NAME[n_name]{};
    int i = 0;
    int j = 0;
    int k = 0;
    int c = 0;
    int op1 = 0;
    int op2 = 0;
    int n_id = 0;       //用户总数
    int id_rest;     //未中奖用户数
    char num_prz[2];        //奖品种类数
    char name[n_name]{};
    for(i=0;i<2;i++) num_prz[i] = fgetc(inf_prz);
    int n_prz = atoi(num_prz);  //奖品种类数
    int n_p_t = 0;
    int n_p = 0;            //单个奖品数量
    int id_line=0;         //中奖用户的ID位置
    int counter = 0;
    int line_list[n_prz*99];         //储存已中奖用户

    while(word!=inf_s[0]) word = fgetc(inf_set);
    op1 = (word=fgetc(inf_set)) - '0';
    while(word!=inf_s[0]) word = fgetc(inf_set);
    op2 = (word=fgetc(inf_set)) - '0';


    while(word!=EOF){
        word = fgetc(inf_IDs);
        if(word == id_sign[0]) n_id++;
    }
    id_rest = n_id;

    cout << line << "抽奖结果" <<line<< endl;
    for(i=0;i<n_prz;i++){   //循环抽奖品总数次
        cout << "第" << i+1 << "组抽奖：" << endl;
        while(word!=prz_m_s[0]) word = fgetc(inf_prz);
        for(j=0;word!='\n';j++) {
            word = fgetc(inf_prz);
            answer[j] = word;
        }
        n_p_t = atoi(answer);

        for(j=0;j<n_p_t;j++){
            while(word != prz_n_s[0]) word = fgetc(inf_prz);
            for(k=0;k<2;k++) num_prz[k] = fgetc(inf_prz);
            for(k=0;k<n_name;k++) NAME[k] = '\0';   //初始化奖品名称
            while(word != prz_name[0]) word = fgetc(inf_prz);
            for(k=0;(word = fgetc(inf_prz))!='\n';k++)
                NAME[k] = word;
            n_p = atoi(num_prz);    //读取此种奖品数量
            for(k=0;k<n_p;k++){         //循环抽此奖品数量次
                for(c=0;c<id_len;c++)   //初始化ID
                    ID[c] = '\0';
                while(1){               //随机ID
                    id_line = rand()%n_id;
                    if(!Used_Line(id_line,counter,line_list)) break;
                }

                line_list[counter] = id_line;             //储存中奖ID
                if(op1==1) Get_ID(ID,id_line,inf_IDs);        //读取用户ID
                if(op2==1) Get_name(name,id_line,inf_IDs);
                cout <<"恭喜：" <<ID<<" " << name << " 中奖：";
                cout << NAME << endl;

                id_rest--;              //剩余ID数-1
                if(id_rest<=0){        //判断用户是否有剩余
                    cout << "已无用户！" << endl;
                    hitback();
                    return;
                }
                Record_Time(inf_hstr);
                if(op1==1){
                    fwrite("\0|\0中奖ID: ",s_c,11,inf_hstr);
                     fwrite(ID,s_c,strlen(ID),inf_hstr);
                    fwrite("\0",s_c,1,inf_hstr);
                }
                if(op2==1) {
                    fwrite("\0|\0中奖人：",s_c,11,inf_hstr);
                    fwrite(name,s_c,strlen(name),inf_hstr);
                }
                fwrite("\0|\0",s_c,3,inf_hstr);
                fwrite(" 奖品名称：",s_c,11,inf_hstr);
                fwrite(NAME,s_c,strlen(NAME),inf_hstr);
                Blank(inf_hstr);
                counter++;
            }
        }
    }

    fclose(inf_IDs);
    fclose(inf_prz);
    fclose(inf_hstr);
    hitback();
}

void Get_ID(char *str, int line, FILE *file)
{
    fseek(file,0,SEEK_SET);
    char out = '0';
    int k = 0;
    int len = strlen(str);
    for(k=0;k<len;k++) str[k] = '\0';
    for(k=-1;k<line;out = fgetc(file)){
        if(out == id_sign[0]) k++;
    }
    for(k=0;out!=name_sign[0];k++){
        str[k] = out;
        out = fgetc(file);
    }
}

void Get_name(char *str, int line, FILE *file)
{
    fseek(file,0,SEEK_SET);
    char out = '0';
    int k = 0;
    int len = strlen(str);
    for(k=0;k<len;k++) str[k] = '\0';
    for(k=-1;k<line;out = fgetc(file)){
        if(out == name_sign[0]) k++;
    }
    for(k=0;out!='\n';k++){
        str[k] = out;
        out = fgetc(file);
    }
}

int Used_Line(int id, int m, int line_list[])
{
    int k = 0;
    for(k=0;k<m;k++){
        if(id==line_list[k])
            return 1;
    }
    return 0;
}

void F_Add(const char *f,string b,string &t)
{
    t = f+b;
}

void Show_set()
{
    clrscr();
    if((inf_set = fopen("sys_inf/inf_set.txt","w"))==NULL){
        cout << "打开文件失败！"<< endl;
        hitback();
        return;
    }

    int num = -1;
    int op1 = 0;
    int op2 = 0;
    int op3 = 0;
    int op4 = 0;

    cout << line << "滚动设置"<< line << endl;
    cout << "设置滚动次数(0-100)"<< endl;

    while(num<0||num>100)
            num = Input_N(answer);
    if(num!=0){
        cout << "是否开启ID显示？" << endl;
        while(op1!=1&&op1!=2){
            cout << "1.开启 | 2.关闭" << endl;
            op1 = Input_N(answer);
        }
        if(op1==1){
            cout << "是否开启名称显示？" << endl;
            while(op2!=1&&op2!=2){
                cout << "1.开启 | 2.关闭" << endl;
                op2 = Input_N(answer);
            }
        }
        else op2 = 1;
    }

    itoa(num,answer,10);
    fwrite(answer,s_c,strlen(answer),inf_set);
    Blank(inf_set);
    itoa(op1,answer,10);
    fwrite(answer,s_c,strlen(answer),inf_set);
    Blank(inf_set);
    itoa(op2,answer,10);
    fwrite(answer,s_c,strlen(answer),inf_set);
    Blank(inf_set);
    fwrite(inf_s,s_c,1,inf_set);

    clrscr();
    cout << line << "抽奖格式显示" <<line << endl;
    cout << "是否显示学号(ID)?" << endl;
    while(op3!=1&&op3!=2){
        cout << "1.显示 | 2.不显示" <<endl;
        op3 = Input_N(answer);
    }
    itoa(op3,answer,10);
    fwrite(answer,s_c,1,inf_set);
    Blank(inf_set);
    fwrite(inf_s,s_c,1,inf_set);
    if(op3==1){
        cout << "是否显示姓名?" << endl;
        while(op4!=1&&op4!=2){
            cout << "1.显示 | 2.不显示" << endl;
            op4 = Input_N(answer);
        }
        itoa(op4,answer,10);
        fwrite(answer,s_c,1,inf_set);
    }
    else fwrite("1",s_c,1,inf_set);
    fclose(inf_set);
    cout <<"修改成功！" << endl;
    hitback();
    return;
}
void Sroll()
{
    clrscr();
    int i = 0;
    int id = 0;
    int n_id = 0;
    int op0 = 0;
    int op1 = 0;
    int op2 = 0;
    char word = 'a';
    char LINE[3]{};
    char ID[id_len]{};
    char name[n_name]{};

    for(i=0;word!='\n';i++){
        word = fgetc(inf_set);
        LINE[i] = word;
    }
    op0 = atoi(LINE);
    if(op0 == 0) return;

    word = fgetc(inf_set);
    op1 = word - '0';
    word = fgetc(inf_set);
    word = fgetc(inf_set);
    op2 = word - '0';

    for(word='a';word!=EOF;word=fgetc(inf_IDs))
        if(word==id_sign[0]) n_id++;

    srand((int)time(NULL));
    for(i=0;i<op0;i++){
        clrscr();
        id = rand()%n_id;
        if(op1==1) {
            cout << line;
            Get_ID(ID,id,inf_IDs);
        }
        if(op2==1) {
            cout << line;
            Get_name(name,id,inf_IDs);
        }
        cout << line << line << endl;
        cout << "正在抽奖：";
        cout << ID << " " << name << endl;
    }

    fseek(inf_IDs,0,SEEK_SET);
    fseek(inf_set,0,SEEK_SET);
    clrscr();
}

void Record_Time(FILE *file)
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    int year = p->tm_year - 100;
    int mon = 1+p->tm_mon;
    int day = p->tm_mday;
    int hour = 8+p->tm_hour;
    int mini = p->tm_min;
    int sec = p->tm_sec;
    char time[5];
    fwrite("时间:",s_c,5,file);
    itoa(year,time,10);
    if(strlen(time)<=1) fwrite("0",s_c,1,file);
    fwrite(time,s_c,strlen(time),file);
    fwrite("/",s_c,1,file);
    itoa(mon,time,10);
    if(strlen(time)<=1) fwrite("0",s_c,1,file);
    fwrite(time,s_c,strlen(time),file);
    fwrite("/",s_c,1,file);
    itoa(day,time,10);
    if(strlen(time)<=1) fwrite("0",s_c,1,file);
    fwrite(time,s_c,strlen(time),file);
    fwrite("\0",s_c,1,file);
    itoa(hour,time,10);
    if(strlen(time)<=1) fwrite("0",s_c,1,file);
    fwrite(time,s_c,strlen(time),file);
    fwrite(":",s_c,1,file);
    itoa(mini,time,10);
    if(strlen(time)<=1) fwrite("0",s_c,1,file);
    fwrite(time,s_c,strlen(time),file);
    fwrite(":",s_c,1,file);
    itoa(sec,time,10);
    if(strlen(time)<=1) fwrite("0",s_c,1,file);
    fwrite(time,s_c,strlen(time),file);
    fwrite("\0|\0",s_c,3,file);
}

int Illegal_word(char word)
{
    int j = 0;
    for(j=0;j<n_illegal;j++){
        if(word == illegal_word[j]) {
                cout << "检测到非法字符：";
                cout << word << endl;
                return 1;
        }
    }
    return 0;
}

int Input(string &input, int min_s, int max_s)
{
    int i = 0;
    int l = 0;
    int illegal = 0;
    while(1){
        illegal = 0;
        cin.sync();
        getline(cin,input);
        l = input.length();
        if(l == 0) return 0;
        else if(l>max_s) illegal = 1;
        else if(l<min_s) illegal = 1;
        else for(i=0;i<l;i++){
            if(Illegal_word(input[i]) == 1) illegal = 1;
            if(input[i] == ' ') {
                    cout << "此处禁止输入空格符！" << endl;
                    illegal = 1;
            }
        }
        if(illegal == 1) cout << "请重新输入: ";
        else return 1;
    }
}

int Input_B(string &input, int min_s, int max_s)
{
    int i = 0;
    int len = 0;
    int illegal = 0;
    while(1){
        illegal = 0;
        cin.sync();
        getline(cin,input);
        len = input.length();
        if(len == 0) return 0;
        else if(len < min_s) illegal = 1;
        else for(i=0;i<len;i++){
            if(Illegal_word(input[i]) == 1) illegal = 1;
        }
        if(illegal == 1) cout << "请重新输入: ";
        else return 1;
    }
    return 1;
}

int Input_N(char *input)
{
    num = 0;
    int i = 0;
    for(i=0;i<3;i++) input[i] = '\0';
    while(1){
        cin >> input;
        if(input[0]=='0') return 0;
        if((num=atoi(input))!=0) break;
    }
    return num;
}

void clrscr()
{
    system("cls");
}

void hitback()
{
    cout << endl;
    system("pause");
}

void Blank(FILE* file)
{
    fwrite("\n",s_c,1,file);
}

