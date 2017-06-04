#include <cstdlib>
#include <cmath>
#include <windows.h>
#include <ctime>
#include <string>
#include "header.h"
using namespace std;




// 点与线
void DrawPixels(HWND hwnd, HDC hdc)
{
	RECT r;
	GetClientRect(hwnd, &r);  // 获得客户区域
	SetMapMode(hdc, MM_ISOTROPIC);  // 设置映像模式
	SetWindowExtEx(hdc, 100, 100, NULL);  // 设置窗口坐标范围
	SetViewportExtEx(hdc, r.right, r.bottom, NULL);  // 设置视口坐标范围

	FillRect(hdc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));  // 设置客户区背景
	TextOut(hdc, 47.5, 49, TEXT("TEST"), lstrlen(TEXT("TEST")));  // 输出一个文本
	for (int i = 10; i<50; i += 1)
	{
		SetPixelV(hdc, i, i, RGB(5 * i, 255 - 5 * i, 5 * i));  // 输出一个像素
		SetPixelV(hdc, 100 - i, i, RGB(5 * i, 255 - 5 * i, 5 * i));
		SetPixelV(hdc, 100 - i, 100 - i, RGB(5 * i, 255 - 5 * i, 5 * i));
		SetPixelV(hdc, i, 100 - i, RGB(5 * i, 255 - 5 * i, 5 * i));
	}
	MoveToEx(hdc, 10, 10, NULL);  // 移动到初始点
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 0, 255)));
	LineTo(hdc, 90, 10);  // 画线至终止点

	MoveToEx(hdc, 90, 10, NULL);
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 0, 255)));
	LineTo(hdc, 90, 90);
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 255, 255)));

	MoveToEx(hdc, 90, 90, NULL);
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 255, 0)));
	LineTo(hdc, 10, 90);

	MoveToEx(hdc, 10, 90, NULL);
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
	LineTo(hdc, 10, 10);

}

// 三角形
void DrawTriangle(HWND hwnd, HDC hdc)
{
	RECT r;
	GetClientRect(hwnd, &r);  // 获得客户区域
	SetMapMode(hdc, MM_ISOTROPIC);  // 设置映像模式
	SetWindowExtEx(hdc, 100, 100, NULL);  // 设置窗口坐标范围
	SetViewportExtEx(hdc, r.right, r.bottom, NULL);  // 设置视口坐标范围

	for (int i = 0; i <= 50; i += 10)
	{
		MoveToEx(hdc, i, i, NULL);
		SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255 - i, 100 + i, 255 - i)));
		LineTo(hdc, 100 - i, i);

		MoveToEx(hdc, 100 - i, i, NULL);
		SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(100 + i, 255 - i, 255 - i)));
		LineTo(hdc, 100 - i, 100 - i);

		MoveToEx(hdc, 100 - i, 100 - i, NULL);
		SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255 - i, 255 - i, 100 + i)));
		LineTo(hdc, i, i);
	}

}

// 抛物线
void DrawArcs(HWND hwnd, HDC hdc)
{
	RECT r;
	GetClientRect(hwnd, &r);  // 获得客户区域
	SetMapMode(hdc, MM_ISOTROPIC);  // 设置映像模式
	SetWindowExtEx(hdc, 400, 300, NULL);  // 设置窗口坐标范围
	SetViewportExtEx(hdc, r.right, r.bottom, NULL);  // 设置视口坐标范围

	int x1, x2 = 350, y1 = 50, y2 = 250;
	for (x1 = 50; x1 < 200; x1 += 5)
	{
		SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255 - x1, x1, 255)));
		Arc(hdc, x1, y1, 200, 150, 200, 150, 50, 150);
		Arc(hdc, 200, 150, x2, y2, 200, 150, 350, 150);
		y1 += 3; x2 -= 5; y2 -= 3;
	}
}

