#define MVAL 32000
short mval=MVAL*(13/140.0);
char wave=0;

void saw(){
int f=sss;
unsigned char *data;
int pcmreturn, l1, l2;
static int l3=0;
short s1;
int frames;

int sc=(exact_rate/f);

data = (unsigned char *)malloc(periodsize);
frames = periodsize >> 2;

//s*=exact_rate/(float)frames;

	//for(l1 = 0; l1 < s; l1++) {
	while(playing && wave==0){
		for(l2=0; l2 < frames; l2++, l3++) {
		s1 = ((l3%sc)/(float)sc)*mval*2 - mval;  
		data[4*l2] = (unsigned char)s1;
		data[4*l2+1] = s1 >> 8;
		data[4*l2+2] = (unsigned char)s1;
		data[4*l2+3] = s1 >> 8;
		}
		l3%=2*sc;
		while ((pcmreturn = snd_pcm_writei(pcm_handle, data, frames)) < 0) {
		snd_pcm_prepare(pcm_handle);
		fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
		}
		if(f!=sss) f=sss, sc=(exact_rate/f);
	}
free(data);
}

void sqr(){
int f=sss;
unsigned char *data;
int pcmreturn, l1, l2;
static int l3=0;
short s1;
int frames;

int sc=(exact_rate/f)>>1;

data = (unsigned char *)malloc(periodsize);
frames = periodsize >> 2;

//s*=exact_rate/(float)frames;

	//for(l1 = 0; l1 < s; l1++) {
	while(playing && wave==1){
		for(l2=0; l2 < frames; l2++, l3++) {
		s1 = ((l3/sc)%2)*mval*2 - mval;  
		data[4*l2] = (unsigned char)s1;
		data[4*l2+1] = s1 >> 8;
		data[4*l2+2] = (unsigned char)s1;
		data[4*l2+3] = s1 >> 8;
		}
		l3%=2*sc;
		while ((pcmreturn = snd_pcm_writei(pcm_handle, data, frames)) < 0) {
		snd_pcm_prepare(pcm_handle);
		fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
		}
		if(f!=sss) f=sss, sc=(exact_rate/f);
	}
free(data);
}

void sine(){
int f=sss;
unsigned char *data;
int pcmreturn, l1, l2;
static int l3=0;
short s1;
int frames;

int sc=(exact_rate/f);

data = (unsigned char *)malloc(periodsize);
frames = periodsize >> 2;

//s*=exact_rate/(float)frames;

	//for(l1 = 0; l1 < s; l1++) {
	while(playing && wave==2){
		for(l2=0; l2 < frames; l2++, l3++) {
		s1 = sin(2*M_PI*l3/(float)sc)*mval;  
		data[4*l2] = (unsigned char)s1;
		data[4*l2+1] = s1 >> 8;
		data[4*l2+2] = (unsigned char)s1;
		data[4*l2+3] = s1 >> 8;
		}
		l3%=2*sc;
		while ((pcmreturn = snd_pcm_writei(pcm_handle, data, frames)) < 0) {
		snd_pcm_prepare(pcm_handle);
		fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
		}
		if(f!=sss) f=sss, sc=(exact_rate/f);
	}
free(data);
}

void tri(){
int f=sss;
unsigned char *data;
int pcmreturn, l1, l2;
static int l3=0;
short s1=0;
int frames;

int sc=(exact_rate/f);

data = (unsigned char *)malloc(periodsize);
frames = periodsize >> 2;

//s*=exact_rate/(float)frames;

	//for(l1 = 0; l1 < s; l1++) {
	while(playing && wave==3){
		for(l2=0; l2 < frames; l2++, l3++) {
		s1 = mval*4*(abs((l3 % sc) - sc/2)-sc/4)/sc;
		data[4*l2] = (unsigned char)s1;
		data[4*l2+1] = s1 >> 8;
		data[4*l2+2] = (unsigned char)s1;
		data[4*l2+3] = s1 >> 8;
		}
		l3%=2*sc;
		while ((pcmreturn = snd_pcm_writei(pcm_handle, data, frames)) < 0) {
		snd_pcm_prepare(pcm_handle);
		fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
		}
		if(f!=sss) f=sss, sc=(exact_rate/f);
	}
free(data);
}

void plw(){
switch(wave){
case 0: saw(); break;
case 1: sqr(); break;
case 2: sine(); break;
case 3: tri(); break;
}
}
