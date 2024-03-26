#include "mdmld/mld.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    printf("Structure database\n");

    int i = 0;
    for (struct_db_rec_t *rec = db->pHead; rec != NULL; rec = rec->pNext)
    {
        printf("structure No: %d (%p)\n", i++, rec);
        print_structure_rec(rec);
    }
}

void
print_object_rec(object_db_rec_t *obj_rec, int i)
{
    if(!obj_rec) return;
 
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    printf("| %-3d ptr = %-10p | next = %-14p | units = %-4d | struct_name = %-19s |\n", 
        i, obj_rec->ptr, obj_rec->pNext, obj_rec->units, obj_rec->pRec->struct_name); 
    printf("+-----------------------------------------------------------------------------------------------------+\n");
}

void
print_object_db(object_db_t *object_db)
{
    printf("Object database\n");

    unsigned int i = 0;
    object_db_rec_t *head = object_db->pHead;
    for(; head; head = head->pNext)
    {
        print_object_rec(head, i++);
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

static object_db_rec_t *
object_db_look_up(object_db_t *object_db, void *ptr)
{
    object_db_rec_t *head = object_db->pHead;
    if(!head) return NULL;

    for(; head; head = head->pNext)
    {
        if(head->ptr == ptr)
            return head;
    }
    return NULL;
}

static struct_db_rec_t *
struct_db_look_up(struct_db_t *struct_db, char *struct_name)
{    
    struct_db_rec_t *head = struct_db->pHead;
    if(!head) return NULL;
 
    for(; head; head = head->pNext)
    {
        if(strncmp(head->struct_name, struct_name, MAX_STRUCTURE_NAME_SIZE) == 0)
            return head;
    }
    return NULL;
}


static void
add_to_object_db(object_db_t *object_db, void *ptr, int units, struct_db_rec_t *struct_rec)
{
    // Check if the object is already registered
    object_db_rec_t *obj_rec = object_db_look_up(object_db, ptr);
    assert(!obj_rec);

    // Allocate memory for the object record
    obj_rec = calloc(1, sizeof(object_db_rec_t));

    obj_rec->pNext = NULL;
    obj_rec->ptr   = ptr;
    obj_rec->units = units;
    obj_rec->pRec  = struct_rec;

    // Add to object database
    object_db_rec_t *head = object_db->pHead;    
    if(!head)
    {
        object_db->pHead = obj_rec;
        obj_rec->pNext   = NULL;
        ++object_db->count;
        return;
    }

    obj_rec->pNext   = head;
    object_db->pHead = obj_rec;
    ++object_db->count;
}


void *
xcalloc(object_db_t *object_db, char *struct_name, int units)
{
    // Check if the structure is already registered
    struct_db_rec_t *struct_rec = struct_db_look_up(object_db->pDB, struct_name);
    assert(struct_rec);

    // Allocate memory and add to object database
    void *ptr = calloc(units, struct_rec->ds_size);
    add_to_object_db(object_db, ptr, units, struct_rec);
    return ptr;
}