// 正弦曲线
struct pixel
{
	double x, y;
};
void DrawCos(HWND hwnd, HDC hdc)
{
	RECT r;
	GetClientRect(hwnd, &r);  // 获得客户区域
	SetMapMode(hdc, MM_ISOTROPIC);  // 设置映像模式
	SetWindowExtEx(hdc, 1000, 1000, NULL);  // 设置窗口坐标范围
	SetViewportExtEx(hdc, r.right, r.bottom, NULL);  // 设置视口坐标范围

	MoveToEx(hdc, 0, MAXIMUM / 2 - 1, NULL);
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
	LineTo(hdc, 1000, MAXIMUM / 2 - 1);

	MoveToEx(hdc, 0, MAXIMUM / 2, NULL);
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
	LineTo(hdc, 1000, MAXIMUM / 2);

	MoveToEx(hdc, 0, MAXIMUM / 2 + 1, NULL);
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
	LineTo(hdc, 1000, MAXIMUM / 2 + 1);

	// 设置1000个离散点
	pixel pt[MAXIMUM];
	for (int i = 0; i < MAXIMUM; i++)
	{
		pt[i].x = i * 1000 / MAXIMUM;
		pt[i].y = (int)(MAXIMUM / 2 * (1 - sin(2 * 3.14*i / MAXIMUM)));
	}

	// 将1000个离散点连接
	MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
	for (int i = 1; i < MAXIMUM; i++)
	{
		SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0.25*i, 255 - 0.25*i, 0.25*i)));
		LineTo(hdc, pt[i].x, pt[i].y);
	}
}

