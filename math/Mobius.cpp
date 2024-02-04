int N = 100010;
vl primechk(N), mu;
void init() {
    primechk[1] = 0;
    for (int i = 2; i <= N - 1 ; i++) {
        if (primechk[i] == 1) {
            mu[i] = -mu[i];
            for (int j=2 ; i * j <= N - 1; j++) {
                primechk[i * j]=0;
                if (j % i == 0) mu[i * j] = 0;
                else mu[i * j]= -mu[i * j];
            }
        }
    }
}
