void xevl(){
Atom wm_delete_window;
Window ntrdwin, ulwin;
char c;
short f;
int useless;
char hertz[12];
int slv=14;
char pk=0;

sprintf(hertz, "%d Hz", sss);

xinit();

wm_delete_window = XInternAtom(d, "WM_DELETE_WINDOW", False);
XSetWMProtocols(d, win, &wm_delete_window, 1);

while(!done){
XNextEvent(d, &xev);
switch(xev.type){
case Expose:
	if(xev.xexpose.window==text)
	XDrawImageString(d, text, gc2, 5, 15, hertz, strlen(hertz));

	for(int i=0;i<BC;i++)
	if(xev.xexpose.window==btns[i]) XDrawImageString(d, btns[i], gc, 5, 15, bl[i], strlen(bl[i]));
	break;
case ButtonPress:
	if(xev.xbutton.button==Button1){
		if(xev.xbutton.window==btns[0]){
			playing=1;
			pthread_cond_signal(&playingcond);
		}else if(xev.xbutton.window==btns[1]){
			playing=0;
		}else if(xev.xbutton.window==btns[2]){
			done=1;
			pthread_cond_signal(&playingcond);
		}else if(xev.xbutton.window==btns[3]){
			sss-=100;
		}else if(xev.xbutton.window==btns[4]){
			sss-=10;
		}else if(xev.xbutton.window==btns[5]){
			sss-=1;
		}else if(xev.xbutton.window==btns[6]){
			sss+=1;
		}else if(xev.xbutton.window==btns[7]){
			sss+=10;
		}else if(xev.xbutton.window==btns[8]){
			sss+=100;
		}else if(xev.xbutton.window==btns[9]){
			sss/=10;
		}else if(xev.xbutton.window==btns[10]){
			sss/=2;
		}else if(xev.xbutton.window==btns[11]){
			sss-=1000;
		}else if(xev.xbutton.window==btns[12]){
			sss+=1000;
		}else if(xev.xbutton.window==btns[13]){
			sss*=2;
		}else if(xev.xbutton.window==btns[14]){
			sss*=10;
		}else if(xev.xbutton.window==btns[15]){
			wave=0;
		}else if(xev.xbutton.window==btns[16]){
			wave=1;
		}else if(xev.xbutton.window==btns[17]){
			wave=2;
		}else if(xev.xbutton.window==btns[18]){
			wave=3;
		}else if(xev.xbutton.window==fill || xev.xbutton.window==bar){
			if(xev.xbutton.x<=141 && xev.xbutton.x>0) slv=xev.xbutton.x;
			volume=(slv-1)/140.0;
			mval=MVAL*volume;
			XSetWindowBackground(d, fill, ((unsigned long)((1-volume)*0xff00)&0xff00)|((unsigned long)(volume*0xff0000)&0xff0000));
			XResizeWindow(d, fill, xev.xbutton.x, 11);
		}else{
			for(int i=0;i<WK;i++) if(xev.xbutton.window==white[i]){
			sss=wf[i];
			playing=1;
			pthread_cond_signal(&playingcond);
			pk=1;
			break;
			}
			for(int i=0;i<BK;i++) if(xev.xbutton.window==black[i]){
			sss=bf[i];
			playing=1;
			pthread_cond_signal(&playingcond);
			pk=1;
			break;
			}
		}


		if(sss>22000) sss=22000; else if(sss<1) sss=1;
		sprintf(hertz, "%d Hz", sss);
		XClearWindow(d, text);
		XDrawImageString(d, text, gc2, 5, 15, hertz, strlen(hertz));
	}else if(xev.xbutton.button==Button4){
		if(xev.xbutton.window==fill || xev.xbutton.window==bar){
		if(slv+10<=141) slv+=10; else slv=141;
		volume=(slv-1)/140.0;
		mval=MVAL*volume;
		XSetWindowBackground(d, fill, ((unsigned long)((1-volume)*0xff00)&0xff00)|((unsigned long)(volume*0xff0000)&0xff0000));
		XResizeWindow(d, fill, slv, 11);
		}
	}else if(xev.xbutton.button==Button5){
		if(xev.xbutton.window==fill || xev.xbutton.window==bar){
		if(slv-10>0) slv-=10; else slv=1;
		volume=(slv-1)/140.0;
		mval=MVAL*volume;
		XSetWindowBackground(d, fill, ((unsigned long)((1-volume)*0xff00)&0xff00)|((unsigned long)(volume*0xff0000)&0xff0000));
		XResizeWindow(d, fill, slv, 11);
		}
	}
	break;
case ButtonRelease:
	for(int i=0;i<WK;i++) if(xev.xbutton.window==white[i]) playing=0, pk=0;
	for(int i=0;i<BK;i++) if(xev.xbutton.window==black[i]) playing=0, pk=0;
	break;
case ClientMessage:
	if (xev.xclient.data.l[0] == wm_delete_window) {
		done=1;
		pthread_cond_signal(&playingcond);
	}
	break;
case KeyPress:
	XLookupString(&xev.xkey, &c, 1, NULL, NULL);
	//printf("character: %c\n", c);
	f=0;
	switch(c){
	case 'q': f=wf[0]; break;
	case 'w': f=wf[1]; break;
	case 'e': f=wf[2]; break;
	case 'r': f=wf[3]; break;
	case 't': f=wf[4]; break;
	case 'a': f=wf[5]; break;
	case 's': f=wf[6]; break;
	case 'd': f=wf[7]; break;
	case 'f': f=wf[8]; break;
	case 'g': f=wf[9]; break;
	case 'y': f=wf[10]; break;
	case 'u': f=wf[11]; break;
	case 'i': f=wf[12]; break;
	case 'o': f=wf[13]; break;
	case 'p': f=wf[14]; break;
	case 'j': f=wf[15]; break;
	case 'k': f=wf[16]; break;
	case 'l': f=wf[17]; break;
	case ';': f=wf[18]; break;

	case '`': f=bf[0]; break;
	case '0': f=bf[10]; break;
	case '-': f=bf[11]; break;
	case '=': f=bf[12]; break;
	default:
	for(int i=1;i<=9;i++) if(c=='0'+i) f=bf[i];
	}
	if(f!=0){
		sss=f;
		if(sss>22000) sss=22000; else if(sss<1) sss=1;
		sprintf(hertz, "%d Hz", sss);
		XClearWindow(d, text);
		XDrawImageString(d, text, gc2, 5, 15, hertz, strlen(hertz));
		playing=1;
		pthread_cond_signal(&playingcond);
		pk=1;
	}
	break;
case KeyRelease:
	playing=0, pk=0;
	break;
case MotionNotify:
	if(xev.xmotion.window==fill || xev.xmotion.window==bar){
		if(xev.xmotion.x<=141 && xev.xmotion.x>0) slv=xev.xmotion.x;
		volume=(slv-1)/140.0;
		mval=MVAL*volume;
		XSetWindowBackground(d, fill, ((unsigned long)((1-volume)*0xff00)&0xff00)|((unsigned long)(volume*0xff0000)&0xff0000));
		XResizeWindow(d, fill, slv, 11);
		break;
	}else{
		XQueryPointer(d, win, &ulwin, &ntrdwin, &useless, &useless, &useless, &useless, &useless);
		for(int i=0;i<WK;i++) if(ntrdwin==white[i]){
			sss=wf[i];
			if(sss>22000) sss=22000; else if(sss<1) sss=1;
			sprintf(hertz, "%d Hz", sss);
			XClearWindow(d, text);
			XDrawImageString(d, text, gc2, 5, 15, hertz, strlen(hertz));
			break;
		}
		for(int i=0;i<BK;i++) if(ntrdwin==black[i]){
			sss=bf[i];
			if(sss>22000) sss=22000; else if(sss<1) sss=1;
			sprintf(hertz, "%d Hz", sss);
			XClearWindow(d, text);
			XDrawImageString(d, text, gc2, 5, 15, hertz, strlen(hertz));
			break;
		}
	}
	break;
}
}
xclose();
}
