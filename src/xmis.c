#define BC 19
#define WK 19
#define BK 13
#define WKW 15
#define BKW 12

Display* d;
XSetWindowAttributes at, bat;
Window win, text, bar, fill;
XSizeHints wmsiz;
XWMHints wmh;
XTextProperty winn, iconn;
XEvent xev;
char* wn="wave generator";
char* in="wave generator";
int sn, done=0;
unsigned long valuemask, clr=0xf;

XColor exact, closest;
GC gc, gc2;
XGCValues xgcv;

Window btns[BC];
char* bl[BC]={"Play", "Stop", "Quit", "-100", "-10", "-1", "+1", "+10", "+100", "/10", "/2", "-1000", "+1000", "*2", "*10", "saw", "sqr", "sin", "tri"};

Window white[WK], black[BK];
const short wf[WK]={65, 73, 82, 87, 98, 110, 123, 131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392};
const short bf[BK]={69, 78, 93, 104, 117, 139, 156, 185, 208, 233, 277, 311, 370};

void xinit(){
//open display
d=XOpenDisplay("");

//create main window
sn=DefaultScreen(d);
at.background_pixel=WhitePixel(d, sn);
//at.background_pixel=0xffff00;
at.border_pixel=BlackPixel(d, sn);
at.event_mask=ButtonPressMask|KeyPressMask|KeyReleaseMask;
valuemask=CWBackPixel|CWBorderPixel|CWEventMask;
win=XCreateWindow(d, RootWindow(d, sn), 200, 200, 350, 250, 2, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &at);

//wm hints
wmsiz.flags=USPosition|USSize;
XSetWMNormalHints(d, win, &wmsiz);
wmh.initial_state=NormalState;
wmh.flags=StateHint;
XSetWMHints(d, win, &wmh);
XStringListToTextProperty(&wn, 1, &winn);
XSetWMName(d, win, &winn);
XStringListToTextProperty(&in, 1, &iconn);
XSetWMIconName(d, win, &iconn);

//colors
XAllocNamedColor(d, XDefaultColormap(d, sn), "black", &exact, &closest);
xgcv.foreground=exact.pixel;
XAllocNamedColor(d, XDefaultColormap(d, sn), "web gray", &exact, &closest);
xgcv.background=exact.pixel;
valuemask=GCForeground|GCBackground;
gc=XCreateGC(d, win, valuemask, &xgcv);
gc2=XCreateGC(d, win, 0, NULL);
XSetBackground(d, gc2, WhitePixel(d, sn));
XSetForeground(d, gc2, BlackPixel(d, sn));

//button
valuemask=CWBackPixel|CWBorderPixel|CWEventMask;
bat.background_pixel=WhitePixel(d, sn);
bat.border_pixel=BlackPixel(d, sn);
//bat.border_pixel=0x404040;

	bat.event_mask=ExposureMask;
	//text
	text=XCreateWindow(d, win, 110, 45, 60, 20, 1, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &bat);

	bat.event_mask=Button1MotionMask|ButtonReleaseMask|ButtonPressMask|ExposureMask;
	//keyboard
	for(int i=0;i<WK;i++){
	white[i]=XCreateWindow(d, win, i*WKW, 160, WKW, 80, 1, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &bat);
	}
	bat.background_pixel=BlackPixel(d, sn);
	for(int i=0;i<BK;i++){
	black[i]=XCreateWindow(d, win, (2*WKW-BKW)/2+WKW*i+WKW*((i>1)+(i>4)+(i>6)+(i>9)+(i>11)), 160, BKW, 60, 0, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &bat);
	}

bat.event_mask=ButtonPressMask|ExposureMask;
bat.background_pixel=xgcv.background;
for(int i=0;i<BC;i++){
if(i<3) btns[i]=XCreateWindow(d, win, i*35, 0, 35, 20, 1, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &bat);
else if(i<9) btns[i]=XCreateWindow(d, win, (i-3)*35+(i>5)*70, 30, 35, 20, 1, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &bat);
else if(i<15) btns[i]=XCreateWindow(d, win, (i-9)*35+(i>11)*70, 60, 35, 20, 1, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &bat);
else btns[i]=XCreateWindow(d, win, (i-15)*39, 90, 35, 20, 1, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &bat);
}

at.background_pixel=0xd3d3d3;
at.event_mask=ButtonPressMask|ButtonReleaseMask|Button1MotionMask;
valuemask=CWBackPixel|CWBorderPixel|CWEventMask;
bar=XCreateWindow(d, win, 15, 120, 141, 11, 1, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &at);
//at.background_pixel=BlackPixel(d, sn);
at.background_pixel=((unsigned long)((1-volume)*0xff00)&0xff00)|((unsigned long)(volume*0xff0000)&0xff0000);
at.event_mask=ButtonPressMask|ButtonReleaseMask|Button1MotionMask;
valuemask=CWBackPixel|CWBorderPixel|CWEventMask;
fill=XCreateWindow(d, bar, 0, 0, 14, 11, 0, DefaultDepth(d, sn), InputOutput, DefaultVisual(d, sn), valuemask, &at);


XMapWindow(d, win);
XMapWindow(d, text);
XMapWindow(d, bar);
XMapWindow(d, fill);
for(int i=0;i<WK;i++)
XMapWindow(d, white[i]);
for(int i=0;i<BK;i++)
XMapWindow(d, black[i]);
for(int i=0;i<BC;i++)
XMapWindow(d, btns[i]);
}

void xclose(){
XUnmapWindow(d, win);
XDestroyWindow(d, win);
XCloseDisplay(d);
}
