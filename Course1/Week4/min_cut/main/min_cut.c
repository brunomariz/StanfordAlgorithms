#include "../inc/min_cut.h"

MC_G *create_g() {
    MC_G *g = mc_g_create();

    mc_g_add_v(g, mc_v_create(1));
    mc_g_add_v(g, mc_v_create(2));
    mc_g_add_v(g, mc_v_create(3));
    mc_g_add_v(g, mc_v_create(4));
    mc_g_add_v(g, mc_v_create(5));
    mc_g_add_v(g, mc_v_create(6));
    mc_g_add_v(g, mc_v_create(7));
    mc_g_add_v(g, mc_v_create(8));
    mc_g_create_e(g, 1, 2);
    mc_g_create_e(g, 2, 3);
    mc_g_create_e(g, 3, 4);
    mc_g_create_e(g, 4, 5);
    mc_g_create_e(g, 5, 6);
    mc_g_create_e(g, 6, 7);
    mc_g_create_e(g, 7, 8);
    mc_g_create_e(g, 8, 1);
    mc_g_create_e(g, 1, 7);
    mc_g_create_e(g, 2, 8);
    mc_g_create_e(g, 2, 7);
    mc_g_create_e(g, 3, 6);
    mc_g_create_e(g, 3, 5);
    mc_g_create_e(g, 4, 6);
    return g;
}

MC_G *read_g(const char *filename) {
    MC_G *g = mc_g_create();

    // Read input file
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    // Create vertices
    fp = fopen(filename, "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        // Get vertex
        const char s[2] = "\t";
        char *token;
        token = strtok(line, s);
        int v = atoi(token);
        // Create vertex
        mc_g_add_v(g, mc_v_create(v));

        i++;
    }

    // Create edges
    fp = fopen(filename, "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        // Get vertex
        const char s[2] = "\t";
        char *token;
        token = strtok(line, s);
        int v = atoi(token);

        // Create edges
        token = strtok(NULL, s);
        while (token != NULL) {
            int adjacent_v = atoi(token);
            if ((adjacent_v != 0) && (adjacent_v > v)) {
                mc_g_create_e(g, v, adjacent_v);
            }
            token = strtok(NULL, s);
        }
        i++;
    }

    fclose(fp);
    if (line) free(line);

    return g;
}

int main() {
    MC_G *g = read_g("Course1/Week4/min_cut/input.txt");
    printf("==\n");
    mc_g_print(g);

    int smallest = g->e_list->length;
    int n = g->v_list->length;
    int iterations = n * n * log(n);
    for (size_t i = 0; i < iterations; i++) {
        g = read_g("Course1/Week4/min_cut/input.txt");
        while (g->v_list->length > 2) {
            mc_g_contract_by_random_e(g);
        }

        // if (i % (int)(iterations * 0.1) == 0) {
        //     printf("%6lu Min cut: %d\n", i, g->e_list->length);
        // }

        if (smallest > g->e_list->length) {
            smallest = g->e_list->length;
        }
    }
    printf("==\nMin cut: %d\n", smallest);

    // MC_G *g = mc_g_create();

    // mc_g_add_v(g, mc_v_create(1));
    // mc_g_add_v(g, mc_v_create(2));
    // mc_g_add_v(g, mc_v_create(3));
    // mc_g_add_v(g, mc_v_create(4));
    // mc_g_create_e(g, 1, 2);
    // mc_g_create_e(g, 1, 3);
    // mc_g_create_e(g, 2, 3);
    // mc_g_create_e(g, 2, 4);
    // mc_g_create_e(g, 3, 4);
    // printf("==\n");
    // mc_g_print(g);

    // printf("==\n");
    // printf("CONTRACT!\n");
    // mc_g_contract_by_v_ids(g, 1, 3);
    // printf("==\n");
    // mc_g_print(g);
    // printf("==\n");
    // printf("CONTRACT!\n");
    // mc_g_contract_by_v_ids(g, 2, 1);
    // printf("==\n");
    // mc_g_print(g);

    // printf("==\nV count:%d\nMin cut: %d\n", g->v_list->length,
    //    g->e_list->length);

    return 0;
}