// 时钟
class Shape
{
public:
	virtual void move(double dx, double dy) = 0;
	virtual void SetColor(COLORREF mColor) = 0;
};
class Point : public Shape
{
private:
	double x;
	double y;
	COLORREF color;
public:
	Point()
	{
		x = 0.0;
		y = 0.0;
	}
	Point(double x1, double y1)
	{
		x = x1;
		y = y1;
	}
	double get_x() const
	{
		return x;
	}
	double get_y() const
	{
		return y;
	}
	COLORREF get_color() const
	{
		return color;
	}
	virtual void move(double dx, double dy)
	{
		x += dx;
		y += dy;
	}
	virtual void SetColor(COLORREF mColor)
	{
		color = mColor;
	}
};
class Line : public Shape
{
private:
	Point from;
	Point to;
	COLORREF color;
public:
	Line()
	{
	}
	Line(Point p1, Point p2)
	{
		from = p1;
		to = p2;
	}
	Point get_start() const
	{
		return from;
	}
	Point get_end() const
	{
		return to;
	}
	COLORREF get_color() const
	{
		return color;
	}
	virtual void move(double dx, double dy)
	{
		from.move(dx, dy);
		to.move(dx, dy);
	}
	virtual void SetColor(COLORREF mColor)
	{
		color = mColor;
	}
};
class Circle : public Shape
{
private:
	Point center;
	double radius;
	COLORREF color;
public:
	Circle()
	{
		radius = 0.0;
	}
	Circle(Point p, double r)
	{
		center = p;
		radius = r;
	}
	Point get_center() const
	{
		return center;
	}
	double get_radius() const
	{
		return radius;
	}
	COLORREF get_color() const
	{
		return color;
	}
	virtual void move(double dx, double dy)
	{
		center.move(dx, dy);
	}
	virtual void SetColor(COLORREF mColor)
	{
		color = mColor;
	}
};
class Message
{
private:
	Point start;
	string text;
public:
	Message()
	{
	}
	Message(Point s, double x)
	{
		start = s;
		char buf[20];
		sprintf_s(buf, "%g", x);
		text = buf;
	}
	Message(Point s, const string& m)
	{
		start = s;
		text = m;
	}
	Point get_start() const
	{
		return start;
	}
	string get_text() const
	{
		return text;
	}
	void move(double dx, double dy)
	{
		start.move(dx, dy);
	}
};
class GraphicWindow
{
private:
	int user_to_disp_x(double x) const
	{
		return (int)((x - _user_xmin)*_disp_xmax / (_user_xmax - _user_xmin));
	}
	int user_to_disp_y(double y) const
	{
		return (int)((y - _user_ymin)*_disp_ymax / (_user_ymax - _user_ymin));
	}
	double disp_to_user_x(int x) const
	{
		return (double)x*(_user_xmax - _user_xmin) / _disp_xmax + _user_xmin;
	}
	double disp_to_user_y(int y) const
	{
		return (double)y*(_user_ymax - _user_ymin) / _disp_ymax + _user_ymin;
	}
	void point(double x, double y, COLORREF mColor)
	{
		const int POINT_RADIUS = 3;
		int disp_x = user_to_disp_x(x);
		int disp_y = user_to_disp_y(y);
		SelectObject(_hdc, CreatePen(PS_SOLID, 1, mColor));
		Ellipse(_hdc, disp_x - POINT_RADIUS, disp_y - POINT_RADIUS, disp_x + POINT_RADIUS, disp_y + POINT_RADIUS);
	}
	void line(double xfrom, double yfrom, double xto, double yto, COLORREF mColor)
	{
		SelectObject(_hdc, CreatePen(PS_SOLID, 1, mColor));
		MoveToEx(_hdc, user_to_disp_x(xfrom), user_to_disp_y(yfrom), 0);
		LineTo(_hdc, user_to_disp_x(xto), user_to_disp_y(yto));
	}
	void ellipse(double x, double y, double ra, double rb, COLORREF mColor)
	{
		SelectObject(_hdc, CreatePen(PS_SOLID, 1, mColor));
		Ellipse(_hdc, user_to_disp_x(x - ra), user_to_disp_y(y - rb), user_to_disp_x(x + ra), user_to_disp_y(y + rb));
	}
	void text(string s, double x, double y)
	{
		const char* t = s.c_str();
		SetBkMode(_hdc, TRANSPARENT);
		TextOut(_hdc, user_to_disp_x(x), user_to_disp_y(y),(TCHAR*) t, lstrlen((TCHAR*)t));
	}
	double _user_xmin, _user_xmax, _user_ymin, _user_ymax;
	int _disp_xmax, _disp_ymax;
	HDC _hdc;
public:
	GraphicWindow() : _user_xmin(-10), _user_xmax(10), _user_ymin(10), _user_ymax(-10)
	{
	}
	void coord(double xmin, double ymin, double xmax, double ymax)
	{
		_user_xmin = xmin, _user_xmax = xmax;
		_user_ymin = ymin, _user_ymax = ymax;
	}
	void clear()
	{
		COLORREF color = RGB(255, 255, 255);
		HBRUSH brush = CreateSolidBrush(color);
		HBRUSH saved_brush = (HBRUSH)SelectObject(_hdc, brush);
		PatBlt(_hdc, 0, 0, _disp_xmax, _disp_ymax, PATCOPY);
		SelectObject(_hdc, saved_brush);
		DeleteObject(brush);
	}
	GraphicWindow& operator <<(Point p)
	{
		point(p.get_x(), p.get_y(), p.get_color());
		return *this;
	}
	GraphicWindow& operator <<(Circle c)
	{
		ellipse(c.get_center().get_x(), c.get_center().get_y(), c.get_radius(), c.get_radius(), c.get_color());
		return *this;
	}
	GraphicWindow& operator <<(Line s)
	{
		line(s.get_start().get_x(), s.get_start().get_y(), s.get_end().get_x(), s.get_end().get_y(), s.get_color());
		return *this;
	}
	GraphicWindow& operator <<(Message t)
	{
		text(t.get_text(), t.get_start().get_x(), t.get_start().get_y());
		return *this;
	}
	void open(HWND hwnd, HDC mainwin_hdc)
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		_disp_xmax = rect.right - 1;
		_disp_ymax = rect.bottom - 1;
		_hdc = mainwin_hdc;
		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_HATCHED;
		logBrush.lbColor = RGB(0, 192, 192);
		logBrush.lbHatch = HS_CROSS;
		SelectObject(_hdc, GetStockObject(BLACK_BRUSH));
		SelectObject(_hdc, GetStockObject(BLACK_PEN));
		SelectObject(_hdc, GetStockObject(SYSTEM_FONT));
		clear();
	}
};
GraphicWindow cwin;
void mclock()
{
	Shape* pShape;
	cwin << Message(Point(-1, 7), "Live Clock");
	int radius = 6;
	Point org(0, 0);
	pShape = &org;
	pShape->SetColor(RGB(255, 255, 255));
	cwin << org;
	Circle clkPlate(org, radius);
	pShape = &clkPlate;
	pShape->SetColor(RGB(0, 0, 255));
	cwin << clkPlate;
	double x, y, x_s, y_s, x_m, y_m, x_h, y_h;
	for (int i = 0; i < 12; i++)
	{
		x = 0.9*radius*sin(3.14*i / 6);
		y = 0.9*radius*cos(3.14*i / 6);
		Point mPoint(x, y);
		pShape = &mPoint;
		pShape->SetColor((RGB(255, 255, 255)));
		cwin << mPoint;
	}
	struct tm local;
	time_t t;
	t = time(NULL);
	localtime_s(&local, &t);
	x_s = 0.89*radius*sin(3.14*(local.tm_sec) / 30);
	y_s = 0.89*radius*cos(3.14*(local.tm_sec) / 30);
	x_m = 0.7*radius*sin(3.14*(local.tm_min+ local.tm_sec/60.0) / 30);
	y_m = 0.7*radius*cos(3.14*(local.tm_min +local.tm_sec/60.0) / 30);
	x_h = 0.5*radius*sin(3.14*(local.tm_hour+local.tm_min/60.0 + local.tm_sec / 3600.0) / 6);
	y_h = 0.5*radius*cos(3.14*(local.tm_hour+local.tm_min / 60.0 + local.tm_sec / 3600.0) / 6);

	Point hEnd(x_h, y_h), mEnd(x_m, y_m), sEnd(x_s, y_s);
	Line hLine(org, hEnd), mLine(org, mEnd), sLine(org, sEnd);

	hLine.SetColor((RGB(255, 0, 0)));
	mLine.SetColor((RGB(255, 255, 0)));
	sLine.SetColor((RGB(local.tm_sec*50%255, 255- local.tm_sec * 10 % 255, local.tm_sec * 100 % 255)));
	cwin << hLine << mLine << sLine << org;
}

