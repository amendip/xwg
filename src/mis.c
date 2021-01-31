int ainit(){
pcm_name = strdup("plughw:0,0");
snd_pcm_hw_params_alloca(&hwparams);
if (snd_pcm_open(&pcm_handle, pcm_name, stream, 0) < 0) {
	fprintf(stderr, "Error opening PCM device %s\n", pcm_name);
	return 1;
}
if (snd_pcm_hw_params_any(pcm_handle, hwparams) < 0) {
	fprintf(stderr, "Can not configure this PCM device.\n");
	return 1;
}

if (snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
	fprintf(stderr, "Error setting access.\n");
	return 1;
}

/* Set sample format */
if (snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE) < 0) {
	fprintf(stderr, "Error setting format.\n");
	return 1;
}

/* Set sample rate. If the exact rate is not supported */
/* by the hardware, use nearest possible rate.         */ 
exact_rate = rate;
if (snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &exact_rate, 0) < 0) {
	fprintf(stderr, "Error setting rate.\n");
	return 1;
}
if (rate != exact_rate) {
	fprintf(stderr, "The rate %d Hz is not supported by your hardware.\n==> Using %d Hz instead.\n", rate, exact_rate);
}

/* Set number of channels */
if (snd_pcm_hw_params_set_channels(pcm_handle, hwparams, 2) < 0) {
	fprintf(stderr, "Error setting channels.\n");
	return 1;
}

/* Set number of periods. Periods used to be called fragments. */ 
if (snd_pcm_hw_params_set_periods(pcm_handle, hwparams, periods, 0) < 0) {
	fprintf(stderr, "Error setting periods.\n");
	return 1;
}

/* Set buffer size (in frames). The resulting latency is given by */
/* latency = periodsize * periods / (rate * bytes_per_frame)     */
if (snd_pcm_hw_params_set_buffer_size(pcm_handle, hwparams, (periodsize * periods)>>2) < 0) {
	fprintf(stderr, "Error setting buffersize.\n");
	return 1;
}

/* Apply HW parameter settings to */
/* PCM device and prepare device  */
if (snd_pcm_hw_params(pcm_handle, hwparams) < 0) {
	fprintf(stderr, "Error setting HW params.\n");
	return 1;
}

//snd_pcm_writei(pcm_handle, data, num_frames);

//snd_pcm_sframes_t snd_pcm_writen(pcm_handle, data, num_frames);

return 0;
}

void adie(){
/* Stop PCM device and drop pending frames */
snd_pcm_drop(pcm_handle);

/* Stop PCM device after pending frames have been played */ 
//snd_pcm_drain(pcm_handle);
}
