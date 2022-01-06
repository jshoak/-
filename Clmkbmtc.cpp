#include "pch.h"
#include "Clmkbmtc.h"

int Clearrecvbuf(SOCKET* sock, char* buf)
{
    timeval time_out = { 0 };
    fd_set read_fds = { 0 };
    FD_ZERO(&read_fds);
    FD_SET(*sock, &read_fds);
    while (true)
    {
        if (select(FD_SETSIZE, &read_fds, NULL, NULL, &time_out) <= 0)
            return 1;
        Recvdatas(sock, buf);
    }
    return 0;
}

int Senddatas(SOCKET* sock, char* buf, int nbytes)
{
    int total = sizeof(int), rev = 0;
    char* cnumber = (char*)&nbytes;
    while (total) {
        cnumber += rev;
        rev = send(*sock, cnumber, total, 0);
        total -= rev;
        if (rev < 0)return 0;
    }rev = 0;
    total = 0;
    while (nbytes) {
        buf += rev;
        rev = send(*sock, buf, nbytes, 0);
        nbytes -= rev;
        total += rev;
        if (rev < 0)return 0;
    }
    return total;
}

int Recvdatas(SOCKET* sock, char* buf)
{
    int total = sizeof(int), rev = 0, number = 0;
    char* cnumber = (char*)&number;
    while (total) {
        cnumber += rev;
        rev = recv(*sock, cnumber, total, 0);
        total -= rev;
        if (rev < 0)return 0;
    }rev = 0;
    total = number;
    while (total) {
        buf += rev;
        rev = recv(*sock, buf, total, 0);
        total -= rev;
        if (rev < 0)return 0;
    }
    return number;
}

TCPv4_server::TCPv4_server(int portp, int portc) :id(ID), nrecvbuf(BUF)
{
	memset(&server, 0, sizeof(sockaddr));
	memset(&clif, 0, sizeof(clieninf));
	if (WSAStartup(MAKEWORD(2, 2), &wsad) != 0)
        MessageBox(NULL, TEXT("请求协议失败,版本2.2"), TEXT("提示"), MB_OK);
	picture = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//TCP
	control = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//TCP
	vary = (SOCK_IN)&server;
	vary->sin_family = AF_INET;  //使用IPv4地址
	vary->sin_addr.s_addr = htonl(INADDR_ANY); //自动获取IP地址
	vary->sin_port = htons(portp);  //端口
    bind(picture, &server, sizeof(sockaddr));
	vary->sin_port = htons(portc);
    bind(control, &server, sizeof(sockaddr)); 
}

TCPv4_server::~TCPv4_server()
{
	closesocket(picture);
	closesocket(control);
	closesocket(clif.picture);
	closesocket(clif.control);
	WSACleanup();
}

clieninf TCPv4_server::Waitingconnec()
{
	listen(picture, 5);
	listen(control, 5);
	clif.id = id;
	id++;
	clif.picture = accept(picture, NULL, NULL);
	clif.control = accept(control, NULL, NULL);
	setsockopt(clif.picture, SOL_SOCKET, SO_RCVBUF, (const char*)&nrecvbuf, sizeof(int));//设置缓冲区
	//setsockopt(inf.picture, SOL_SOCKET, SO_SNDBUF, (const char*)&nrecvbuf, sizeof(int));//设置缓冲区
	return clif;
}

TCPv4_client::TCPv4_client(int portp, int portc) :pop(portp), poc(portc)
{
	memset(&server, 0, sizeof(sockaddr));
	memset(&inf, 0, sizeof(clieninf));
    vary = (SOCK_IN)&server;
    vary->sin_family = AF_INET;  //使用IPv4地址
    inet_pton(AF_INET, "127.0.0.1", &vary->sin_addr.s_addr);
}

TCPv4_client::~TCPv4_client()
{
	closesocket(inf.picture);
	closesocket(inf.control);;
}

