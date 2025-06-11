#include <cstdlib>
#include <cstdio>

double predictDelay(double dist, int hour) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "python3 ml/predict.py %.2f %d > ml/output.txt", dist, hour);
    system(cmd);

    FILE* f = fopen("ml/output.txt", "r");
    if (!f) return dist * 1.5;  // fallback
    double delay;
    fscanf(f, "%lf", &delay);
    fclose(f);
    return delay;
}

