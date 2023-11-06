#include "../inc/min_cut.h"

MC_V *mc_v_create(int id) {
    MC_V *v = malloc(sizeof(MC_V));
    v->id = id;
    v->incident_edges = mc_e_list_create();
    v->contracted_vs = mc_v_list_create();
    return v;
}

void mc_v_self_connections_remove(MC_V *v, MC_EList *e_list) {
    // Remove self connections on v
    CS_SListItem *item = v->incident_edges->head;
    for (size_t i = 0; i < v->incident_edges->length; i++) {
        MC_E *incident_edge = item->data;
        // if incident edge has 2 equal edges (self connection/loop)
        if (incident_edge->v1 == incident_edge->v2) {
            mc_e_list_remove(v->incident_edges, incident_edge);
            if (e_list != NULL) {
                // mc_e_list_remove(e_list, )
            }
        }
    }
}

MC_VList *mc_v_list_create() {
    CS_SList *list = c_structures_s_list_create();
    return list;
}

void mc_v_list_append(MC_VList *v_list, MC_V *v) {
    c_structures_s_list_append(v_list, v);
}

int mc_v_list_internal_compare(void *data1, void *data2) {
    MC_V *v1 = data1;
    MC_V *v2 = data2;
    if (v1 == v2) {
        return 1;
    }
    return 0;
}

void mc_v_list_remove(MC_VList *v_list, MC_V *v) {
    int index =
        c_structures_s_list_index_of(v_list, v, mc_v_list_internal_compare);
    c_structures_s_list_remove(v_list, index);
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
