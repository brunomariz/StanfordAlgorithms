#include "../inc/min_cut.h"

MC_V *mc_v_create(int id) {
    MC_V *v = malloc(sizeof(MC_V));
    v->id = id;
    v->incident_edges = mc_e_list_create();
    return v;
}

MC_VList *mc_v_list_create() {
    CS_SList *list = c_structures_s_list_create();
    return list;
}

void mc_v_list_append(MC_VList *v_list, MC_V *v) {
    c_structures_s_list_append(v_list, v);
}

// Print callback for vertex list
void mc_v_list_print_callback(void *data, int iter) {
    // Custom print function made specifically for My_data
    MC_V *v = (MC_V *)data;
    printf("[vertex %d] id: %d | ", iter, v->id);
    printf("Adjacent vertices: ");
    CS_SListItem *current_item = v->incident_edges->head;
    for (size_t i = 0; i < v->incident_edges->length; i++) {
        MC_E *current_edge = current_item->data;
        if (current_edge->v1 != v) {
            printf("%d ", current_edge->v1->id);
        } else {
            printf("%d ", current_edge->v2->id);
        }
        current_item = current_item->next;
    }

    printf("\n");
}

void mc_v_list_print(MC_VList *v_list) {
    printf("Vertex list:\n");
    c_structures_s_list_print(v_list, mc_v_list_print_callback);
}
