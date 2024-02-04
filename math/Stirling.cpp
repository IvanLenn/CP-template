int stg[2010][2010]; //may change type to Mint

void stg_init() {
    stg[0][0] = 1;
    for (int i = 1; i <= 2000; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) stg[i][j] = 0;
            else if (j == i) stg[i][j] = 1;
            else stg[i][j] = stg[i - 1][j - 1] + j * stg[i - 1][j];
        }
    }
}
