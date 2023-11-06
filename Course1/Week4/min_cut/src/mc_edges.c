#include "../inc/min_cut.h"

MC_E *mc_e_create(MC_V *v1, MC_V *v2) {
    MC_E *e = malloc(sizeof(MC_E));
    e->v1 = v1;
    e->v2 = v2;
    c_structures_s_list_append(e->v1->incident_edges, e);
    c_structures_s_list_append(e->v2->incident_edges, e);
    return e;
}

MC_EList *mc_e_list_create() {
    CS_SList *list = c_structures_s_list_create();
    return list;
}

void mc_e_list_append(MC_EList *e_list, MC_E *e) {
    c_structures_s_list_append(e_list, e);
}

int mc_e_list_internal_compare(void *data1, void *data2) {
    MC_E *e1 = data1;
    MC_E *e2 = data2;
    if (e1 == e2) {
        return 1;
    }
    return 0;
}

void mc_e_list_remove(MC_EList *e_list, MC_E *e) {
    int index =
        c_structures_s_list_index_of(e_list, e, mc_e_list_internal_compare);
    c_structures_s_list_remove(e_list, index);
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