void TCPv4_client::sclienstop()
{
    inf.picture = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//TCP
    inf.control = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//TCP
    vary->sin_port = htons(pop);  //端口
    connect(inf.picture, &server, sizeof(sockaddr));//发送连接请求
    vary->sin_port = htons(poc);
    connect(inf.control, &server, sizeof(sockaddr));//发送连接请求
}
/************************************************************/
BmpDc::BmpDc(int width, int height, HWND deskwnd) :quantity(0), i(0), j(0), k(0),
cpress(0), dpress(0), DeskWnd(deskwnd), widsize(WIDTHBYTES(width)), heisize(0), numsize(0)
{
    GetWindowRect(DeskWnd, &rsize);
    DeskDC = GetDC(DeskWnd);
    memDC = CreateCompatibleDC(DeskDC);
    DeskBmp = CreateCompatibleBitmap(DeskDC, width, height);
    SelectObject(memDC, DeskBmp);
    bmData = new BYTE[height * widsize]();
    CompressbmData = new BYTE[height * widsize]();
    memset(&bih, 0, sizeof(BITMAPINFOHEADER));
    memset(&bfh, 0, sizeof(BITMAPFILEHEADER));
    bih.biSize = 40;
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;
    bih.biSizeImage = height * widsize;
    bfh.bfType = 0x4d42;
    bfh.bfSize = bih.biSizeImage + 54;
    bfh.bfOffBits = 54;
}

BmpDc::BmpDc() :quantity(0), i(0), j(0), k(0), cpress(0)
, dpress(0), heisize(0), numsize(0), widsize(0)
, DeskWnd(NULL), DeskDC(NULL), memDC(NULL),
DeskBmp(NULL), bmData(NULL), CompressbmData(NULL)
{
    memset(&bih, 0, sizeof(BITMAPINFOHEADER));
    memset(&bfh, 0, sizeof(BITMAPFILEHEADER));
    memset(&rsize, 0, sizeof(RECT));
    bih.biSize = 40;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;
    bfh.bfType = 0x4d42;
    bfh.bfOffBits = 54;
}

BmpDc::~BmpDc()
{
    delete[] bmData;
    delete[] CompressbmData;
    ReleaseDC(DeskWnd, DeskDC);
    DeleteDC(memDC);
}

void BmpDc::Reinitialize(int width, int height, HWND deskwnd)
{
    delete[] bmData;
    delete[] CompressbmData;
    ReleaseDC(DeskWnd, DeskDC);
    DeleteDC(memDC);
    DeskWnd = deskwnd;
    widsize = WIDTHBYTES(width);
    GetWindowRect(DeskWnd, &rsize);
    DeskDC = GetDC(DeskWnd);
    memDC = CreateCompatibleDC(DeskDC);
    DeskBmp = CreateCompatibleBitmap(DeskDC, width, height);
    SelectObject(memDC, DeskBmp);
    bmData = new BYTE[height * widsize]();
    CompressbmData = new BYTE[height * widsize]();
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biSizeImage = height * widsize;
    bfh.bfType = 0x4d42;
    bfh.bfSize = bih.biSizeImage + 54;
    bfh.bfOffBits = 54;
}

bool BmpDc::JudgeGetBmpData()
{
    quantity = 0;
    StretchBlt(memDC, 0, 0, bih.biWidth, bih.biHeight, DeskDC, 0, 0, rsize.right, rsize.bottom, SRCINVERT);
    GetDIBits(memDC, DeskBmp, 0, bih.biHeight, bmData, (BITMAPINFO*)&bih, DIB_RGB_COLORS);
    for (i = 0; i < bih.biSizeImage; i += (3 * JPIXELS))
        if (bmData[i] == 0)
            quantity++;
    StretchBlt(memDC, 0, 0, bih.biWidth, bih.biHeight, DeskDC, 0, 0, rsize.right, rsize.bottom, SRCCOPY);
    GetDIBits(memDC, DeskBmp, 0, bih.biHeight, bmData, (BITMAPINFO*)&bih, DIB_RGB_COLORS);
    if (quantity == bih.biSizeImage / (3 * JPIXELS))
        return false;
    else
        return true;
}

void BmpDc::CompressBmpData()
{
    memset(CompressbmData, 0, bih.biSizeImage);
    cpress = 0;
    for (i = 0; i < (unsigned int)bih.biHeight; i++)
    {
        heisize = i * widsize;
        for (j = 0; j < (unsigned int)bih.biWidth * 3; j += (3 * CDPIXELS))
        {
            numsize = heisize + j;
            if (CompressbmData[cpress] == bmData[numsize] &&
                CompressbmData[cpress + 1] == bmData[numsize + 1] &&
                CompressbmData[cpress + 2] == bmData[numsize + 2] &&
                CompressbmData[cpress + 3] < 255)
            {
                CompressbmData[cpress + 3]++;
            }
            else
            {
                cpress += 4;
                CompressbmData[cpress] = bmData[numsize];
                CompressbmData[cpress + 1] = bmData[numsize + 1];
                CompressbmData[cpress + 2] = bmData[numsize + 2];
            }
        }
    }
}

