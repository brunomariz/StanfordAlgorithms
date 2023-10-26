#ifndef _MIN_CUT
#define _MIN_CUT

#include <stdio.h>
#include <stdlib.h>

#include "../../../../c_structures/inc/c_structures.h"

typedef struct mc_v MC_V;
typedef struct mc_e MC_E;

typedef CS_SList MC_EList;
typedef CS_SList MC_VList;

// === Edges ===

// Struct for edge
struct mc_e {
    MC_V *v1;
    MC_V *v2;
};

MC_E *mc_e_create(MC_V *v1, MC_V *v2);
MC_EList *mc_e_list_create();
void mc_e_list_append(MC_EList *e_list, MC_E *e);
// Print callback for edge list
void mc_e_list_print_callback(void *data, int iter);
void mc_e_list_print(MC_VList *v_list);

// === Vertices ===

// Struct for vertex
struct mc_v {
    int id;
    MC_EList *incident_edges;
};

MC_V *mc_v_create(int id);
MC_VList *mc_v_list_create();
void mc_v_list_append(MC_VList *v_list, MC_V *v);
// Print callback for vertex lists
void mc_v_list_print_callback(void *data, int iter);
void mc_v_list_print(MC_VList *v_list);

#endif