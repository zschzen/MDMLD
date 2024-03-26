#include "mdmld/mld.h"

#include <stdio.h>
#include <stdlib.h>

const char *DATA_TYPE[TYPES_COUNT] =
{
    "UINT8",
    "UINT32",
    "INT32",
    "CHAR",
    "OBJ_PTR",
    "FLOAT",
    "DOUBLE",
    "OBJ_STRUCT"
};

void
print_structure_rec(struct_db_rec_t *rec)
{
    if(!rec) return;

    printf("+------------------------------------------------------+\n");
    printf("| %-20s | size = %-8d | #flds = %-3d |\n", rec->struct_name, rec->ds_size, rec->n_fields);
    printf("+------------------------------------------------------+------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < rec->n_fields; i++)
    {

        field_info_t *field = &rec->pFields[i];
        printf("  %-20s |", " ");
        printf("%-3d %-20s | dtype = %-15s | size = %-5d | offset = %-6d|  nstructname = %-20s  |\n",
                i, field->fname, DATA_TYPE[field->dtype], field->size, field->offset, field->nested_str_name);
        printf("  %-20s |", "");
        printf("--------------------------------------------------------------------------------------------------------------------------|\n");
    }
}

void
print_structure_db(struct_db_t *db)
{   
    if(!db) return;
 
    int i = 0;
    for (struct_db_rec_t *rec = db->pHead; rec != NULL; rec = rec->pNext)
    {
        printf("structure No: %d (%p)\n", i++, rec);
        print_structure_rec(rec);
    }
}


int
add_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec)
{
    struct_db_rec_t *head = struct_db->pHead;
    if(!head)
    {
        struct_db->pHead = struct_rec;
        struct_rec->pNext = NULL;
        struct_db->count++;
        return 0;
    }

    struct_rec->pNext = head;
    struct_db->pHead = struct_rec;
    struct_db->count++;
    return 0;
}
