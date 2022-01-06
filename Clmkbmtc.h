#pragma once
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define SOCK_IN sockaddr_in*
#define BUF 6 * 1024 * 1024
#define ID 666

typedef struct clientinformation
{
    int id;
    SOCKET picture;//���洫��
    SOCKET control;//����
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
    SOCKET picture;//���洫��
    SOCKET control;//����
    sockaddr server;
    int id;
    int nrecvbuf;
};

class TCPv4_client
{
public:
    TCPv4_client(int portp, int portc);//���ӷ�����
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
#define JPIXELS 10  //���ظ������жϣ�
#define CDPIXELS 2  //���ظ�����ѹ����

class BmpDc
{
public:
    BmpDc(int width/*ͼƬ��*/, int height/*ͼƬ��*/, HWND deskwnd/*GetDesktopWindow()������*/);
    BmpDc();
    ~BmpDc();
    void Reinitialize(int width, int height, HWND deskwnd);//���³�ʼ��
    bool JudgeGetBmpData();//����ͼ���ж��Ƿ�һ��,����true��ʾ��һ��
    void CompressBmpData();//ѹ��ͼ��
    void DecompressBmpData();//��ѹ��ͼ��
    void ShowBmp();//��ʾλͼ
    void SaveBmp(const char* str);//���浽�ļ�
    BYTE* bmData;//λͼ����
    BYTE* CompressbmData;//λͼѹ������
    BITMAPINFOHEADER bih;
    BITMAPFILEHEADER bfh;
    RECT rsize;//������
    unsigned int cpress;//ѹ���������ֽ�
private:
    HWND DeskWnd;
    HDC memDC;//����DC
    HDC DeskDC;//����DC
    HBITMAP DeskBmp;//����λͼ  
    int quantity;//�ۼ��ж�ͼ��
    unsigned int dpress;//��ԭ����RGB
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