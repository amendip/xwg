#include <alsa/asoundlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <pthread.h>
#include <math.h>

char playing=0;
float volume=13/140.0;
int sss=200;
pthread_cond_t playingcond = PTHREAD_COND_INITIALIZER;  
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 

#include "vars.c"
#include "mis.c"
#include "play.c"
#include "xmis.c"
#include "xevl.c"


void *alsa(void *arg){
char p2=0;
ainit();
pthread_mutex_lock(&lock);
while(!done) {
	if(playing){
		if(!p2) snd_pcm_prepare(pcm_handle);
		plw();
		p2=1;
	}else{
		if(p2) snd_pcm_drain(pcm_handle);
		p2=0;
		pthread_cond_wait(&playingcond, &lock);
	}
}
pthread_mutex_unlock(&lock);
adie();
}

void *x(void *arg){
xevl();
}

int main(){
pthread_t snd, gfx;

pthread_create(&snd, NULL, alsa, NULL);
pthread_create(&gfx, NULL, x, NULL);
pthread_join(snd, NULL);
pthread_join(gfx, NULL);

return 0;
}