/* 动画: 不同频率正弦函数的旋转矢量合成 */
void SineComposation(HWND hwnd, HDC hdc)
{
	RECT r;
	GetClientRect(hwnd, &r);  // 获得客户区域
	SetMapMode(hdc, MM_ISOTROPIC);  // 设置映像模式
	SetWindowExtEx(hdc, 1000, 1000, NULL);  // 设置窗口坐标范围
	SetViewportExtEx(hdc, r.right, r.bottom, NULL);  // 设置视口坐标范围
	
	TextOut(hdc, 150, 200, TEXT("不同频率正弦函数的旋转矢量合成"), lstrlen(TEXT("不同频率正弦函数的旋转矢量合成")));  // 标题
	
	/* 读取系统时间 */
	struct tm local;
	time_t t;
	t = time(NULL);
	localtime_s(&local, &t);

	/* 画出横轴和纵轴,并加粗 */
	for (int j = -1; j <= 1; j++)
	{
		MoveToEx(hdc, 200, 500+j, NULL);
		SelectObject(hdc, CreatePen(PS_DASH, 1, RGB(0, 0, 0)));
		LineTo(hdc, 500, 500+j);
		MoveToEx(hdc, 500, 500+j, NULL);
		SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
		LineTo(hdc, 800, 500+j);
		MoveToEx(hdc, 500+j, 200, NULL);
		SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
		LineTo(hdc, 500+j, 800);
	}
	
	/* 三段首尾相连的旋转矢量的相关参数 */
	double x0=200,y0=500,x1, x2, x3, y1, y2, y3;
	const int r1=150, r2=75, r3=50;
	x1 = x0 + r1*cos(3.14*(local.tm_sec) / 30);
	y1 = y0 - r1*sin(3.14*(local.tm_sec) / 30);
	x2 = x1 + r2*cos(3.14*(local.tm_sec) / 7.5);
	y2 = y1 - r2*sin(3.14*(local.tm_sec) / 7.5);
	x3 = x2 + r3*cos(3.14*(local.tm_sec) / 3.75);
	y3 = y2 - r3*sin(3.14*(local.tm_sec) / 3.75);
	
	/* 画出三段旋转矢量,并加粗 */
	for(int j = -1; j <= 1; j++)
		for (int i = -1; i <= 1; i++)
		{
			MoveToEx(hdc, x0 + i, y0 + j, NULL);
			SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 0, 0)));
			LineTo(hdc, x1 + i, y1 + j);

			MoveToEx(hdc, x1 + i, y1 + j, NULL);
			SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 255, 0)));
			LineTo(hdc, x2 + i, y2 + j);

			MoveToEx(hdc, x2 + i, y2 + j, NULL);
			SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 255)));
			LineTo(hdc, x3 + i, y3 + j);
		}

	
	/* 画出截止到当前秒的若干个正弦曲线散点 */
	pixel pt[60];
	for (int i = 0; i <= local.tm_sec; i++)
	{
		double a, b, c, d, e, f;
		a = x0 + r1*cos(3.14*(i) / 30);
		b = y0 - r1*sin(3.14*(i) / 30);
		c = a + r2*cos(3.14*(i) / 7.5);
		d = b - r2*sin(3.14*(i) / 7.5);
		e = c + r3*cos(3.14*(i) / 3.75);
		f = d - r3*sin(3.14*(i) /3.75);
		pt[i].x = 500 + i * 5;
		pt[i].y = f;
	}
	
	/* 将60个散点连接 */
	for (int i = 0; i < local.tm_sec; i++)
	{
		double r, g, b;
		r = r1*sin(3.14*(i) / 30);
		g = r2*sin(3.14*(i) / 7.5);
		b = r3*sin(3.14*(i) / 3.75);
		if (r < 0)
			r = 0;
		if (g < 0)
			g = 0;
		if (b < 0)
			b = 0;
		MoveToEx(hdc, pt[i].x, pt[i].y, NULL);
		SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(200-g-b, 200-r-b, 200-r-g)));  // 用颜色体现合成曲线中的各频率成分
		LineTo(hdc, pt[i+1].x, pt[i+1].y);
	}

	/* 画出矢量端与曲线端的连接线 */
	MoveToEx(hdc, x3, y3, NULL);
	SelectObject(hdc, CreatePen(PS_DOT, 1, RGB(0, 0, 0)));
	LineTo(hdc, pt[local.tm_sec].x, pt[local.tm_sec].y);
	MoveToEx(hdc, pt[local.tm_sec].x, pt[local.tm_sec].y, NULL);
	SelectObject(hdc, CreatePen(PS_DOT, 1, RGB(0, 0, 0)));
	LineTo(hdc, pt[local.tm_sec].x, 500);
}



