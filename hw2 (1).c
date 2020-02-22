//Gannon Traynor

void add_index(int numbers[], int len) {
	int i;
	for(i = 0; i < len; i++){
		numbers[i] += i;
	}

}

void min_and_max(int scores[], int len, int *minptr, int *maxptr) {
	int i;
	*minptr = scores[0];
	*maxptr = scores[0];
	for(i = 0; i < len; i++){
		if(*minptr < scores[i]) *minptr = scores[i];
		if(*maxptr > scores[i]) *maxptr = scores[i];
	}
}

void copy_array(int *dest, int* src, int len) {
	int i;
	for(i = 0; i < len; i++){
		dest[i] = src[i];
	}


}

void reverse_array(int x[], int len) {
	int i;
	int j = 0;
	int temp[len + 1]
	for(i = len; i >= 0; i--){
		temp[j] = x[i];
		j++;
	}
	int h;
	for(h = 0; h < len; h++){
		x[h] = temp[h];
	}
}

void convert_temp(int deg, char scale, int *dptr, char *sptr) {
	if( scale == 'C'){
		*dptr = (deg* 1.8) + 32;
		*sptr = 'F'
	}
	else(){
		*dptr = (deg - 32) / 1.8;
		*sptr = 'C';

}

