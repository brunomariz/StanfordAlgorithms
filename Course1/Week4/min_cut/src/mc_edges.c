#include "../inc/min_cut.h"

MC_E *mc_e_create(MC_V *v1, MC_V *v2) {
    MC_E *e = malloc(sizeof(MC_E));
    e->v1 = v1;
    e->v2 = v2;
    return e;
}

MC_EList *mc_e_list_create() {
    CS_SList *list = c_structures_s_list_create();
    return list;
}

void mc_e_list_append(MC_EList *e_list, MC_E *e) {
    c_structures_s_list_append(e_list, e);
    c_structures_s_list_append(e->v1->incident_edges, e);
    c_structures_s_list_append(e->v2->incident_edges, e);
}

// Print callback for example 1
void mc_e_list_print_callback(void *data, int iter) {
    // Custom print function made specifically for My_data
    MC_E *e = (MC_E *)data;
    printf("[edge %d] v1: %d | v2: %d\n", iter, e->v1->id, e->v2->id);
}

void mc_e_list_print(MC_EList *e_list) {
    printf("Edge list:\n");
    c_structures_s_list_print(e_list, mc_e_list_print_callback);
}