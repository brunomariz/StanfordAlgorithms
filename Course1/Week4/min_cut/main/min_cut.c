#include "../inc/min_cut.h"

int main() {
    MC_V *v1 = mc_v_create(1);
    MC_V *v2 = mc_v_create(2);
    MC_V *v3 = mc_v_create(3);
    MC_V *v4 = mc_v_create(4);
    MC_VList *v_list = mc_v_list_create();
    mc_v_list_append(v_list, v1);
    mc_v_list_append(v_list, v2);
    mc_v_list_append(v_list, v3);
    mc_v_list_append(v_list, v4);

    MC_E *e1 = mc_e_create(v1, v2);
    MC_E *e2 = mc_e_create(v1, v3);
    MC_E *e3 = mc_e_create(v2, v3);
    MC_E *e4 = mc_e_create(v2, v4);
    MC_E *e5 = mc_e_create(v3, v4);
    MC_EList *e_list = mc_e_list_create();
    mc_e_list_append(e_list, e1);
    mc_e_list_append(e_list, e2);
    mc_e_list_append(e_list, e3);
    mc_e_list_append(e_list, e4);
    mc_e_list_append(e_list, e5);

    mc_v_list_print(v_list);
    mc_e_list_print(e_list);

    return 0;
}

// Create contraction algorithm