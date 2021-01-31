int rate = 44100; /* Sample rate */
int exact_rate;   /* Sample rate returned by */
                  /* snd_pcm_hw_params_set_rate_near */ 
int dir;          /* exact_rate == rate --> dir = 0 */
	          /* exact_rate < rate  --> dir = -1 */
	          /* exact_rate > rate  --> dir = 1 */
int periods = 2;       /* Number of periods */
snd_pcm_uframes_t periodsize = 8192; /* Periodsize (bytes) */
snd_pcm_t *pcm_handle;
snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;
snd_pcm_hw_params_t *hwparams;
char *pcm_name;