/*--------------------------------------------------------------------------------------------------------------------------------------*/



long FAR PASCAL ccc_win_proc(HWND hwnd, 
	                         UINT message, 
							 UINT wParam, 
							 LONG lParam) 
{
	static int menuId = 0;
	PAINTSTRUCT ps;
    HDC hdc;
	int wmId, wmEvent;
    switch (message)
    {
		case WM_CREATE:
			SetTimer(hwnd, 1, 1000, NULL);
			break;
		
		case WM_TIMER:
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		
			// 命令消息处理
	    case WM_COMMAND:
	    	wmId = LOWORD(wParam);
		    wmEvent = HIWORD(wParam);
	        //分析菜单选择:
	        switch (wmId)
		    {
		        case IDM_FIG1:
		            menuId=IDM_FIG1;
			        InvalidateRect(hwnd,NULL,TRUE);  // “清屏”
					break;
		        case IDM_FIG2:
			        menuId=IDM_FIG2;
			        InvalidateRect(hwnd,NULL,TRUE);
					break;
				case IDM_FIG3:
					menuId = IDM_FIG3;
					InvalidateRect(hwnd, NULL, TRUE);
					break;
				case IDM_FIG4:
					menuId = IDM_FIG4;
					InvalidateRect(hwnd, NULL, TRUE);
					break;
				case IDM_FIG5:
					menuId = IDM_FIG5;
					InvalidateRect(hwnd, NULL, TRUE);
					break;
				case IDM_FIG6:
					menuId = IDM_FIG6;
					InvalidateRect(hwnd, NULL, TRUE);
					break;
				case IDM_EXIT:
			        DestroyWindow(hwnd);
					break;
				default:
					return DefWindowProc(hwnd, message, wParam, lParam);
		    }
			break;
        // 绘图消息处理
		case WM_PAINT:
		    hdc = BeginPaint(hwnd, &ps);			      
			if (menuId)
			{
				
				switch (menuId)
				{
				case IDM_FIG1:
					DrawPixels(hwnd, hdc);
					break;
				case IDM_FIG2:
					DrawTriangle(hwnd, hdc);
					break;
				case IDM_FIG3:
					DrawArcs(hwnd, hdc);
					break;
				case IDM_FIG4:
					DrawCos(hwnd, hdc);
					break;
				case IDM_FIG5:
					cwin.open(hwnd, hdc);
					mclock();
					break;
				case IDM_FIG6:
					SineComposation(hwnd, hdc);
					break;
				}
			}
			
            EndPaint(hwnd, &ps);       
			break;
        // 
		case WM_DESTROY:
			KillTimer(hwnd, 1);
			PostQuitMessage(0);
			break;
        
        default:
		     return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}


int PASCAL WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR,
	int nShowCmd)
{
	MSG msg;
	WNDCLASS wndclass;

	// 初始化窗口类，并向操作系统注册该窗口类
	if (!hPrevInstance)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = ccc_win_proc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName = MAKEINTRESOURCE(IDC_TEST);
		wndclass.lpszClassName =(TCHAR*) "CCC_WIN";

		RegisterClass(&wndclass);
	}

	// 初始化窗口，生成窗口并显示更新窗口
	char title[80] = "案例1 张子一 2015210XXX号";
	HWND hwnd = CreateWindow((TCHAR*)"CCC_WIN",
		                     (TCHAR*)title,
		                     WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		                     CW_USEDEFAULT,
		                     CW_USEDEFAULT,
		                     GetSystemMetrics(SM_CYFULLSCREEN) * 3 / 4,
		                     GetSystemMetrics(SM_CYFULLSCREEN) * 3 / 4,
		                     NULL,
		                     NULL,
		                     hInstance,
		                     0);
	// 显示窗口
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
