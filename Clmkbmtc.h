#pragma once
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define SOCK_IN sockaddr_in*
#define BUF 6 * 1024 * 1024
#define ID 666

typedef struct clientinformation
{
    int id;
    SOCKET picture;//画面传输
    SOCKET control;//控制
}clieninf;

int Clearrecvbuf(SOCKET* sock, char* buf);

int Senddatas(SOCKET* sock, char* buf, int nbytes);

int Recvdatas(SOCKET* sock, char* buf);

class TCPv4_server
{
public:
    TCPv4_server(int portp, int portc);
    ~TCPv4_server();
    clieninf Waitingconnec();
    clieninf clif;
private:
    SOCK_IN vary;
    WSADATA wsad;
    SOCKET picture;//画面传输
    SOCKET control;//控制
    sockaddr server;
    int id;
    int nrecvbuf;
};

class TCPv4_client
{
public:
    TCPv4_client(int portp, int portc);//连接服务器
    ~TCPv4_client();
    void sclienstop();
    clieninf inf;
private:
    int pop;
    int poc;
    SOCK_IN vary;
    sockaddr server;
};
/************************************************************/
#include <fstream>
#include <windows.h>
#define BYTES3(i) (i * 3)
#define BYTES4(i) (4 - (BYTES3(i) % 4))
#define WIDTHBYTES(i) (BYTES3(i) % 4 ? BYTES3(i) + BYTES4(i) : i * 3)
#define JPIXELS 10  //像素个数（判断）
#define CDPIXELS 2  //像素个数（压缩）

class BmpDc
{
public:
    BmpDc(int width/*图片宽*/, int height/*图片高*/, HWND deskwnd/*GetDesktopWindow()桌面句柄*/);
    BmpDc();
    ~BmpDc();
    void Reinitialize(int width, int height, HWND deskwnd);//重新初始化
    bool JudgeGetBmpData();//保存图像并判断是否一样,返回true表示不一样
    void CompressBmpData();//压缩图像
    void DecompressBmpData();//解压缩图像
    void ShowBmp();//显示位图
    void SaveBmp(const char* str);//保存到文件
    BYTE* bmData;//位图数据
    BYTE* CompressbmData;//位图压缩数据
    BITMAPINFOHEADER bih;
    BITMAPFILEHEADER bfh;
    RECT rsize;//桌面宽高
    unsigned int cpress;//压缩后所在字节
private:
    HWND DeskWnd;
    HDC memDC;//兼容DC
    HDC DeskDC;//窗口DC
    HBITMAP DeskBmp;//兼容位图  
    int quantity;//累加判断图像
    unsigned int dpress;//还原像素RGB
    unsigned int k;
    int widsize;
    int heisize;
    int numsize;
    unsigned int i;
    unsigned int j;
};
/************************************************************/
typedef struct mousekeyinformation
{
    int xd;
    int y;
    int k;
    int c;
}mkinf;

void KeyImitate(int k, int d);

void MouseImitate(int x, int y, int d);

void MouseImitate(int x, int y);