void BmpDc::DecompressBmpData()
{
    cpress = 0;
    for (i = 0; i < (unsigned int)bih.biHeight; i++)
    {
        heisize = i * widsize;
        for (j = 0; j < (unsigned int)bih.biWidth * 3; j += (3 * CDPIXELS))
        {
            numsize = heisize + j;
            if (CompressbmData[cpress + 3]--)
            {
                bmData[numsize] = CompressbmData[cpress];
                bmData[numsize + 1] = CompressbmData[cpress + 1];
                bmData[numsize + 2] = CompressbmData[cpress + 2];
            }
            else
            {
                cpress += 4;
                bmData[numsize] = CompressbmData[cpress];
                bmData[numsize + 1] = CompressbmData[cpress + 1];
                bmData[numsize + 2] = CompressbmData[cpress + 2];
            }
        }
    }
    memset(CompressbmData, 0, bih.biSizeImage);
}

void BmpDc::ShowBmp()
{
    GetWindowRect(DeskWnd, &rsize);
    SetDIBits(memDC, DeskBmp, 0, bih.biHeight, bmData, (BITMAPINFO*)&bih, DIB_RGB_COLORS);
    StretchBlt(DeskDC, 0, 0, rsize.right - rsize.left, rsize.bottom - rsize.top, memDC, 0, 0, bih.biWidth, bih.biHeight, SRCCOPY);
}

void BmpDc::SaveBmp(const char* str)
{
    std::ofstream outfile(str, std::ios::binary);
    outfile.write((char*)&bfh, sizeof(BITMAPFILEHEADER));
    outfile.write((char*)&bih, sizeof(BITMAPINFOHEADER));
    outfile.write((char*)bmData, bih.biSizeImage);
    outfile.close();
}
/******************************按键模拟******************************/
void KeyImitate(int k, int d)
{
    /*------------------------------------------------
        k：键值
        d：1按下，2抬起
    ------------------------------------------------*/
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = k;
    input.ki.dwFlags = d;
    SendInput(1, &input, sizeof(INPUT));
}
/********************************************************************/

/******************************鼠标模拟******************************/
void MouseImitate(int x, int y, int d)
{
    /*------------------------------------------------
        x：横坐标 屏幕分辨率
        y：竖坐标 屏幕分辨率
        d:
        左键 2按下，4抬起
        右键 8按下，10抬起
        移动 32769绝对位置（误差最大1像素）
    ------------------------------------------------*/
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dx = (int)(65536.0 / GetSystemMetrics(SM_CXSCREEN) * x);
    input.mi.dy = (int)(65536.0 / GetSystemMetrics(SM_CYSCREEN) * y);
    input.mi.dwFlags = d;
    SendInput(1, &input, sizeof(INPUT));
}

void MouseImitate(int x, int y)
{
    /*------------------------------------------------
        （与鼠标灵敏度有关）
        鼠标相对位置移动（单位像素，鼠标灵敏度默认值10）
        x：横坐标偏移量
        y：竖坐标偏移量
    ------------------------------------------------*/
    int aMouseInfo[3] = { 0 };
    int bMouseInfo[3] = { 0 };
    INPUT input = { 0 };
    SystemParametersInfoW(SPI_GETMOUSE, 0, aMouseInfo, 0);//检索两个鼠标阈值和鼠标加速度
    SystemParametersInfoW(SPI_SETMOUSE, 0, bMouseInfo, SPIF_SENDCHANGE);//设置两个鼠标阈值和鼠标加速度
    input.type = INPUT_MOUSE;
    input.mi.dx = x;
    input.mi.dy = y;
    input.mi.dwFlags = TOUCHEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
    SystemParametersInfoW(SPI_SETMOUSE, 0, aMouseInfo, SPIF_SENDCHANGE);
}
/********************************************************************/