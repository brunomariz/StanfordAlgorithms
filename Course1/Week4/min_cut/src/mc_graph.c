#include "../inc/min_cut.h"

MC_G *mc_g_create() {
    MC_G *g = malloc(sizeof(MC_G));
    g->e_list = mc_e_list_create();
    g->v_list = mc_v_list_create();
    return g;
}

void mc_g_add_v(MC_G *g, MC_V *v) { mc_v_list_append(g->v_list, v); }

void mc_g_create_e(MC_G *g, int v1_id, int v2_id) {
    // Find v1 and v2 by ids
    MC_V *v1 = mc_g_find_v_by_id(g, v1_id);
    MC_V *v2 = mc_g_find_v_by_id(g, v2_id);
    // Create edge
    MC_E *e = mc_e_create(v1, v2);
    // Add to list
    mc_e_list_append(g->e_list, e);
}

void mc_g_print(MC_G *g) {
    printf("Graph:\n");
    mc_v_list_print(g->v_list);
    mc_e_list_print(g->e_list);
}

int internal_mc_g_compare_ids_callback(void *data1, void *data2) {
    int id1 = *(int *)data1;
    int id2 = *(int *)data2;
    if (id1 == id2) {
        return 1;
    }
    return 0;
}

MC_V *mc_g_find_v_by_id(MC_G *g, int id) {
    CS_SListItem *item = c_structures_s_list_find_item(
        g->v_list, &id, internal_mc_g_compare_ids_callback);

    MC_V *v = item->data;
    return v;
}

void mc_g_contract(MC_G *g, int v1_id, int v2_id) {
    MC_V *v1 = mc_g_find_v_by_id(g, v1_id);
    MC_V *v2 = mc_g_find_v_by_id(g, v2_id);

    // Add v2 to v1's contracted vertices list
    mc_v_list_append(v1->contracted_vs, v2);
    // Remove v2 from graph
    mc_v_list_remove(g->v_list, v2);
    // Replace v2 for v1 for all incident edges on v2
    CS_SListItem *item = v2->incident_edges->head;
    for (size_t i = 0; i < v2->incident_edges->length; i++) {
        MC_E *incident_edge = item->data;
        // Replace v2 for v1 on incident edge
        if (incident_edge->v1 == v2) {
            incident_edge->v1 = v1;
        } else {
            incident_edge->v2 = v1;
        }
        item = item->next;
    }
    // Remove self connections
    mc_v_self_connections_remove(v1);
}
